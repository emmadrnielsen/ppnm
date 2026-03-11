# pragma once
# include "linalg.h"



// Opgave A.1: 
void timesJ(pp::matrix& A, std::size_t p, std::size_t q, double theta);
// Tells the complier there exists a function called timesJ
// with these inputs and this return type. The function itself
// is in the .cc file. 


// Opgave A.2: 
void Jtimes(pp::matrix& A, std::size_t p, std::size_t q, double theta);



// Opgave A.3: 
struct JacobiResult {
    // laver en struct som returnerer følgende
    pp::vector eigenvalues; 
    pp::matrix eigenvectors;
    int sweeps; 
    int rotations;
};

JacobiResult jacobi(pp::matrix A, double eps = 1e-12, int maxSweeps = 100);
// Function declaration: return_type function_name(parameters)
// There exists a function called jacobi that returns a JacobiResult


