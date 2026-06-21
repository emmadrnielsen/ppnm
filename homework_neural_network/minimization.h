#pragma once

#include "linalg.h"

#include <functional>


namespace pp {

using objective = std::function<double(const vector&)>;

struct minimization_result {
    vector x; // stores the point where the algorithm stopped
              // if minimization succeeds, this is the estimated
              // location of the minimum
    int steps; // number of Newton iterations performed
    bool converged; // why the algorithm stopped.
                    // if it is bc the norm of the gradient
                    // is less than acc or if it is bc
                    // the maximum number of iterations
                    // was reached. 
};

// these are the functions from the assignment:
vector gradient(const objective& phi, const vector& x);

matrix hessian(const objective& phi, const vector& x);

minimization_result newton(
    const objective& phi,
    vector x,
    double accuracy = 1e-3,
    int max_steps = 1000
);

// Opgave C:
vector central_gradient(
    const objective& phi,
    const vector& x
);

matrix central_hessian(
    const objective& phi,
    const vector& x
);

minimization_result newton_central(
    const objective& phi,
    vector x,
    double accuracy = 1e-3,
    int max_steps = 1000
);

using gradient_function =
    std::function<vector(const vector&)>;

minimization_result newton(
    const objective& phi,
    const gradient_function& gradient_phi,
    vector x,
    double accuracy = 1e-3,
    int max_steps = 1000
);

}