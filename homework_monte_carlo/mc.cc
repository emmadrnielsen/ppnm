#include "mc.h"
#include <random>
#include <cmath>

// Opgave A2:
lcg::lcg(unsigned int seed0,
         unsigned int a0,
         unsigned int c0,
         unsigned int m0)
    : seed(seed0), a(a0), c(c0), m(m0)
{
}

double lcg::operator()()
{
    seed = (a*seed + c) % m;
    return static_cast<double>(seed + 1.0) / static_cast<double>(m + 1.0);
}


// Opgave A1:
std::tuple<double,double> plainmc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    std::function<double()> random_double
    // I use random double because it does not
    // matter which generator the random number
    // comes from. 
)
{
    int dim = a.size(); // samme som i opgaven bare i c++ sprog

    double V = 1.0; // samme som i opgaven
    for(int i = 0; i < dim; i++){
        V *= b[i] - a[i];
    } // samme som i opgaven

    double sum = 0.0; // samme somm i opgaven
    double sum2 = 0.0;

    // This line creates a vector called x with dim entries:
    std::vector<double> x(dim); 

    for(int i = 0; i < N; i++){
        for(int k = 0; k < dim; k++){ // i stedet for list 
            // comprehension bruger vi et forloop. - foreslag fra
            // chatgpt. 
            double r = random_double();
            x[k] = a[k] + r*(b[k] - a[k]);
            // this line converts a random number between 0 and 1
            // to a random number between ak and bk
        }

        double fx = f(x);

        sum += fx;
        sum2 += fx*fx; // samme som i opgaven
    }

    double mean = sum/N; // samme som i opgaven
    double sigma = std::sqrt(sum2/N - mean*mean);

    double result = mean*V; // samme som i opgaven
    double error = sigma*V/std::sqrt(N);

    return std::make_tuple(result, error);
}

// Opgave B1:
double corput(int n, int base) // ligesom i lecture notes
{
    double q = 0.0; // ligesom i notes
    double bk = 1.0/base; // ~notes

    while(n > 0){ // ~notes
        q += (n % base)*bk;
        n /= base;
        bk /= base;
    } // præcis ligesom i notes

    return q;
}

std::vector<int> prime_numbers(int n) // like notes
{
    std::vector<int> primes; // laver en tom vektor ligesom i notes
    int candidate = 2; // ~notes

    while((int)primes.size() < n){ //~notes
        bool is_prime = true; // ~notes

        for(int p : primes){ // ~notes
            if(p*p > candidate) break;
            if(candidate % p == 0){
                is_prime = false;
                break;
            }
        }

        if(is_prime) primes.push_back(candidate);

        candidate++;
    }

    return primes;
} // præcis ligesom i lecture notes

// også fra lecture notes:
std::vector<double> halton(int n, int dim)
{
    std::vector<int> bases = prime_numbers(dim);
    std::vector<double> x(dim); // vektor x med længde dim

    for(int i = 0; i < dim; i++){ // samme som i lecture notes bare med for-loop i stedet for list comprehension
        x[i] = corput(n, bases[i]);
    }

    return x;
}


// This is the quasi-random integrator and it
// works similarly to plainmc except it uses
// halton points. 
std::tuple<double,double> quasimc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N
)
{
    int dim = a.size();

    // first we calculate the volume like in plainmc
    double V = 1.0;
    for(int i = 0; i < dim; i++){
        V *= b[i] - a[i];
    }

    double sum1 = 0.0;
    double sum2 = 0.0;

    std::vector<double> x(dim);

    for(int i = 1; i <= N; i++){
        // computes two separate estimates:
        std::vector<double> u1 = halton(i, dim); // halton points
        std::vector<double> u2 = halton(i + N, dim); // shifted halton points
                                                     // second sequence estimate

        // map the points from unit cube to integration interval:
        for(int k = 0; k < dim; k++){
            x[k] = a[k] + u1[k]*(b[k] - a[k]);
        }
        sum1 += f(x);

        for(int k = 0; k < dim; k++){
            x[k] = a[k] + u2[k]*(b[k] - a[k]);
        }
        sum2 += f(x);
    }

    double result1 = V*sum1/N;
    double result2 = V*sum2/N;

    // the final result is the average of the two estimates
    double result = 0.5*(result1 + result2);
    double error = std::abs(result1 - result2);

    return std::make_tuple(result, error);
}



// Opgave C:

// If N < nmin:
//     return plain Monte Carlo

// Sample nmin points:
//     estimate left/right sub-variances for each dimension

// Find the dimension with largest sub-variance:
//     split_dim

// Subdivide the volume along split_dim:
//     left box and right box

// Divide remaining points proportional to sub-variances:
//     actually proportional to sigma = sqrt(variance), because error depends on sigma/sqrt(N)

// Dispatch two recursive calls:
//     stratifiedmc(left)
//     stratifiedmc(right)

// Estimate grand integral and error:
//     I_left + I_right
//     sqrt(err_left^2 + err_right^2)


std::tuple<double,double> stratifiedmc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    std::function<double()> random_double,
    int nmin
)
{
    int dim = a.size();

    if(N <= 2*nmin){
        return plainmc(f, a, b, N, random_double);
    }
    // the 2 is there so that later when we want to
    // split the remaining points between left and right
    // there is always going to be at least one point
    // for both left and right. This is to prevent
    // plainmc breaking because it divides by 0. 

    std::vector<double> x(dim);

    std::vector<double> sum_left(dim, 0.0);
    std::vector<double> sum_right(dim, 0.0);
    std::vector<double> sum2_left(dim, 0.0);
    std::vector<double> sum2_right(dim, 0.0);

    std::vector<int> n_left(dim, 0);
    std::vector<int> n_right(dim, 0);

    // Sample nmin points and collect statistics for possible splits
    for(int i = 0; i < nmin; i++){
        for(int k = 0; k < dim; k++){
            x[k] = a[k] + random_double()*(b[k] - a[k]);
        }

        double fx = f(x);

        for(int k = 0; k < dim; k++){
            double mid = 0.5*(a[k] + b[k]);

            if(x[k] < mid){
                n_left[k]++;
                sum_left[k] += fx;
                sum2_left[k] += fx*fx;
            }
            else{
                n_right[k]++;
                sum_right[k] += fx;
                sum2_right[k] += fx*fx;
            }
        }
    }

    // Find dimension with largest combined sub-variance
    int split_dim = 0;
    double max_subvariance = -1.0;

    std::vector<double> var_left(dim, 0.0);
    std::vector<double> var_right(dim, 0.0);

    for(int k = 0; k < dim; k++){
        if(n_left[k] > 1){
            double mean_left = sum_left[k]/n_left[k];
            var_left[k] = sum2_left[k]/n_left[k] - mean_left*mean_left;
            if(var_left[k] < 0) var_left[k] = 0;
        }

        if(n_right[k] > 1){
            double mean_right = sum_right[k]/n_right[k];
            var_right[k] = sum2_right[k]/n_right[k] - mean_right*mean_right;
            if(var_right[k] < 0) var_right[k] = 0;
        }

        double combined = var_left[k] + var_right[k];

        if(combined > max_subvariance){
            max_subvariance = combined;
            split_dim = k;
        }
    }

    // Create left and right sub-volumes
    std::vector<double> a_left = a;
    std::vector<double> b_left = b;
    std::vector<double> a_right = a;
    std::vector<double> b_right = b;

    double mid = 0.5*(a[split_dim] + b[split_dim]);

    b_left[split_dim] = mid;
    a_right[split_dim] = mid;

    // Divide remaining points proportional to sub-standard deviations
    int remaining = N - nmin;

    // The assignment says to divide points proportional
    // to sub-variances, so we use var_left and var_right
    // directly
    double weight_left = var_left[split_dim];
    double weight_right = var_right[split_dim];

    int N_left;
    int N_right;

    if(weight_left + weight_right > 0.0){
        N_left = static_cast<int>(
            remaining*weight_left/(weight_left + weight_right)
        );
    }
    else{
        N_left = remaining/2;
    }

    N_right = remaining - N_left;

    // Avoid putting all points in one side
    if(N_left < 1){
        N_left = 1;
        N_right = remaining - 1;
    }

    if(N_right < 1){
        N_right = 1;
        N_left = remaining - 1;
    }

    auto [I_left, err_left] = stratifiedmc(
        f,
        a_left,
        b_left,
        N_left,
        random_double,
        nmin
    );

    auto [I_right, err_right] = stratifiedmc(
        f,
        a_right,
        b_right,
        N_right,
        random_double,
        nmin
    );

    double I_total = I_left + I_right;
    double err_total = std::sqrt(err_left*err_left + err_right*err_right);

    return std::make_tuple(I_total, err_total);
}