#pragma once

#include "linalg.h"

#include <cstddef>
#include <functional>

struct ann {
    std::size_t n; // number of hidden neurons
    std::function<double(double)> f; // activation function
    std::function<double(double)> df; // first derivative of activation function
    std::function<double(double)> ddf; // second derivative of activation function
    std::function<double(double)> integral_f; // anti-derivative of activation function

    pp::vector p; // network parameters

    ann( // constructor
        std::size_t number_of_neurons,
        std::function<double(double)> activation,
        std::function<double(double)> activation_derivative,
        std::function<double(double)> activation_second_derivative,
        std::function<double(double)> activation_antiderivative
    );

    double response(double x) const; 
    // return the response of the network to the input signal x
    double derivative(double x) const;
    double second_derivative(double x) const;
    double antiderivative(double x) const;

    void train(const pp::vector& x, const pp::vector& y); 
    // train the network to interpolate the given table {x, y} 
};