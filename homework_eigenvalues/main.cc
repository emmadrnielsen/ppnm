#include "jacobi.h"
#include "hydrogen.h"
#include "linalg.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdlib>

int main(int argc, char** argv) {

    // // Test for opgave A (lavet af chat)
    // pp::matrix A(3,3,0.0);

    // A(0,0) = 4;  A(0,1) = 1;  A(0,2) = 1;
    // A(1,0) = 1;  A(1,1) = 3;  A(1,2) = 0;
    // A(2,0) = 1;  A(2,1) = 0;  A(2,2) = 2;

    // // print A
    // std::cout << "A = \n" << A << "\n";

    // // run Jacobi algorithm
    // JacobiResult result = jacobi(A);

    // // define V and V^T as the matrix of eigenvectors and its transposed
    // pp::matrix V = result.eigenvectors;
    // pp::matrix VT = V.transpose();

    // // compute V^T A V
    // pp::matrix Dtest = VT * A * V;
    // std::cout << "V^T A V = \n" << Dtest << "\n";

    // // compute V D V^T 
    // pp::matrix Atest = V * Dtest * VT;
    // std::cout << "V D V^T = \n" << Atest << "\n";

    // // compute V^T V
    // std::cout << "V^T V = \n" << VT * V << "\n";

    // //compute V V^T
    // std::cout << "V V^T = \n" << V * VT << "\n";



    // OPGAVE B:
    // Starter med at gøre så prgrammet kan køres på følgende måde:
    // ./main -rmax 10 -dr 0.3
    // for loopet er der så man også kan bytte rundt på rækkefølgen

    double rmax = 0, dr = 0;

    for(int i = 1; i < argc; i++){
        if(std::string(argv[i]) == "-rmax") rmax = std::atof(argv[i+1]);
        if(std::string(argv[i]) == "-dr")   dr   = std::atof(argv[i+1]);
    }

    // Nu vil jeg så gerne lave den næste del:
    // "Diagonalize the matrix using your 
    // Jacobi routine and obtain the 
    // eigenvalues and eigenvectors."

    pp::vector r;
    pp::matrix H = buildHamiltonian(rmax, dr, r);

    JacobiResult result = jacobi(H);

    pp::vector e = result.eigenvalues;
    pp::matrix V = result.eigenvectors;

    //Take eigenvector from matrix V, convert it into the physical
    //radial wavefunction f(r), and write it to a file
    saveWavefunction("wf0.txt", r, V, 0, dr);
    saveWavefunction("wf1.txt", r, V, 1, dr);
    saveWavefunction("wf2.txt", r, V, 2, dr);

    // printing the corresponding energies:
    std::cout << "e[0] = " << e[0] << "\n";
    std::cout << "e[1] = " << e[1] << "\n";
    std::cout << "e[2] = " << e[2] << "\n";



    // For printing more than 1 energy state:
    // for (std::size_t i = 0; i < e.size(); ++i) {
    //     std::cout << "e[" << i << "] = " << e[i] << "\n";
    // }

    // For printing only the ground state energy:
    std::cout << "e[0] = " << e[0] << "\n";

    return 0;
}