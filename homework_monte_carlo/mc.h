#ifndef MC_H
#define MC_H

#include <vector>
#include <functional>
#include <tuple>

// Opgave A2:
class lcg {
private:
    unsigned int seed;
    unsigned int a;
    unsigned int c;
    unsigned int m;

public:
    lcg(unsigned int seed0,
        unsigned int a0 = 1664525,
        unsigned int c0 = 1013904223,
        unsigned int m0 = 4294967295u);

    double operator()();
};


// Opgave A1: defineret ligesom i opgavebeskrivelsen
std::tuple<double,double> plainmc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N, 
    std::function<double()> random_double

); // funktionen returnerer to tal; 
    // integral estimate and error estimate


// Opgave B1:
double corput(int n, int base); // s. 5 i lecture notes

std::vector<int> prime_numbers(int n); // s. 6 i lecture notes

std::vector<double> halton(int n, int dim); // s. 6 i lecture notes

std::tuple<double,double> quasimc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N
);

// Opgave C:
std::tuple<double,double> stratifiedmc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N,
    std::function<double()> random_double,
    int nmin = 64
); // this returns integral estimate, error estimate

#endif