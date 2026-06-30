#ifndef MC_H
#define MC_H

#include <vector>
#include <functional>
#include <tuple>
#include <cstdint>

// Opgave A2:
class lcg {
private:
    std::uint64_t seed;
    std::uint64_t a;
    std::uint64_t c;
    std::uint64_t m;

public:
    lcg(std::uint64_t seed0,
        std::uint64_t a0 = 1664525,
        std::uint64_t c0 = 1013904223,
        std::uint64_t m0 = (1ULL << 32));

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