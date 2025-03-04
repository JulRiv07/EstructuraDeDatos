#include <iostream> //Se incluyte la libreria

using namespace std; 

template <typename T> //Para dar el tipo de datos que almacenara la lista

class List {

    private:
        class Node { // Se declara la clase Node que tendra direccion y dato que guardaremos 
            private:
                T data_; // Dato de tipo T que guardaremos
                Node* next_; // Puntero al siguiente 
        
            public:
                Node(){ 
                    data_ = Type(); //Se inicializa con el constructor Type dandole el tipo de dato
                    next_ = nullptr; //Se inicializa como un puntero nulo
                }

                Node(const Type& elem){ //Constructor con elem como atributo constante, const indica que el atributo no se modificara dentro del constructor!
                    data_ = elem; // data_ será de elem que ya fue enviado, con el tipo que le da Type
                    next_ = nullptr; // Se inicializa next_ como un puntero nulo 
                }

                void setNext(Node *newNext){ // El constructor recibe la direccion de memoria de otro nodo
                    next_ = newNext; // Se modifica a donde apunta next_
                }

                Node* getNext(){ //Constructor de nodo como puntero que devuelve el puntero al siguiente nodo
                    return next_;
                }
        };

    private: 
        Node *first_; // Puntero que apunta al primer nodo de la lista
        Node *last_; // Puntero que apunta al ultimo nodo de la lista
        unsigned int size_; //Numero de elementos de la lista 
    public: 
        list(){ // Se crea el constructor lista 
            first_ = nullptr; // Se inicializa como puntero nulo
            last_ = nullptr; // Se inicializa como puntero nulo
            size_ = 0; // Se inicializa en 0
        }

        void push_back(const Type& elem){ //Funcion que agrega elemento al final 
            Node *newNode = new Node(elem); //Se crea un nuevo nodo y se le asigna memoria dinamica
            last_ -> setNext(newNode); //Ultimo nodo actual apunta al nuevo nodo
            last_ = newNode;  // Se guarda el puntero al otro nodo 
            if(!empty()){ //Si la lista esta vacia el nuevo nodo sera el primero y el ultimo elemento
                first_ = newNode;
            }
            size_++; //Se increment el tamaño de la lista 
        }        

        void pop_back(){ // Funcion que elimina el ultimo elemento de la lista
            Node* p = first_, temp = nullptr; // Se declaran dos punteros (p con el valor del puntero al primer elemento) y (temp como nulo) 
            for(int i = 0, i < size_ - 1; i++){ //Se recorre la lista 
                p = p->getNext; // Se va modificando a donde apunta p hasta llegar al penultimo
            }
            temp = p; //Al llegar al penultimo nodo ahora temp es el valor de la posicion p
            delete[] last; // Se elimina el ultimo elemento 
            temp -> setNext(nullptr); //Que el nuevo nodo no apunte a nada 
            last_ = temp; // Ahora el ultimo elemento es el temp es decir el penultimo nodo
            size_--; //Se disminuye el tamaño de la lista 
        }

        void push_front(const type &elem){   //Funcion que agrega elemento al inicio
            Node* newnode = new Node(elem); 
            newNode -> setNext(first_);  // El nuevo nodo apunta a first_ 
            first_ = newNode; //First_ apunta al nuvo nodo
            if(empty()){ // Si la lsta esta vacia entonces apunta a el recien añadido
                last_ = newNode; 
            }
            size_++; //Se aumenta el tamaño+ de la lista 
        }

        void pop_front(){ //Funcion que agrega elemento al inicio
            Node *temp = first_; // Se declara el puntero temp como el primer elemento 
            delete[] first_; //Se elimina el primer elemento
            first_ = temp -> next; // Se declara el primer elemento como el puntero 
            size_--; //Se disminuye el tamaño
        }

        unsigned int size()const { // tipo unsigned int y se indica que la funcion no modifica el objeto
            return size_;
        }

        bool empty() const{ //Retorna 1 si la lista esta vacia y 0 si no lo esta.
            return size_ == 0;
        }
};

int main(){
    cout << "Listas: " << endl;

    return 0;
}