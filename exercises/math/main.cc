#include<iostream>
#include<cstdio>
#include"hello.h"
#include"sfuns.h"
#include <cmath>
#include <numbers>
#include <iomanip>

int main() {
//Hello World exercise that is still there
//    hello();

//Exercise 1:
std::cout << "Exercise 1:" << "\n";
        double sqrt2 = std::sqrt(2.0);
        double two_1_5 = std::pow(2.0, 1.0/5.0);
        double e_pow_pi = std::exp(std::numbers::pi);
        double pi_pow_e = std::pow(std::numbers::pi, std::numbers::e);

        std::cout << "sqrt(2) = " << sqrt2 << "\n";
        std::cout << "2^(1/5) = " << two_1_5 << "\n";
        std::cout << "e^pi = " << e_pow_pi << "\n";
        std::cout << "pi^e = " << pi_pow_e << "\n";

//Exercise 2:
std::cout << "Exercise 2:" << "\n";
   double x = 1;
   double y = sfuns::fgamma(x);
   std::cout << "fgamma(1)=" << y << "\n";
   std::printf("fgamma(1)=%g\n",y);
   for(double x=1; x<=9; x+=1){
           std::cout << "fgamma{" << x << "}=" << sfuns::fgamma(x) << "\t"
                   << "tgamma(" << x << ")=" << std::tgamma(x) << "\t"
                   << "lngamma(" << x << ")=" << sfuns::lngamma(x) << "\n"; 

   }
    return 0;
}
