#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>

using namespace std;

typedef pair<int, int> Edge;

class Graph {
private:
    int V; 
    vector<vector<Edge>> adjList;

public:

    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        if (u == v) return;
        adjList[u].push_back({weight, v});
        adjList[v].push_back({weight, u});
    }

    bool hasEdge(int u, int v) {
        for (auto& edge : adjList[u]) {
            if (edge.second == v)
                return true;
        }
        return false;
    }

    void print() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < V; ++i) {
            cout << i << ": ";
            for (auto& edge : adjList[i]) {
                cout << "(" << edge.second << ", " << edge.first << ") ";
            }
            cout << "\n";
        }
    }

    void primMST() {
        vector<bool> inMST(V, false); 
        vector<int> key(V, numeric_limits<int>::max()); 
        vector<int> parent(V, -1); 
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq; 

        key[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (auto& [weight, v] : adjList[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push({weight, v});
                    parent[v] = u;
                }
            }
        }

        // Display result
        cout << "\nEdges in the Minimum Spanning Tree (Prim):\n";
        int totalWeight = 0;
        for (int i = 1; i < V; ++i) {
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i << " (weight " << key[i] << ")\n";
                totalWeight += key[i];
            }
        }
        cout << "Total weight of MST: " << totalWeight << endl;
    }
};

int main() {
    int n = 25;
    Graph g(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> nodeDist(0, n - 1);
    uniform_int_distribution<> weightDist(1, 100);

    int edgesAdded = 0;
    while (edgesAdded < 60) { 
        int u = nodeDist(gen);
        int v = nodeDist(gen);
        int w = weightDist(gen);
        if (u != v && !g.hasEdge(u, v)) {
            g.addEdge(u, v, w);
            edgesAdded++;
        }
    }

    g.print();
    g.primMST();

    return 0;
}