#include "roots.h"
#include <iostream>
#include <cmath>
#include <string>
#include "ode.h"
#include <fstream>

void run_task_A_debug()
{
    // 1D test: x^2 - 2 = 0
    auto f1 = [](pp::vector x){
        pp::vector fx(1);
        fx[0] = x[0]*x[0] - 2.0;
        return fx;
    };

    pp::vector x1(1);
    x1[0] = 1.0;

    pp::vector root1 = newton(f1, x1, 1e-10);

    std::cout << "1D test: f(x) = x^2 - 2\n";
    std::cout << "root x          = " << root1[0] << "\n";
    std::cout << "expected sqrt(2)= " << std::sqrt(2.0) << "\n";
    std::cout << "f(root)         = " << f1(root1)[0] << "\n\n";


    // 2D test:
    // f0(x,y) = x^2 - 4
    // f1(x,y) = y^2 - 9
    auto f2 = [](pp::vector x){
        pp::vector fx(2);
        fx[0] = x[0]*x[0] - 4.0;
        fx[1] = x[1]*x[1] - 9.0;
        return fx;
    };

    pp::vector x2(2);
    x2[0] = 1.0;
    x2[1] = 2.0;

    pp::vector root2 = newton(f2, x2, 1e-10);

    std::cout << "2D test: f(x,y) = (x^2-4, y^2-9)\n";
    std::cout << "root x = " << root2[0] << "\n";
    std::cout << "root y = " << root2[1] << "\n";
    std::cout << "expected approximately (2,3)\n";

    pp::vector froot2 = f2(root2);
    std::cout << "f0(root) = " << froot2[0] << "\n";
    std::cout << "f1(root) = " << froot2[1] << "\n";
}

// Opgave A3
// the extremums are where the gradient is 0
void run_task_A_rosenbrock()
{
    auto grad_rosenbrock = [](pp::vector v){
        double x = v[0];
        double y = v[1];

        pp::vector grad(2); // the gradient w respect to x and y

        grad[0] = 2.0*(x - 1.0) - 400.0*x*(y - x*x); // gradient w respect to x
        grad[1] = 200.0*(y - x*x); // gradient w respect to y

        return grad;
    };

    auto rosenbrock = [](double x, double y){
        return (1.0 - x)*(1.0 - x) + 100.0*(y - x*x)*(y - x*x);
    };

    pp::vector start(2);
    start[0] =  1.2;
    start[1] =  1.2;

    pp::vector root = newton( // use newton routine to solve gradient = 0
        grad_rosenbrock,
        start,
        1e-10,
        1e-3,
        1000
    );

    pp::vector grad_at_root = grad_rosenbrock(root);

    std::cout << "Rosenbrock minimum by solving grad f = 0\n";
    std::cout << "x = " << root[0] << "\n";
    std::cout << "y = " << root[1] << "\n";
    std::cout << "f(x,y) = " << rosenbrock(root[0], root[1]) << "\n";
    std::cout << "grad_x = " << grad_at_root[0] << "\n";
    std::cout << "grad_y = " << grad_at_root[1] << "\n";
}

// Opgave A4
// igen bruger gradienten til at finde minimum for funktionen
// fordi gradienten er 0 ved minimum
void run_task_A_himmelblau()
{
    auto grad_himmelblau = [](pp::vector v){
        double x = v[0];
        double y = v[1];

        double A = x*x + y - 11.0;
        double B = x + y*y - 7.0;
        // functionen er lig f(x, y) = A**2 + B**2

        pp::vector grad(2);

        grad[0] = 4.0*x*A + 2.0*B;
        grad[1] = 2.0*A + 4.0*y*B;

        return grad;
    };

    auto himmelblau = [](double x, double y){
        return (x*x + y - 11.0)*(x*x + y - 11.0)
             + (x + y*y - 7.0)*(x + y*y - 7.0);
    };

    std::vector<pp::vector> starts = {
        pp::vector{ 3.0,  2.0},
        pp::vector{-2.0,  3.0},
        pp::vector{-3.0, -3.0},
        pp::vector{ 3.0, -2.0}
    };

    std::cout << "Himmelblau minima by solving grad f = 0\n\n";

    for(std::size_t i = 0; i < starts.size(); i++){
        pp::vector root = newton(
            grad_himmelblau,
            starts[i],
            1e-10,
            1e-3,
            1000
        );

        pp::vector grad_at_root = grad_himmelblau(root);

        std::cout << "start " << i+1 << "\n";
        std::cout << "x = " << root[0] << "\n";
        std::cout << "y = " << root[1] << "\n";
        std::cout << "f(x,y) = " << himmelblau(root[0], root[1]) << "\n";
        std::cout << "grad_x = " << grad_at_root[0] << "\n";
        std::cout << "grad_y = " << grad_at_root[1] << "\n\n";
    }
}


// Opgave B1:
void run_task_B()
{
    const double rmin = 1e-3;
    const double rmax = 8.0;

    /*
     * M(E) integrates the Schrodinger equation for a trial energy E
     * and returns f_E(rmax).
     *
     * Newton will search for an energy satisfying M(E) = 0.
     */
    // From chatgpt:
    auto M = [rmin, rmax](pp::vector energy){ // M receives a vector energy and remembers rmin and rmax from the surrounding code
        double E = energy[0];

        // y[0] = f(r)
        // y[1] = f'(r)
        auto schrodinger = [E](double r, pp::vector y){
            pp::vector dydr(2);

            dydr[0] = y[1];
            dydr[1] = -2.0*(E + 1.0/r)*y[0];

            return dydr;
        };

        // Boundary conditions near r = 0:
        pp::vector yinit(2);
        yinit[0] = rmin - rmin*rmin;
        yinit[1] = 1.0 - 2.0*rmin;

        auto [rvalues, yvalues] = driver(
            schrodinger,
            rmin,
            rmax,
            yinit,
            0.01,   // initial ODE step size
            1e-6,   // absolute ODE accuracy
            1e-6    // relative ODE accuracy
        );

        pp::vector result(1);
        result[0] = yvalues.back()[0];

        return result;
    };

    // Initial guess for the ground-state energy
    pp::vector energy_guess(1);
    energy_guess[0] = -0.7;

    pp::vector root = newton(
        M,
        energy_guess,
        1e-6,
        1e-3,
        100
    );

    double E0 = root[0];

    std::cout << "Hydrogen ground state\n";
    std::cout << "Numerical energy = " << E0 << "\n";
    std::cout << "Exact energy     = " << -0.5 << "\n";
    std::cout << "Absolute error   = "
              << std::abs(E0 + 0.5) << "\n";
    std::cout << "M(E0)            = "
              << M(root)[0] << "\n";

    // Integrate again using the energy found by Newton.
    auto schrodinger = [E0](double r, pp::vector y){
        pp::vector dydr(2);

        dydr[0] = y[1];
        dydr[1] = -2.0*(E0 + 1.0/r)*y[0];

        return dydr;
    };

    pp::vector yinit(2);
    yinit[0] = rmin - rmin*rmin;
    yinit[1] = 1.0 - 2.0*rmin;

    auto [rvalues, yvalues] = driver(
        schrodinger,
        rmin,
        rmax,
        yinit,
        0.01,
        1e-6,
        1e-6
    );

    // Save numerical and exact wave functions for plotting.
    std::ofstream data("hydrogen.data");

    data << "# r numerical exact\n";

    for(std::size_t i = 0; i < rvalues.size(); i++){
        double r = rvalues[i];
        double numerical = yvalues[i][0];
        double exact = r*std::exp(-r);

        data << r << " "
             << numerical << " "
             << exact << "\n";
    }
}


// Opgave B2: pretty much the same as run_task_B
double hydrogen_energy(
    double rmin,
    double rmax,
    double ode_acc,
    double ode_eps
){
    auto M = [=](pp::vector energy){
        double E = energy[0];

        auto schrodinger = [E](double r, pp::vector y){
            pp::vector dydr(2);
            dydr[0] = y[1];
            dydr[1] = -2.0*(E + 1.0/r)*y[0];
            return dydr;
        };

        pp::vector yinit(2);
        yinit[0] = rmin - rmin*rmin;
        yinit[1] = 1.0 - 2.0*rmin;

        auto [rs, ys] = driver(
            schrodinger, rmin, rmax, yinit,
            0.01, ode_acc, ode_eps
        );

        pp::vector result(1);
        result[0] = ys.back()[0];
        return result;
    };

    pp::vector guess(1);
    guess[0] = -0.7;

    // Keep root accuracy tighter than the errors being investigated.
    pp::vector root = newton(M, guess, 1e-7, 1e-4, 100);

    return root[0];
}

void run_task_B2_convergence()
{
    std::ofstream rmax_data("convergence_rmax.data");
    for(double rmax : {3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 12.0}){
        std::cout << "Calculating rmax = " << rmax << std::endl;

        double E = hydrogen_energy(1e-3, rmax, 1e-7, 1e-7);
        double error = std::abs(E + 0.5);

        rmax_data << rmax << " " << error << "\n";
    }

    std::ofstream rmin_data("convergence_rmin.data");
    for(double rmin : {1e-1, 5e-2, 1e-2, 5e-3, 1e-3, 5e-4, 1e-4}){
        std::cout << "Calculating rmin = " << rmin << std::endl;

        double E = hydrogen_energy(rmin, 10.0, 1e-7, 1e-7);
        double error = std::abs(E + 0.5);

        rmin_data << rmin << " " << error << "\n";
    }

    std::ofstream acc_data("convergence_acc.data");
    for(double acc : {1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7}){
        std::cout << "Calculating acc = " << acc << std::endl;

        // eps = 0, so only acc is varied
        double E = hydrogen_energy(1e-3, 10.0, acc, 0.0);
        double error = std::abs(E + 0.5);

        acc_data << acc << " " << error << "\n";
    }

    std::ofstream eps_data("convergence_eps.data");
    for(double eps : {1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7}){
        std::cout << "Calculating eps = " << eps << std::endl;

        // acc = 0, so only eps is varied
        double E = hydrogen_energy(1e-3, 10.0, 0.0, eps);
        double error = std::abs(E + 0.5);

        eps_data << eps << " " << error << "\n";
    }

    std::cout << "Convergence calculations finished.\n";
}


int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage: ./main A_debug\n";
        return 1;
    }

    std::string task = argv[1];

    if(task == "A_debug"){
        run_task_A_debug();
    }
    else if(task == "A_rosenbrock"){
        run_task_A_rosenbrock();
    }
    else if(task == "A_himmelblau"){
        run_task_A_himmelblau();
    }
    else if(task == "B"){
        run_task_B();
    }
    else if(task == "B2"){
        run_task_B2_convergence();
    }
    else{
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;
}