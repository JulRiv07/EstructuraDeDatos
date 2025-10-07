#include <iostream> 
#include <vector>
#include <list>

using namespace std;

class GrafoNN {
    private: 
        int v;
        vector <list<int>> adj;

    public:

        GrafoNN(int dest){
            v = dest;
            adj.resize(v);
        }

        void AddArist(int x, int y){
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        void show(){
            for (int i = 0; i < v; i++){
                cout << i << ": ";
                for (int j : adj[i]){
                    cout << j << " ";
                }
                cout << endl;
            }
        }
};

class GrafoDN{
    private: 
        int v;
        vector <list<int>> adj;

    public:

    GrafoDN(int dest){
        v = dest;
        adj.resize(v);
    }

    void AddArist(int x, int y){
        adj[x].push_back(y);
    }

    void show(){
        for(int i = 0; i < v; i++){
            cout << i << ": ";
            for(int j : adj[i]){
                cout << j << " ";
            }
            cout << endl;
        }
    }

};

class Arista {
    public:
        int dest;
        int peso;

        Arista(int x, int y){
            dest = x;
            peso = y;
        }
};

class GrafoNP{
    private:
        int v;
        vector<list<Arista>> adj;
    
    public:

    GrafoNP(int dest){
        v = dest;
        adj.resize(v);
    }

    void AddArista(int x, int y, int peso){
        adj[x].push_back(Arista(v, peso));
        adj[y].push_back(Arista(x, peso));
    }

    void show(){
        for(int i = 0; i < v; i++){
            cout << i << ": ";
            for(const Arista& arista : adj{i}){
                cout << "(" << arista.dest << ", " << arista.peso << ") ";
            
                cout << endl;
        }
    }
};



int main() {
    cout << "Grafo No Dirigido y No Ponderado:\n";
    GrafoNN g1(5);
    g1.AddArist(0, 1);
    g1.AddArist(0, 4);
    g1.AddArist(1, 2);
    g1.show();

    cout << endl;

    cout << "\nGrafo Dirigido y No Ponderado:\n";
    GrafoDN g2(5);
    g2.AddArist(0, 1);
    g2.AddArist(0, 4);
    g2.AddArist(1, 2);
    g2.show();

    return 0;
}