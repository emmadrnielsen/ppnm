#include "minimization.h"

#include <cmath>
#include <cstddef>
#include <limits>

namespace pp {

vector gradient(const objective& phi, const vector& x)
{
    vector g(x.size(), 0.0);
    vector x_shifted = x;

    const double phi_x = phi(x); // this is the function
                                 // evaluated at the original
                                 // unshifted point. 

    for (std::size_t i = 0; i < x.size(); ++i) {
        const double dx =
            (1.0 + std::abs(x[i])) * std::pow(2.0, -26);

        x_shifted[i] += dx; // adds dx to x

        g[i] = (phi(x_shifted) - phi_x) / dx;
        // This calculates the partial derivative

        x_shifted[i] = x[i]; // goes back to original x
                            // the code in the assignment
                            // does this by subtracting dx
                            // again. 
                            // The coordinate is restored
                            // before the next coordinate
                            // is tested
    }

    return g;
}


matrix hessian(const objective& phi, const vector& x)
{
    const std::size_t n = x.size();

    matrix H(n, n, 0.0); // H = matrix(len(x), len(x))
    vector x_shifted = x;

    const vector g_x = gradient(phi, x); // same as in the assignment

    for (std::size_t j = 0; j < n; ++j) {
        const double dx =
            (1.0 + std::abs(x[j])) * std::pow(2.0, -13);

        x_shifted[j] += dx;

        const vector g_shifted = gradient(phi, x_shifted);

        x_shifted[j] = x[j]; // puts x back to original

        for (std::size_t i = 0; i < n; ++i) {
            H(i, j) = (g_shifted[i] - g_x[i]) / dx;
        }
    }

    return H;
}

// the line search repeatedly needs to calculate 
// xtrial = x + λΔx. This is a helper function for that:
static vector trial_point(
    const vector& x,
    const vector& dx,
    double lambda
)
{
    return x + lambda * dx;
}


minimization_result newton(
    const objective& phi,
    vector x,
    double accuracy,
    int max_steps
)
{
    constexpr double regularization = 1e-6; // Levenberg regularization
    constexpr double minimum_lambda = 1.0 / 1024.0; // for backtracking linesearch

    for (int step = 0; step < max_steps; ++step) {
        const vector g = gradient(phi, x); // ~assignment

        if (g.norm() < accuracy) {
            return {x, step, true}; // job done. 
                                    // return immediately exits
                                    // the entire newton function.
                                    // A small gradient means the current
                                    // point is approximately stationary. 
        }

        matrix H = hessian(phi, x); // ~assignment

        for (std::size_t i = 0; i < H.rows(); ++i) {
            H(i, i) += regularization; // ~assignment
        }

        qr decomposition(H);
        const vector dx = decomposition.solve(-1.0 * g); // ~assignment
        // This uses QR decomposition to solve HΔx=−g.

        const double phi_x = phi(x); // original phi
        double lambda = 1.0; // ~assignment

        while (lambda > minimum_lambda) { // backtracking linesearch
            const vector candidate = trial_point(x, dx, lambda);

            if (phi(candidate) < phi_x) {
                break; // good step
            }

            lambda /= 2.0;
        }

        x = trial_point(x, dx, lambda);
    }

    return {x, max_steps, false};
}


// Opgave C:
vector central_gradient(
    const objective& phi,
    const vector& x
)
{
    const double epsilon =
        std::numeric_limits<double>::epsilon();

    const double epsilon_step = std::cbrt(epsilon);

    vector g(x.size(), 0.0);

    for (std::size_t i = 0; i < x.size(); ++i) {
        const double dx =
            (1.0 + std::abs(x[i])) * epsilon_step;

        vector x_plus = x;
        vector x_minus = x;

        x_plus[i] += dx;
        x_minus[i] -= dx;

        g[i] =
            (phi(x_plus) - phi(x_minus)) / (2.0 * dx);
    }

    return g;
}

matrix central_hessian(
    const objective& phi,
    const vector& x
)
{
    const std::size_t n = x.size();

    const double epsilon =
        std::numeric_limits<double>::epsilon();

    const double epsilon_step = std::cbrt(epsilon);

    matrix H(n, n, 0.0);
    const double phi_x = phi(x);

    for (std::size_t i = 0; i < n; ++i) {
        const double dxi =
            (1.0 + std::abs(x[i])) * epsilon_step;

        vector x_plus = x;
        vector x_minus = x;

        x_plus[i] += dxi;
        x_minus[i] -= dxi;

        H(i, i) =
            (phi(x_plus) - 2.0 * phi_x + phi(x_minus))
            / (dxi * dxi);

        for (std::size_t j = i + 1; j < n; ++j) {
            const double dxj =
                (1.0 + std::abs(x[j])) * epsilon_step;

            vector x_pp = x;
            vector x_pm = x;
            vector x_mp = x;
            vector x_mm = x;

            x_pp[i] += dxi;
            x_pp[j] += dxj;

            x_pm[i] += dxi;
            x_pm[j] -= dxj;

            x_mp[i] -= dxi;
            x_mp[j] += dxj;

            x_mm[i] -= dxi;
            x_mm[j] -= dxj;

            const double value =
                (
                    phi(x_pp)
                    - phi(x_pm)
                    - phi(x_mp)
                    + phi(x_mm)
                )
                / (4.0 * dxi * dxj);

            H(i, j) = value;
            H(j, i) = value;
        }
    }

    return H;
}

minimization_result newton_central(
    const objective& phi,
    vector x,
    double accuracy,
    int max_steps
)
{
    constexpr double regularization = 1e-6; // Levenberg regularization
    constexpr double minimum_lambda = 1.0 / 1024.0; // for backtracking linesearch

    for (int step = 0; step < max_steps; ++step) {
        const vector g = central_gradient(phi, x);

        if (g.norm() < accuracy) {
            return {x, step, true}; // job done. 
                                    // return immediately exits
                                    // the entire newton function.
                                    // A small gradient means the current
                                    // point is approximately stationary. 
        }

        matrix H = central_hessian(phi, x);

        for (std::size_t i = 0; i < H.rows(); ++i) {
            H(i, i) += regularization; // ~assignment
        }

        qr decomposition(H);
        const vector dx = decomposition.solve(-1.0 * g); // ~assignment
        // This uses QR decomposition to solve HΔx=−g.

        const double phi_x = phi(x); // original phi
        double lambda = 1.0; // ~assignment

        while (lambda > minimum_lambda) { // backtracking linesearch
            const vector candidate = trial_point(x, dx, lambda);

            if (phi(candidate) < phi_x) {
                break; // good step
            }

            lambda /= 2.0;
        }

        x = trial_point(x, dx, lambda);
    }

    return {x, max_steps, false};
}

minimization_result newton(
    const objective& phi,
    const gradient_function& gradient_phi,
    vector x,
    double accuracy,
    int max_steps
)
{
    constexpr double regularization = 1e-6;
    constexpr double minimum_lambda = 1.0 / 1024.0;

    for (int step = 0; step < max_steps; ++step) {
        vector g = gradient_phi(x);

        if (g.norm() < accuracy) {
            return {x, step, true};
        }

        std::size_t number_of_parameters = x.size();
        matrix H(
            number_of_parameters,
            number_of_parameters,
            0.0
        );

        for (std::size_t j = 0;
             j < number_of_parameters;
             ++j) {
            double dx =
                (1.0 + std::abs(x[j]))
                * std::pow(2.0, -26);

            vector x_shifted = x;
            x_shifted[j] += dx;

            vector g_shifted = gradient_phi(x_shifted);

            for (std::size_t i = 0;
                 i < number_of_parameters;
                 ++i) {
                H(i, j) = (g_shifted[i] - g[i]) / dx;
            }
        }

        for (std::size_t i = 0; i < H.rows(); ++i) {
            H(i, i) += regularization;
        }

        qr decomposition(H);
        vector dx = decomposition.solve(-1.0 * g);

        // A descent direction must satisfy grad(C) dot dx < 0.
        if (g.dot(dx) >= 0.0) {
            dx = -1.0 * g;
        }

        double phi_x = phi(x);
        double lambda = 1.0;
        bool accepted = false;

        while (lambda >= minimum_lambda) {
            vector candidate = x + lambda * dx;

            if (phi(candidate) < phi_x) {
                x = candidate;
                accepted = true;
                break;
            }

            lambda /= 2.0;
        }

        if (!accepted) {
            return {x, step, false};
        }
    }

    return {x, max_steps, false};
}

}