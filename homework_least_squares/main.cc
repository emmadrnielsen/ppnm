#include "linalg.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdlib>
#include <random>
#include <cmath>
#include <fstream>
#include <vector>
#include <functional>

bool approx(double a, double b, double eps = 1e-10) {
    return std::abs(a - b) < eps;
}

bool approx_equal(const pp::matrix& A, const pp::matrix& B, double eps = 1e-9){ // har ændret eps til 1e-9 for at testen virker
    if (A.rows() != B.rows() || A.cols() != B.cols()) return false;

    for (std::size_t i = 0; i < A.rows(); ++i) {
        for (std::size_t j = 0; j < A.cols(); ++j) {
            if (!approx(A(i,j), B(i,j), eps)) return false;
        }
    }
    return true;
}

bool approx_equal(const pp::vector& a, const pp::vector& b, double eps = 1e-10) {
    if (a.size() != b.size()) return false;

    for (std::size_t i = 0; i < a.size(); ++i) {
        if (std::abs(a[i] - b[i]) > eps)
            return false;
    }
    return true;
}

bool is_upper_triangular(const pp::matrix& R, double eps = 1e-10){
    for (std::size_t i = 0; i < R.rows(); ++i) {
        for (std::size_t j = 0; j < R.cols(); ++j) {
            if (i > j && std::abs(R(i,j)) > eps) return false;
        }
    }
    return true;
}

pp::matrix identity(std::size_t n) {
    pp::matrix I(n, n, 0.0);
    for (std::size_t i = 0; i < n; ++i) I(i,i) = 1.0;
    return I;
}

pp::matrix random_matrix(std::size_t rows, std::size_t cols) {
    pp::matrix A(rows, cols, 0.0);

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            A(i,j) = dist(gen);
        }
    }
    return A;
}

pp::vector random_vector(std::size_t n) {
    pp::vector b(n, 0.0);
    std::mt19937 gen(123);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (std::size_t i = 0; i < n; ++i)
        b[i] = dist(gen);

    return b;
}


int main() {

    // Task A1: Tester QR_decomp for tall matrix
    std::cout << "Task A1: Tests QR_decomp for tall matrix:\n\n";
    std::size_t n = 6;
    std::size_t m = 3;

    pp::matrix A = random_matrix(n, m);

    pp::qr decomp(A);

    auto Q = decomp.Q;
    auto R = decomp.R;

    std::cout << "R upper triangular: "
            << (is_upper_triangular(R) ? "PASS" : "FAIL") << "\n";
    
    pp::matrix QtQ = Q.transpose() * Q;
    pp::matrix I = identity(m);

    std::cout << "Q^T Q = I: "
            << (approx_equal(QtQ, I) ? "PASS" : "FAIL") << "\n";

    pp::matrix QR = Q * R;

    std::cout << "Q R = A: "
            << (approx_equal(QR, A) ? "PASS" : "FAIL") << "\n\n\n";

    

    // Task A2: Routine that makes least squares fit
    std::cout << "Task A2: Makes least-squares fit:\n\n";

    // First we need to define the data to fit

    // Decide the number of data points:
    std::cout << "The number of data points is set to 10\n\n";
    int N = 10;

    // The data set is a vector {xi, yi, dyi}
    pp::vector xi(N), yi(N), dyi(N);

    // For simple test we have the points lie on a straight line
    // Model: y = 2 + 3x + x^2
    std::cout << "The points lie on a straight line y = 2 + 3x + x^2\n\n";
    for (int i = 0; i < N; i++) {
        xi[i] = i;
        yi[i] = 2.0 + 3.0 * xi[i] + xi[i]*xi[i];
        dyi[i] = 1.0;

        // If we want to add small noise to the data we can write
        // yi[i] = 2.0 + 3.0 * xi[i] + xi[i]*xi[i] + 0.05 * std::cos(i);
    }

    // Then we need to define the set of functions fk

    // The set of functions fk is also a vector and it consists of functions:
    std::cout << "The set of functions fk is 1, x, and x^2\n\n";
    std::vector<std::function<double(double)>> fk = {
        [](double){return 1.0;},
        [](double x){return x;},
        [](double x){return x*x;}
    };

    // Now we run it through the lsfit routine
    // pp::vector c = pp::lsfit(fk, xi, yi, dyi); // Hører til opgave A2

    auto [c, Cov] = pp::lsfit(fk, xi, yi, dyi); // Hører til opgave B1

    std::cout << "Returns the vector of the best fit coefficients:\n\n";
    std::cout << "lsfit test: \n";
    std::cout << "c0 = " << c[0] << "\n";
    std::cout << "c1 = " << c[1] << "\n";
    std::cout << "c2 = " << c[2] << "\n\n\n";



    // Task A3: Investigate decay data
    std::cout << "Task A3: Investigate radioactive decay\n\n";

    // The data set:
    pp::vector t{1, 2, 3, 4, 6, 9, 10, 13, 15};
    pp::vector y{117, 100, 88, 72, 53, 29.5, 25.5, 15.2, 11.1};
    pp::vector dy{6, 5, 4, 4, 4, 3, 3, 2, 2};

    // Størrelse af datasæt:
    std::size_t n3 = t.size();

    // For lsfit to work we need the fit function to be
    // a linear combination. So instead of y = a*e^(-l*t),
    // we write ln(y) = ln(a) - l*t
    // So we need to take ln to all the y values

    pp::vector Y(n3), dY(n3);
    for (std::size_t i = 0; i < n3; ++i){
        Y[i] = std::log(y[i]);
        dY[i] = dy[i]/y[i];
    }

    // The function is thus of the shape: f = c0 + c1*t
    std::vector<std::function<double(double)>> fs = {
        [](double ){return 1.0;},
        [](double x){return x;}
    };

    // Fit transformed data:
    // pp::vector c3 = pp::lsfit(fs, t, Y, dY); // Hører til opgave A3
    
    auto [c3, Cov3] = pp::lsfit(fs, t, Y, dY); // Hører til opgave B1

    std::cout<<"Fit of ln(y) = ln(a) - lambda*t \n";
    std::cout<<"c0 = ln(a) = " << c3[0] << "\n";
    std::cout<<"c1 = -lambda = " << c3[1] << "\n";
    std::cout<<"a = exp(c[0]) = " << std::exp(c3[0]) << "\n";
    std::cout<<"lambda = -c[1] = " << -c3[1] << "\n\n\n";

    // Task A4: plot
    std::cout << "Task A4: plot experimental data and best fit\n\n";

    // Data for plotting
    std::ofstream datafile("decay_data.txt");
    for (std::size_t i = 0; i < n3; ++i) {
        datafile << t[i] << " " << y[i] << " " << dy[i] << "\n";
    }

    // Write fitted curve
    std::ofstream fitfile("decay_fit.txt");
    for (double x = 0; x <= 16; x += 0.1) {
        double yfit = std::exp(c3[0]) * std::exp(c3[1] * x); 
        fitfile << x << " " << yfit << "\n";
    }

    // Halflife from fit:
    std::cout << "T_1/2 (from fit) = " << std::log(2.0)/(-c3[1]) << " days \n";

    // The modern value:
    std::cout << "T_1/2 (modern value) = 3.632 days" << "\n";
    std::cout << "The plot is plotted with the command gnuplot plot.gp\n\n\n";


    // Opgave B1: uncertainties
    // har lavet pp::vector c3 om til auto [c3, Cov3] længere oppe
    // fordi jeg har lavet lsfit op til en tuple

    // std::cout << "For opgave B printer jeg bare det samme som tidligere men med usikkerheder nu:" << "\n";
    std::cout << "Task B:\n\n";
    std::cout << "For Task B I print the same as earlier but with uncertainties now:" << "\n";

    for (std::size_t i = 0; i < c3.size(); ++i) {
        double dc3 = std::sqrt(Cov3(i,i));
        std::cout << "c[" << i << "] = "
                  << c3[i]
                  << " ± "
                  << dc3 << "\n";
    }

    // Opgave B2: Error propagation for halflife

    // Calculate halflife:
    std::cout << "T_1/2 = " << std::log(2.0)/(-c3[1]) << "\n";

    // Standard error propagation:
    // T_1/2_err = d/dlambda (ln2/lambda) * lambda_err = ln2/lambda**2 * lambda_err
    std::cout << "T_1/2_err = " << std::log(2.0)/((-c3[1])*(-c3[1]))*std::sqrt(Cov3(1, 1)) << "\n";

    // The modern value:
    std::cout << "The modern value is 3.632 days, which is not at all within the uncertainty" << "\n";



    // Opgave C: Quality of uncertainties

    // Uncertainties:
    std::cout << "Task C: best fit. Plot by writing gnuplot uncertaintiesplot.gp\n\n";
    double dc3_0 = std::sqrt(Cov3(0,0));
    double dc3_1 = std::sqrt(Cov3(1,1));

    // Fit:
    std::ofstream bandfile("decay_band.txt");
    for (double xx = 0; xx <= 16; xx += 0.1) {
        double y0 = std::exp(c3[0] + c3[1]*xx); // this is the fit

        double y1 = std::exp((c3[0] + dc3_0) + (c3[1] + dc3_1)*xx); // added uncertainties
        double y2 = std::exp((c3[0] + dc3_0) + (c3[1] - dc3_1)*xx); // add/subtract
        double y3 = std::exp((c3[0] - dc3_0) + (c3[1] + dc3_1)*xx); // subtract/add
        double y4 = std::exp((c3[0] - dc3_0) + (c3[1] - dc3_1)*xx);

        bandfile << xx << " " << y0 << " " << y1 << " " << y2 << " " << y3 << " " << y4 << "\n";
    }



    return 0;
}


