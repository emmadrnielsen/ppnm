#include<iostream>
#include<cstdio>
#include<vector>
#include<limits>
#include<cmath>
#include<iomanip>
#include "approx.h"


int main(){
    //Opgave 1:
    std::cout << "\n Opgave 1 \n";

    float f=1.0f; 
    while(1.0f + f != 1.0f) {f /= 2.0f;} 
    f *= 2.0f;

    double d=1.0; 
    while(1.0 + d != 1.0) {d /= 2.0;} 
    d *= 2.0;

    long double l=1.0L; 
    while(1.0L + l != 1.0L) {l/=2.0L;} 
    l *= 2.0L;

    std::printf("float eps = %.10g\n",f);
    std::printf("double eps = %.17g\n",d);
    std::printf("long double eps = %.21Lg\n\n",l);

    std::cout << "float eps system = " << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << "double eps system = " << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << "long double eps system = " << std::numeric_limits<long double>::epsilon() << "\n\n";

    std::cout << "pow(2, -52)= " << std::pow(2, -52) << "\n";
    std::cout << "po2(2, -23)= " << std::pow(2, -23) << "\n";

    //Opgave 2:
    std::cout << "\n Opgave 2 \n";

    double epsilon=std::pow(2,-52);
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;

    std::cout << "epsilon=std::pow(2,-52) \n";
    std::cout << "tiny=epsilon/2 \n";
    std::cout << "a=1+tiny+tiny \n";
    std::cout << "b=tiny+tiny+1 \n";

    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "tiny =        " << tiny << "\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";

    //Opgave 3:
    std::cout << " \n Opgave 3 \n";

    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;

    std::cout << "d1==d2? " << (d1==d2 ? "true":"false") << "\n"; 

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1=" << d1 << "\n";
    std::cout << "d2=" << d2 << "\n";

    std::cout << std::boolalpha;
    std::cout << "approx(d1,d2)? " << approx(d1, d2) << "\n";

}