#ifndef ODE_H
#define ODE_H

#include "linalg.h"
#include <functional>
#include <tuple>
#include <vector>


// Task A1:
std::tuple<pp::vector, pp::vector> rkstep12(
    std::function<pp::vector(double, pp::vector)> f,
    // f is a function which takes vector y and returns a vector
    double x,
    pp::vector y,
    double h
); // declares the function rkstep12


// Task A2:
std::tuple<std::vector<double>, std::vector<pp::vector>> driver(
    std::function<pp::vector(double, pp::vector)> f,
    double a, 
    double b, 
    pp::vector yinit,
    double h = 0.125,
    double acc = 0.01,
    double eps = 0.01
);


#endif

// chatgpt^^