#include <iostream>
#include <vector>
using namespace std;

const int DIM = 6; // wymiar macierzy i wektora stanu

// Mnożenie macierzy DIM x DIM
vector<vector<long long>> multiplyMatrix(const vector<vector<long long>> &A, const vector<vector<long long>> &B) {
    vector<vector<long long>> C(DIM, vector<long long>(DIM, 0));
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            for (int k = 0; k < DIM; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Potęgowanie macierzy metodą szybkiego potęgowania
vector<vector<long long>> matrixPower(vector<vector<long long>> A, long long p) {
    // macierz jednostkowa DIM x DIM
    vector<vector<long long>> result(DIM, vector<long long>(DIM, 0));
    for (int i = 0; i < DIM; i++)
        result[i][i] = 1;
    
    while (p > 0) {
        if (p & 1)
            result = multiplyMatrix(result, A);
        A = multiplyMatrix(A, A);
        p >>= 1;
    }
    return result;
}

// Mnożenie macierzy DIM x DIM przez wektor DIM x 1
vector<long long> multiplyMatrixVector(const vector<vector<long long>> &A, const vector<long long> &v) {
    vector<long long> res(DIM, 0);
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            res[i] += A[i][j] * v[j];
        }
    }
    return res;
}

int main() {
    // Ustalamy warunki początkowe: c0 = 1, c1 = 1, c2 = 1.
    // Obliczamy c3 = c2 + c1 + c0 + (3^2 + 3 + 1) = 1 + 1 + 1 + 13 = 16.
    // Wektor stanu dla n=3: [c3, c2, c1, 3^2, 3, 1] = [16, 1, 1, 9, 3, 1]
    vector<long long> v3 = {28, 1, 1, 9, 3, 1};
    
    // Macierz przejścia A (6 x 6)
    vector<vector<long long>> A = {
        {3, 2, 1, 2, 5, 4},
        {1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 2, 1},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 1}
    };
    
    long long n;
    cout << "Podaj n (n >= 0): ";
    cin >> n;
    
    // Dla n < 0 nie definiujemy. Dla n = 0, 1, 2, 3 zwracamy warunki początkowe:
    if(n == 0) {
        cout << "c0 = 1" << endl;
        return 0;
    } else if(n == 1) {
        cout << "c1 = 1" << endl;
        return 0;
    } else if(n == 2) {
        cout << "c2 = 1" << endl;
        return 0;
    } 
    
    // Dla n >= 4 obliczamy A^(n-3)
    vector<vector<long long>> Aexp = matrixPower(A, n - 3);
    
    // Obliczamy v_n = A^(n-3) * v3
    vector<long long> vn = multiplyMatrixVector(Aexp, v3);
    
    // Pierwszy element wektora stanowego to c_n
    cout << "c" << n << " = " << vn[0] << endl;
    
    return 0;
}

