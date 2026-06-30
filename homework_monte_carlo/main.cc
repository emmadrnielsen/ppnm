#include "mc.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>


// opgave A3:
void run_task_A_circle()
{
    auto circle = [](const std::vector<double>& x){
        double r2 = x[0]*x[0] + x[1]*x[1];

        if(r2 <= 1.0) return 1.0;
        else return 0.0;
        // this creates
        // f(x, y) = 
        // 1 if x^2 + y^2 <= 1
        // 0 if x^2 + y^2 > 1.
        // which if integrated over the square 
        // [-1, 1] x [-1, 1], the result should
        // be the area of the circle (π) 
    };

    std::vector<double> a = {-1.0, -1.0};
    std::vector<double> b = { 1.0,  1.0};

    double exact = std::acos(-1.0); // this is just pi

    std::cout << "# N result estimated_error actual_error 1/sqrt(N)\n";
    // tries different values of N
    for(int N = 100; N <= 1000000; N *= 10){
        lcg rng(12345);

        auto random_double = [&rng](){
            return rng();
        };

        auto [result, estimated_error] = plainmc(
            circle,
            a,
            b,
            N,
            random_double
        );

        double actual_error = std::abs(result - exact);

        std::cout << N << " "
                  << result << " "
                  << estimated_error << " "
                  << actual_error << " "
                  << 1.0/std::sqrt(N) << "\n";
    }
}

void run_task_A_ellipsoid()
{
    double ax = 1.0;
    double by = 2.0;
    double cz = 3.0;

    // define the function from the assingment:
    auto ellipsoid = [ax, by, cz](const std::vector<double>& x){
        double value =
            x[0]*x[0]/(ax*ax)
          + x[1]*x[1]/(by*by)
          + x[2]*x[2]/(cz*cz);

        if(value <= 1.0) return 1.0;
        else return 0.0;
        // returns 1 inside ellipsoid and 0 outside
    };

    // this is the integration box
    // and it is [-1, 1] x [-2, 2] x [-3, 3]
    std::vector<double> lower = {-ax, -by, -cz};
    std::vector<double> upper = { ax,  by,  cz};

    int N = 1000000;

    lcg rng(12345);

    auto random_double = [&rng](){
        return rng();
    };

    auto [result, estimated_error] = plainmc(
        ellipsoid,
        lower,
        upper,
        N,
        random_double
    );

    // this is the formula for the volume from the assignment
    double exact = 4.0/3.0 * std::acos(-1.0) * ax * by * cz;

    std::cout << "# Volume of ellipsoid\n";
    std::cout << "N               = " << N << "\n";
    std::cout << "result          = " << result << "\n";
    std::cout << "exact           = " << exact << "\n";
    std::cout << "actual error    = " << std::abs(result - exact) << "\n";
    std::cout << "estimated error = " << estimated_error << "\n";
}

void run_task_B_quasi_circle()
{
    auto circle = [](const std::vector<double>& x){
        double r2 = x[0]*x[0] + x[1]*x[1];
        return r2 <= 1.0 ? 1.0 : 0.0;
    };

    std::vector<double> a = {-1.0, -1.0};
    std::vector<double> b = { 1.0,  1.0};

    double exact = std::acos(-1.0);

    std::cout << "# N plain_actual_error quasi_actual_error plain_estimated_error quasi_estimated_error\n";

    for(int N = 100; N <= 1000000; N *= 10){
        lcg rng(12345);

        auto random_double = [&rng](){
            return rng();
        };

        auto [plain_result, plain_error] = plainmc(
            circle,
            a,
            b,
            N,
            random_double
        );

        auto [quasi_result, quasi_error] = quasimc(
            circle,
            a,
            b,
            N
        );

        std::cout << N << " "
                  << std::abs(plain_result - exact) << " "
                  << std::abs(quasi_result - exact) << " "
                  << plain_error << " "
                  << quasi_error << "\n";
    }
}

void run_task_B_singular()
{
    int N = 1000000;
    double exact = 1.3932039296856768591842462603255;
    double pi = std::acos(-1.0);

    // the function to integrate is this
    auto f = [pi](const std::vector<double>& x){
        double cx = std::cos(pi*x[0]);
        double cy = std::cos(pi*x[1]);
        double cz = std::cos(pi*x[2]);

        return 1.0/(1.0 - cx*cy*cz);
    };

    std::vector<double> a = {0.0, 0.0, 0.0};
    std::vector<double> b = {1.0, 1.0, 1.0};

    // i) LCG generator
    lcg rng_lcg(12345);

    auto random_lcg = [&rng_lcg](){
        return rng_lcg();
    };

    auto [result_lcg, error_lcg] = plainmc(
        f,
        a,
        b,
        N,
        random_lcg
    );

    // ii) Standard C++ generator
    std::mt19937 gen(12345);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    auto random_std = [&gen, &dist](){
        return dist(gen);
    };

    auto [result_std, error_std] = plainmc(
        f,
        a,
        b,
        N,
        random_std
    );

    // iii) Quasi-random Halton sequence
    auto [result_quasi, error_quasi] = quasimc(
        f,
        a,
        b,
        N
    );

    std::cout << "# Singular 3D integral\n";
    std::cout << "# exact = " << exact << "\n\n";

    std::cout << "LCG\n";
    std::cout << "result          = " << result_lcg << "\n";
    std::cout << "estimated error = " << error_lcg << "\n";
    std::cout << "actual error    = " << std::abs(result_lcg - exact) << "\n\n";

    std::cout << "std::mt19937\n";
    std::cout << "result          = " << result_std << "\n";
    std::cout << "estimated error = " << error_std << "\n";
    std::cout << "actual error    = " << std::abs(result_std - exact) << "\n\n";

    std::cout << "Halton quasi-random\n";
    std::cout << "result          = " << result_quasi << "\n";
    std::cout << "estimated error = " << error_quasi << "\n";
    std::cout << "actual error    = " << std::abs(result_quasi - exact) << "\n";
}

// opgave C:
void run_task_C_stratified()
{
    auto circle = [](const std::vector<double>& x){
        double r2 = x[0]*x[0] + x[1]*x[1];
        return r2 <= 1.0 ? 1.0 : 0.0;
    };

    std::vector<double> a = {-1.0, -1.0};
    std::vector<double> b = { 1.0,  1.0};

    int N = 100000;
    double exact = std::acos(-1.0);

    lcg rng_plain(12345);
    auto random_plain = [&rng_plain](){ return rng_plain(); };

    auto [plain_result, plain_error] = plainmc(
        circle,
        a,
        b,
        N,
        random_plain
    );

    lcg rng_strat(12345);
    auto random_strat = [&rng_strat](){ return rng_strat(); };

    auto [strat_result, strat_error] = stratifiedmc(
        circle,
        a,
        b,
        N,
        random_strat
    );

    std::cout << "# Unit circle area comparison\n";
    std::cout << "N = " << N << "\n\n";

    std::cout << "plain MC\n";
    std::cout << "result          = " << plain_result << "\n";
    std::cout << "estimated error = " << plain_error << "\n";
    std::cout << "actual error    = " << std::abs(plain_result - exact) << "\n\n";

    std::cout << "stratified MC\n";
    std::cout << "result          = " << strat_result << "\n";
    std::cout << "estimated error = " << strat_error << "\n";
    std::cout << "actual error    = " << std::abs(strat_result - exact) << "\n";
}



int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage: ./main [A_circle | A_ellipsoid | B_quasi | B_singular | C]\n";
        return 1;
    }

    std::string task = argv[1];

    if(task == "A_circle"){
        run_task_A_circle();
    }
    else if(task == "A_ellipsoid"){
        run_task_A_ellipsoid();
    }
    else if(task == "B_quasi"){
        run_task_B_quasi_circle();
    }
    else if(task == "B_singular"){
        run_task_B_singular();
    }
    else if(task == "C"){
        run_task_C_stratified();
    }
    else{
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;
}