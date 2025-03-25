#include <iostream>

using namespace std;

template <typename Type> 
class Vector{

    private:

        Type *storage;
        unsigned int capacity;
        unsigned int size;

        void resize(){

            cout << "resize";
            capacity *= 1.5;
            Type* storage2 = new Type[capacity];
            
            for (unsigned int i = 0; i < capacity; i++)
            {
                storage2[i] = storage[i];
            }

            delete [] storage2;
            storage = storage2;
            
        }

    public:

        Vector(){
            capacity = 10;
            storage = new Type[capacity];
            size = 0; 
        }

        void pushBack(const Type *elem){
            
            if(size == capacity){
                resize();
            }

            storage[size] = *elem;
            size++;
        }

        unsigned int sizee() const{
            return size;
        }

        void popback(){
            size--;
        }

        Type& at(unsigned int pos) const{
            return storage[pos];
        }
        
        void print(){  
            for (unsigned int i = 0; i < size; i++){
                cout << storage[i] << " "; 
            }
            cout << endl;
        }

};

template <typename Type> 
class ListaSimple{
    private:
        class Nodo{
            public:
                Type data;
                Nodo *next;

                Nodo(){
                    data = Type();
                    next = nullptr;
                }
        
                void setnext(Nodo *newnext){
                    next = newnext;
                }
        
                Nodo* getnext(){
                    return next;
                }
        };

        Nodo *first;
        unsigned int size;

    public:

    ListaSimple(){
        first = nullptr;
        size = 0;
    }

    bool empty(){
        return size == 0;
    }
        
    void pushback(const Type elem){
        Nodo *newnodo = new Nodo();
        newnodo -> data = elem;
        newnodo -> setnext(nullptr);

        if(empty()){
            first = newnodo;
        } else {
            Nodo *temp = first;
            while (temp->getnext() != nullptr) { 
                temp = temp->getnext();
            }
            temp->setnext(newnodo);
        }

        size++;
    }
    
    void popback(){
        Nodo *p = first;
        for(unsigned int i = 0; i < size - 2; i++){
            p = p -> getnext();
        }

        delete p -> getnext();
        p -> setnext(nullptr);
        size--;
    }

    void pushfront(const Type elem){
        Nodo *newnodo = new Nodo();
        newnodo -> data = elem;
        if(empty()){
            newnodo -> setnext(nullptr);
        } else newnodo -> setnext(first);
        first = newnodo;
        size++;
    }

    void popfront() {
    
        Nodo *temp = first;    
        first = first->getnext();
        delete temp;   
        size--;        
    }
    void print(){
        Nodo *p = first;
        while(p != nullptr){
            cout << p -> data << " ";
            p = p -> getnext();
        }
    }
        
};

template <typename Type> 
class ListaDoble{
    private:
        class Nodo{

            public:

                Type data;
                Nodo* next;

                Nodo(){
                    data = Type();
                    next = nullptr;
                }

                void setnext(Nodo *newnext){
                    next = newnext;
                }

                Nodo* getnext(){
                    return next;
                }
        };

        Nodo* first;
        Nodo* last;
        unsigned int size;

    public: 
        
        ListaDoble(){
            first = nullptr;
            last = nullptr;
            size = 0;
        }

        bool empty(){
            return size == 0;
        }

        void pushfront(const Type elem){
            Nodo* newnodo = new Nodo();
            newnodo -> data = elem; 
            newnodo -> setnext(first);
            first = newnodo;
            if(empty()){
                last = newnodo;
            } 
            size++;
        }

        void popfront(){
            Nodo* temp = first;
            delete [] first;
            first = temp -> next;
            size--;
        }

        void pushback(const Type elem){
            Nodo* newnodo = new Nodo();
            newnodo -> data = elem;
            newnodo -> setnext(nullptr);

            if(empty()){
                first = newnodo;
                last = newnodo;
            } else{
                last -> setnext(newnodo);
                last = newnodo;
            }  
        }

        void popback(){
            Nodo* p = first, *temp = nullptr;
            for(unsigned int i = 0; i < size - 1 ; i++){
                p = p -> getnext();
            }
            temp = p;
            delete [] last;
            temp -> setnext(nullptr);
            last = temp;
            size--;
        }

        void print(){
            Nodo* temp = first;
            while(temp != nullptr){
                cout << temp -> data << " ";
                temp = temp -> getnext();
            }
        }
};

template <typename Type>
class ListaCircular{
    private:

        class Nodo{
            public: 
                Type data;
                Nodo *next;

                Nodo(){
                    data = Type();
                    next = nullptr;
                }

                void setnext(Nodo* newnext){
                    next = newnext;
                }   

                Nodo* getnext(){
                    return next;
                }
        };

        Nodo *last;
        unsigned int size;

    public:

        ListaCircular(){
            last = nullptr;
            size = 0;
        }

        bool empty(){
            return size == 0;
        }

        void pushback(const Type elem){
            Nodo *newnodo = new Nodo();
            newnodo -> data = elem;
            if(empty()){
                last = newnodo;
                last -> setnext(last);
            } else {
                newnodo -> setnext(last->getnext());
                last -> setnext(newnodo);
                last = newnodo;
            }
            size++;
        }

        void pushfront(const Type elem){
            Nodo *newnodo = new Nodo();
            newnodo -> data = elem;
            if(empty()){
                last = newnodo;
                newnodo -> setnext(last);
            } else {
                newnodo -> setnext(last -> getnext());
                last -> setnext(newnodo);
            }
            size++;
        }

        void popback(){
            Nodo *p = last -> getnext();
            while(p -> getnext() != last){
                p = p -> getnext();
            }
            p -> setnext(last->getnext());
            delete last;
            last = p;
            size--;
        }

        void popfront(){
            Nodo* temp = last->next;
            last->next = temp->next;
            delete temp;
            size--;
        }

        void print() {
        
            Nodo* p = last->getnext();
            do {
                cout << p->data << " ";
                p = p->getnext();
            } while (p != last->getnext());
            cout << endl;
        }
};

template <typename Type>
class ListaCdoble{
    private:
        class Nodo{
            public:
                Type data;
                Nodo *next;
                Nodo *prev;

                Nodo(){
                    data = Type();
                    next = nullptr;
                    prev = nullptr;
                }

                void setnext(Nodo *newnext){
                    next = newnext;
                }    

                void setprev(Nodo *newprev){
                    prev = newprev;
                }

                Nodo *getnext(){
                    return next;
                }

                Nodo *getprev(){
                    return prev;
                }
            };

        Nodo *last;
        unsigned int size;

    public:
        ListaCdoble(){
            last = nullptr;
            size = 0;
        }

        bool empty(){
            return size == 0;
        }

        void pushback(const Type elem){
            Nodo *newnodo = new Nodo();
            newnodo -> data = elem;
            if(empty()){
                last = newnodo;
                last -> setnext(last);
                last -> setprev(last);
            } else {
                newnodo -> setnext(last->getnext());
                newnodo -> setprev(last);
                last -> getnext() -> setprev(newnodo);
                last -> setnext(newnodo);
                last = newnodo;
            }
            size++;
        }

        void pushfront(const Type elem){
            Nodo *newnodo = new Nodo();
            newnodo -> data = elem;
            if(empty()){
                last = newnodo;
                last -> setnext(last);
                last -> setprev(last);
            } else {
                newnodo -> setnext(last -> getnext());
                newnodo -> setprev(last);
                last -> getnext() -> setprev(newnodo);
                last -> setnext(newnodo);
            }
            size++;
        }

        void popback(){
            Nodo *temp = last;
            last = last -> getprev();
            last -> setnext(temp -> getnext());
            temp -> getnext() -> setprev(last);
            delete temp;
            size--;
        }

        void popfront(){
            Nodo *p = last -> getnext();
            last -> setnext(p->getnext());
            p -> getnext() -> setprev(last);
            delete p;
            size--;
        }

        void print() {    
            Nodo *current = last->getnext(); 
            do {
                cout << current->data << " ";
                current = current->getnext();
            } while (current != last->getnext());
            
            cout << "\n";
        }
};

int main() {
    int opcion;

    do {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Probar Vector" << endl;
        cout << "2. Probar Lista simplemente enlazada" << endl;
        cout << "3. Probar Lista doblemente enlazada" << endl;
        cout << "4. Probar Lista circular simplemente enlazada" << endl;
        cout << "4. Probar Lista circular doblemente enlazada " << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "\n--- Prueba de Vector ---" << endl;
                Vector<int> vec;
                cout << "Agregando 10, 20, 30..." << endl;
                vec.pushBack(new int(10));
                vec.pushBack(new int(20));
                vec.pushBack(new int(30));
                vec.print();

                cout << "Eliminando último elemento..." << endl;
                vec.popback();
                vec.print();

                cout << "Elemento en índice 0: " << vec.at(0) << endl;
                break;
            }
            case 2: {
                cout << "\n--- Prueba de Lista Simple ---" << endl;
                ListaSimple<int> lista;
                lista.pushback(5);
                lista.pushfront(1);
                lista.pushback(10);
                lista.print();

                cout << "\nEliminando el primer elemento..." << endl;
                lista.popfront();
                lista.print();

                cout << "\nEliminando el último elemento..." << endl;
                lista.popback();
                lista.print();
                break;
            }
            case 3: {
                cout << "\n--- Prueba de Lista Doble ---" << endl;
                ListaDoble<int> lista;
                lista.pushback(100);
                lista.pushfront(50);
                lista.pushback(150);
                lista.print();

                cout << "\nEliminando el primer elemento..." << endl;
                lista.popfront();
                lista.print();

                cout << "\nEliminando el último elemento..." << endl;
                lista.popback();
                lista.print();
                break;
            }
            case 4: {
                cout << "\n--- Prueba de Lista Circular ---" << endl;
                ListaCircular<int> lista;
                lista.pushback(7);
                lista.pushfront(3);
                lista.pushback(9);
                lista.print();

                cout << "\nEliminando el primer elemento..." << endl;
                lista.popfront();
                lista.print();

                cout << "\nEliminando el último elemento..." << endl;
                lista.popback();
                lista.print();
                break;
            }
            case 5: {
                cout << "\n--- Prueba de Lista Circular Doble ---" << endl;
                ListaCdoble<int> lista;
                lista.pushback(7);
                lista.pushfront(3);
                lista.pushback(9);
                lista.print();

                cout << "\nEliminando el primer elemento..." << endl;
                lista.popfront();
                lista.print();

                cout << "\nEliminando el último elemento..." << endl;
                lista.popback();
                lista.print();
                break;
            }
            case 0:
                cout << "Baii" << endl;
                break;
            default:
                cout << "Opción invalida" << endl;
        }
    } while (opcion != 0);

    return 0;
}