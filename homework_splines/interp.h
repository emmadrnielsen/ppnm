#ifndef INTERP_H    // Prevents the .h file being loaded more than once
#define INTERP_H    // in the same compilation (suggested by chatgpt)

#include <vector>
#include <functional>

// Task A1:
double linterp(const std::vector<double>& x,
               const std::vector<double>& y,
               double z);

int binsearch(const std::vector<double>& x, double z);

// Task A2:
double linterpInteg(const std::vector<double>& x, const std::vector<double>& y, double z);


// Task B1: 
struct qspline {
    std::vector<double> x, y;
    int n;
    std::vector<double> b, c;

    qspline(const std::vector<double>& xs,
            const std::vector<double>& ys);

    double eval(double z) const;
    double deriv(double z) const;
    double integ(double z) const;
}; // This is the c++ replacement for the line: typedef struct {int n; double *x, *y, *b, *c;} qspline;


// Task C:
std::function<double(double)> make_qspline(std::vector<double> x,
                                           std::vector<double> y); 





#endif



