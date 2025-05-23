#include <iostream>
#include <vector>

using namespace std;

/* 

    Hello, in this code it will be analyzed the strongly connected components (SCCs).
    For this analysis, we’ll need a matrix (obviously), but a special kind of matrix...
    Also, we’ll use some operations like getting the identity matrix, logical functions like Or and And, 
    and then something a bit more complex: the Boolean product between matrices.

    The idea is to build a reachability matrix using the adjacency matrix of the graph.
    This will help us figure out which nodes can reach which others. 
    Then we get the transpose of that matrix, and using an AND operation between the two, 
    we can find out which nodes are mutually reachable — and that gives us the SCCs.

    Finally, we’ll print those components and show which nodes belong to the same group.
    Hope this helps understand the logic behind the code!

*/


using Matrix = vector<vector<bool>>; 

// return the identity matrix
Matrix identity(int n) {
    Matrix I(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
        I[i][i] = true;
    return I;
}

// OR, function between matrix
Matrix Or(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix R(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            R[i][j] = A[i][j] || B[i][j];
    return R;
}

// AND, function between matrix
Matrix And(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix R(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            R[i][j] = A[i][j] && B[i][j];
    return R;
}

// Transposed of matrix 
Matrix Transposed(const Matrix &A) {
    int n = A.size();
    Matrix T(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            T[j][i] = A[i][j];
    return T;
}

// bool product (OR, AND)
Matrix Bool_product(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix R(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                R[i][j] = R[i][j] || (A[i][k] && B[k][j]);
    return R;
}

// Reachability matrix
Matrix Reachability(const Matrix &A) {
    int n = A.size();
    Matrix C = identity(n);
    Matrix P = A;
    for (int i = 0; i < n; ++i) {
        C = Or(C, P);
        P = Bool_product(P, A);
    }
    return C;
}

// Show the components strongly connected
void Show_components(const Matrix &SCC) {
    int n = SCC.size();
    vector<bool> visitado(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) {
            cout << "Componente: ";
            for (int j = 0; j < n; ++j) {
                if (SCC[i][j]) {
                    cout << j << " ";
                    visitado[j] = true;
                }
            }
            cout << endl;
        }
    }
}

// Print matrix
void Print(const Matrix &M, const string &nombre) {
    cout << "\nMatriz " << nombre << ":\n";
    for (const auto& fila : M) {
        for (bool val : fila)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    // Here I’m defining the adjacency matrix A for a directed graph with 8 nodes.
    // Each row is a starting node, and each column is a destination node.
    // A '1' means there’s an edge from node i to node j.
    Matrix A = {
        {0, 1, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 1, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 0}  
    };

    // Now I calculate the reachability matrix C from A.
    // This matrix shows which nodes can be reached from each other node.
    Matrix C = Reachability(A);

    // Next, I get the transpose of C, which flips rows and columns.
    // This helps check mutual reachability between nodes.
    Matrix Ct = Transposed(C);

    // To find the strongly connected components, I do a logical AND between C and Ct.
    // SCC[i][j] is true only if node i can reach j and node j can reach i.
    Matrix SCC = And(C, Ct);

    // I print out the SCC matrix with a clear label so it’s easy to read.
    Print(SCC, "SCC (Strongly Connected Components)");

    // Finally, I list out the actual strongly connected components,
    // showing which nodes belong together in each component.
    Show_components(SCC);

    // End of the program, returning 0 means everything ran fine.
    return 0;
}

