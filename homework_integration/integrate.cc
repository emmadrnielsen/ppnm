#include "integrate.h"
#include <cmath>
#include <stdexcept>
#include <functional>
#include <limits>
#include <stdexcept>
#include <tuple>


// Opgave A1: Lavet ligesom i opgavebeskrivelsen
double integrate(
    std::function<double(double)> f,
    double a,
    double b,
    double acc,
    double eps,
    double f2,
    double f3,
    int depth
)
{
    if(depth > 100000){
        throw std::runtime_error("integrate: maximum recursion depth reached");
    }
    double h = b - a; // definerer h ligesom i opgaven

    // If this is the first call, there are no reusable points yet
    if(std::isnan(f2)){
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    // Higher-order rule
    double Q = (2*f1 + f2 + f3 + 2*f4)/6 * h;

    // Lower-order embedded rule
    double q = (f1 + f2 + f3 + f4)/4 * h;

    double err = std::abs(Q - q);
    double tol = acc + eps*std::abs(Q);

    if(err < tol){
        return Q; // hvis err<tol så returnerer vi Q og er
                    // glade og ellers deles intervallet op i 2
    }
    else{
        double m = (a + b)/2;

        double left = integrate(
            f,
            a,
            m,
            acc/std::sqrt(2.0),
            eps,
            f1,
            f2,
            depth + 1
        );

        double right = integrate(
            f,
            m,
            b,
            acc/std::sqrt(2.0),
            eps,
            f3,
            f4,
            depth + 1
        );

        return left + right;
    }
}

// Opgave A3: 
double erf_integral(double z, double acc, double eps)
{
    const double pi = std::acos(-1.0);

    if(z < 0){
        return -erf_integral(-z, acc, eps); // den første ligning
    }

    else if(z <= 1.0){
        auto f = [](double x){
            return std::exp(-x*x);
        };

        return 2.0/std::sqrt(pi) * integrate(f, 0.0, z, acc, eps); // ligning 2
    }

    else{
        auto f = [z](double t){
            double x = z + (1.0 - t)/t;
            return std::exp(-x*x)/(t*t);
        };

        return 1.0 - 2.0/std::sqrt(pi) * integrate(f, 0.0, 1.0, acc, eps); // ligning 3
    }
}

// Opgave B1:
double integrate_clenshaw_curtis(
    std::function<double(double)> f,
    double a,
    double b,
    double acc,
    double eps
)
{
    const double pi = std::acos(-1.0); 

    auto transformed = [f, a, b](double theta)
    {
        // hvis theta = 0 er x = b, hvis theta = pi er x = a
        double x = (a + b)/2.0 + (b - a)/2.0 * std::cos(theta);
        // overordnede ligning differentieret
        double dx_dtheta_abs = (b - a)/2.0 * std::sin(theta);

        return f(x) * dx_dtheta_abs;
    };

    return integrate(transformed, 0.0, pi, acc, eps);
}
// The structure is:
// original integral:
// ∫_a^b f(x) dx

// change variable:
// x = (a+b)/2 + (b-a)/2 cos(theta)

// new integral:
// ∫_0^π g(theta) dtheta

// then use your old integrate(...) on g(theta)


// Opgave B4:
double integrate_infinite(
    std::function<double(double)> f,
    double a,
    double b,
    double acc,
    double eps
)
{
    const double inf = std::numeric_limits<double>::infinity();

    if(std::isfinite(a) && std::isfinite(b)){
        return integrate_clenshaw_curtis(f, a, b, acc, eps);
    }

    // Integral from a to +infinity
    if(std::isfinite(a) && b == inf){
        auto g = [f, a](double t){
            double x = a + (1.0 - t)/t;
            double dxdt = 1.0/(t*t);
            return f(x)*dxdt;
        };

        return integrate_clenshaw_curtis(g, 0.0, 1.0, acc, eps);
    }

    // Integral from -infinity to b
    if(a == -inf && std::isfinite(b)){
        auto g = [f, b](double t){
            double x = b - (1.0 - t)/t;
            double dxdt = 1.0/(t*t);
            return f(x)*dxdt;
        };

        return integrate_clenshaw_curtis(g, 0.0, 1.0, acc, eps);
    }

    // Integral from -infinity to +infinity
    if(a == -inf && b == inf){
        auto g = [f](double t){
            double x = t/(1.0 - t*t);
            double dxdt = (1.0 + t*t)/((1.0 - t*t)*(1.0 - t*t));
            return f(x)*dxdt;
        };

        return integrate_clenshaw_curtis(g, -1.0, 1.0, acc, eps);
    }

    throw std::invalid_argument("integrate_infinite: unsupported limits");
}


// Opgave C:
std::tuple<double,double> integrate_error(
    std::function<double(double)> f,
    double a,
    double b,
    double acc,
    double eps,
    double f2,
    double f3,
    int depth
)
{
    if(depth > 100000){
        throw std::runtime_error("integrate_error: maximum recursion depth reached");
    }

    double h = b - a;

    if(std::isnan(f2)){
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    double Q = (2*f1 + f2 + f3 + 2*f4)/6 * h;
    double q = (f1 + f2 + f3 + f4)/4 * h;

    double err = std::abs(Q - q);
    double tol = acc + eps*std::abs(Q);

    if(err < tol){
        return std::make_tuple(Q, err);
    }
    else{
        double m = (a + b)/2;

        auto [Q1, err1] = integrate_error(
            f,
            a,
            m,
            acc/std::sqrt(2.0),
            eps,
            f1,
            f2,
            depth + 1
        );

        auto [Q2, err2] = integrate_error(
            f,
            m,
            b,
            acc/std::sqrt(2.0),
            eps,
            f3,
            f4,
            depth + 1
        );

        double Q_total = Q1 + Q2;
        double err_total = std::sqrt(err1*err1 + err2*err2);

        return std::make_tuple(Q_total, err_total);
    }
}