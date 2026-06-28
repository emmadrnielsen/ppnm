
#include "interp.h"
#include <iostream>
#include <vector>
#include <cmath>

// Chatgpt was used as help for all the parts but with prompts.
// So it is not necessarily a representation of how CHATGPT would solve
// the problems on its own. 
void run_task_A()
{
// Task A3:
    std::vector<double> x; // Initialiserer x og y som to tomme vektorer
    std::vector<double> y;

    // Table: x_i = 0, 0.5, 1, ..., 9
    for(double xi = 0; xi <= 9.0; xi += 0.5){
        x.push_back(xi); // tilføjer x- og y-værdier til vektorerne
        y.push_back(std::cos(xi));
    }

    // Output columns:
    // z, linear spline, integral of linear spline, exact cos(z), exact sin(z)
    std::cout << "# z linterp linterpInteg cos(z) sin(z)\n";

    for(double z = 0; z <= 9.0; z += 0.05){
        std::cout << z << " "
                  << linterp(x, y, z) << " "
                  << linterpInteg(x, y, z) << " "
                  << std::cos(z) << " " // the linear spline should follow cos(z)
                  << std::sin(z) << "\n"; // The integral of the linear spline should be close to sin(z)
                                          // because the integral of cos is sin. 
    }
}

// Task B
void run_task_B()
{
    std::vector<double> x;
    std::vector<double> y; // initialiserer x og y vektorer som før

    for(double xi = 0; xi <= 9.0; xi += 0.5){
        x.push_back(xi);
        y.push_back(std::cos(xi)); // laver de samme vektorer som før
    }

    qspline qs(x, y);

    std::cout << "# z qspline qspline_deriv qspline_integ cos(z) -sin(z) sin(z)\n";

    for(double z = 0; z <= 9.0; z+=0.05){
        std::cout << z << " "
                  << qs.eval(z) << " "
                  << qs.deriv(z) << " "
                  << qs.integ(z) << " "
                  << std::cos(z) << " " // follows original data
                  << -std::sin(z) << " " // the derivative should follow this
                  << std::sin(z) << "\n"; // the integral from 0 to z should follow
    }
}


// Hint til task B:
void debug_qspline()
{
    std::vector<double> x = {1, 2, 3, 4, 5};

    std::vector<double> y_const = {1, 1, 1, 1, 1}; // This is the first row in the table in the hint
    std::vector<double> y_linear = {1, 2, 3, 4, 5}; // second line
    std::vector<double> y_square = {1, 4, 9, 16, 25}; // third row

    qspline s_const(x, y_const);
    qspline s_linear(x, y_linear);
    qspline s_square(x, y_square);

    auto print_bc = [](const qspline& s, const std::string& name){
        std::cout << name << "\n";

        std::cout << "b: ";
        for(double bi : s.b) std::cout << bi << " ";
        std::cout << "\n";

        std::cout << "c: ";
        for(double ci : s.c) std::cout << ci << " ";
        std::cout << "\n\n";
    };

    // Manually calculated expected coefficients:
    //
    // y = 1:
    // p = {0, 0, 0, 0}
    // Expected b = {0, 0, 0, 0}
    // Expected c = {0, 0, 0, 0}
    //
    // y = x:
    // p = {1, 1, 1, 1}
    // Expected b = {1, 1, 1, 1}
    // Expected c = {0, 0, 0, 0}
    //
    // y = x^2:
    // p = {3, 5, 7, 9}
    // Expected b = {2, 4, 6, 8}
    // Expected c = {1, 1, 1, 1}
    //
    // These values can be compared with the program output below.

    print_bc(s_const, "Test y = 1");
    print_bc(s_linear, "Test y = x");
    print_bc(s_square, "Test y = x^2");
}

// Task C
void run_task_C()
{
    std::vector<double> x;
    std::vector<double> y;

    for(double xi = 0; xi <= 9.0; xi += 0.5){
        x.push_back(xi);
        y.push_back(std::cos(xi));
    }

    auto f = make_qspline(x, y);

    std::cout << "# z functional_qspline cos(z)\n";

    for(double z = 0; z <= 9.0; z += 0.05){
        std::cout << z << " "
                  << f(z) << " "
                  << std::cos(z) << "\n";
    }
}


int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage: ./main A or ./main B or ./main debug\n";
        return 1;
    }

    std::string task = argv[1];

    if(task == "A"){
        run_task_A();
    }
    else if(task == "B"){
        run_task_B();
    }
    else if(task == "debug"){
        debug_qspline();
    }
    else if(task == "C"){
        run_task_C();
    }
    else{
        std::cerr << "Unknown task: " << task << "\n";
        std::cerr << "Use A or B\n";
        return 1;
    }
}