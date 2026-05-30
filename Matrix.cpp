#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Matrix {
private:
    int R, C;
    vector<T> a;

public:
    Matrix(int r = 0, int c = 0, T val = T())
        : R(r), C(c), a(r * c, val) {}

    int rows() const { return R; }
    int cols() const { return C; }

    T& operator()(int i, int j) {
        return a[i * C + j];
    }

    const T& operator()(int i, int j) const {
        return a[i * C + j];
    }

    static Matrix identity(int n) {
        Matrix I(n, n);
        for (int i = 0; i < n; i++) I(i, i) = 1;
        return I;
    }

    Matrix operator+(const Matrix& B) const {
        assert(R == B.R && C == B.C);
        Matrix res(R, C);
        for (int i = 0; i < R * C; i++) res.a[i] = a[i] + B.a[i];
        return res;
    }

    Matrix operator-(const Matrix& B) const {
        assert(R == B.R && C == B.C);
        Matrix res(R, C);
        for (int i = 0; i < R * C; i++) res.a[i] = a[i] - B.a[i];
        return res;
    }

    Matrix operator*(T k) const {
        Matrix res(R, C);
        for (int i = 0; i < R * C; i++) res.a[i] = a[i] * k;
        return res;
    }

    Matrix operator/(T k) const {
        Matrix res(R, C);
        for (int i = 0; i < R * C; i++) res.a[i] = a[i] / k;
        return res;
    }

    Matrix& operator+=(const Matrix& B) {
        assert(R == B.R && C == B.C);
        for (int i = 0; i < R * C; i++) a[i] += B.a[i];
        return *this;
    }

    Matrix& operator-=(const Matrix& B) {
        assert(R == B.R && C == B.C);
        for (int i = 0; i < R * C; i++) a[i] -= B.a[i];
        return *this;
    }

    Matrix& operator*=(T k) {
        for (int i = 0; i < R * C; i++) a[i] *= k;
        return *this;
    }

    Matrix& operator/=(T k) {
        for (int i = 0; i < R * C; i++) a[i] /= k;
        return *this;
    }

    Matrix operator*(const Matrix& B) const {
        assert(C == B.R);
        Matrix res(R, B.C, 0);
        for (int i = 0; i < R; i++) {
            for (int k = 0; k < C; k++) {
                T cur = (*this)(i, k);
                for (int j = 0; j < B.C; j++) {
                    res(i, j) += cur * B(k, j);
                }
            }
        }
        return res;
    }

    Matrix& operator*=(const Matrix& B) {
        *this = *this * B;
        return *this;
    }

    Matrix power(long long e) const {
        assert(R == C);
        Matrix base = *this;
        Matrix ans = identity(R);
        while (e > 0) {
            if (e & 1) ans *= base;
            base *= base;
            e >>= 1;
        }
        return ans;
    }

    Matrix transpose() const {
        Matrix res(C, R);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                res(j, i) = (*this)(i, j);
            }
        }
        return res;
    }

    T determinant() const {
        assert(R == C);
        Matrix temp = *this;
        T det = 1;
        for (int col = 0; col < R; col++) {
            int pivot = -1;
            for (int row = col; row < R; row++) {
                if (temp(row, col) != T()) {
                    pivot = row;
                    break;
                }
            }
            if (pivot == -1) return 0;
            if (pivot != col) {
                for (int j = 0; j < C; j++) {
                    swap(temp(pivot, j), temp(col, j));
                }
                det = -det;
            }
            T pivotVal = temp(col, col);
            det *= pivotVal;
            for (int row = col + 1; row < R; row++) {
                T factor = temp(row, col) / pivotVal;

                for (int j = col; j < C; j++) {
                    temp(row, j) -= factor * temp(col, j);
                }
            }
        }
        return det;
    }

    Matrix inverse() const {
        assert(R == C);
        int n = R;
        Matrix aug(n, 2 * n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                aug(i, j) = (*this)(i, j);
            }
            aug(i, i + n) = 1;
        }
        for (int col = 0; col < n; col++) {
            int pivot = -1;
            for (int row = col; row < n; row++) {
                if (aug(row, col) != T()) {
                    pivot = row;
                    break;
                }
            }
            if (pivot == -1) {
                throw invalid_argument("Matrix is singular");
            }
            for (int j = 0; j < 2 * n; j++) {
                swap(aug(pivot, j), aug(col, j));
            }
            T div = aug(col, col);
            for (int j = 0; j < 2 * n; j++) {
                aug(col, j) /= div;
            }
            for (int row = 0; row < n; row++) {
                if (row == col) continue;
                T factor = aug(row, col);
                for (int j = 0; j < 2 * n; j++) {
                    aug(row, j) -= factor * aug(col, j);
                }
            }
        }
        Matrix inv(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                inv(i, j) = aug(i, j + n);
            }
        }
        return inv;
    }

    vector<T> solve(vector<T> b) const {
        assert(R == C);
        assert((int)b.size() == R);
        int n = R;
        Matrix aug(n, n + 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                aug(i, j) = (*this)(i, j);
            }
            aug(i, n) = b[i];
        }
        for (int col = 0; col < n; col++) {
            int pivot = -1;
            for (int row = col; row < n; row++) {
                if (aug(row, col) != T()) {
                    pivot = row;
                    break;
                }
            }
            if (pivot == -1) {
                throw invalid_argument("No unique solution");
            }
            for (int j = col; j <= n; j++) {
                swap(aug(pivot, j), aug(col, j));
            }
            T div = aug(col, col);
            for (int j = col; j <= n; j++) {
                aug(col, j) /= div;
            }
            for (int row = 0; row < n; row++) {
                if (row == col) continue;
                T factor = aug(row, col);
                for (int j = col; j <= n; j++) {
                    aug(row, j) -= factor * aug(col, j);
                }
            }
        }
        vector<T> x(n);
        for (int i = 0; i < n; i++) {
            x[i] = aug(i, n);
        }
        return x;
    }

    struct LUResult {
        Matrix L;
        Matrix U;
        vector<int> p;
        int swaps;
    };

    LUResult lu() const {
        assert(R == C);
        int n = R;
        Matrix U = *this;
        Matrix L = identity(n);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        int swaps = 0;
        for (int col = 0; col < n; col++) {
            int pivot = col;
            for (int row = col; row < n; row++) {
                if (abs(U(row, col)) > abs(U(pivot, col))) pivot = row;
            }
            if (U(pivot, col) == T()) throw invalid_argument("Matrix is singular");
            if (pivot != col) {
                for (int j = 0; j < n; j++) swap(U(pivot, j), U(col, j));
                for (int j = 0; j < col; j++) swap(L(pivot, j), L(col, j));
                swap(p[pivot], p[col]);
                swaps++;
            }
            for (int row = col + 1; row < n; row++) {
                T factor = U(row, col) / U(col, col);
                L(row, col) = factor;
                for (int j = col; j < n; j++) U(row, j) -= factor * U(col, j);
            }
        }
        return {L, U, p, swaps};
    }

    vector<T> solveLU(const vector<T>& b) const {
        assert(R == C);
        assert((int)b.size() == R);
        int n = R;
        LUResult res = lu();
        vector<T> pb(n);
        for (int i = 0; i < n; i++) pb[i] = b[res.p[i]];
        vector<T> y(n);
        for (int i = 0; i < n; i++) {
            T sum = pb[i];
            for (int j = 0; j < i; j++) sum -= res.L(i, j) * y[j];
            y[i] = sum;
        }
        vector<T> x(n);
        for (int i = n - 1; i >= 0; i--) {
            T sum = y[i];
            for (int j = i + 1; j < n; j++) sum -= res.U(i, j) * x[j];
            x[i] = sum / res.U(i, i);
        }
        return x;
    }

    T determinantLU() const {
        assert(R == C);
        LUResult res = lu();
        T det = (res.swaps % 2 ? -1 : 1);
        for (int i = 0; i < R; i++) det *= res.U(i, i);
        return det;
    }

    Matrix inverseLU() const {
        assert(R == C);
        int n = R;
        Matrix inv(n, n);
        LUResult res = lu();
        for (int col = 0; col < n; col++) {
            vector<T> b(n, 0);
            b[col] = 1;
            vector<T> pb(n);
            for (int i = 0; i < n; i++) pb[i] = b[res.p[i]];
            vector<T> y(n);
            for (int i = 0; i < n; i++) {
                T sum = pb[i];
                for (int j = 0; j < i; j++) sum -= res.L(i, j) * y[j];
                y[i] = sum;
            }
            vector<T> x(n);
            for (int i = n - 1; i >= 0; i--) {
                T sum = y[i];
                for (int j = i + 1; j < n; j++) sum -= res.U(i, j) * x[j];
                x[i] = sum / res.U(i, i);
            }
            for (int row = 0; row < n; row++) inv(row, col) = x[row];
        }
        return inv;
    }

    friend ostream& operator<<(ostream& os, const Matrix& M) {
        for (int i = 0; i < M.R; i++) {
            for (int j = 0; j < M.C; j++) {
                os << M(i, j) << " ";
            }
            os << '\n';
        }
        return os;
    }
};


int main() {
    Matrix<double> A(2, 2);
    A(0, 0) = 2;
    A(0, 1) = 1;
    A(1, 0) = 6;
    A(1, 1) = 5;
    auto res = A.lu();
    cout << "A:\n" << A;
    cout << "L:\n" << res.L;
    cout << "U:\n" << res.U;
    cout << "det(A): " << A.determinantLU() << '\n';
    vector<double> b = {5, 11};
    vector<double> x = A.solveLU(b);
    cout << "solution:\n";
    for (double v : x) cout << v << " ";
    cout << '\n';
    cout << "inverse:\n" << A.inverseLU();
    cout << "A^5:\n" << A.power(5);
    return 0;
}