#include <iostream> 
#include <random>
#include <ctime>
#include <cmath>      
#include <algorithm> 

using namespace std;

template<typename KeyType, typename ValueType> 
class Treap {
private:
    class Node {
    public:
        KeyType key;
        ValueType value;
        double priority;
        Node* left;
        Node* right;

        // Constructor del nodo que recibe la llave, valor y prioridad
        Node(KeyType k, ValueType v, double p) {
            key = k;
            value = v;
            priority = p;
            left = nullptr;
            right = nullptr; 
        }
    };

    Node* root;
    mt19937 rng;
    uniform_real_distribution<double> priority_dist;

    // Priority random generator
    double generatePriority() {
        return priority_dist(rng);
    }

    // Rotaciones 

    // Rota el árbol a la derecha buscando cumplir las propiedades del Treap
    Node* rotateRight(Node* y) {
        Node* x = y->left; // Crea un nodo con el valor del nodo a la izquierda de 'y'
        Node* T2 = x->right; // Crea un nodo que apunta la derecha de 'x' 
        x->right = y; // Pone a la derecha de 'x' el nodo 'y' 
        y->left = T2; // Pone el nodo guardado en T2 (anterior derecha de x) a la izquierda de 'y' 
        return x; // Retorna 'x', ya todo está rotado 
    }

    // Rota el árbol a la izquierda buscando cumplir las propiedades del Treap
    Node* rotateLeft(Node* x) {
        Node* y = x->right; // Crea un nodo que guarda la derecha del nodo 
        Node* T2 = y->left; // Crea un nodo que guarda la izquierda de 'y'
        y->left = x; // Pone a la izquierda de 'y' el nodo 'x' (original)
        x->right = T2; // Pone a la derecha de 'x' el nodo T2
        return y; // Devuelve el nodo con todas las rotaciones ya hechas
    }

    // Inserción de un nodo al Treap
    Node* insert(Node* node, KeyType key, ValueType value) {
        if (!node) { // Si el nodo está vacío 
            return new Node(key, value, generatePriority());
        }

        if (key < node->key) { // Si la llave a insertar es menor a la del nodo actual 
            node->left = insert(node->left, key, value); // Recursivamente se busca el lugar para el nodo a la izquierda
            if (node->left->priority > node->priority) // Si la prioridad del nodo a la izquierda es mayor que la del nodo actual
                node = rotateRight(node);   // Se hace rotación a la derecha
        } else if (key > node->key) { // Si la llave es mayor
            node->right = insert(node->right, key, value); // Recursivamente se busca el lugar para el nodo a la derecha 
            if (node->right->priority > node->priority) // Si la prioridad del nodo a la derecha es mayor
                node = rotateLeft(node); // Se hace rotación a la izquierda
        } else { // Si la llave ya existe
            node->value = value; // Solo se actualiza el valor 
        }

        return node; // Retorna el nodo
    }

    // Eliminación de un nodo manteniendo las propiedades del Treap
    Node* deleteNode(Node* node, KeyType key) {
        if (!node) return nullptr; // Si el nodo está vacío no hace nada

        if (key < node->key) {  // Si la llave es menor que la del nodo actual...
            node->left = deleteNode(node->left, key); // Se va moviendo recursivamente por izquierda
        } else if (key > node->key) { // Si la llave es mayor que la del nodo actual...
            node->right = deleteNode(node->right, key); // Se va moviendo recursivamente por derecha 
        } else { // Si no es porque ya llegó 
            if (!node->left) { // Si el nodo no tiene hijo izquierdo 
                Node* temp = node->right; // Se guarda temporalmente la derecha del nodo 
                delete node; // Se elimina el nodo
                return temp; // Se retorna el nodo guardado temporalmente 
            } else if (!node->right) { // Si el nodo no tiene hijo derecho
                Node* temp = node->left; // Se guarda temporalmente la izquierda del nodo
                delete node; // Se elimina el nodo
                return temp; // Se retorna el nodo temporal 
            } else { // Si tiene ambos hijos
                if (node->left->priority > node->right->priority) { // Si el nodo izquierdo tiene mayor prioridad
                    node = rotateRight(node); // Se hace rotación a la derecha
                    node->right = deleteNode(node->right, key); // El nuevo nodo a la derecha será el resultado de eliminar el nodo a la derecha original
                } else { // Si la prioridad a la derecha es mayor
                    node = rotateLeft(node); // Se hace rotación a la izquierda
                    node->left = deleteNode(node->left, key); // El nuevo nodo a la izquierda será el resultado de eliminar el nodo a la izquierda original
                }
            }
        }

        return node; // Retorna el nodo
    }

    // Búsqueda básica
    Node* search(Node* node, KeyType key) {
        if (!node) return nullptr; // Si el nodo está vacío, no se encuentra
        if (key == node->key) return node; // Si se encuentra la llave, se retorna el nodo 
        if (key < node->key) // Si la llave a buscar es menor que la del nodo actual 
            return search(node->left, key); // Se hace recursivamente por la izquierda
        else // Si es mayor
            return search(node->right, key); // Se hace recursivamente por la derecha
    }

    // Inorder traversal
    void inorder(Node* node) {
        if (node) { // Si el nodo existe
            inorder(node->left); // Se hace recursión por la izquierda
            cout << "Key: " << node->key << " | Value: " << node->value << " | Priority: " << node->priority << "\n"; 
            inorder(node->right); // Se hace recursión por la derecha
        }
    }

    // Calcula la altura del Treap desde el nodo actual
    int computeHeight(Node* node) {
        if (!node) return 0; // Si el nodo es nulo, su altura es 0
        return 1 + std::max(computeHeight(node->left), computeHeight(node->right)); // Retorna 1 (por el nodo actual) más la mayor altura entre los hijos
    }

    // Cuenta cuántos nodos hay en el Treap desde el nodo actual
    int countNodes(Node* node) {
        if (!node) return 0; // Si el nodo es nulo, no hay nada que contar
        return 1 + countNodes(node->left) + countNodes(node->right); // Cuenta este nodo (1) más todos los de su subárbol izquierdo y derecho
    }

public:
    Treap() // Constructor del Treap
        : root(nullptr),
          rng(static_cast<unsigned int>(std::time(nullptr))),
          priority_dist(0.0, 1.0) {}

    // Llamado al insertar desde el usuario
    void insert(KeyType key, ValueType value) {
        root = insert(root, key, value);
    }

    // Llamado a eliminar desde el usuario
    void deleteKey(KeyType key) {
        root = deleteNode(root, key);
    }

    // Busca una llave
    bool search(KeyType key, ValueType& result) {
        Node* node = search(root, key);
        if (node) {
            result = node->value;
            return true;
        }
        return false;
    }

    // Imprime el árbol en orden
    void printInorder() {
        std::cout << "\nInorder traversal of Treap:\n";
        inorder(root);
    }

    // Altura del Treap 
    int height() {
        return computeHeight(root);
    }

    // Muestra estadísticas del Treap como el tamaño, altura y altura óptima esperada
    void stats() {
        int count = countNodes(root); // Cuenta total de nodos del árbol (n)
        int h = computeHeight(root);  // Calcula la altura actual del árbol (máxima profundidad)
        
        // Altura óptima esperada si el árbol estuviera perfectamente balanceado (log base e de n)
        double optimalHeight = count > 0 ? std::log(count) : 0.0;

        // Imprime todas las estadísticas
        std::cout << "\n--- Treap Stats ---\n";
        std::cout << "Size: " << count << "\n"; // Número de nodos en el árbol
        std::cout << "Height: " << h << "\n"; // Altura real del árbol
        std::cout << "Optimal Height (log(n)): " << optimalHeight << "\n"; // Altura ideal si estuviera balanceado
    }
};

// Función main de ejemplo
int main() {
    Treap<int, string> treap;
    // Se crea un treap con llave como entero y valor como string...

    // Se insertan los elementos al Treap...
    treap.insert(30, "thirty");
    treap.insert(20, "twenty");
    treap.insert(40, "forty");
    treap.insert(10, "ten");

    // Imprime el Treap y las estadisticas jaaajaaj
    treap.printInorder();
    treap.stats();

    // Ahora eliminamos un nodo 
    treap.deleteKey(20);
    // Imprime el Treap actualizado  y las estadisticas 
    treap.printInorder();
    treap.stats();

    return 0;
}
