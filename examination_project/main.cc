#include "cholesky.h"

#include <cmath>
#include <iostream>
#include <random>

void run_task_1()
{
    // size of matrix is chosen to be 4.
    const std::size_t n = 4;
    const double lambda = 1.0;
    const double tolerance = 1e-10;

    // 1. Generate a random n x n matrix B.
    pp::matrix B(n, n, 0.0);

    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            B(i, j) = distribution(generator);
        }
    }

    // 2. Construct A = B^T B + lambda I.
    pp::matrix A = B.transpose() * B;

    for (std::size_t i = 0; i < n; ++i) {
        A(i, i) += lambda;
    }

    // 3. Factorize A = L L^T.
    pp::cholesky decomposition(A);
    pp::matrix L = decomposition.L;

    // 4. Check that L is lower triangular.
    bool lower_triangular = true;

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            if (std::abs(L(i, j)) > tolerance) {
                lower_triangular = false;
            }
        }
    }

    // 5. Check that the diagonal elements are positive.
    bool positive_diagonal = true;

    for (std::size_t i = 0; i < n; ++i) {
        if (L(i, i) <= 0.0) {
            positive_diagonal = false;
        }
    }

    // 6. Check that L L^T approximately equals A.
    pp::matrix LLT = L * L.transpose();
    bool correct_factorization = true;

    // checks every matrix element of both matrices
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            const double difference =
                std::abs(LLT(i, j) - A(i, j)); 

            // the allowed error scales with the size
            // of A(i, j). If A(i, j) is close to zero
            // the allowed error is approximately tolerance
            // but if A(i, j) is large a larger error is also
            // permitted. 
            if (difference >
                tolerance * (1.0 + std::abs(A(i, j)))) {
                correct_factorization = false;
            }
        }
    }

    std::cout << std::boolalpha;

    std::cout << "1. Generate random 4x4 matrix B\n\n";
    std::cout << "B = \n" << B << "\n";
    
    std::cout << "2. Construct symmetric positive-definite matrix A\n\n";
    std::cout << "A = B^T B + lambda I:\n" << A << "\n";

    std::cout << "3. Factorize into LL^T\n\n";
    std::cout << "L = \n" << L << "\n";
    std::cout << "L L^T = \n" << LLT << "\n";

    std::cout << "4. Check that L is lower triangular\n\n";
    std::cout << "L is lower triangular: "
              << lower_triangular << "\n\n";

    std::cout << "5. Check that the diagonal elements of L are positive\n\n";
    std::cout << "L has positive diagonal: "
              << positive_diagonal << "\n\n";

    std::cout << "6. Check that LL^T = A\n\n";
    std::cout << "L L^T equals A: "
              << correct_factorization << "\n\n";

}


void run_task_2()
{
    const std::size_t n = 4;
    const double lambda = 1.0;
    const double tolerance = 1e-10;

    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    // 1. Generate a random square matrix B.
    pp::matrix B(n, n, 0.0);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            B(i, j) = distribution(generator);
        }
    }

    // 2. Construct a symmetric positive-definite matrix A = B^T B + lambda I.
    pp::matrix A = B.transpose() * B;

    for (std::size_t i = 0; i < n; ++i) {
        A(i, i) += lambda;
    }

    // 3. Generate a random vector b.
    pp::vector b(n, 0.0);

    for (std::size_t i = 0; i < n; ++i) {
        b[i] = distribution(generator);
    }

    // 4. Factorize A = L L^T and solve A x = b.
    pp::cholesky decomposition(A);
    pp::matrix L = decomposition.L;
    pp::matrix LT = L.transpose();

    // 5. Solve Ax = b
    pp::vector x = decomposition.solve(b);

    // 6. Check that A*x approximately equals b.
    pp::vector Ax = A * x;

    bool correct_solution = true;

    for (std::size_t i = 0; i < n; ++i) {
        const double difference = std::abs(Ax[i] - b[i]);

        if (difference > tolerance * (1.0 + std::abs(b[i]))) {
            correct_solution = false;
        }
    }

    std::cout << std::boolalpha;

    std::cout << "Test Linear Equation solver:\n\n";
    std::cout << "1. Generate a random square matrix B of size 4\n\n";
    std::cout << "B = \n" << B << "\n";
    std::cout << "2. Construct A = B^T B + lambda I\n\n";
    std::cout << "A = \n" << A << "\n";
    std::cout << "3. Generate a random vector b of size 4\n\n";
    std::cout << "b = \n" << b << "\n";
    std::cout << "4. Factorize A into LL^T\n\n";
    std::cout << "L = \n" << L << "\n";
    std::cout << "L^T = \n" << LT << "\n";
    std::cout << "5. Solve Ax = b\n\n";
    std::cout << "x = \n" << x << "\n";
    std::cout << "6. Check that Ax = b\n\n";
    std::cout << "A*x = \n" << Ax << "\n";

    std::cout << "A*x equals b: "
              << correct_solution << "\n";

}

void run_task_3()
{
    const double tolerance = 1e-10;

    // testing it on a 2x2 matrix with known solution
    pp::matrix A(2, 2, 0.0);

    A(0, 0) = 4.0;
    A(0, 1) = 2.0;
    A(1, 0) = 2.0;
    A(1, 1) = 3.0;

    pp::cholesky decomposition(A);

    const double determinant = decomposition.det();
    const double expected = 8.0; // the solution

    const bool correct_determinant =
        std::abs(determinant - expected)
        <= tolerance * (1.0 + std::abs(expected));

    std::cout << std::boolalpha;

    std::cout << "A = \n" << A << "\n";
    std::cout << "det(A) = " << determinant << "\n";
    std::cout << "expected det(A) = " << expected << "\n";
    std::cout << "det(A) correct = "
              << correct_determinant << "\n";
}

void run_task_4()
{
    const std::size_t n = 3;
    const double tolerance = 1e-10;

    pp::matrix A(n, n, 0.0);

    A(0, 0) = 4.0;
    A(0, 1) = 2.0;
    A(0, 2) = 0.0;

    A(1, 0) = 2.0;
    A(1, 1) = 5.0;
    A(1, 2) = 1.0;

    A(2, 0) = 0.0;
    A(2, 1) = 1.0;
    A(2, 2) = 3.0;

    pp::cholesky decomposition(A);

    pp::matrix Ainv = decomposition.inverse();

    pp::matrix product = A * Ainv;

    bool correct_inverse = true;

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            const double expected = (i == j) ? 1.0 : 0.0;
            const double difference =
                std::abs(product(i, j) - expected);

            if (difference > tolerance) {
                correct_inverse = false;
            }
        }
    }

    std::cout << std::boolalpha;

    std::cout << "A = \n" << A << "\n";
    std::cout << "A inverse = \n" << Ainv << "\n";
    std::cout << "A * A inverse = \n" << product << "\n";

    std::cout << "A inverse is correct: "
              << correct_inverse << "\n";
}

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << "  ./main decomposition\n"
                  << "  ./main linear\n"
                  << "  ./main determinant\n"
                  << "  ./inverse\n\n";
        return 1;
    }

    const std::string task = argv[1];

    if (task == "decomposition") {
        run_task_1();
    }
    else if (task == "linear"){
        run_task_2();
    }
    else if (task == "determinant"){
        run_task_3();
    }
    else if (task == "inverse"){
        run_task_4();
    }
    else {
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;


}