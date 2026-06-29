#include "neural.h"
#include "minimization.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

// Task A:
ann::ann(
    std::size_t number_of_neurons,
    std::function<double(double)> activation,
    std::function<double(double)> activation_derivative,
    std::function<double(double)> activation_second_derivative,
    std::function<double(double)> activation_antiderivative
)
    : n(number_of_neurons),
      f(activation),
      df(activation_derivative),
      ddf(activation_second_derivative),
      integral_f(activation_antiderivative),
      p(3 * number_of_neurons, 0.0)
      // all a b and w values are initialized as 0
      // but that wont work for b because b is used 
      // in division Fp(x) = ∑i f((x-ai)/bi)*wi
      // so we need to initialize b to 1 instead of 0:
{
    for (std::size_t i = 0; i < n; ++i) {
        p[3 * i + 1] = 1.0; 
    }
}

// this function implements Fp(x) = ∑i f((x-ai)/bi)*wi
double ann::response(double x) const
{
    double sum = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double ai = p[3 * i]; // location of wavelet
        double bi = p[3 * i + 1]; // width of the wavelet
        double wi = p[3 * i + 2]; // height and sign of wavelet's contribution

        if (bi == 0.0) {
            throw std::invalid_argument(
                "ann::response: neuron scale b cannot be zero"
            );
        }

        double scaled_x = (x - ai) / bi;
        sum += wi * f(scaled_x);
    }

    return sum;
}

void ann::train(const pp::vector& x, const pp::vector& y)
{
    if (x.size() != y.size()) {
        throw std::invalid_argument(
            "ann::train: x and y must have the same size"
        );
    }

    if (x.size() == 0) {
        throw std::invalid_argument(
            "ann::train: no training data"
        );
    }

    double xmin = x[0];
    double xmax = x[0];

    for (std::size_t k = 1; k < x.size(); ++k) {
        xmin = std::min(xmin, x[k]);
        xmax = std::max(xmax, x[k]);
    }

    double interval = xmax - xmin;

    if (interval == 0.0) {
        interval = 1.0;
    }

    double spacing =
        n > 1 ? interval / static_cast<double>(n - 1) : interval;

    // initialize neurons across the interval. 
    // The neuron centers a_i are spread from xmin to xmax.
    // The widths b_i are set from the spacing.
    // The weights w_i start at 1.0
    for (std::size_t i = 0; i < n; ++i) {
        double fraction =     // this prevents division by n-1
            n > 1             // when the network has only one neuron. 
                ? static_cast<double>(i)
                    / static_cast<double>(n - 1)
                : 0.5;

        p[3 * i] = xmin + fraction * interval;
        p[3 * i + 1] = spacing;
        p[3 * i + 2] = 1.0;
    }

    auto cost = [this, &x, &y](
        // this: allows access to the current network and its p
        // &x: uses the original training vector without copying it
        // &y: uses the original target vector without copying it
        const pp::vector& parameters
    ) {
        p = parameters;

        double sum = 0.0;

        for (std::size_t k = 0; k < x.size(); ++k) {
            double residual = response(x[k]) - y[k];
            sum += residual * residual;
        }

        return sum;
    };

    // analytical gradient
    auto cost_gradient = [this, &x, &y](
        const pp::vector& parameters
    ) {
        pp::vector gradient(3 * n, 0.0);

        p = parameters;

        for (std::size_t k = 0; k < x.size(); ++k) {
            double residual = response(x[k]) - y[k];

            for (std::size_t i = 0; i < n; ++i) {
                double ai = parameters[3 * i];
                double bi = parameters[3 * i + 1];
                double wi = parameters[3 * i + 2];

                if (std::abs(bi) < 1e-12) {
                    throw std::invalid_argument(
                        "ann::train: neuron scale too close to zero"
                    );
                }

                double zi = (x[k] - ai) / bi;
                double derivative = df(zi);

                gradient[3 * i] +=
                    2.0 * residual
                    * (-wi / bi)
                    * derivative;

                gradient[3 * i + 1] +=
                    2.0 * residual
                    * (-wi * zi / bi)
                    * derivative;

                gradient[3 * i + 2] +=
                    2.0 * residual
                    * f(zi);
            }
        }

        return gradient;
    };
    
    // use minimizer to train the network:
    pp::minimization_result result =
        pp::newton(cost, cost_gradient, p, 1e-5, 1000);

    std::cerr << "Minimizer steps = " << result.steps << "\n";
    std::cerr << "Converged = " << std::boolalpha
            << result.converged << "\n";
    std::cerr << "Gradient norm = "
            << cost_gradient(result.x).norm() << "\n";

    p = result.x;
}

// Task B:
double ann::derivative(double x) const
{
    double sum = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double ai = p[3 * i];
        double bi = p[3 * i + 1];
        double wi = p[3 * i + 2];

        if (std::abs(bi) < 1e-12) {
            throw std::invalid_argument(
                "ann::derivative: neuron scale too close to zero"
            );
        }

        double zi = (x - ai) / bi;

        sum += (wi / bi) * df(zi);
    }

    return sum;
}

double ann::second_derivative(double x) const
{
    double sum = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double ai = p[3 * i];
        double bi = p[3 * i + 1];
        double wi = p[3 * i + 2];

        if (std::abs(bi) < 1e-12) {
            throw std::invalid_argument(
                "ann::second_derivative: neuron scale too close to zero"
            );
        }

        double zi = (x - ai) / bi;

        sum += (wi / (bi * bi)) * ddf(zi);
    }

    return sum;
}

double ann::antiderivative(double x) const
{
    double sum = 0.0;

    for (std::size_t i = 0; i < n; ++i) {
        double ai = p[3 * i];
        double bi = p[3 * i + 1];
        double wi = p[3 * i + 2];

        if (std::abs(bi) < 1e-12) {
            throw std::invalid_argument(
                "ann::antiderivative: neuron scale too close to zero"
            );
        }

        double zi = (x - ai) / bi;

        sum += wi * bi * integral_f(zi);
    }

    return sum;
}

