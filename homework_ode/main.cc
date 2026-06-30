
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


void run_task_C()
{
    // First we define the function that will be passed
    // to the ODE solver. The ODE solver solves equations
    // of the form z' = f(t, z). We call the function
    // f for three_body in this case.
    // The function takes variable t which is the time
    // and z which contains all positions and velocities
    // of the three bodies. 
    auto three_body = [](double t, pp::vector z)
    {
        // the acceleration does not explicitly depend on
        // time so we just write this to avoid warnings.
        (void)t; 

        // The function z has 12 entries. The first
        // 6 are velocities and the last 6 are 
        // positions. 

        // Velocities
        double vx1 = z[0];
        double vy1 = z[1];

        double vx2 = z[2];
        double vy2 = z[3];

        double vx3 = z[4];
        double vy3 = z[5];

        // Positions
        double x1 = z[6];
        double y1 = z[7];

        double x2 = z[8];
        double y2 = z[9];

        double x3 = z[10];
        double y3 = z[11];

        // since z has 12 components, so does z'.
        // initialize vector with 12 entries that
        // stores the derivative of z. 
        pp::vector dzdt(12);

        // Helper for acceleration contribution from body j on body i.
        // The body being accelerated is at poisition (xi, yi).
        // The body attracting it is at position (xj, yj).
        auto acceleration = [](double xi, double yi, double xj, double yj) {
            double dx = xj - xi;
            double dy = yj - yi;
            double r = std::sqrt(dx*dx + dy*dy); // distance between the bodies

            // using the equation from the assignment
            // v_i' = sum (r_j - r_i)/|r_j - r_i|^3
            // we can write the equation of motion like
            // this:
            double ax = dx/(r*r*r);
            double ay = dy/(r*r*r);

            // For a pair of bodies, the acceleration
            // contribution is 
            // a = (r_j - r_i)/|r_j - r_i|^3
            // (we ignore G and m because the assignment
            // says to set them to 1.)
            // We can then make the vector a like this:
            pp::vector a(2);
            a[0] = ax;
            a[1] = ay;

            return a;
        };

        // Acceleration contributions:
        // Accelerations on body 1:
        pp::vector a12 = acceleration(x1, y1, x2, y2);
        pp::vector a13 = acceleration(x1, y1, x3, y3);

        // Accelerations on body 2:
        pp::vector a21 = acceleration(x2, y2, x1, y1);
        pp::vector a23 = acceleration(x2, y2, x3, y3);

        // Accelerations on body 3:
        pp::vector a31 = acceleration(x3, y3, x1, y1);
        pp::vector a32 = acceleration(x3, y3, x2, y2);

        // Velocity derivatives = acceleration
        dzdt[0] = a12[0] + a13[0]; // vx1'
        dzdt[1] = a12[1] + a13[1]; // vy1'

        dzdt[2] = a21[0] + a23[0]; // vx2'
        dzdt[3] = a21[1] + a23[1]; // vy2'

        dzdt[4] = a31[0] + a32[0]; // vx3'
        dzdt[5] = a31[1] + a32[1]; // vy3'

        // Position derivatives = velocity
        dzdt[6] = vx1;  // x1'
        dzdt[7] = vy1;  // y1'

        dzdt[8] = vx2;  // x2'
        dzdt[9] = vy2;  // y2'

        dzdt[10] = vx3; // x3'
        dzdt[11] = vy3; // y3'

        return dzdt;
        // Now the driver knows how the whole system
        // changes per time
    };

    // create the initial state vector 
    pp::vector zinit(12);

    // Standard figure-eight initial conditions
    zinit[6] = -0.97000436; // x1
    zinit[7] =  0.24308753; // y1

    zinit[8] =  0.97000436; // x2
    zinit[9] = -0.24308753; // y2

    zinit[10] = 0.0; // x3
    zinit[11] = 0.0; // y3

    zinit[0] = -0.466203685; // vx1
    zinit[1] = -0.43236573;  // vy1

    zinit[2] = -0.466203685; // vx2
    zinit[3] = -0.43236573;  // vy2

    zinit[4] = 0.93240737; // vx3
    zinit[5] = 0.86473146; // vy3

    double period = 6.3259;
    // integrating from 0 to period should make 
    // the bodies complete one full cycle

    // now we call the ODE driver. 
    auto [tlist, zlist] = driver(
        three_body,
        0.0,
        period,
        zinit,
        0.01,
        1e-5,
        1e-5
    );

    std::cout << "# t x1 y1 x2 y2 x3 y3\n";

    for(std::size_t i = 0; i < tlist.size(); i++){
        std::cout << tlist[i] << " "
                  << zlist[i][6] << " "
                  << zlist[i][7] << " "
                  << zlist[i][8] << " "
                  << zlist[i][9] << " "
                  << zlist[i][10] << " "
                  << zlist[i][11] << "\n";
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage: ./main A3, A4, or B1 or B2 or B3 or C\n";
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
    else if(task == "C"){
        run_task_C();
    }
    else{
        std::cerr << "Unknown task: " << task << "\n";
        std::cerr << "Use A3 or A4 or B1 or B2 or B3 or C\n";
        return 1;
    }

    return 0;
}