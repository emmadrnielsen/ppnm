#pragma once
#include "linalg.h"


namespace pp { 

struct cholesky { 
    matrix L; // Stores the result of A = LL^T

    explicit cholesky(const matrix& A); 
    // Declares the constructor that will perform the decomposition

    vector solve(const vector& b) const;
    double det() const;
    matrix inverse() const;
};

} // namespace pp

