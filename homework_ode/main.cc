
#include "ode.h"
#include <iostream>
#include <cmath>

void run_task_A3()
{
    // Debug/test: u'' = -u
    // Rewrite as:
    // y0 = u
    // y1 = u'
    // y0' = y1
    // y1' = -y0

    auto harmonic = [](double x, pp::vector y)
    {
        (void)x;
        pp::vector dydx(2);

        dydx[0] = y[1];   // y0' = y1
        dydx[1] = -y[0];  // y1' = -y0

        return dydx;
    };

    pp::vector yinit(2);
    yinit[0] = 1.0; // u(0)
    yinit[1] = 0.0; // u'(0)

    double a = 0.0;
    double b = 10.0;

    auto [xlist, ylist] = driver(
        harmonic,
        a,
        b,
        yinit,
        0.125,  // initial step size
        0.01,   // absolute accuracy
        0.01    // relative accuracy
    );

    std::cout << "# x u_numeric u_exact uprime_numeric uprime_exact\n";

    for(std::size_t i = 0; i < xlist.size(); i++){
        double x = xlist[i];
        pp::vector y = ylist[i];

        std::cout << x << " "
                  << y[0] << " "
                  << std::cos(x) << " "
                  << y[1] << " "
                  << -std::sin(x) << "\n";
    }

}

void run_task_A4()
{
    // SciPy odeint example: damped pendulum
    // theta' = omega
    // omega' = -b*omega - c*sin(theta)

    double b_friction = 0.25;
    double c_gravity = 5.0;
    const double pi = std::acos(-1.0);

    auto pendulum = [b_friction, c_gravity](double t, pp::vector y)
    {
        (void)t;

        pp::vector dydt(2);

        double theta = y[0];
        double omega = y[1];

        dydt[0] = omega;
        dydt[1] = -b_friction*omega - c_gravity*std::sin(theta);

        return dydt;
    };

    pp::vector yinit(2);
    yinit[0] = pi - 0.1; // theta(0)
    yinit[1] = 0.0;      // omega(0)

    auto [tlist, ylist] = driver(
        pendulum,
        0.0,
        10.0,
        yinit,
        0.125, // initial step size
        0.01, // absolute accuracy
        0.01 // relative accuracy
    );

    std::cout << "# t theta omega\n";

    for(std::size_t i = 0; i < tlist.size(); i++){
        std::cout << tlist[i] << " "
                  << ylist[i][0] << " "
                  << ylist[i][1] << "\n";
    }
}

void run_task_B1()
{
    double epsilon = 0.0;

    auto orbit = [epsilon](double phi, pp::vector y)
    {
        (void)phi;

        pp::vector dydphi(2);

        double u = y[0];
        double uprime = y[1];

        dydphi[0] = uprime;
        dydphi[1] = 1.0 - u + epsilon*u*u;

        return dydphi;
    };

    pp::vector yinit(2);
    yinit[0] = 1.0; // u(0)
    yinit[1] = 0.0; // u'(0)

    double a = 0.0;
    double b = 10.0 * 2.0 * std::acos(-1.0); // 10 rotations

    auto [philist, ylist] = driver(
        orbit,
        a,
        b,
        yinit,
        0.125,
        0.01,
        0.01
    );

    std::cout << "# phi u uprime x y\n";

    for(std::size_t i = 0; i < philist.size(); i++){
        double phi = philist[i];
        double u = ylist[i][0];

        double r = 1.0/u;
        double x = r*std::cos(phi);
        double y = r*std::sin(phi);

        std::cout << phi << " "
                  << ylist[i][0] << " "
                  << ylist[i][1] << " "
                  << x << " "
                  << y << "\n";
    }
}

void run_task_B2()
{
    double epsilon = 0.0;

    auto orbit = [epsilon](double phi, pp::vector y)
    {
        (void)phi;

        pp::vector dydphi(2);

        double u = y[0];
        double uprime = y[1];

        dydphi[0] = uprime;
        dydphi[1] = 1.0 - u + epsilon*u*u;

        return dydphi;
    };

    pp::vector yinit(2);
    yinit[0] = 1.0;   // u(0)
    yinit[1] = -0.5;  // u'(0)

    double a = 0.0;
    double b = 10.0 * 2.0 * std::acos(-1.0); // 10 rotations

    auto [philist, ylist] = driver(
        orbit,
        a,
        b,
        yinit,
        0.02,   // smaller initial step for smoother orbit
        0.01,
        0.01
    );

    std::cout << "# phi u uprime x y\n";

    for(std::size_t i = 0; i < philist.size(); i++){
        double phi = philist[i];
        double u = ylist[i][0];

        double r = 1.0/u;
        double x = r*std::cos(phi);
        double y = r*std::sin(phi);

        std::cout << phi << " "
                  << ylist[i][0] << " "
                  << ylist[i][1] << " "
                  << x << " "
                  << y << "\n";
    }
}

void run_task_B3()
{
    double epsilon = 0.01;

    auto orbit = [epsilon](double phi, pp::vector y)
    {
        (void)phi;

        pp::vector dydphi(2);

        double u = y[0];
        double uprime = y[1];

        dydphi[0] = uprime;
        dydphi[1] = 1.0 - u + epsilon*u*u;

        return dydphi;
    };

    pp::vector yinit(2);
    yinit[0] = 1.0;   // u(0)
    yinit[1] = -0.5;  // u'(0)

    double a = 0.0;
    double b = 20.0 * 2.0 * std::acos(-1.0); // 20 rotations

    auto [philist, ylist] = driver(
        orbit,
        a,
        b,
        yinit,
        0.02,
        0.01,
        0.01
    );

    std::cout << "# phi u uprime x y\n";

    for(std::size_t i = 0; i < philist.size(); i++){
        double phi = philist[i];
        double u = ylist[i][0];

        double r = 1.0/u;
        double x = r*std::cos(phi);
        double y = r*std::sin(phi);

        std::cout << phi << " "
                  << ylist[i][0] << " "
                  << ylist[i][1] << " "
                  << x << " "
                  << y << "\n";
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage: ./main A3, A4, or B1 or B2 or B3\n";
        return 1;
    }

    std::string task = argv[1];

    if(task == "A3"){
        run_task_A3();
    }
    else if(task == "A4"){
        run_task_A4();
    }
    else if(task == "B1"){
        run_task_B1();
    }
    else if(task == "B2"){
        run_task_B2();
    }
    else if(task == "B3"){
        run_task_B3();
    }
    else{
        std::cerr << "Unknown task: " << task << "\n";
        std::cerr << "Use A3 or A4\n";
        return 1;
    }

    return 0;
}