#include <iostream>
#include <vector>
#include <limits>
#include <climits>

using namespace std;

class Graph
{
private:
    vector<vector<long long>> adjacency_matrix;
    const long long INF = LLONG_MAX;

public:
    Graph(int n) : adjacency_matrix(n, vector<long long>(n, INF))
    {
        for (int i = 0; i < n; ++i)
            adjacency_matrix[i][i] = 0; // Distance from a node to itself is 0
    }

    void add_edge(int from, int to, long long weight)
    {
        if (from == to)
            return;
        adjacency_matrix[from][to] = weight;
    }

    void print_matrix(const vector<vector<long long>> &matrix)
    {
        int size = matrix.size();
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (matrix[i][j] >= 99999999)
                    cout << ". ";
                else
                    cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void print_adjacency_matrix()
    {
        cout << "Adjacency matrix (weights):\n";
        print_matrix(adjacency_matrix);
    }

    vector<vector<long long>> min_plus_multiply(const vector<vector<long long>> &A, const vector<vector<long long>> &B)
    {
        int n = A.size();
        vector<vector<long long>> result(n, vector<long long>(n, INF));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int k = 0; k < n; ++k)
                {
                    if (A[i][k] != INF && B[k][j] != INF)
                    {
                        long long sum = A[i][k] + B[k][j];
                        if (sum < result[i][j])
                            result[i][j] = sum;
                    }
                }
            }
        }
        return result;
    }

    void shortest_paths()
    {
        int n = adjacency_matrix.size();
        vector<vector<long long>> result = adjacency_matrix;

        for (int i = 1; i < n; ++i)
        {
            result = min_plus_multiply(result, adjacency_matrix);
        }

        cout << "\nShortest path cost matrix (min-plus):\n";
        print_matrix(result);
    }
};

int main()
{
    Graph g(4);
    g.add_edge(0, 1, 2);
    g.add_edge(1, 2, 3);
    g.add_edge(0, 3, 10);
    g.add_edge(3, 2, 1);

    g.print_adjacency_matrix();
    g.shortest_paths();

    return 0;
}
