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

        //Nantiene la propiedad de Heap maximo
        void heapifyUp(int index) { // Recibe como parametro el indice del nodo 
            while (index > 0 && heap[parent(index)].first < heap[index].first) { // Mientras que el indice sea mayor que 0 y el padre sea menor al elemento en dicho indice
                swap(heap[index], heap[parent(index)]); // Intercambia el hijo (Elemento en el indice) con el padre 
                index = parent(index); // Se modifica el indice a la posicion del padre
            } 
        }


        //Baja el nodo raiz hasta que este en la ppsicion correcta para mantener la propiedad 
        void heapifyDown(int index) { // Recibe como parametro el indice del nodo
            int largest  = index; //Dice que el nodo actual tiene la mayor prioridad 
            int l = left(index); // Izquierda del indice 
            int r = right(index); // Derecha del indice 

            if (l < static_cast<int>(heap.size()) && heap[l].first > heap[largest].first) 
            // Si el hijo izquierdo tiene mayor prioridad y l pertenece al vector 
                largest = l; // Ahora la mayor prioridad la tendra el hijo izquierdo 
            if (r < static_cast<int>(heap.size()) && heap[r].first > heap[largest].first)
            // Lo mismo, si r pertence al vector y el elemento en su indice tiene mayor prioridad 
                largest = r; // Ahora la mayor orioridad la tendra el hijo derecho 

            if (largest != index) { // Si largest cambio de valor en el proceso entonces...
                swap(heap[index], heap[largest]); // Se intercambia el elemento en el indice original con largest 
                heapifyDown(largest); // Se hace recursion de la funcion...
            }
        }

        int parent(int i) const { // El padre será...
            return (i - 1) / 2; 
        } 

        int left(int i) const {  // La izquierda será...
            return 2 * i + 1; 
        }
        
        int right(int i) const { //La derecha será...
            return 2 * i + 2; 
        }

    public:

        HeapMax(int min_priority = 1, int max_priority = 100) // Constructor de la clase 
            : rng(random_device{}()), dist(min_priority, max_priority) {} // Generará prioridades aleatorias en el rango de min y max priority 

        // Metodo de insercion en el heap
        void insert(const T& value) { //Su atributo es el valor a ingresar 
            int priority = dist(rng); // Genera una prioridad aleatoria basado en "rng"
            heap.push_back(make_pair(priority, value)); // Coloca al final el elemento como pareja <priority y value>
            heapifyUp(heap.size() - 1); // Ordena el heap de ser necesario, manda como atributo la posicion final
        }

        //Funcion que extrae el maximo elemento del heap 
        T extractMax() { 
            if (heap.empty()) // Si el heap esta vacio...
                throw runtime_error("Heap is empty"); // Rompe el programa 

            T maxValue = heap[0].second; // Guarda como valor maximo el segundo elemento en la pareja almacenada por la raiz
            heap[0] = heap.back(); // Se modifica la raiz por el ultimo elemento 
            heap.pop_back(); //Elimina el elemento final eliminando los duplicados
            heapifyDown(0); //Arregla el heap de ser necesario, envia como atributo la nueva raiz
            return maxValue; // Retorna el valor maximo guardado anteriormente 
        }

        //Imprime el heap 
        void printHeap() const { 
            for (const auto& p : heap) { //Va recorriendo las p (parejas) del heap
                cout << "[P:" << p.first << ", V:" << p.second << "] "; // Imoprime las parejas p.first (prioridad) p.second (valor)
            }
            cout << "\n"; //Salto de linea 
        }

        // Funcion booleana que dice si el heap esta vacio
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

        void heapifyUp(int index) { // Recibe como parametro el indice del nodo 
            while (index > 0 && heap[parent(index)].first > heap[index].first) {  // Mientras que el indice sea mayor que 0 y el padre sea mayor al elemento en dicho indice
                swap(heap[index], heap[parent(index)]); // Se intercambia el elemento con el padre, quedando el menor como el padre 
                index = parent(index); // Se modifica el indice y se repite el ciclo  
            }
        }

        //Repara el heap de ser necesario, bajando el elemento hasta que se cumplan las propiedades
        void heapifyDown(int index) {
            int smallest = index; // Mas pequeño es el atributo
            int l = left(index); // Hijo a la izquierda del indice
            int r = right(index); // Hijo a la derecha del indice 

            if (l < static_cast<int>(heap.size()) && heap[l].first < heap[smallest].first) 
                // Si el hijo izquierdo si esta en el vector y es menor que el elemento en el indice 
                smallest = l; // Se actualiza el mas pequeño  
            if (r < static_cast<int>(heap.size()) && heap[r].first < heap[smallest].first)
                // Si el hijo derecho si esta en el vector y es menor que el elemento en el indice 
                smallest = r; // Se actualiza el mas pequeño  

            if (smallest != index) { // Si el mas pequeño cambió en el proceso entonces...
                swap(heap[index], heap[smallest]); // Se intercambia el elemento en el indice con el mas pequeño 
                heapifyDown(smallest); // Se hace la recursion 
            }
        }

        int parent(int i) const { // El padre será...
            return (i - 1) / 2; 
        } 

        int left(int i) const {  // La izquierda será...
            return 2 * i + 1; 
        }
        
        int right(int i) const { //La derecha será...
            return 2 * i + 2; 
        }

    public:
        HeapMin(int min_priority = 1, int max_priority = 100) //Constructor de la clase 
            : rng(random_device{}()), dist(min_priority, max_priority) {} // Elegirá valores aleatorios en el rango de min y max priority

        // Metodo de insercion, recibe como parametro el valor a insertar 
        void insert(const T& value) { 
            int priority = dist(rng); // Se genera una prioridad
            heap.push_back(make_pair(priority, value)); //Pone al final del heap la pareja <prioridad (aleatoria) y valor>
            heapifyUp(heap.size() - 1); // Reacomoda el arbol de ser necesario enviando como indice la posicion del elemento 
        }

        T extractMin() { // Extrae el valor minimo del Heap 
            if (heap.empty()) // Si el heap esta vacio...
                throw runtime_error("Heap is empty"); //Rompe el programa 

            T maxValue = heap[0].second; // Guarda como valor maximo el valor a la cabeza del heap (Segundo elemento de la pareja: Value)
            heap[0] = heap.back(); // Cambia el elemento a la cabeza en su lugar coloca el ultimo elemento del heap
            heap.pop_back(); //Elimina el ultimo elemento (Quita el duplicado )
            heapifyDown(0); // Reorganiza de ser necesario, enviando el nuevo elemento a la cabeza
            return maxValue; // Retorna el que fue guardado como maximo 
        }

        void printHeap() const { //Imprime el heap 
            for (const auto& p : heap) { // Recorre cada p (pareja) del heap 
                cout << "[P:" << p.first << ", V:" << p.second << "] ";
                // Imprime: p.first (Prioridad) p.second (Valor)
            }
            cout << "\n"; // Salto de linea 
        }

        // Metodo booleano que nos dice si el arbol esta vacio o no 
        bool isEmpty() const {
            return heap.empty();
        }
};

//Main y pruebas
int main() {
    HeapMin<string> heapm; // Heapmin llamado heapm

    //Se agregan elementos al heap 
    heapm.insert("perro");
    heapm.insert("gato");
    heapm.insert("pájaro");
    heapm.insert("elefante");
    //Se imprime el heap...
    heapm.printHeap();
    cout << "Elemento con menor prioridad: " << heapm.extractMin()<< "\n";
    //Se muestra el elemento con menor prioridad y se elimina 
    heapm.printHeap(); // Se imprime el heap actualizado 

    HeapMax<string> heapM; // Heapmax llamado heapM

    //Se agregan elementos al heap 
    heapM.insert("Carro");
    heapM.insert("Moto");
    heapM.insert("Avion");
    heapM.insert("Barco");
    //Se imprime el heap...
    heapM.printHeap();
    cout << "Elemento con mayor prioridad: " << heapM.extractMax() << "\n";
    //Se muestra el elemento con mayor prioridad y se elimina 
    heapM.printHeap(); // Se imprime el heap actualizado 

    return 0;
}
