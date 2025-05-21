#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest;   
    int weight;       

    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};
class DisjointSet {
private:
    vector<int> parent;  
    vector<int> rank;    

public:

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV)
            return false; 

        if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else if (rank[rootV] < rank[rootU])
            parent[rootV] = rootU;
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

class Graph {
private:
    int V;                  
    vector<Edge> edges;     

public:

    Graph(int vertices) {
        V = vertices ;
    }

    void addEdge(int src, int dest, int weight) {
        edges.emplace_back(src, dest, weight);
    }

    vector<Edge> kruskalMST() {
        vector<Edge> mst;           
        DisjointSet ds(V);          

        sort(edges.begin(), edges.end());

        for (Edge& edge : edges) {
            if (ds.unite(edge.src, edge.dest)) {
                mst.push_back(edge);
                if ((int)mst.size() == V - 1)
                    break;
            }
        }

        return mst;
    }

    void printMST(const vector<Edge>& mst) {
        int totalWeight = 0;
        cout << "Edges in the MST:\n";
        for (const Edge& e : mst) {
            cout << e.src << " -- " << e.dest << " == " << e.weight << "\n";
            totalWeight += e.weight;
        }
        cout << "Total weight of MST: " << totalWeight << "\n";
    }
};

int main() {
    int vertices = 1000;
    Graph graph(vertices);

    for (int i = 0; i < vertices - 1; i++) {
        graph.addEdge(i, i + 1, rand() % 100 + 1);  
        if (i + 10 < vertices)
            graph.addEdge(i, i + 10, rand() % 100 + 1);
    }

    vector<Edge> mst = graph.kruskalMST();
    graph.printMST(mst);

    return 0;
}
