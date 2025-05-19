#include <iostream>   
#include <vector>     
#include <algorithm>  

using namespace std;

class Edge {
public:
    int src, dest;   // Nodo origen y destino
    int weight;      // Peso de la arista

    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}

    // Para ordenar aristas por peso
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};


class DisjointSet {
private:
    vector<int> parent, rank;

public:
    // Constructor inicializa N sets disjuntos (cada nodo es su propio padre)
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // Encuentra el padre (representante) del set con path compression
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Une dos sets si son diferentes, usando union por rango
    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV)
            return false; // Ya están en el mismo set (ciclo)

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
    int V;                  // Número de vértices
    vector<Edge> edges;     // Lista de aristas

public:
    Graph(int vertices) : V(vertices) {}

    // Agrega una arista
    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    // Ejecuta el algoritmo de Kruskal para encontrar MST
    vector<Edge> kruskalMST() {
        vector<Edge> result;      // Aristas del MST
        DisjointSet ds(V);

        // Ordena aristas por peso ascendente
        sort(edges.begin(), edges.end());

        for (Edge& e : edges) {
            if (ds.unite(e.src, e.dest)) {
                result.push_back(e);
                if (result.size() == V - 1)
                    break;  // MST completo
            }
        }

        return result;
    }
};

int main() {
    Graph g(4); // Grafo con 4 nodos (0 a 3)

    // Agregar aristas: (origen, destino, peso)
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    vector<Edge> mst = g.kruskalMST();

    cout << "Aristas del MST:\n";
    for (const Edge& e : mst) {
        cout << e.src << " -- " << e.dest << " == " << e.weight << "\n";
    }

    return 0;
}
