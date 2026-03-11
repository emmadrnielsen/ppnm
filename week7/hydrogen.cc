#include "hydrogen.h"
#include <fstream>
#include <cmath>
#include <stdexcept>

pp::matrix buildHamiltonian(double rmax, double dr, pp::vector& rgrid) {
    // her er der bare indsat det som der står i opgaven. 
    // jeg har erstattet [] med () fordi det er sådan
    // matricer fungerer i min kode, men ellers er det
    // bare det helt samme. 
    int npoints = (int)(rmax/dr)-1;
    rgrid = pp::vector(npoints);
    for(int i=0;i<npoints;i++) rgrid[i]=dr*(i+1);
    pp::matrix H(npoints,npoints);
    for(int i=0;i<npoints-1;i++){
        H(i,i)  =-2*(-0.5/dr/dr);
        H(i,i+1)= 1*(-0.5/dr/dr);
        H(i+1,i)= 1*(-0.5/dr/dr);
    }
    H(npoints-1,npoints-1)=-2*(-0.5/dr/dr);
    for(int i=0;i<npoints;i++)H(i,i)+=-1/rgrid[i];

    return H;
}

void saveWavefunction(const std::string& filename,
                      const pp::vector& rgrid,
                      const pp::matrix& eigenvectors,
                      std::size_t stateIndex,
                      double dr) {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("could not open file");
    }

    double factor = 1.0 / std::sqrt(dr);

    for (std::size_t i = 0; i < rgrid.size(); ++i) {
        out << rgrid[i] << " " << factor * eigenvectors(i, stateIndex) << "\n";
    }
}