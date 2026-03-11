#include<iostream>
#include<cmath>
#include<string>
#include<iomanip>
#include<vector>
#include <numbers>
#include<limits>
const double PI = std::numbers::pi;

double my_erf(double x){
    // single precision error function (Abramowitz and Stegun, from Wikipedia)
    if(x<0) return -my_erf(-x);
    std::vector<double> a {0.254829592,-0.284496736,1.421413741,-1.453152027,1.061405429};
    double t=1/(1+0.3275911*x);
    double sum=t*(a[0]+t*(a[1]+t*(a[2]+t*(a[3]+t*a[4]))));/* the right thing */
    return 1-sum*std::exp(-x*x);
    } 

double sgamma(double x){
    if(x<0)return PI/std::sin(PI*x)/sgamma(1-x);
    if(x<9)return sgamma(x+1)/x;
    double lnsgamma=std::log(2*PI)/2+(x-0.5)*std::log(x)-x
        +(1.0/12)/x-(1.0/360)/(x*x*x)+(1.0/1260)/(x*x*x*x*x);
    return std::exp(lnsgamma);
}

double lngamma(double x){
    if (x <= 0) return std::numeric_limits<double>::quiet_NaN();
    if (x < 9)  return lngamma(x+1) - std::log(x);
    return x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
}


int main(int argc, char** argv){
    std::string mode = (argc > 1) ? argv[1] : "erf";

    if(mode == "erf"){
        double xmin = -3, xmax = 3, dx = 0.1;

        for(double x = xmin; x <= xmax; x += dx){
            // 3 columns so gnuplot can plot both:
            // x   my_erf(x)   std::erf(x)
            std::cout << x << " " << my_erf(x) << " " << std::erf(x) << "\n";
        }
        return 0;
    }

    else if(mode == "gamma"){
        // curve data (stdout): x  sgamma(x)
        for(double x = -5.0; x <= 6.0; x += 0.001){
            std::cout << x << " " << sgamma(x) << "\n";
        }

        // factorial test points (stderr): x  n! where x=n+1
        double fact = 1.0;
        for(int n = 0; n <= 6; n++){
            if(n > 0) fact *= n;
            double X = n + 1;
            std::cerr << X << " " << fact << "\n";
        }
        return 0;
    }

    else if(mode == "lngamma"){
        for(double x = 0; x <= 10.0; x += 0.001){
            std::cout << x << " " << lngamma(x) << "\n";
        }

        double fact = 1.0;
        for(int n = 0; n <= 10; n++){
            if(n > 0) fact *= n;
            double X = n + 1;
            std::cerr << X << " " << std::log(fact) << "\n";
        }
        return 0;
    }
    else{
    std::cerr << "Usage: ./main [erf|gamma|lngamma]\n";
    return 1;
    }
}