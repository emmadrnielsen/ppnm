#ifndef ROOTS_H
#define ROOTS_H

#include "linalg.h"
#include <functional>


// Opgave A:
// pp::matrix jacobian(
//     std::function<pp::vector(pp::vector)> f,
//     pp::vector x,
//     pp::vector fx
// ); // ligesom i opgaven tager den f, x og fx og returnerer en matrix J

pp::vector newton(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    double acc = 1e-2,
    double alpha_min = 1e-3,
    int max_iter = 100
); // defineret ligesom i opgaven

// Opgave C1:
// The declaration from opg A is replaced with this:
void jacobian(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    const pp::vector& fx,
    pp::matrix& J
);

#endif