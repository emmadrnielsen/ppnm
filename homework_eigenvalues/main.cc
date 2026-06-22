#include "jacobi.h"
#include "hydrogen.h"
#include "linalg.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdlib>
#include <random>
#include <fstream>
#include <chrono>

void run_task_A3(){
    // Test for opgave A (lavet af chat)

    std::cout << "First a simple test, with predefined matrix\n\n";
    pp::matrix A(3,3,0.0);

    A(0,0) = 4;  A(0,1) = 1;  A(0,2) = 1;
    A(1,0) = 1;  A(1,1) = 3;  A(1,2) = 0;
    A(2,0) = 1;  A(2,1) = 0;  A(2,2) = 2;

    // print A
    std::cout << "A = \n" << A << "\n";

    // run Jacobi algorithm
    JacobiResult result = jacobi(A);

    // define V and V^T as the matrix of eigenvectors and its transposed
    pp::matrix V = result.eigenvectors;
    pp::matrix VT = V.transpose();

    // compute V^T A V
    pp::matrix Dtest = VT * A * V;
    std::cout << "V^T A V = \n" << Dtest << "\n";

    // compute V D V^T 
    pp::matrix Atest = V * Dtest * VT;
    std::cout << "V D V^T = \n" << Atest << "\n";

    // compute V^T V
    std::cout << "V^T V = \n" << VT * V << "\n";

    //compute V V^T
    std::cout << "V V^T = \n" << V * VT << "\n\n";

    std::cout << "Now a test with a random symmetric matrix B\n\n";
    const std::size_t n = 3;
    pp::matrix B(n, n, 0.0);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    // Generate a random symmetric matrix
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i; j < n; ++j) {
            const double random_value = distribution(generator);

            B(i, j) = random_value;
            B(j, i) = random_value;
        }
    }

    std::cout << "Random symmetrix matrix B: \n\n";
    std::cout << "B = \n" << B << "\n";

    JacobiResult result_B = jacobi(B);

    pp::matrix V_B = result_B.eigenvectors;
    pp::matrix VT_B = V_B.transpose();

    pp::matrix Dtest_B = VT_B * B * V_B;
    std::cout << "V^T B V =\n" << Dtest_B << "\n";

    pp::matrix Btest = V_B * Dtest_B * VT_B;
    std::cout << "V D V^T =\n" << Btest << "\n";

    std::cout << "V^T V =\n" << VT_B * V_B << "\n";
    std::cout << "V V^T =\n" << V_B * VT_B << "\n";

}

void run_task_B(int argc, char** argv){
    // OPGAVE B:
    // Starter med at gøre så prgrammet kan køres på følgende måde:
    // ./main -rmax 30 -dr 0.2
    // for loopet er der så man også kan bytte rundt på rækkefølgen

    double rmax = 0, dr = 0; // initializing values

    // Reading the command line:
    // Start at 2 because argv[1] contains "B".
    for (int i = 2; i < argc; ++i) {
        const std::string argument = argv[i];

        // when -rmax is read, the following argument is converted to a number
        if (argument == "-rmax" && i + 1 < argc) { 
            rmax = std::atof(argv[++i]);
        }
        // when -dr is read, the following argument is converted to a number
        else if (argument == "-dr" && i + 1 < argc) {
            dr = std::atof(argv[++i]);
        }
    }

    // Preventing invalid grids:
    // 1. rmax must be positive
    // 2. dr must be positive
    // 3. rmax must be larger than dr.
    if (rmax <= 0.0 || dr <= 0.0 || rmax <= dr) {
        std::cerr << "Use positive values with rmax > dr.\n"
                  << "Example: ./main B -rmax 30 -dr 0.2\n";
        return;
    }

    // Nu vil jeg så gerne lave den næste del:
    // "Diagonalize the matrix using your 
    // Jacobi routine and obtain the 
    // eigenvalues and eigenvectors."

    pp::vector r;
    pp::matrix H = buildHamiltonian(rmax, dr, r);

    // Diagonalizing the Hamiltonian:
    JacobiResult result = jacobi(H);

    pp::vector e = result.eigenvalues; // calculated energies
    pp::matrix V = result.eigenvectors; // corresponding eigenvectors 

    //Take eigenvector from matrix V, convert it into the physical
    //radial wavefunction f(r), and write it to a file
    // the conversion performed by saveWavefunction() is f_k(r_i) = V(i,k) / sqrt(dr)
    saveWavefunction("wf0.txt", r, V, 0, dr); // ground state
    saveWavefunction("wf1.txt", r, V, 1, dr); // first excited s-state
    saveWavefunction("wf2.txt", r, V, 2, dr); // second excited s-state

    // printing the corresponding energies:
    // std::cout << "e[0] = " << e[0] << "\n";
    // std::cout << "e[1] = " << e[1] << "\n";
    // std::cout << "e[2] = " << e[2] << "\n";

    // printing the corresponding energies and comparing with exact results:
    std::cout << "State   Numerical energy   Exact energy\n";

    for (std::size_t i = 0; i < 3; ++i) {
        const double n = static_cast<double>(i + 1);
        const double exact_energy = -1.0 / (2.0 * n * n);

        std::cout << i + 1
                << "       " << e[i]
                << "             " << exact_energy
                << "\n";
    }



    // For printing more than 1 energy state:
    // for (std::size_t i = 0; i < e.size(); ++i) {
    //     std::cout << "e[" << i << "] = " << e[i] << "\n";
    // }

    // For printing only the ground state energy:
    // std::cout << "e[0] = " << e[0] << "\n";
}

// Made by chatgpt:
void run_task_B_convergence()
{
    std::cout << "Calculating convergence with respect to dr...\n";

    std::ofstream dr_file("dr_data.txt");

    if (!dr_file) {
        std::cerr << "Could not create dr_data.txt\n";
        return;
    }

    // Keep rmax fixed and vary dr.
    const double fixed_rmax = 10.0;

    // Testing different dr values
    for (double dr : {0.5, 0.3, 0.2, 0.1, 0.05}) {
        pp::vector r;
        pp::matrix H = buildHamiltonian(fixed_rmax, dr, r);
        JacobiResult result = jacobi(H);

        const double ground_state_energy = result.eigenvalues[0];

        dr_file << dr << " " << ground_state_energy << "\n";

        std::cout << "dr = " << dr
                  << ", e0 = " << ground_state_energy << "\n";
    }

    dr_file.close();

    std::cout << "\nCalculating convergence with respect to rmax...\n";

    std::ofstream rmax_file("rmax_data.txt");

    if (!rmax_file) {
        std::cerr << "Could not create rmax_data.txt\n";
        return;
    }

    // Keep dr fixed and vary rmax.
    const double fixed_dr = 0.1;

    // Testing different rmax values 
    for (double rmax : {5.0, 6.0, 8.0, 10.0, 12.0, 15.0}) {
        pp::vector r;
        pp::matrix H = buildHamiltonian(rmax, fixed_dr, r);
        JacobiResult result = jacobi(H);

        const double ground_state_energy = result.eigenvalues[0];

        rmax_file << rmax << " " << ground_state_energy << "\n";

        std::cout << "rmax = " << rmax
                  << ", e0 = " << ground_state_energy << "\n";
    }

    rmax_file.close();

    std::cout << "\nCreated dr_data.txt and rmax_data.txt\n";
}


// The chosen C task is the "Check that the number of operations
// for matrix diagonalization scales as O(n^3)"
void run_task_C(std::size_t N)
{
    // create an NxN matrix
    pp::matrix A(N, N, 0.0);

    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    // Generate a random symmetric NxN matrix.
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = i; j < N; ++j) {
            const double value = distribution(generator);
            
            // The same value is placed at the mirrored
            // positions (i, j) and (j, i)
            A(i, j) = value;
            A(j, i) = value;
        }
    }

    // Only measure the diagonalization itself.
    const auto start = std::chrono::high_resolution_clock::now();

    JacobiResult result = jacobi(A);

    const auto stop = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> elapsed = stop - start;

    // Two columns: matrix size and elapsed time.
    std::cout << N << " " << elapsed.count() << "\n";

    // Checks whether the returned eigenvalue vector is empty
    if (result.eigenvalues.size() == 0) {
        std::cerr << "Diagonalization failed\n";
    }
}



int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage:\n"
                << "  ./main A\n"
                << "  ./main B -rmax 30 -dr 0.2\n"
                << "  ./main Bconvergence\n"
                << "  ./main C N\n";
        return 1;
    }

    const std::string task = argv[1];

    if (task == "A") {
        run_task_A3();
    }
    else if (task == "B") {
        run_task_B(argc, argv);
    }
    else if(task == "Bconvergence"){
        run_task_B_convergence();
    }
    else if (task == "C") {
        if (argc < 3) {
            std::cerr << "Usage: ./main C N\n";
            return 1;
        }

        const int N = std::atoi(argv[2]);

        if (N <= 0) {
            std::cerr << "N must be positive\n";
            return 1;
        }

        run_task_C(static_cast<std::size_t>(N));
    }
    else {
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;


}