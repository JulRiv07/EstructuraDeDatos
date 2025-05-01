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
        Node* y = nodo->getRight(); // Se crea un puntero 'y' apuntando al hijo derecho del nodo original. 

        nodo->setRight(y->getLeft());  // El hijo izquierdo de 'y' se convierte en el nuevo hijo derecho de 'nodo'. 
        // (porque 'nodo' baja a la izquierda de 'y')

        if (y->getLeft() != nullptr) // Si ese nuevo hijo derecho (antes hijo izquierdo de 'y') no es nulo, 
            y->getLeft()->setParent(nodo); // se actualiza su padre a 'nodo'.

        y->setParent(nodo->getParent()); // 'y' hereda el padre del nodo original.

        if (nodo->getParent() == nullptr)
            root_ = y; // Si el nodo original era la raíz, entonces ahora 'y' se convierte en la nueva raíz.
        else if (nodo == nodo->getParent()->getLeft())
            nodo->getParent()->setLeft(y); // Si el nodo original era hijo izquierdo, ahora su padre apuntará a 'y' como hijo izquierdo.
        else
            nodo->getParent()->setRight(y); // Si era hijo derecho, el padre apuntará a 'y' como hijo derecho.

        y->setLeft(nodo); // 'nodo' se convierte en hijo izquierdo de 'y'.

        nodo->setParent(y); // Y el nuevo padre de 'nodo' será 'y'.
    }

    /*
        Se realiza una rotación a la derecha cuando un nodo tiene un hijo izquierdo rojo
        que a su vez tiene un hijo izquierdo rojo, generando un desequilibrio a la izquierda.
        La rotación permite subir al hijo izquierdo y mantener el balance del árbol.
    */


    void rotateRight(Node* nodo) {
        Node* x = nodo->getLeft(); // Se crea un puntero 'x' que apunta a la izquierda del nodo original
        nodo->setLeft(x->getRight()); //El nodo original guarda a la izquierda la derecha de 'x'
        if (x->getRight() != nullptr) // Si la derecha de 'x' no es nula entonces...
            x->getRight()->setParent(nodo); // La derecha de 'x' guarda como padre el nodo original 

        x->setParent(nodo->getParent()); // 'x' uarda como padre el padre del nodo original 
        if (nodo->getParent() == nullptr) //Si el nodo original no tiene padre entonces...
            root_ = x; // 'x' se vuelve la raiz
        else if (nodo == nodo->getParent()->getRight())// Si no, si el nodo original era hijo derecho entonces...
            nodo->getParent()->setRight(x); // Ahora su padre apuntará a 'x' como hijo derecho
        else
            nodo->getParent()->setLeft(x); // Su padre apuntará a 'x' como hijo izquierdo

        x->setRight(nodo); // 'x' guarda a su derecha el nodo original 
        nodo->setParent(x); // El nuevo padre del nodo orignal es 'x'
    }

    /*
        Esta función se encarga de reequilibrar el árbol después de insertar un nuevo nodo.
        El nodo que se pasa como parámetro es el recién insertado.
    */

    void fixInsert(Node* z) {
        while (z->getParent() && z->getParent()->getColor() == RED) { // Mientras que el nodo no sea la raiz y el padre sea rojo 
            if (z->getParent() == z->getParent()->getParent()->getLeft()) { // Si el padre es hijo izquierdo
                Node* y = z->getParent()->getParent()->getRight(); // Se crea un puntero 'y' que apunta al tio, el otro hijo del abuelo
                if (y && y->getColor() == RED) { // Si el tio es rojo y no es nulo, entonces...
                    z->getParent()->setColor(BLACK); // Se pinta el padre del nodo original de negro
                    y->setColor(BLACK); // Se pinta el tio de negro 
                    z->getParent()->getParent()->setColor(RED); // Se pinta de rojo el abuelo 
                    z = z->getParent()->getParent(); //Subimos hasta el abuelo para seguir verificando
                } else {
                    if (z == z->getParent()->getRight()) { // Si es triangular
                        z = z->getParent(); //subimos un nivel
                        rotateLeft(z); //Se hace rotacion a la izquierda
                    }
                    z->getParent()->setColor(BLACK); // se pinta el padre del nodo original de negro
                    z->getParent()->getParent()->setColor(RED); // se pinta el abuelo del nodo original de rojo 
                    rotateRight(z->getParent()->getParent()); // Se rota a la derecha mandando como atributo al abuelo del nodo original
                }
            } else { // Si no entonces el padre es hijo derecho
                Node* y = z->getParent()->getParent()->getLeft(); // Se crea un puntero 'y' que apunta a el tio izquierdo 
                if (y && y->getColor() == RED) { // Si 'y' no es nulo y es rojo
                    z->getParent()->setColor(BLACK); // pinta el padre de negro
                    y->setColor(BLACK);//pinta el tio de negro 
                    z->getParent()->getParent()->setColor(RED);// pinta el abuelo de rojo 
                    z = z->getParent()->getParent();// sube al abuelo para verificar lo demas
                } else {
                    if (z == z->getParent()->getLeft()) { // Si es triangular
                        z = z->getParent();//Sube un nivel 
                        rotateRight(z);// Se hace rotacion a la derecha
                    }
                    z->getParent()->setColor(BLACK); //Pinta el padre de negro
                    z->getParent()->getParent()->setColor(RED); // Pinta el abuelo de rojo
                    rotateLeft(z->getParent()->getParent()); // Hace rotacion a la izquierda mandando como atributo el abuelo
                }
            }
        }
        root_->setColor(BLACK); // La raiz se pinta de negro, siempre!!!
    }

    // Reemplaza el subárbol en la posición de u con el subárbol en la posición de v

    void transplant(Node* u, Node* v) {
        if (u->getParent() == nullptr) // Si u no tiene padre entonces es la raiz
            root_ = v; // ahora v es la raiz 
        else if (u == u->getParent()->getLeft()) // Si no, si 'u' es el hijo izquierdo...
            u->getParent()->setLeft(v); //Ahora el hijo izquierdo será 'v'
        else
            u->getParent()->setRight(v); //Ahora el hijo derecho será 'v'
        if (v != nullptr) //Si 'v' es nulo enrtonces...
            v->setParent(u->getParent()); //El padre de 'v' será el padre de 'u'
    }

    // Devuelve el nodo con el valor mínimo en el subárbol cuyo nodo raíz es 'node'
 
    Node* minimum(Node* node) { 
        while (node->getLeft() != nullptr) //Mientras no sea nulo a la izquierda...
            node = node->getLeft(); //node baja a la izquierda buscando el menor
        return node; // Retorna el nodo menor a la izquierda del subarbol
    }

    //Se encarga de mantener el balance y las propiedades del árbol después de una eliminación

    void fixDelete(Node* x) {
        while (x != root_ && (x == nullptr || x->getColor() == BLACK)) { //Mientras que el nodo no sea la raiz y (Sea nulo o negro)
            if (x == x->getParent()->getLeft()) { // Si 'x' es hijo izquierdo...
                
                Node* w = x->getParent()->getRight(); //Puntero que apunta al hermano a la derecha del nodo 'x'

                if (w->getColor() == RED) { //Si el hermano es rojo 
                    w->setColor(BLACK); // Se colorea el hermano de negro
                    x->getParent()->setColor(RED); // Se pinta de rojo al padre de 'x' 
                    rotateLeft(x->getParent()); // Se realiza rotacion a la izquierda mandando como atributo el papá
                    w = x->getParent()->getRight(); // Actualiza al nuevo hermano derecho
                }

                if ((w->getLeft() == nullptr || w->getLeft()->getColor() == BLACK) && (w->getRight() == nullptr || w->getRight()->getColor() == BLACK)) {
                // Si el nodo hermano es nulo a la izquierda o tiene un hijo negro a su izquierda y a la derecha se cumple lo mismo 
                    w->setColor(RED); // Se pinta el hermano de rojo 
                    x = x->getParent(); // 'x' Subimos al padre
                } else {
                    if (w->getRight() == nullptr || w->getRight()->getColor() == BLACK) { // Si solo a la derecha del hermano es nulo o negro 
                        if (w->getLeft()) { // Si tiene un hijo a la izquierda (Rojo)
                            w->getLeft()->setColor(BLACK);  //Se pinta a negro el hijo izquierdo 
                        } 
                        w->setColor(RED); //Se pinta al hermano de rojo
                        rotateRight(w);// Se rota a la derecha enviando 'w' como atributo 
                        w = x->getParent()->getRight(); //Se actualiza el hermano al nuevo nodo derecho 
                    }
                    w->setColor(x->getParent()->getColor());// 'w' se colorea del mismo color del padre de 'x'
                    x->getParent()->setColor(BLACK); // Se pinta el padre de 'x' de color negro 
                    if (w->getRight()) w->getRight()->setColor(BLACK); // Si tiene un hijo rojo a la derecha, entonces se pinta ese hijo de negro 
                    rotateLeft(x->getParent()); // Se rota a la izquierda enviando como atributo el padre de x 
                    x = root_; // Se declara 'x' como la raiz 
                }
            } else {
                Node* w = x->getParent()->getLeft(); // Se crea un puntero que apunta al hermano a la izquierda del nodo 'x'
                if (w->getColor() == RED) { // Si el hermano es rojo entonces...
                    w->setColor(BLACK); //Se colorea el hermano de negro
                    x->getParent()->setColor(RED); //Se colorea de rojo el padre del nodo 'x' 
                    rotateRight(x->getParent()); // Se rota  a la derecha enviando el padre como atributo 
                    w = x->getParent()->getLeft(); // Se actualiza al nuevo hermano del nodo 'x'
                }
                if ((w->getRight() == nullptr || w->getRight()->getColor() == BLACK) && (w->getLeft() == nullptr || w->getLeft()->getColor() == BLACK)) {
                // Si tiene hijo a la derecha o si el hijo derecho es negro y si tiene hijo a la izquierda y si el hijo izquierdo es negro 
                    w->setColor(RED); // Se colorea de rojo el hermano 
                    x = x->getParent(); // Se sube la doble negrura al padre 
                } else {
                    if (w->getLeft() == nullptr || w->getLeft()->getColor() == BLACK) { // Si el hermano no tiene hijo izquierdo o si el hijo izquierdo es negro 
                        if (w->getRight()) w->getRight()->setColor(BLACK); // Si tiene hijo a la derecha, entonces se pinta de negro el hijo derecho 
                        w->setColor(RED); // Se colorea el hermano de rojo 
                        rotateLeft(w); // Se rota a la izquierda enviando el hermano como atributo 
                        w = x->getParent()->getLeft(); // Se actualiza al nuevo hermano 
                    }
                    w->setColor(x->getParent()->getColor()); // Se colorea el hermano del color del padre 
                    x->getParent()->setColor(BLACK); // Se colorea el padre de negro 
                    if (w->getLeft()) w->getLeft()->setColor(BLACK); //Si el hermano tiene hijo izquierdo, entonces Se pinta de negro el hijo izquierdo
                    rotateRight(x->getParent()); // Se rota enviando como atributo el padre 
                    x = root_; // Se actualiza la raiz a 'x'
                }
            }
        }

        if (x) x->setColor(BLACK); // Si 'x' no es nulo, entonces se pinta de negro 
    }

    // Busca un nodo que contenga el valor 'data' en el árbol

    Node* search(const T& data) const {
        Node* current = root_; // Comenzamos desde la raíz
        while (current != nullptr && data != current->getData()) { // Mientras no sea nulo y no sea igual al dato buscado, entonces...
            if (data < current->getData()) {
                current = current->getLeft(); // Si es menor, vamos a la izquierda
            } else {
                current = current->getRight(); // Si es mayor, vamos a la derecha
            }
        }   
        return current; // Si lo encontramos, lo retornamos; si no, retorna nullptr
    }

    //Para imprimir el arbol (Igual que en el BST)

    void inorder(Node* node) const { 
        if (node != nullptr) { // Si el arbol todavia tiene elementos entonces
            inorder(node->getLeft()); // Recursividad para ir recorriendo los elementos de la izquierda
            cout << node->getData() << (node->getColor() == RED ? " (R) " : " (B) "); // Imprime los datos y el color que tenian
            inorder(node->getRight());// Recursividad para ir recorriendo los elementos de la derecha
        }
    }

public:

    //Llamado del insert para el usuario 
    void insert(const T& data) {
        Node* newNode = new Node(data);// Se crea un nuevo nodo que almacenara el valor a insertar
        Node* y = nullptr; // Se crean los punteros, 'y' como nulo y 'x' como la raiz
        Node* x = root_;

        while (x != nullptr) { //Mientras 'x' no sea nulo entonces...
            y = x; // Se iguala 'y' a 'x'
            if (data < x->getData()) 
                x = x->getLeft(); // Se va moviendo por la izquierda del arbol si es menor 
            else
                x = x->getRight();// Se va moviendo por la derecha del arbol si es menor 
        }

        newNode->setParent(y); //El padre de nuevo nodo será 'y'
        if (y == nullptr) // Si no hay padre quiere decir que estaba vacio 
            root_ = newNode; // Será la raiz
        else if (data < y->getData()) // Si es menos que el padre...
            y->setLeft(newNode); // Lo ponermos en la izquierda
        else
            y->setRight(newNode); // Si no, a la derecha

        fixInsert(newNode); //Se realizan todos los procesos necesarios para ubicar el nuevo nodo
    }

    //Llamado del remove para el usuario 
    void remove(const T& data) {  // Se llama con el dato a borrar 
        Node* z = search(data); // Busca si esta el dato en el arbol 
        if (!z) return; // Si no esta entonces no retorna nada 

        Node* y = z; // 'y' es el nodo que se eliminará o que reemplazará a 'z'
        Color yOriginalColor = y->getColor(); // Se guarda el color original de 'y'
        Node* x = nullptr; // Este será el nodo que tomará el lugar de 'y' (el que sube)
        if (z->getLeft() == nullptr) { // Si 'z' no tiene hijo izquierdo 
            x = z->getRight();// 'x' es el nuevo hijo del padre de 'z'
            transplant(z, z->getRight()); // Reemplazamos 'z' por su hijo derecho
        } else if (z->getRight() == nullptr) { // Si no, si 'z' no tiene hijo derecho 
            x = z->getLeft(); // 'x' es el nuevo hijo del padre de 'z'
            transplant(z, z->getLeft()); // Se remplaza 'z' por su hijo izquierdo 
        } else { // Si no...
            y = minimum(z->getRight()); // Se busca el minimo, el sucesor 
            yOriginalColor = y->getColor(); // sE guarda el color del sucesor 
            x = y->getRight(); // x será el hijo derecho del sucesor 
            if (y->getParent() == z) { // Si 'y' es el hijo de 'z'
                if (x) x->setParent(y); //Si 'x' no es nulo entonces su padré será 'y'
            } else { // Si no...
                transplant(y, y->getRight()); //Se cambia y por su hijo derecho 
                y->setRight(z->getRight()); // Se guarda como hijo derecho de 'y' a la derecha de 'z'
                y->getRight()->setParent(y); // Se actualiza el padre del nuevo hijo derecho de 'y'
            }
            transplant(z, y); // Se remplaza 'z' por 'y' 
            y->setLeft(z->getLeft()); // Se guarda como hijo izquierdo el hijo izquierdo de 'z'
            y->getLeft()->setParent(y); // Se actualiza el padre del nuevo hijo izquierdo de 'y'
            y->setColor(z->getColor()); // Se guarda 'y' con el color de 'z' 
        }

        delete z; // Borramos el nodo original

        if (yOriginalColor == BLACK && x != nullptr) //Si el color original era negro entonces...
            fixDelete(x); // Se repara el arbol de ser necesario
    }

    //Imprime el arbol con el metodo inorder 

    void printInOrder() const { 
        inorder(root_); //Se llama el metodo con la raiz como atributo 
        cout << endl;
    }
};+

int main() { //Main funcion principal (Probar el codigo)
    RBT<int> tree; //Se crea el arbol
    //Insertar 5 elementos donde la raiz inicial es 10
    tree.insert(10); 
    tree.insert(20);
    tree.insert(15);
    tree.insert(30);
    tree.insert(5);
    tree.printInOrder(); // Iprimir el arbol actual 

    tree.remove(15); // Remover el 15 
    tree.printInOrder(); // Iprimir el arbol actual 
    return 0;
}
