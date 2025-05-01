#include <iostream>
using namespace std;
enum Color { RED, BLACK }; // Colores que usaremos...

template <typename T> // Tipo de dato que tomará el RBT
class RBT { // Se crea la clase RBT
private: 

    class Node { // Se crea la clase Node
    private:

        T data_; // Data de tipo T 
        Node* left_; // Puntero a la izquierda de tipo Node
        Node* right_; // Puntero a la derecha de tipo Node 
        Node* parent_; // Puntero al padre de tipo Node
        Color color_; // Color de tipo color 

    public:

        //Constructor de la clase con un atributo de tipo T que almacena el dato que se encontrará en el nodo
        Node(const T value){
            data_ = value;
            left_ = nullptr;
            right_ = nullptr;
            parent_ = nullptr;
            color_ = RED;
        }

        //Devuelve el dato almacenado en el nodo 
        T getData() const { 
            return data_; 
        }

        //Guarda el dato que almacenará el nodo
        void setData(const T& data) {
             data_ = data; 
        }

        //Toma el nodo a la izquiera del nodo actual 
        Node* getLeft() const { 
            return left_; 
        }

        //Guarda el nodo a la izquiera del nodo actual
        void setLeft(Node* left) { 
            left_ = left; 
        }

        //Toma el nodo a la derecha del nodo actual
        Node* getRight() const { 
            return right_; 
        }

        //Guarda el nodo a la derecha del nodo actual
        void setRight(Node* right) { 
            right_ = right; 
        }

        //Toma el padre 
        Node* getParent() const { 
            return parent_; 
        }

        //Guarda el nodo como padre 
        void setParent(Node* parent) { 
            parent_ = parent; 
        }

        //Toma el color almecenado en el nodo
        Color getColor() const { 
            return color_; 
        }

        //Guarda el color del nodo
        void setColor(Color color) { 
            color_ = color; 
        }

    };

    Node* root_ = nullptr; //Declara la raiz como un puntero nulo de tipo Node

    /* 
        Se realiza una rotación a la izquierda cuando un nodo tiene un hijo derecho rojo
        que a su vez tiene un hijo derecho rojo, generando un desequilibrio a la derecha.
        La rotación permite subir al hijo derecho y mantener el balance del árbol.
    */

    void rotateLeft(Node* nodo) {
        Node* y = nodo->getRight();
        nodo->setRight(y->getLeft());
        if (y->getLeft() != nullptr)
            y->getLeft()->setParent(nodo);

        y->setParent(nodo->getParent());
        if (nodo->getParent() == nullptr)
            root_ = y;
        else if (nodo == nodo->getParent()->getLeft())
            nodo->getParent()->setLeft(y);
        else
            nodo->getParent()->setRight(y);

        y->setLeft(nodo);
        nodo->setParent(y);
    }

    void rotateRight(Node* nodo) {
        Node* x = nodo->getLeft();
        nodo->setLeft(x->getRight());
        if (x->getRight() != nullptr)
            x->getRight()->setParent(nodo);

        x->setParent(nodo->getParent());
        if (nodo->getParent() == nullptr)
            root_ = x;
        else if (nodo == nodo->getParent()->getRight())
            nodo->getParent()->setRight(x);
        else
            nodo->getParent()->setLeft(x);

        x->setRight(nodo);
        nodo->setParent(x);
    }

    void fixInsert(Node* z) {
        while (z->getParent() && z->getParent()->getColor() == RED) {
            if (z->getParent() == z->getParent()->getParent()->getLeft()) {
                Node* y = z->getParent()->getParent()->getRight();
                if (y && y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getRight()) {
                        z = z->getParent();
                        rotateLeft(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    rotateRight(z->getParent()->getParent());
                }
            } else {
                Node* y = z->getParent()->getParent()->getLeft();
                if (y && y->getColor() == RED) {
                    z->getParent()->setColor(BLACK);
                    y->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    z = z->getParent()->getParent();
                } else {
                    if (z == z->getParent()->getLeft()) {
                        z = z->getParent();
                        rotateRight(z);
                    }
                    z->getParent()->setColor(BLACK);
                    z->getParent()->getParent()->setColor(RED);
                    rotateLeft(z->getParent()->getParent());
                }
            }
        }
        root_->setColor(BLACK);
    }

    void transplant(Node* u, Node* v) {
        if (u->getParent() == nullptr)
            root_ = v;
        else if (u == u->getParent()->getLeft())
            u->getParent()->setLeft(v);
        else
            u->getParent()->setRight(v);
        if (v != nullptr)
            v->setParent(u->getParent());
    }

    Node* minimum(Node* node) {
        while (node->getLeft() != nullptr)
            node = node->getLeft();
        return node;
    }

    void fixDelete(Node* x) {
        while (x != root_ && (x == nullptr || x->getColor() == BLACK)) {
            if (x == x->getParent()->getLeft()) {
                Node* w = x->getParent()->getRight();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    rotateLeft(x->getParent());
                    w = x->getParent()->getRight();
                }
                if ((w->getLeft() == nullptr || w->getLeft()->getColor() == BLACK) &&
                    (w->getRight() == nullptr || w->getRight()->getColor() == BLACK)) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getRight() == nullptr || w->getRight()->getColor() == BLACK) {
                        if (w->getLeft()) w->getLeft()->setColor(BLACK);
                        w->setColor(RED);
                        rotateRight(w);
                        w = x->getParent()->getRight();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    if (w->getRight()) w->getRight()->setColor(BLACK);
                    rotateLeft(x->getParent());
                    x = root_;
                }
            } else {
                Node* w = x->getParent()->getLeft();
                if (w->getColor() == RED) {
                    w->setColor(BLACK);
                    x->getParent()->setColor(RED);
                    rotateRight(x->getParent());
                    w = x->getParent()->getLeft();
                }
                if ((w->getRight() == nullptr || w->getRight()->getColor() == BLACK) &&
                    (w->getLeft() == nullptr || w->getLeft()->getColor() == BLACK)) {
                    w->setColor(RED);
                    x = x->getParent();
                } else {
                    if (w->getLeft() == nullptr || w->getLeft()->getColor() == BLACK) {
                        if (w->getRight()) w->getRight()->setColor(BLACK);
                        w->setColor(RED);
                        rotateLeft(w);
                        w = x->getParent()->getLeft();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(BLACK);
                    if (w->getLeft()) w->getLeft()->setColor(BLACK);
                    rotateRight(x->getParent());
                    x = root_;
                }
            }
        }
        if (x) x->setColor(BLACK);
    }

    Node* search(Node* node, const T& key) const {
        if (node == nullptr || node->getData() == key)
            return node;
        if (key < node->getData())
            return search(node->getLeft(), key);
        else
            return search(node->getRight(), key);
    }

    void inorder(Node* node) const {
        if (node != nullptr) {
            inorder(node->getLeft());
            cout << node->getData() << (node->getColor() == RED ? " (R) " : " (B) ");
            inorder(node->getRight());
        }
    }

public:
    void insert(const T& data) {
        Node* newNode = new Node(data);
        Node* y = nullptr;
        Node* x = root_;

        while (x != nullptr) {
            y = x;
            if (data < x->getData())
                x = x->getLeft();
            else
                x = x->getRight();
        }

        newNode->setParent(y);
        if (y == nullptr)
            root_ = newNode;
        else if (data < y->getData())
            y->setLeft(newNode);
        else
            y->setRight(newNode);

        fixInsert(newNode);
    }

    void remove(const T& data) {
        Node* z = search(root_, data);
        if (!z) return;

        Node* y = z;
        Color yOriginalColor = y->getColor();
        Node* x;

        if (z->getLeft() == nullptr) {
            x = z->getRight();
            transplant(z, z->getRight());
        } else if (z->getRight() == nullptr) {
            x = z->getLeft();
            transplant(z, z->getLeft());
        } else {
            y = minimum(z->getRight());
            yOriginalColor = y->getColor();
            x = y->getRight();
            if (y->getParent() == z) {
                if (x) x->setParent(y);
            } else {
                transplant(y, y->getRight());
                y->setRight(z->getRight());
                y->getRight()->setParent(y);
            }
            transplant(z, y);
            y->setLeft(z->getLeft());
            y->getLeft()->setParent(y);
            y->setColor(z->getColor());
        }
        if (yOriginalColor == BLACK && x != nullptr)
            fixDelete(x);
    }

    void printInOrder() const {
        inorder(root_);
        cout << endl;
    }
};

int main() {
    RBT<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(15);
    tree.insert(30);
    tree.insert(5);
    tree.printInOrder();

    tree.remove(15);
    tree.printInOrder();

    return 0;
}
