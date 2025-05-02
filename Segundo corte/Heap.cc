#include <iostream>
#include <vector>
#include <utility>   // pair
#include <random>    // random_device, mt19937, uniform_int_distribution
#include <algorithm> // swap

using namespace std;

// Tipo de dato que tomará el heap
template <typename T>
//Clase HeapMax: Buscara el elemento con mayor prioridad en el vector 
class HeapMax { 
private:
    vector<pair<int, T>> heap;       // par: <prioridad, valor>
    mt19937 rng;                     // generador random
    uniform_int_distribution<int> dist; // distribución para prioridad

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)].first < heap[index].first) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int l = left(index);
        int r = right(index);

        if (l < static_cast<int>(heap.size()) && heap[l].first > heap[smallest].first)
            smallest = l;
        if (r < static_cast<int>(heap.size()) && heap[r].first > heap[smallest].first)
            smallest = r;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const   { return 2 * i + 1; }
    int right(int i) const  { return 2 * i + 2; }

public:
    HeapMax(int min_priority = 1, int max_priority = 100)
        : rng(random_device{}()), dist(min_priority, max_priority) {}

    void insert(const T& value) {
        int priority = dist(rng);
        heap.push_back(make_pair(priority, value));
        heapifyUp(heap.size() - 1);
    }

    T extractMax() {
        if (heap.empty())
            throw runtime_error("Heap is empty");

        T maxValue = heap[0].second;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxValue;
    }

    void printHeap() const {
        for (const auto& p : heap) {
            cout << "[P:" << p.first << ", V:" << p.second << "] ";
        }
        cout << "\n";
    }

    bool isEmpty() const {
        return heap.empty();
    }
};

// Plantilla para un Heap Máximo basado en prioridad aleatoria
template <typename T>
class HeapMin {
private:
    vector<pair<int, T>> heap;       // par: <prioridad, valor>
    mt19937 rng;                     // generador random
    uniform_int_distribution<int> dist; // distribución para prioridad

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)].first > heap[index].first) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int l = left(index);
        int r = right(index);

        if (l < static_cast<int>(heap.size()) && heap[l].first < heap[smallest].first)
            smallest = l;
        if (r < static_cast<int>(heap.size()) && heap[r].first < heap[smallest].first)
            smallest = r;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const   { return 2 * i + 1; }
    int right(int i) const  { return 2 * i + 2; }

public:
    HeapMin(int min_priority = 1, int max_priority = 100)
        : rng(random_device{}()), dist(min_priority, max_priority) {}

    void insert(const T& value) {
        int priority = dist(rng);
        heap.push_back(make_pair(priority, value));
        heapifyUp(heap.size() - 1);
    }

    T extractMin() {
        if (heap.empty())
            throw runtime_error("Heap is empty");

        T maxValue = heap[0].second;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxValue;
    }

    void printHeap() const {
        for (const auto& p : heap) {
            cout << "[P:" << p.first << ", V:" << p.second << "] ";
        }
        cout << "\n";
    }

    bool isEmpty() const {
        return heap.empty();
    }
};


int main() {
    HeapMin<string> heapm;

    heapm.insert("perro");
    heapm.insert("gato");
    heapm.insert("pájaro");
    heapm.insert("elefante");

    heapm.printHeap();

    cout << "Elemento con menor prioridad: " << heapm.extractMin()<< "\n";

    heapm.printHeap();

    HeapMax<string> heapM;

    heapM.insert("Carro");
    heapM.insert("Moto");
    heapM.insert("Avion");
    heapM.insert("Barco");

    heapM.printHeap();
    cout << "Elemento con mayor prioridad: " << heapM.extractMax() << "\n";


    heapM.printHeap();

    return 0;
}
