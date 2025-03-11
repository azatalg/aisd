#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

long long binom(int n, int k) {
    if (k > n) return 0;
    k = min(k, n - k);
    long long res = 1;
    for (int i = 0; i < k; i++) {
        res = res * (n - i) / (i + 1);
    }
    return res;
}

struct Matrix {
    int rows, cols;
    vector<vector<long long>> m;
    Matrix(int r, int c) : rows(r), cols(c), m(r, vector<long long>(c, 0)) {}
    Matrix(const vector<vector<long long>> &v) : rows(v.size()), cols(v.empty() ? 0 : v[0].size()), m(v) {}
    Matrix operator*(const Matrix &other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < other.cols; j++)
                for (int k = 0; k < cols; k++)
                    result.m[i][j] += m[i][k] * other.m[k][j];
        return result;
    }
};

ostream& operator<<(ostream &os, const Matrix &A) {
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++)
            os << setw(10) << A.m[i][j] << " ";
        os << "\n";
    }
    return os;
}

Matrix matrixPower(Matrix A, long long p) {
    Matrix result(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
        result.m[i][i] = 1;
    while(p > 0) {
        if (p & 1)
            result = result * A;
        A = A * A;
        p >>= 1;
    }
    return result;
}

Matrix calc1(vector<long long>& init, vector<long long>& rec, vector<long long>& pol) {
    int k = init.size();
    int d = pol.size() - 1;
    long long n = k; 
    long long an = 0;
    for (int i = 0; i < k; i++) {
        an += rec[i] * init[k - 1 - i];
    }
    long long polyVal = 0;
    for (int j = 0; j <= d; j++) {
        long long pwr = 1;
        for (int t = 0; t < d - j; t++) pwr *= n;
        polyVal += pol[j] * pwr;
    }
    an += polyVal;
    vector<long long> state;
    state.push_back(an);
    for (int i = k - 1; i >= 1; i--) {
        state.push_back(init[i]);
    }
    for (int j = 0; j <= d; j++) {
        long long pwr = 1;
        for (int t = 0; t < d - j; t++) pwr *= n;
        state.push_back(pwr);
    }
    Matrix M(state.size(), 1);
    for (int i = 0; i < state.size(); i++) {
         M.m[i][0] = state[i];
    }
    return M;
}

Matrix constructTransitionMatrix(int k, int d, const vector<long long>& rec, const vector<long long>& poly) {
    int N = k + d + 1;
    Matrix A(N, N);
    for (int j = 0; j < k; j++) {
        A.m[0][j] = rec[j];
    }
    for (int j = 0; j <= d; j++) {
        long long t = 0;
        for (int r = 0; r <= j; r++) {
            t += poly[r] * binom(d - r, j - r);
        }
        A.m[0][k + j] = t;
    }
    for (int i = 1; i < k; i++) {
        A.m[i][i - 1] = 1;
    }
    for (int r = 0; r <= d; r++) {
        for (int c = 0; c <= d; c++) {
            if (c < r) A.m[k + r][k + c] = 0;
            else A.m[k + r][k + c] = binom(d - r, d - c);
        }
    }
    return A;
}

int main(){
    int k, d, n;
    cout << "Podaj rzad rekurencji k: ";
    cin >> k;
    vector<long long> init(k), rec(k);
    cout << "Podaj " << k << " pierwszych wyrazow ciagu (a0, a1, ..., a_{k-1}): ";
    for (int i = 0; i < k; i++) cin >> init[i];

    cout << "Podaj " << k << " wspolczynnikow rekurencji: ";
    for (int i = 0; i < k; i++) cin >> rec[i];
    
    cout << "Podaj stopien wielomianu d (P(n) ma d+1 wspolczynnikow): ";
    cin >> d;
   
    vector<long long> poly(d + 1);
    cout << "Podaj " << d + 1 << " wspolczynnikow wielomianu P(n): ";
   
    for (int i = 0; i <= d; i++) cin >> poly[i];
   
    cout << "Podaj n (indeks, dla ktorego chcesz obliczyc a_n): ";
    cin >> n;
    
    Matrix stateVec = calc1(init, rec, poly);
    int N = k + d + 1;
    
    Matrix T = constructTransitionMatrix(k, d, rec, poly);
    cout<<"Macierz rekurencji:\n"<<T<<'\n'; 
    if(n < k) {
        cout << "a_n = " << init[n] << "\n";
        return 0;
    }
    
    Matrix Texp = matrixPower(T, n - k);
    Matrix resState = Texp * stateVec;
    cout << "a_n = " << resState.m[0][0] << "\n";
    
    return 0;
}

