#include <iostream>
#include <vector>

using namespace std;

/*

    Hi I'm Julian Rivera...
    In this code, I’m working with matrices to explore how to calculate a transpose and perform a matrix-vector multiplication. 
    I created a custom matrix A that represents some directed relationships (kind of like a graph), 
    and a vector B that we multiply with the transpose of A. 
    The goal is to see how data changes when it's transformed and then combined with another vector. 
    At the end, I print everything to clearly understand what's happening in each step.

*/

using Matrix = vector<vector<int>>; // Defino Matrix como una matriz de enteros

Matrix transpose(const Matrix &A) {
    int rows = A.size();
    int cols = A[0].size();
    Matrix T(cols, vector<int>(rows)); // Creo una matriz T con dimensiones invertidas
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            T[j][i] = A[i][j]; // Cambio filas por columnas
    return T;
}

Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
    int a_cols = A[0].size();

    if (a_cols != p) {
        cerr << "Error: dimensiones incompatibles para multiplicación de matrices." << endl;
        exit(EXIT_FAILURE);
    }

    Matrix R(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                R[i][j] += A[i][k] * B[k][j];

    return R;
}

void print_matrix(const Matrix &M, const string &label) {
    cout << "\nMatriz " << label << ":\n";
    for (const auto& row : M) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    // Define matrix A representing some connections or relationships. 
    // This matrix is different from the previous one to make the example more interesting.
    Matrix A = {
        {0, 1, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0}
    };

    // Define vector B, which will be multiplied by the transpose of matrix A.
    Matrix B = {
        {0},
        {1},
        {0},
        {0},
        {0},
        {0}
    };

    // Calculate the transpose of matrix A and store it in T.
    Matrix T = transpose(A);

    // Multiply the transposed matrix T by vector B, and store the result in TB.
    Matrix TB = multiply(T, B);

    // Print matrix A to display its original values.
    print_matrix(A, "A");

    // Print matrix T to show the transpose of A.
    print_matrix(T, "A Transpuesta");

    // Print vector B to show the vector used for multiplication.
    print_matrix(B, "B");

    // Print the result of multiplying T by B.
    print_matrix(TB, "T * B");

    return 0;
}

