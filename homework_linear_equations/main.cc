#include<iostream>
#include <random>
#include <cmath>
#include"linalg.h"

bool approx(double a, double b, double eps = 1e-10) {
    return std::abs(a - b) < eps;
}

bool approx_equal(const pp::matrix& A, const pp::matrix& B, double eps = 1e-10){
    if (A.rows() != B.rows() || A.cols() != B.cols()) return false;

    for (std::size_t i = 0; i < A.rows(); ++i) {
        for (std::size_t j = 0; j < A.cols(); ++j) {
            if (!approx(A(i,j), B(i,j), eps)) return false;
        }
    }
    return true;
}

bool approx_equal(const pp::vector& a, const pp::vector& b, double eps = 1e-10) {
    if (a.size() != b.size()) return false;

    for (std::size_t i = 0; i < a.size(); ++i) {
        if (std::abs(a[i] - b[i]) > eps)
            return false;
    }
    return true;
}

bool is_upper_triangular(const pp::matrix& R, double eps = 1e-10){
    for (std::size_t i = 0; i < R.rows(); ++i) {
        for (std::size_t j = 0; j < R.cols(); ++j) {
            if (i > j && std::abs(R(i,j)) > eps) return false;
        }
    }
    return true;
}

pp::matrix identity(std::size_t n) {
    pp::matrix I(n, n, 0.0);
    for (std::size_t i = 0; i < n; ++i) I(i,i) = 1.0;
    return I;
}

pp::matrix random_matrix(std::size_t rows, std::size_t cols) {
    pp::matrix A(rows, cols, 0.0);

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            A(i,j) = dist(gen);
        }
    }
    return A;
}

pp::vector random_vector(std::size_t n) {
    pp::vector b(n, 0.0);
    std::mt19937 gen(123);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (std::size_t i = 0; i < n; ++i)
        b[i] = dist(gen);

    return b;
}

void run_task_A2(){
    std::cout << "Problem A2\n\n";
    std::cout << "1. Generates a random tall matrix A(n,m) with n = 6 and m = 3\n\n";
    std::size_t n = 6;
    std::size_t m = 3;

    pp::matrix A = random_matrix(n, m);
    std::cout << "A =  \n" << A << "\n";

    std::cout << "2. Factorizes A into QR\n\n";
    pp::qr decomp(A);

    auto Q = decomp.Q;
    auto R = decomp.R;

    std::cout << "Q = \n" << Q << "\n";
    std::cout << "R = \n" << R << "\n";

    std::cout << "3. Checks that R is upper triangular\n\n";
    std::cout << "R upper triangular: "
            << (is_upper_triangular(R) ? "PASS" : "FAIL") << "\n\n";
    
    std::cout << "4. Checks that QtQ = 1\n\n";
    pp::matrix QtQ = Q.transpose() * Q;
    pp::matrix I = identity(m);

    std::cout << "Q^T Q = I: "
            << (approx_equal(QtQ, I) ? "PASS" : "FAIL") << "\n\n";

    
    std::cout << "5. Checks that QR = A\n\n";
    pp::matrix QR = Q * R;

    std::cout << "Q R = A: "
            << (approx_equal(QR, A) ? "PASS" : "FAIL") << "\n\n\n" << "------------" << "\n";
}

void run_task_A3(){
    std::cout << "Problem A3\n\n";

    std::cout << "1. Generates a random square matrix of size 4\n\n";
    std::size_t n = 4;

    pp::matrix A = random_matrix(n, n);
    std::cout << "A = \n" << A << "\n";

    std::cout << "2. Generates a random vector b of size 4\n\n";
    pp::vector b = random_vector(n);
    std::cout << "b = \n" << b << "\n";

    std::cout << "3. Factorizes A into QR\n\n";
    pp::qr decomp(A);

    auto Q = decomp.Q;
    auto R = decomp.R;

    std::cout << "Q = \n" << Q << "\n";
    std::cout << "R = \n" << R << "\n";

    std::cout << "4. Solves QRx = b\n\n";
    pp::vector x = decomp.solve(b);
    std::cout << "x = \n" << x << "\n";

    std::cout << "5. Checks that Ax = b\n\n";
    pp::vector Ax = A * x;

    std::cout << "Check Ax = b: " << (approx_equal(Ax, b) ? "PASS" : "FAIL") << "\n\n\n" << "------------" << "\n";
}

void run_task_A4(){
    std::cout << "Problem A4\n\n";
    std::cout << "Calculates the determinant of matrix R\n\n";
    // Option 1:
    //std::size_t n = 4;
    //pp::matrix A = random_matrix(n,n);

    // Option 2:  (jeg får +2 ud i stedet for -2 (som er svaret) men ifølge chat er det fordi det(R) ikke altid er lig med det(A), men det(A)=det(Q)det(R) i stedet)
    pp::matrix A(2,2);
    A(0,0)=1; A(0,1)=2;
    A(1,0)=3; A(1,1)=4;
    std::cout << "Matrix A = \n" << A << "\n";

    pp::qr decomp(A);
    auto Q = decomp.Q;
    auto R = decomp.R;

    std::cout << "Q = \n" << Q << "\n";
    std::cout << "R = \n" << R << "\n";

    double detA = decomp.det();

    std::cout << "det(R) = " << detA << "\n\n";
    std::cout
        << "Modified Gram-Schmidt gives positive diagonal elements in R,\n"
        << "so their product gives |det(A)| rather than its sign. - Chatgpt\n";
}

void run_task_B(){
    std::cout << "Problem B\n\n";

    std::cout << "1. Generates a random square matrix A of size 4\n\n";
    std::size_t n = 4;
    pp::matrix A = random_matrix(n,n);
    std::cout << "A = \n" << A << "\n";

    std::cout << "2. Factorizes A into QR\n\n";
    pp::qr decomp(A);
    auto Q = decomp.Q;
    auto R = decomp.R;

    std::cout << "Q = \n" << Q << "\n";
    std::cout << "R = \n" << R << "\n";

    std::cout << "3. Calculates the inverse B\n\n";
    pp::matrix B = decomp.inverse();
    std::cout << "B = \n" << B << "\n";

    std::cout << "4. Checks that AB = I, where I is the identity matrix\n\n";

    pp::matrix I = identity(n);
    std::cout << "I = \n" << I << "\n";

    std::cout << "Check A * A^{-1} = I: " << (approx_equal(A * B, I) ? "PASS" : "FAIL") << "\n";
    std::cout << "Check A^{-1} * A = I: " << (approx_equal(B * A, I) ? "PASS" : "FAIL") << "\n";

}

void run_task_C(std::size_t N){
    pp::matrix A = random_matrix(N, N);
    pp::qr decomp(A);

    //  prevent the compiler from optimizing everything away
    std::cout << decomp.R(0,0) << "\n";
}

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << "  ./main A\n"
                  << "  ./main B\n"
                  << "  ./main C N\n";
        return 1;
    }

    const std::string task = argv[1];

    if (task == "A") {
        run_task_A2();
        run_task_A3();
        run_task_A4();
    }
    else if (task == "B") {
        run_task_B();
    }
    else if (task == "C") {
        if (argc < 3) {
            std::cerr << "Usage: ./main C N\n";
            return 1;
        }

        const std::size_t N = std::stoul(argv[2]);
        run_task_C(N);
    }
    else {
        std::cerr << "Unknown task: " << task << "\n";
        return 1;
    }

    return 0;


}