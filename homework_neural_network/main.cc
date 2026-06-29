#include "neural.h"
#include "minimization.h"

#include <cmath>
#include <iostream>
#include <string>
#include <fstream>


// Opgave A
void run_task_A1()
{
    // The activation function is chosen to be a
    // gaussian wavelet f(x) = x * exp(-x^2)
    auto wavelet = [](double x) {
        return x * std::exp(-x * x);
    };

    auto wavelet_derivative = [](double x) {
        return (1.0 - 2.0 * x * x)
            * std::exp(-x * x);
    };

    auto wavelet_second_derivative = [](double x) {
        return (4.0 * x * x * x - 6.0 * x)
            * std::exp(-x * x);
    };

    auto wavelet_antiderivative = [](double x) {
        return -0.5 * std::exp(-x * x);
    };

    ann network(
        5,
        wavelet,
        wavelet_derivative,
        wavelet_second_derivative,
        wavelet_antiderivative
    );

    // Parameters of neuron 0: a0, b0, w0
    network.p[0] = -0.5;
    network.p[1] = 0.4;
    network.p[2] = 1.0;

    // Parameters of neuron 1: a1, b1, w1
    network.p[3] = 0.0;
    network.p[4] = 0.4;
    network.p[5] = 1.0;

    // Parameters of neuron 2: a2, b2, w2
    network.p[6] = 0.5;
    network.p[7] = 0.4;
    network.p[8] = 1.0;

    for (double x = -1.0; x <= 1.0; x += 0.1) {
        std::cout << x << " " << network.response(x) << "\n";
    }
}


void run_task_A2()
{
    auto wavelet = [](double x) {
        return x * std::exp(-x * x); // gaussian wavelet
    };

    auto wavelet_derivative = [](double x) {
        return (1.0 - 2.0 * x * x)
            * std::exp(-x * x);
    };

    auto wavelet_second_derivative = [](double x) {
        return (4.0 * x * x * x - 6.0 * x)
            * std::exp(-x * x);
    };

    auto wavelet_antiderivative = [](double x) {
        return -0.5 * std::exp(-x * x);
    };

    auto target = [](double x) {
        return std::cos(5.0 * x - 1.0)
             * std::exp(-x * x);
    };

    constexpr std::size_t number_of_points = 15;

    pp::vector x(number_of_points);
    pp::vector y(number_of_points);

    for (std::size_t k = 0; k < number_of_points; ++k) {
        x[k] = -1.0
             + 2.0 * static_cast<double>(k)
             / static_cast<double>(number_of_points - 1);

        y[k] = target(x[k]);
    }

    ann network(
        5,
        wavelet,
        wavelet_derivative,
        wavelet_second_derivative,
        wavelet_antiderivative
    );
    network.train(x, y);

    double cost = 0.0;

    for (std::size_t k = 0; k < number_of_points; ++k) {
        double residual = network.response(x[k]) - y[k];
        cost += residual * residual;
    }

    std::cerr << "Final cost = " << cost << "\n";

    std::ofstream output("network.data");

    // the output columns are 
    // x    exact-function    neural-network
    output << "# x exact network\n";

    constexpr std::size_t plot_points = 201;

    for (std::size_t k = 0; k < plot_points; ++k) {
        double z = -1.0
                 + 2.0 * static_cast<double>(k)
                 / static_cast<double>(plot_points - 1);

        output << z << " "
               << target(z) << " "
               << network.response(z) << "\n";
    }

    std::ofstream points("training.data");

    points << "# x y\n";

    for (std::size_t k = 0; k < number_of_points; ++k) {
        points << x[k] << " " << y[k] << "\n";
    }
}


void run_task_B()
{
    auto wavelet = [](double x) {
        return x * std::exp(-x * x);
    };

    auto wavelet_derivative = [](double x) {
        return (1.0 - 2.0 * x * x)
             * std::exp(-x * x);
    };

    auto wavelet_second_derivative = [](double x) {
        return (4.0 * x * x * x - 6.0 * x)
             * std::exp(-x * x);
    };

    auto wavelet_antiderivative = [](double x) {
        return -0.5 * std::exp(-x * x);
    };

    auto target = [](double x) {
        return std::cos(5.0 * x - 1.0)
             * std::exp(-x * x);
    };

    auto target_derivative = [](double x) {
        double angle = 5.0 * x - 1.0;

        return std::exp(-x * x)
             * (
                   -5.0 * std::sin(angle)
                   - 2.0 * x * std::cos(angle)
               );
    };

    auto target_second_derivative = [](double x) {
        double angle = 5.0 * x - 1.0;

        return std::exp(-x * x)
             * (
                   (4.0 * x * x - 27.0) * std::cos(angle)
                   + 20.0 * x * std::sin(angle)
               );
    };

    constexpr std::size_t number_of_points = 15;

    pp::vector x(number_of_points);
    pp::vector y(number_of_points);

    for (std::size_t k = 0; k < number_of_points; ++k) {
        x[k] = -1.0
             + 2.0 * static_cast<double>(k)
             / static_cast<double>(number_of_points - 1);

        y[k] = target(x[k]);
    }

    ann network(
        5,
        wavelet,
        wavelet_derivative,
        wavelet_second_derivative,
        wavelet_antiderivative
    );

    network.train(x, y);

    std::ofstream output("derivatives.data");

    output << "# x target network "
           << "target_derivative network_derivative "
           << "target_second_derivative network_second_derivative "
           << "network_antiderivative\n";

    double antiderivative_at_left =
        network.antiderivative(-1.0);

    constexpr std::size_t plot_points = 201;

    for (std::size_t k = 0; k < plot_points; ++k) {
        double z = -1.0
                 + 2.0 * static_cast<double>(k)
                 / static_cast<double>(plot_points - 1);

        double integral =
            network.antiderivative(z)
            - antiderivative_at_left;

        output
            << z << " "
            << target(z) << " "
            << network.response(z) << " "
            << target_derivative(z) << " "
            << network.derivative(z) << " "
            << target_second_derivative(z) << " "
            << network.second_derivative(z) << " "
            << integral << "\n";
    }
}

void run_task_C()
{
    auto wavelet = [](double x) {
        return x * std::exp(-x * x);
    };

    auto wavelet_derivative = [](double x) {
        return (1.0 - 2.0 * x * x)
             * std::exp(-x * x);
    };

    auto wavelet_second_derivative = [](double x) {
        return (4.0 * x * x * x - 6.0 * x)
             * std::exp(-x * x);
    };

    auto wavelet_antiderivative = [](double x) {
        return -0.5 * std::exp(-x * x);
    };

    constexpr std::size_t number_of_neurons = 5;

    ann network(
        number_of_neurons,
        wavelet,
        wavelet_derivative,
        wavelet_second_derivative,
        wavelet_antiderivative
    );

    const double a = 0.0;
    const double b = 2.0 * std::acos(-1.0);
    const double c = 0.0;

    const double yc = 0.0;
    const double dyc = 1.0;

    const double alpha = 100.0;
    const double beta = 100.0;

    // Initial positions, scales and weights.
    double spacing =
        (b - a) / static_cast<double>(number_of_neurons - 1);

    for (std::size_t i = 0; i < number_of_neurons; ++i) {
        network.p[3 * i] =
            a + static_cast<double>(i) * spacing;

        network.p[3 * i + 1] = spacing;
        network.p[3 * i + 2] = 1.0;
    }

    auto cost = [&network, a, b, c, yc, dyc, alpha, beta](
        const pp::vector& parameters
    ) {
        network.p = parameters;

        constexpr std::size_t intervals = 40;
        double h = (b - a) / static_cast<double>(intervals);

        double integral = 0.0;

        for (std::size_t k = 0; k <= intervals; ++k) {
            double x =
                a + static_cast<double>(k) * h;

            double residual =
                network.second_derivative(x)
                + network.response(x);

            double weight =
                (k == 0 || k == intervals) ? 0.5 : 1.0;

            integral += weight * residual * residual;
        }

        integral *= h;

        double value_error =
            network.response(c) - yc;

        double derivative_error =
            network.derivative(c) - dyc;

        return integral
             + alpha * value_error * value_error
             + beta * derivative_error * derivative_error;
    };

    pp::minimization_result result =
        pp::newton_central(cost, network.p, 1e-4, 1000);

    network.p = result.x;

    std::cout << "Minimizer steps = "
              << result.steps << "\n";

    std::cout << "Converged = "
              << std::boolalpha
              << result.converged << "\n";

    std::cout << "Final cost = "
              << cost(result.x) << "\n";

    std::cout << "F(0) = "
              << network.response(0.0) << "\n";

    std::cout << "F'(0) = "
              << network.derivative(0.0) << "\n";


    std::ofstream output("ode_network.data");

    output << "# x exact network residual\n";

    constexpr std::size_t plot_points = 201;

    for (std::size_t k = 0; k < plot_points; ++k) {
        double x =
            a + (b - a) * static_cast<double>(k)
            / static_cast<double>(plot_points - 1);

        double exact = std::sin(x);
        double approximation = network.response(x);

        double residual =
            network.second_derivative(x)
            + approximation;

        output << x << " "
            << exact << " "
            << approximation << " "
            << residual << "\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: ./main A1\n";
        return 1;
    }

    std::string task = argv[1];

    if (task == "A1") {
        run_task_A1();
    }
    else if(task == "A2"){
        run_task_A2();
    }
    else if(task == "B"){
        run_task_B();
    }
    else if(task == "C"){
        run_task_C();
    }
    else {
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;
}