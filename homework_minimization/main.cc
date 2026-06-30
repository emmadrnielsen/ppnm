

#include "minimization.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <string>


// Opgave A1:
void run_task_A1()
{
    pp::objective phi = [](const pp::vector& x) {
        const double a = x[0] - 2.0;
        const double b = x[1] + 3.0;

        return a * a + b * b;
    };

    pp::vector starting_point{0.0, 0.0};

    const pp::minimization_result result =
        pp::newton(phi, starting_point);

    std::cout << "Minimum:\n";

    for (std::size_t i = 0; i < result.x.size(); ++i) {
        std::cout << "x[" << i << "] = "
                  << result.x[i] << '\n';
    }

    std::cout << "Newton steps = "
              << result.steps << '\n';

    std::cout << "Converged = "
              << (result.converged ? "yes" : "no")
              << '\n';
}

// Opgave A2:
double rosenbrock(const pp::vector& point)
{
    const double x = point[0];
    const double y = point[1];

    const double first_term = 1.0 - x;
    const double second_term = y - x * x;

    return first_term * first_term
         + 100.0 * second_term * second_term;
}


void run_task_A2()
{
    const pp::vector starting_point{-1.2, 1.0};

    const pp::minimization_result result =
        pp::newton(rosenbrock, starting_point);

    std::cout << "Rosenbrock function\n";
    std::cout << "x = " << result.x[0] << '\n';
    std::cout << "y = " << result.x[1] << '\n';
    std::cout << "f(x,y) = " << rosenbrock(result.x) << '\n';
    std::cout << "Newton steps = " << result.steps << '\n';
    std::cout << "Converged = "
              << (result.converged ? "yes" : "no")
              << '\n';
}

// Opgave A3:
double himmelblau(const pp::vector& point)
{
    const double x = point[0];
    const double y = point[1];

    const double first_term = x * x + y - 11.0;
    const double second_term = x + y * y - 7.0;

    return first_term * first_term
         + second_term * second_term;
}

void run_task_A3(){
    const pp::vector himmelblau_start{4.0, 3.0};
    // The function has multiple minima so if we use 
    // a diffferent starting point like -3.0, 3.0 we
    // would get a different result. 

    const pp::minimization_result himmelblau_result =
        pp::newton(himmelblau, himmelblau_start);

    std::cout << "\nHimmelblau function\n";
    std::cout << "x = " << himmelblau_result.x[0] << '\n';
    std::cout << "y = " << himmelblau_result.x[1] << '\n';
    std::cout << "f(x,y) = "
            << himmelblau(himmelblau_result.x) << '\n';
    std::cout << "Newton steps = "
            << himmelblau_result.steps << '\n';
    std::cout << "Converged = "
            << (himmelblau_result.converged ? "yes" : "no")
            << '\n';
}


// Opgave B:
double breit_wigner(double energy, const pp::vector& parameters)
{
    const double mass = parameters[0];
    const double width = parameters[1];
    const double scale = parameters[2];

    const double energy_difference = energy - mass;

    return scale /
        (energy_difference * energy_difference
         + width * width / 4.0);
}


void run_task_B()
{
    std::vector<double> energy;
    std::vector<double> signal;
    std::vector<double> uncertainty;

    double E;
    double sigma;
    double dsigma;

    while (std::cin >> E >> sigma >> dsigma) {
        energy.push_back(E);
        signal.push_back(sigma);
        uncertainty.push_back(dsigma);
    }

    if (energy.empty()) {
        std::cerr << "No data were read.\n";
        return;
    }

    pp::objective deviation =
        [&](const pp::vector& parameters) {
            double sum = 0.0;

            for (std::size_t i = 0; i < energy.size(); ++i) {
                const double fitted =
                    breit_wigner(energy[i], parameters);

                const double residual =
                    (fitted - signal[i]) / uncertainty[i];

                sum += residual * residual;
            }

            return sum;
        };

    const pp::vector starting_parameters{
        125.0,  // mass
        5.0,    // width
        35.0    // scale
    };

    const pp::minimization_result result =
        pp::newton(deviation, starting_parameters);


    const double mass = result.x[0];

    // The width enters the Breit-Wigner formula as width^2,
    // so the sign is physically irrelevant. I print abs(width)
    // because the physical width should be positive.
    const double width = std::abs(result.x[1]);
    const double scale = result.x[2];

    std::cerr << "Mass = " << mass << " GeV\n";
    std::cerr << "Width = " << width << " GeV\n";
    std::cerr << "Scale = " << scale << '\n';
    std::cerr << "Deviation = " << deviation(result.x) << '\n';
    std::cerr << "Steps = " << result.steps << '\n';
    std::cerr << "Converged = "
              << (result.converged ? "yes" : "no") << '\n';


    for (double e = 101.0; e <= 159.0; e += 0.1) {
        std::cout << e << ' '
                  << breit_wigner(e, result.x) << '\n';
    }

}

// Opgave C:

void run_task_C()
{
    std::cout << "\nRosenbrock comparison:\n";

    const pp::vector starting_point{-1.2, 1.0};

    const pp::minimization_result forward_result =
        pp::newton(rosenbrock, starting_point);

    const pp::minimization_result central_result =
        pp::newton_central(rosenbrock, starting_point);

    std::cout << "Forward differences:\n";
    std::cout << "x = " << forward_result.x[0] << '\n';
    std::cout << "y = " << forward_result.x[1] << '\n';
    std::cout << "f = " << rosenbrock(forward_result.x) << '\n';
    std::cout << "steps = " << forward_result.steps << "\n\n";

    std::cout << "Central differences:\n";
    std::cout << "x = " << central_result.x[0] << '\n';
    std::cout << "y = " << central_result.x[1] << '\n';
    std::cout << "f = " << rosenbrock(central_result.x) << '\n';
    std::cout << "steps = " << central_result.steps << '\n';


    std::cout << "\nHimmelblau comparison:\n";

    const pp::vector himmelblau_start{4.0, 3.0};

    const pp::minimization_result himmelblau_forward =
        pp::newton(himmelblau, himmelblau_start);

    const pp::minimization_result himmelblau_central =
        pp::newton_central(himmelblau, himmelblau_start);

    std::cout << "Forward differences:\n";
    std::cout << "x = " << himmelblau_forward.x[0] << '\n';
    std::cout << "y = " << himmelblau_forward.x[1] << '\n';
    std::cout << "f = " << himmelblau(himmelblau_forward.x) << '\n';
    std::cout << "steps = " << himmelblau_forward.steps << "\n\n";

    std::cout << "Central differences:\n";
    std::cout << "x = " << himmelblau_central.x[0] << '\n';
    std::cout << "y = " << himmelblau_central.x[1] << '\n';
    std::cout << "f = " << himmelblau(himmelblau_central.x) << '\n';
    std::cout << "steps = " << himmelblau_central.steps << '\n';
}


int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage: ./main A1|A2|A3|B|C\n";
        return 1;
    }

    std::string task = argv[1];

    if(task == "A1"){
        run_task_A1();
    }
    else if(task == "A2"){
        run_task_A2();
    }
    else if(task == "A3"){
        run_task_A3();
    }
    else if(task == "B"){
        run_task_B();
    }
    else if(task == "C"){
        run_task_C();
    }
    else{
        std::cerr << "Unknown task: " << task << "\n";
        std::cerr << "Use A1 or A2 or A3 or B or C\n";
        return 1;
    }

    return 0;
}