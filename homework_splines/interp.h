#ifndef INTERP_H    // Prevents the .h file being loaded more than once
#define INTERP_H    // in the same compilation (suggested by chatgpt)

#include <vector>

double linterp(const std::vector<double>& x,
               const std::vector<double>& y,
               double z);

int binsearch(const std::vector<double>& x, double z);

#endif

