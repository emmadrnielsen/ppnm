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

    // For printing more than 1 energy state:
    // for (std::size_t i = 0; i < e.size(); ++i) {
    //     std::cout << "e[" << i << "] = " << e[i] << "\n";
    // }

    // For printing only the ground state energy:
    std::cout << "e[0] = " << e[0] << "\n";
    

    

    // if (argc != 3) {
    //     std::cerr << "Usage: ./main rmax dr\n";
    //     return 1;
    // }

    // double rmax = std::atof(argv[1]);
    // double dr   = std::atof(argv[2]);

    // try {
    //     pp::vector rgrid;
    //     pp::matrix H = buildHydrogenHamiltonian(rmax, dr, rgrid);

    //     JacobiResult result = jacobi(H);

    //     std::cout << std::setprecision(12);
    //     std::cout << "Grid points: " << rgrid.size() << "\n";
    //     std::cout << "Sweeps: " << result.sweeps << "\n";
    //     std::cout << "Rotations: " << result.rotations << "\n\n";

    //     std::cout << "Lowest eigenvalues:\n";
    //     for (std::size_t i = 0; i < 5 && i < result.eigenvalues.size(); ++i) {
    //         std::cout << "E[" << i << "] = " << result.eigenvalues[i] << "\n";
    //     }

    //     saveWavefunction("wf0.dat", rgrid, result.eigenvectors, 0, dr);
    //     if (result.eigenvalues.size() > 1) saveWavefunction("wf1.dat", rgrid, result.eigenvectors, 1, dr);
    //     if (result.eigenvalues.size() > 2) saveWavefunction("wf2.dat", rgrid, result.eigenvectors, 2, dr);

    // } catch (const std::exception& e) {
    //     std::cerr << "Error: " << e.what() << "\n";
    //     return 1;
    // }

    return 0;
}