#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cmath> 

#define PREC 3

using namespace std;

template <typename T>
class Matrix {
    vector<vector<T>> array;
    int R;
    int C;

public:
    Matrix(int r, int c) : R(r), C(c) {
        array.resize(R, vector<T>(C, static_cast<T>(0)));
    }

    Matrix(int r, int c, T val) : R(r), C(c) {
        array.resize(R, vector<T>(C, static_cast<T>(val)));
    }

    void set(int row, int col, T val) {
        if (0 <= row && row < R && 0 <= col && col < C) {
            array[row][col] = val;
        } else {
            throw out_of_range("Index out of bounds");
        }
    }

    T get(int row, int col) const {
        if (0 <= row && row < R && 0 <= col && col < C) {
            return array[row][col];
        } else {
            throw out_of_range("Index out of bounds");
        }
    }

    Matrix<T>& operator+=(const Matrix<T>& B) {
        if (R != B.R || C != B.C) {
            throw invalid_argument("Matrix dimensions must match for addition");
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                array[i][j] += B.array[i][j];
            }
        }
        return *this;
    }

    Matrix<T>& operator-=(const Matrix<T>& B) {
        if (R != B.R || C != B.C) {
            throw invalid_argument("Matrix dimensions must match for subtraction");
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                array[i][j] -= B.array[i][j];
            }
        }
        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& B) const {
        if (R != B.R || C != B.C) {
            throw invalid_argument("Matrix dimensions must match for addition");
        }
        Matrix<T> M(R, C, 0); 
        M += *this;
        M += B;
        return M;
    }

    Matrix<T> operator-(const Matrix<T>& B) const {
        if (R != B.R || C != B.C) {
            throw invalid_argument("Matrix dimensions must match for subtraction");
        }
        Matrix<T> M(R, C, 0); 
        M += *this;
        M -= B;
        return M;
    }

    Matrix<T>& operator+=(T val) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                array[i][j] += val;
            }
        }
        return *this;
    }

    Matrix<T>& operator-=(T val) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                array[i][j] -= val;
            }
        }
        return *this;
    }

    Matrix<T>& operator*=(T val) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                array[i][j] *= val;
            }
        }
        return *this;
    }

    Matrix<T>& operator/=(T val) {
        if (val == 0) {
            throw invalid_argument("Division by zero");
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                array[i][j] /= val;
            }
        }
        return *this;
    }

    Matrix<T>& operator%=(T val) {
        if (val == 0) {
            throw invalid_argument("Modulo by zero");
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                array[i][j] %= val;
            }
        }
        return *this;
    }

    Matrix<T>& operator*=(const Matrix<T>& B) {
        if (C != B.R) {
            throw invalid_argument("Invalid Matrix product");
        }
        vector<vector<T>> result(R, vector<T>(B.C, static_cast<T>(0)));
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < B.C; ++j) {
                T sum = static_cast<T>(0);
                for (int k = 0; k < C; ++k) { 
                    sum += array[i][k] * B.array[k][j];
                }
                result[i][j] = sum;
            }
        }
        array = result;
        C = B.C;
        return *this;
    }

    Matrix<T> operator*(const Matrix<T>& B) const {
        if (C != B.R) {
            throw invalid_argument("Invalid Matrix product");
        }
        Matrix<T> result(R, B.C, static_cast<T>(0));
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < B.C; ++j) {
                T sum = static_cast<T>(0);
                for (int k = 0; k < C; ++k) { 
                    sum += array[i][k] * B.array[k][j];
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }  

    static Matrix<T> identity(int size) {
        Matrix<T> I(size, size, static_cast<T>(0)); 
        for (int i = 0; i < size; ++i) {
            I.set(i, i, static_cast<T>(1));
        }
        return I;
    }

    Matrix<T> cofactor(int row, int col) const {
        if (R != C) {
            throw invalid_argument("Not a square matrix");
        }
        Matrix<T> M(R - 1, C - 1);
        int m = 0, n = 0;
        for (int i = 0; i < R; ++i) {
            if (i == row) continue;
            n = 0;
            for (int j = 0; j < C; ++j) {
                if (j == col) continue;
                M.set(m, n, array[i][j] * ((i + j) % 2 == 0 ? 1 : -1));
                ++n;
            }
            ++m;
        }
        return M;
    }

    T determinant() const {
        if (R != C) {
            throw invalid_argument("Not a square matrix");
        }
        if (R == 1) {
            return array[0][0];
        }
        if (R == 2) {
            return array[0][0] * array[1][1] - array[0][1] * array[1][0];
        }
        T det = static_cast<T>(0);
        for (int i = 0; i < R; ++i) {
            det += array[i][0] * cofactor(i, 0).determinant();
        }
        return det;
    }

    Matrix<T> transpose() const {
        Matrix<T> trans(C, R);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                trans.set(j, i, array[i][j]);
            }
        }
        return trans;
    }

    Matrix<T> adjoint() const {
        if (R != C) {
            throw invalid_argument("Not a square matrix");
        }
        Matrix<T> adj(R, C);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                adj.set(i, j, cofactor(i, j).determinant() * ((i + j) % 2 == 0 ? 1 : -1));
            }
        }
        adj = adj.transpose();
        return adj; 
    }

    Matrix<T> inverse() const {
        T det = this->determinant();
        if (det == 0) {
            throw invalid_argument("Matrix is singular and cannot be inverted");
        }
        Matrix<T> M = this->adjoint();
        M /= det;
        return M;
    }

    int rows() const { return R; }
    int cols() const { return C; }

    template <typename U>
    friend ostream& operator<<(ostream& os, const Matrix<U>& A);
    template <typename U>
    friend Matrix<U> pow(const Matrix<U>& A, int n);
};

template <typename T>
ostream& operator<<(ostream& os, const Matrix<T>& A) {
    os << fixed << setprecision(PREC);
    for (int i = 0; i < A.R; i++) {
        for (int j = 0; j < A.C; j++) {
            os << A.array[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template <typename T>
Matrix<T> pow(const Matrix<T>& A, int n) {
    if (A.rows() != A.cols()) {
        throw invalid_argument("Not a square matrix");
    }
    Matrix<T> result = Matrix<T>::identity(A.rows());
    Matrix<T> base = A;
    while (n) {
        if (n & 1) {
            result *= base;
        }
        base *= base;
        n >>= 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Matrix<double> C(2, 2);
    C.set(0, 0, 1);
    C.set(0, 1, 2);
    C.set(1, 0, 3);
    C.set(1, 1, 4);
    Matrix<double> A = pow(C, 10);
    cout << A;
    return 0;
}
