#include "interp.h"
#include <cassert>
#include <iostream>
#include <utility>


// Task A1:

// Funktion kopieret fra opgaven:
double linterp(const std::vector<double>& x, // x is the array of data points
               const std::vector<double>& y,
               double z){ // z is the single value where we want to interpolate
	int i=binsearch(x,z); 
  	double dx=x[i+1]-x[i]; // Beregner delta x_i (ligning 6 i kapitlet)
  	assert(dx>0); // Program crashes if this is not true (it is for debugging)
  	double dy=y[i+1]-y[i]; // Beregner delta y_i (ligning 6)
    double p = dy/dx; // ligning 6
  	return y[i]+p*(z-x[i]); // Returnerer s_i(x) = y_i + p_i(z - x_i)
                            // Ligning 5
  	}


// Funktion kopieret fra opgaven:
// Location of the index i of the interval containing z
// (such that x[i]<=;z<=x[i+1]). 
int binsearch(const std::vector<double>& x, double z)
	{/* locates the interval for z by bisection */ 
	assert( z>=x[0] && z<=x[x.size()-1] ); // Tjekker om z overhovedet findes
                                           // mellem den mindste x-værdi og den største
	int i=0, j=x.size()-1; // Starts with the whole array, from first x to last
	while(j-i>1){ // keeps going until the two indexes are next to each other
		int mid=(i+j)/2; // looks at middle index between i and j
		if(z>x[mid]) i=mid; else j=mid; // if z is to the right of the middle
                                        // point, move the left boundary up to
                                        // mid. Otherwise, move right boundary
                                        // down to mid. 
		}
	return i; // When the loop stops, i is the left endpoint of the interval
              // The interpolation formula needs the two points around z. 
              // We now know that the left point is (x[i], y[i]) and so the 
              // right point must be (x[i+1], y[i+1]) because we know that 
              // they are neighboring points and i is the left one. 
	}

// Task A2:

double linterpInteg(const std::vector<double>& x, const std::vector<double>& y, double z)
	{
	// From chatgpt:
	int i = binsearch(x, z); // Finder det venstre punkt (x[i], y[i]), så 
							// z befinder sig mellem dette punkt og (x[i+1], y[i+1])

	double integral = 0; // initialiserer integralet (ligning 8)

	// Beregner integralet op til i:
	for(int k = 0; k < i; k++){
		integral += y[k]*(x[k+1]-x[k])+((y[k+1]-y[k])*(x[k+1]-x[k]))/2; // Ligning 8
	}

	// Beregner integralet fra i til z:
	integral += y[i]*(z-x[i])+((y[i+1]-y[i])/(x[i+1]-x[i]))*((z-x[i])*(z-x[i]))/2;

	// Fra CHATGPT:
	// double dx = x[i+1] - x[i];
	// double dz = z - x[i];
	// integral += y[i]*dz + 0.5*(y[i+1]-y[i])/dx*dz*dz;
	return integral;
	}


// Task B1 - CHATGPT har oversat koden fra kapitlet fra C til C++
qspline::qspline(const std::vector<double>& xs,
                 const std::vector<double>& ys)
    : x(xs), y(ys), n(xs.size()), b(n-1), c(n-1)
{
    std::vector<double> h(n-1);
    std::vector<double> p(n-1);

    for(int i = 0; i < n-1; i++){
        h[i] = x[i+1] - x[i];
        p[i] = (y[i+1] - y[i]) / h[i]; // Beregner p ligesom tidligere
										// Ligning 6
    }

    c[0] = 0; // initialiserer c

    // recursion up
    for(int i = 0; i < n-2; i++){
        c[i+1] = (p[i+1] - p[i] - c[i]*h[i]) / h[i+1]; // Ligning 13
    }

    c[n-2] /= 2;

    // recursion down
    for(int i = n-3; i >= 0; i--){
        c[i] = (p[i+1] - p[i] - c[i+1]*h[i+1]) / h[i]; // Ligning 14
    } 

    for(int i = 0; i < n-1; i++){
        b[i] = p[i] - c[i]*h[i]; // Ligning 15
    }
}

double qspline::eval(double z) const
{
    int i = binsearch(x, z);
    double h = z - x[i];

    return y[i] + h*(b[i] + h*c[i]); // Ligning 15
}

double qspline::deriv(double z) const
{
    int i = binsearch(x, z);
    double h = z - x[i];

    return b[i] + 2*c[i]*h;
}

double qspline::integ(double z) const
{
    int i = binsearch(x, z);
    double integral = 0;

    for(int k = 0; k < i; k++){
        double h = x[k+1] - x[k];

        integral += y[k]*h
                  + b[k]*h*h/2
                  + c[k]*h*h*h/3;
    }

    double h = z - x[i];

    integral += y[i]*h
              + b[i]*h*h/2
              + c[i]*h*h*h/3;

    return integral;
}

std::function<double(double)> make_qspline(std::vector<double> x,
										   std::vector<double> y)
{
	int n = x.size();

	std::vector<double> b(n-1);
	std::vector<double> c(n-1);
	std::vector<double> h(n-1);
	std::vector<double> p(n-1);

	for(int i = 0; i < n-1; i++){
		h[i] = x[i+1] - x[i];
		p[i] = (y[i+1] - y[i]) / h[i];
	}

	c[0] = 0;

	// recursion up
	for(int i = 0; i < n-2; i++){
		c[i+1] = (p[i+1] - p[i] - c[i]*h[i]) / h[i+1];
	}

	c[n-2] /= 2;

	// recursion down
	for(int i = n-3; i >= 0; i--){
		c[i] = (p[i+1] - p[i] - c[i+1]*h[i+1]) / h[i];
	}

	for(int i = 0; i < n-1; i++){
		b[i] = p[i] - c[i]*h[i];
	}

	return [x = std::move(x), 
			y = std::move(y),
			b = std::move(b),
			c = std::move(c)]
			(double z)
	{
		int i = binsearch(x, z);
		double h = z - x[i];

		return y[i] + h*(b[i] + h*c[i]);
	};
}