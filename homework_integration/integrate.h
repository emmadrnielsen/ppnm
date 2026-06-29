#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <functional>
#include <tuple>

// Opgave A1
// baseret på functionen i opgaven
double integrate(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 0.001, // disse værdier er givet i opgaven
    double eps = 0.001,
    double f2 = __builtin_nan(""), // nan indicates first call 
    double f3 = __builtin_nan(""),
    int depth = 0
); // This declares a function which returns the numerical
    // approximation to the integral. The arguments f2
    // and f3 are optional reused function values.
    // On the first call, they are NaN, meaning "not
    // available yet."



// Opgave A3:
double erf_integral(double z,
                    double acc = 1e-6, // chatgpt likes 1e-6 better than 0.001
                    double eps = 1e-6);



// Opgave B1:
double integrate_clenshaw_curtis(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 0.001,
    double eps = 0.001
);

// Opgave B4:
double integrate_infinite(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 0.001,
    double eps = 0.001
);

// Opgave C:
std::tuple<double,double> integrate_error(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 0.001,
    double eps = 0.001,
    double f2 = __builtin_nan(""),
    double f3 = __builtin_nan(""),
    int depth = 0
);

#endif