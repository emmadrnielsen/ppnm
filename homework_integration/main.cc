#include "integrate.h"
#include <iostream>
#include <cmath>
#include <string>
#include <functional>
#include <limits>


// Opgave A2: test lavet af chatgpt
void run_task_A_tests()
{
    double acc = 0.001; // værdier fra opgaven
    double eps = 0.001;

    auto test = [acc, eps](std::string name,
                           std::function<double(double)> f,
                           double a,
                           double b,
                           double exact)
    {
        double result = integrate(f, a, b, acc, eps);
        double error = std::abs(result - exact);
        double tolerance = acc + eps*std::abs(result);

        std::cout << name << "\n";
        std::cout << "result    = " << result << "\n";
        std::cout << "exact     = " << exact << "\n";
        std::cout << "error     = " << error << "\n";
        std::cout << "tolerance = " << tolerance << "\n";

        if(error < tolerance)
            std::cout << "status    = OK\n\n";
        else
            std::cout << "status    = NOT OK\n\n";
    };

    test("Integral of sqrt(x)",
         [](double x){ return std::sqrt(x); },
         0.0,
         1.0,
         2.0/3.0);

    test("Integral of 1/sqrt(x)",
         [](double x){ return 1.0/std::sqrt(x); },
         0.0,
         1.0,
         2.0);

    test("Integral of sqrt(1-x^2)",
         [](double x){ return std::sqrt(1.0 - x*x); },
         0.0,
         1.0,
         std::acos(-1.0)/4.0);

    test("Integral of log(x)/sqrt(x)",
         [](double x){ return std::log(x)/std::sqrt(x); },
         0.0,
         1.0,
         -4.0);
}

void run_task_A_erf()
{
    double acc = 1e-6;
    double eps = 1e-6;

    std::cout << "# z erf_integral std_erf difference\n";

    for(double z = -3.0; z <= 3.0; z += 0.05){
        double my_erf = erf_integral(z, acc, eps);
        double exact = std::erf(z);

        std::cout << z << " "
                  << my_erf << " "
                  << exact << " "
                  << std::abs(my_erf - exact) << "\n";
    }
}

// Opgave A4: made by chatgpt
void run_task_A_erf_convergence()
{
    double exact = 0.84270079294971486934;
    double eps = 0.0;

    std::cout << "# acc erf1 error\n";

    for(double acc = 1e-1; acc >= 1e-10; acc /= 10.0){
        double result = erf_integral(1.0, acc, eps);
        double error = std::abs(result - exact);

        std::cout << acc << " "
                  << result << " "
                  << error << "\n";
    }
}

void run_task_B_compare()
{
    double acc = 0.001;
    double eps = 0.001;

    auto compare = [acc, eps](std::string name,
                              auto make_f,
                              double exact)
    {
        int calls_ordinary = 0;

        auto f_ordinary = make_f(calls_ordinary);

        double result_ordinary = integrate(
            f_ordinary,
            0.0,
            1.0,
            acc,
            eps
        );

        int calls_cc = 0;

        auto f_cc = make_f(calls_cc);

        double result_cc = integrate_clenshaw_curtis(
            f_cc,
            0.0,
            1.0,
            acc,
            eps
        );

        std::cout << name << "\n";

        std::cout << "ordinary result = " << result_ordinary
                  << " error = " << std::abs(result_ordinary - exact)
                  << " calls = " << calls_ordinary << "\n";

        std::cout << "CC result       = " << result_cc
                  << " error = " << std::abs(result_cc - exact)
                  << " calls = " << calls_cc << "\n\n";
    };

    compare(
        "Integral of 1/sqrt(x)",
        [](int& calls){
            return [&calls](double x){
                calls++;
                return 1.0/std::sqrt(x);
            };
        },
        2.0
    );

    compare(
        "Integral of log(x)/sqrt(x)",
        [](int& calls){
            return [&calls](double x){
                calls++;
                return std::log(x)/std::sqrt(x);
            };
        },
        -4.0
    );
}

void run_task_B_infinite()
{
    double acc = 0.001;
    double eps = 0.001;

    const double inf = std::numeric_limits<double>::infinity();
    const double pi = std::acos(-1.0);

    // Test 1: integral from 0 to infinity
    int calls_exp = 0;

    auto exponential = [&calls_exp](double x){
        calls_exp++;
        return std::exp(-x);
    };

    double result_exp = integrate_infinite(
        exponential,
        0.0,
        inf,
        acc,
        eps
    );

    double exact_exp = 1.0;

    std::cout << "Integral exp(-x) from 0 to infinity\n";
    std::cout << "result = " << result_exp << "\n";
    std::cout << "exact  = " << exact_exp << "\n";
    std::cout << "error  = " << std::abs(result_exp - exact_exp) << "\n";
    std::cout << "calls = " << calls_exp << "\n\n";


    // Test 2: integral from -infinity to infinity
    int calls_gauss = 0;

    auto gaussian = [&calls_gauss](double x){
        calls_gauss++;
        return std::exp(-x*x);
    };

    double result_gauss = integrate_infinite(
        gaussian,
        -inf,
        inf,
        acc,
        eps
    );

    double exact_gauss = std::sqrt(pi);

    std::cout << "Integral exp(-x*x) from -infinity to infinity\n";
    std::cout << "result = " << result_gauss << "\n";
    std::cout << "exact  = " << exact_gauss << "\n";
    std::cout << "error  = " << std::abs(result_gauss - exact_gauss) << "\n";
    std::cout << "calls = " << calls_gauss << "\n";
}

// Opgave C:
void run_task_C()
{
    double acc = 0.001;
    double eps = 0.001;

    auto test = [acc, eps](std::string name,
                           std::function<double(double)> f,
                           double exact)
    {
        auto [result, estimated_error] = integrate_error(f, 0.0, 1.0, acc, eps);

        double actual_error = std::abs(result - exact);

        std::cout << name << "\n";
        std::cout << "result          = " << result << "\n";
        std::cout << "exact           = " << exact << "\n";
        std::cout << "estimated error = " << estimated_error << "\n";
        std::cout << "actual error    = " << actual_error << "\n\n";
    };

    test(
        "Integral sqrt(x)",
        [](double x){ return std::sqrt(x); },
        2.0/3.0
    );

    test(
        "Integral 1/sqrt(x)",
        [](double x){ return 1.0/std::sqrt(x); },
        2.0
    );

    test(
        "Integral log(x)/sqrt(x)",
        [](double x){ return std::log(x)/std::sqrt(x); },
        -4.0
    );
}


int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage: ./main A\n";
        return 1;
    }

    std::string task = argv[1];

    if(task == "A2"){
        run_task_A_tests();
    }
    else if(task == "A3"){
        run_task_A_erf();
    }
    else if(task == "A4"){
        run_task_A_erf_convergence();
    }
    else if(task == "B2"){
        run_task_B_compare();
    }
    else if(task == "B4"){
        run_task_B_infinite();
    }
    else if(task == "C"){
        run_task_C();
    }
    else{
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;
}