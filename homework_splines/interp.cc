#include "interp.h"
#include <cassert>

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

    