
#pragma once
#include<vector>
#include<stdexcept>
#include<cmath>
#include<iostream>

namespace pp{
struct vector{           //struct and class is basically the same. for struct everything is public
    private: 
        std::vector<double> data_;
    
    public:
    //constructors
    vector() = default;
    explicit vector(std::size_t n, double value = 0.0)
        : data_(n, value) {}

    vector(std::initializer_list<double> init)
        : data_(init) {}

    
    // Size
    std::size_t size() const noexcept { return data_.size(); }

    // Element access
    double& operator[](std::size_t i) { return data_[i]; }
    const double& operator[](std::size_t i) const { return data_[i]; }

    // Arithmetic
    vector& operator+=(const vector& rhs){
        if (size() != rhs.size())
            throw std::invalid_argument("vector size mismatch");
        for (std::size_t i = 0; i < size(); ++i)
            data_[i] += rhs.data_[i];
        return *this;
    }

    vector& operator-=(const vector& rhs) {
        if (size() != rhs.size())
            throw std::invalid_argument("vector size mismatch");
        for (std::size_t i = 0; i < size(); ++i)
            data_[i] -= rhs.data_[i];
        return *this;
    }

    vector& operator*=(double a) {
        for (double& x : data_) x *= a;
        return *this;
    }

    double dot(const vector& rhs) const {
        if (size() != rhs.size())
            throw std::invalid_argument("vector size mismatch");
        double s = 0.0;
        for (std::size_t i = 0; i < size(); ++i)
            s += data_[i] * rhs.data_[i];
        return s;
    }

    double norm() const {
        return std::sqrt(dot(*this));
    }

    // Division by scalar
    vector& operator/=(double a) {
    if (a == 0.0)
        throw std::invalid_argument("division by zero");
    for (double& x : data_) x /= a;
    return *this;
}
};

// For printing:
inline std::ostream& operator<<(std::ostream& os, const vector& v)
{
    for (std::size_t i = 0; i < v.size(); ++i) {
        os << v[i] << "\n";
    }

    return os;
}

// Free operators
inline vector operator+(vector a, const vector& b) { return a += b; }
inline vector operator-(vector a, const vector& b) { return a -= b; }
inline vector operator*(vector v, double a) { return v *= a; }
inline vector operator*(double a, vector v) { return v *= a; }
inline vector operator/(vector v, double a) { return v /= a; }


struct matrix {
private:
    std::size_t rows_ = 0;
    std::vector<pp::vector> cols_;   // column storage

public:
    matrix() = default;

    matrix(std::size_t rows, std::size_t cols, double value = 0.0)
        : rows_(rows), cols_(cols, pp::vector(rows, value)) {}

    // Accessors
    std::size_t rows() const noexcept { return rows_; }
    std::size_t cols() const noexcept { return cols_.size(); }

    // Element access (i = row, j = column)
    double& operator()(std::size_t i, std::size_t j) {
        return cols_[j][i];
    }

    const double& operator()(std::size_t i, std::size_t j) const {
        return cols_[j][i];
    }

    // Matrix-vector product
    pp::vector operator*(const pp::vector& x) const {
        if (cols() != x.size())
            throw std::invalid_argument("dimension mismatch");

        pp::vector y(rows_, 0.0);

        for (std::size_t j = 0; j < cols(); ++j) {
            for (std::size_t i = 0; i < rows_; ++i) {
                y[i] += cols_[j][i] * x[j];
            }
        }

        return y;
    }

    // Matrix-matrix product
    matrix operator*(const matrix& B) const {
        if (cols() != B.rows())
            throw std::invalid_argument("dimension mismatch");

        matrix C(rows_, B.cols(), 0.0);

        for (std::size_t j = 0; j < B.cols(); ++j) {
            C.cols_[j] = (*this) * B.cols_[j];
        }

        return C;
    }

    matrix& operator+=(const matrix& rhs) {
        if (rows() != rhs.rows() || cols() != rhs.cols())
            throw std::invalid_argument("dimension mismatch");
        for (std::size_t j = 0; j < cols(); ++j)
            cols_[j] += rhs.cols_[j];
        return *this;
    }

    matrix& operator-=(const matrix& rhs) {
        if (rows() != rhs.rows() || cols() != rhs.cols())
            throw std::invalid_argument("dimension mismatch");
        for (std::size_t j = 0; j < cols(); ++j)
            cols_[j] -= rhs.cols_[j];
        return *this;
    }

    matrix& operator*=(double a) {
        for (std::size_t j = 0; j < cols(); ++j)
            cols_[j] *= a;
        return *this;
    }
    
    matrix transpose() const {
        matrix T(cols(), rows(), 0.0);
        for (std::size_t i = 0; i < rows(); ++i)
            for (std::size_t j = 0; j < cols(); ++j)
                T(j, i) = (*this)(i, j);
        return T;
    }

    // Return column j of the matrix.
    // The matrix is stored as a vector of column-vectors,
    // so cols_[j] is the j-th column.
    vector& col(std::size_t j) {
        return cols_[j];
    }

    const vector& col(std::size_t j) const {
        return cols_[j];
}
};

// For printing the matrix:
inline std::ostream& operator<<(std::ostream& os, const matrix& A)
{
    for (std::size_t i = 0; i < A.rows(); ++i) {
        for (std::size_t j = 0; j < A.cols(); ++j) {
            os << A(i, j) << " ";
        }
        os << "\n";
    }

    return os;
}

//free operators
inline matrix operator+(matrix A, const matrix& B) { return A += B; }
inline matrix operator-(matrix A, const matrix& B) { return A -= B; }
inline matrix operator*(matrix A, double a) { return A *= a; }
inline matrix operator*(double a, matrix A) { return A *= a; }


struct qr{
    matrix Q;
    matrix R;

    qr(const matrix& A) {
        // compute QR decomposition of A
        std::size_t n = A.rows();
        std::size_t m = A.cols();

        if (n < m)
            throw std::invalid_argument(
                "QR decomposition requires rows >= columns"
            );

        Q = matrix(n , m, 0.0);
        R = matrix(m, m, 0.0);

        matrix V = A; // working copy

        // Modified Gram-Schmidt QR decomposition.
        // V is a working copy of A.
        // At step i, column i is normalized to become Q_i.
        // Then the projection of all later columns onto Q_i is removed.
        // The projection coefficients are stored in R(i,j).
        for (std::size_t i = 0; i < m; i++){
            // R(i, i) = norm of column i
            double norm = V.col(i).norm();
            R(i,i) = norm; 

            if (norm < 1e-12)
                throw std::invalid_argument("linearly dependent columns in A");

            Q.col(i) = V.col(i) / norm;

            for (std::size_t j = i + 1; j < m; j++) {
                R(i, j) = Q.col(i).dot(V.col(j));
                V.col(j) -= Q.col(i) * R(i, j);
            }
        }
    }

    vector solve(vector b) const {
        std::size_t n = Q.rows();
        std::size_t m = Q.cols();

        if (b.size() !=n)
            throw std::invalid_argument("dimension mismatch in solve");

        // Since A = QR, the system Ax = b becomes QRx = b.
        // Multiplying by Q^T gives Rx = Q^T b,
        // because Q^T Q = I.

        // y = Q^T b
        vector y = Q.transpose() * b;

        // solve R x = y by back substitution 
        vector x(m, 0.0);

        for (int i = static_cast<int>(m) - 1; i >= 0; --i) {
            double sum = y[i];

            for (std::size_t j = i + 1; j < m; ++j) {
                sum -= R(i, j) * x[j];
            }

            if (std::abs(R(i, i)) < 1e-12)
                throw std::invalid_argument("singular matrix in solve");

            x[i] = sum / R(i, i);
        }
        return x;
    }

    // For this modified Gram-Schmidt implementation, R has positive diagonal
    // elements because R(i,i) is chosen as a norm.
    // Therefore the product of the diagonal elements gives |det(A)|.
    // It does not necessarily give the signed determinant.
    double det() const {
        if (Q.rows() != Q.cols())
            throw std::invalid_argument(
                "determinant requires a square matrix"
            );
        std::size_t m = R.cols();
        double d = 1.0;

        for (std::size_t i = 0; i < m; ++i) {
            d *= R(i,i);
        }
        return d;
    }

    // The inverse is found column by column.
    // To find column j of A^{-1}, solve A x = e_j,
    // where e_j is the j-th unit vector.
    matrix inverse() const {
        std::size_t n = Q.rows();
        std::size_t m = Q.cols();

        if (n != m)
            throw std::invalid_argument("inverse requires a square matrix");

        matrix B(n, n, 0.0);

        for (std::size_t j = 0; j < n; ++j) {
            vector e(n, 0.0);
            e[j] = 1.0;

            vector x = solve(e);
            B.col(j) = x;
        }

        return B;
    }
};

} // namespace pp
