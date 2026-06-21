#include "ode.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>


// Opgave A1: kopieret fra opgaven
std::tuple<pp::vector, pp::vector> rkstep12(
    std::function<pp::vector(double, pp::vector)> f, // the f from dy/dx=f(x,y) 
    double x, // the current value of the variable
    pp::vector y, // the current value y(x) of the sought function
    double h // the step to be taken
) 
{
    pp::vector k0 = f(x, y); //  embedded lower order formula (Euler)
                            // Ligning 23
                            // calculates the slop at the beginning of the step

    pp::vector k1 = f(x + h/2, y + k0*(h/2)); // higher order formula (midpoint)
                                            // Ligning 29 hvor alpha er lig 1/2
                                            // first estimates the value halfway 
                                            // through the step using Euler's method, 
                                            // then evaluates the slope there. This is
                                            // the midpoint slope. 

    pp::vector yh = y + k1*h; // y(x+h) estimate
                              // uses the midpoint slope to take
                              // the full step. This is the better
                              // estimate 

    pp::vector dy = (k1 - k0)*h; // error estimate
                                 // estimates the error by comparing
                                 // the beginning slope and midpoint slope.
                                 // The driver will later use this dy to
                                 // decide whether the step size h is small
                                 // enough

    return std::make_tuple(yh, dy); 
}

// Opgave A2:
std::tuple<std::vector<double>, std::vector<pp::vector>> driver(
    std::function<pp::vector(double, pp::vector)> f, 
    double a, 
    double b, 
    pp::vector yinit,
    double h, 
    double acc, 
    double eps
)
{ 
    double x = a;
    pp::vector y = yinit;

    double hmax = 0.05;

    std::vector<double> xlist;
    std::vector<pp::vector> ylist;

    xlist.push_back(x);
    ylist.push_back(y);

    while(x < b){
        // Make sure the final step lands exactly on b
        if(x + h > b) h = b - x;

        auto [yh, dy] = rkstep12(f, x, y, h); // each loop attempts one step
                                            // yh = proposed y-value at x+h
                                            // dy = estimated error

        double tol = (acc + eps*yh.norm()) * std::sqrt(h/(b-a)); // computes the tolerance
                                                                 // This combines absolute accuracy acc
                                                                 // and relative accuracy eps.
                                                                  
        double err = dy.norm();

        if(err <= tol){ // if the error is too large, the step is rejected, and the code tries again with a smaller h
            // Accept step
            x += h;
            y = yh;

            xlist.push_back(x); // stores the initial point
            ylist.push_back(y);
        }

        // Adjust step size
        if(err > 0){
            h *= std::min(std::pow(tol/err, 0.25)*0.95, 2.0); // updates the step size. The 0.95 is a safety factor, and the min(..., 2.0) prevents the step size from growing too aggressively
        }
        else{
            h *= 2;
        }
        if(h <= 0){
            throw std::runtime_error("driver: step size became non-positive");
        }

        if(h > hmax) h = hmax;
    }

    return std::make_tuple(xlist, ylist);
}