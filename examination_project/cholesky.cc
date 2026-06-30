#include "cholesky.h"
#include <stdexcept>
#include <cmath>


namespace pp {

cholesky::cholesky(const matrix& A)
{
    // First we check that A is a square matrix:
    if (A.rows() != A.cols()) { 
        throw std::invalid_argument(
            "Cholesky decomposition requires a square matrix"
        );
    }

    // Then we check that A is symmetric:
    const std::size_t n = A.rows();
    const double tolerance = 1e-12; 
    // chatgpt suggests to use 1e-12 instead of 0 because
    // floating-point calculations can produce tiny
    // rounding differences. 
        
    // Basically we check that A(i, j) = A(j, i)
    for (std::size_t i = 0; i < n; ++i) {
        // j starts at i + 1 because there is no need
        // to check the diagonals (A(i, i) is always
        // going to be equal to A(i, i)).
        for (std::size_t j = i + 1; j < n; ++j) {
            if (std::abs(A(i, j) - A(j, i)) > tolerance) {
                throw std::invalid_argument(
                    "Cholesky decomposition requires a symmetric matrix"
                );
            }
        }
    }

    // Since the L matrix is of the same size as A, we can
    // read the number of rows (or columns) in A and use that
    // to create a nxn matrix for L
    L = matrix(n, n, 0.0); // The matrix is initialized as a zero matrix

    // The following code is from wikipedia (with small modifications)
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j <= i; ++j) {
            double sum = 0.0; // float becomes double to match pp::matrix

            for (std::size_t k = 0; k < j; ++k) {
                sum += L(i, k) * L(j, k); // my pp::matrix class uses 
                                          // parentheses instead of []
            }

            if (i == j) {
                const double diagonal = A(i, i) - sum;

                // Checks if matrix is positive-definite (test by chatgpt)
                if (diagonal <= 0.0) {
                    throw std::invalid_argument(
                        "Matrix is not positive-definite"
                    );
                }

                L(i, j) = std::sqrt(diagonal);
            } else {
                L(i, j) = (A(i, j) - sum) / L(j, j);
            }
        }
    }
}

    vector cholesky::solve(const vector& b) const
    {
        const std::size_t n = L.rows();

        // checks that b in Ax = b has the length n
        if (b.size() != n) {
            throw std::invalid_argument("dimension mismatch in Cholesky solve");
        }

        vector y(n, 0.0); // initializes vector y, which
                          // is going to be L^Tx, so we can
                          // rewrite Ax = LL^Tx = Ly = b

        // Forward substitution: solve L y = b
        for (std::size_t i = 0; i < n; ++i) {
            double sum = b[i];

            for (std::size_t k = 0; k < i; ++k) {
                sum -= L(i, k) * y[k]; 
                // we subtract what we already know from the equations above.
                // like fx the first equation is L(0, 0)y0 = b0
                // then for the next line which is L(1, 0)y0 + L(1, 1)y1 = b1
                // what we want to find out is y1 and we already know y0 from
                // solving the first equation, so we can say b1 - L(1, 0)y0
                // then we are left with sum = L(1, 1)y1. 
            }
            // Continuing the explanation using the example above
            // we can now divide sum by L(1, 1) to find y1. The same
            // goes for all the other rows. 
            y[i] = sum / L(i, i);
        }

        // Now we want to solve L^Tx = y. 
        // Since L^T is upper triangular, we start from the last row
        // and move upwards.
        vector x(n, 0.0);

        // Back substitution: solve L^T x = y
        // the code does the same as the forward substitution
        // one except it loops backward. 
        for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
            double sum = y[i];

            for (std::size_t k = i + 1; k < n; ++k) {
                sum -= L(k, i) * x[k];
            }

            x[i] = sum / L(i, i);
        }

        return x;
    }

    // this code does basically the exact same thing
    // as the determinant solver for QR decomposition
    // because R is also a triangular matrix. The only
    // difference is that the determinant in this case
    // is the square of the diagonal elements. 
    double cholesky::det() const
    {
        const std::size_t n = L.rows();

        double determinant = 1.0;

        for (std::size_t i = 0; i < n; ++i) {
            determinant *= L(i, i) * L(i, i);
        }

        return determinant;
    }


    matrix cholesky::inverse() const
    {
        const std::size_t n = L.rows();

        // initializing the inverse A^-1
        matrix inv(n, n, 0.0); 

        // solving Az_j = e_j for each column
        for (std::size_t j = 0; j < n; ++j) {
            vector e(n, 0.0);
            e[j] = 1.0;

            vector x = solve(e);

            inv.col(j) = x;
        }

        return inv;
    }


} // namespace pp