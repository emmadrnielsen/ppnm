#pragma once
#include "linalg.h"
#include <string>

pp::matrix buildHamiltonian(double rmax, double dr, pp::vector& rgrid);

void saveWavefunction(const std::string& filename,
                      const pp::vector& rgrid,
                      const pp::matrix& eigenvectors,
                      std::size_t stateIndex,
                      double dr);