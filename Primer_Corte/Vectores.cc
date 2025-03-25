#include <iostream> //Se incluye la biblioteca
#include <cassert> //Se incluye la biblioteca "cassert": verifica si una condición es falsa en tiempo de ejecución.

using namespace std;

template <typename T> // Se da el tipo de dato que llevara el vector 

class Vector { // Se inicia la clase Vector
private:
    T* storage_; // Puntero al arreglo que manejaremos como vector (de tipo T)
    unsigned int capacity_; //Capacidad del vector
    unsigned int size_; //Tamaño actual del vector 

    void resizeP1() { // Funcion resize (private!)
        cout << "Resize" << endl; // Se muestra que se hizo un resize
        unsigned int capacity2 = capacity_ * 1.5; // Se modifica la capacidad sumandole la mitad de la que se tenia
        T* storage2 = new T[capacity2]; // Se direcciona storage2 con el mismo espacio de memoria de capacity2

        // Se copian los elementos del vector 
        for (unsigned int i = 0; i < size_; i++) { 
            storage2[i] = storage_[i];
        }

        // Liberando memoria antigua
        delete[] storage_; // Se elimina storage_ 
        storage_ = storage2; // Se crea de nuevo storage_ tomando el mismo valor de storage2
        capacity_ = capacity2; // Se recupera capacity_
    }

public:
    Vector() { // Constructor Vector 
        capacity_ = 4; // Capacidad de 5
        storage_ = new T[capacity_]; // Storage_ guarda espacio de memoria dinamica de tamaño capácity y tipo T 
        size_ = 0; // Tamaño actual 0
    }

    Vector(unsigned int c, T element) { // Constructor Vector con dos parametros
        capacity_ = c; // Capacidad dada por c
        storage_ = new T[capacity_]; // Storage_ guarda espacio de memoria dinamica de tamaño capácity y tipo T 
        for (unsigned int i = 0; i < capacity_; i++) { // Se añade el elemento de tipo T
            storage_[i] = element; 
        }
        size_ = capacity_; // El vector se llena 
    }

    ~Vector() { // Destructor
        delete[] storage_; // Se libera memoria
    }

    unsigned int size_() const { // El const hace que no se modifique el estado del objeto
        return size_; // Retorna el tamaño actual
    }

    unsigned int capacity_() const { // El const hace que no se modifique el estado del objeto
        return capacity_; // Retorna el tamaño permitido
    }

    T& at(unsigned int pos) { 
        assert(pos < size_); // Verifica que pos esté dentro del rango válido, si no, detiene el programa
        return storage_[pos];// Retorna una referencia al elemento en la posición pos
    }

    const T& at(unsigned int pos) const { 
        /* Analisis por partes:
            const T& at : Dice que se devuelve una referencia constante al elemento
            Si llegaara a estar dentro, ejemplo: (unsigned int pos), quiere decir que el valor no se modificara a lo largo de la funcion
            const después de los parentesis: quiere decir que la funcion no modifica el estado del objeto 
        */
        assert(pos < size_); // Verifica que pos esté dentro del rango válido, si no, detiene el programa
        return storage_[pos];// Retorna una referencia al elemento en la posición pos
    }

    const T& operator[](unsigned int index) const {
        /* Analisis por partes:
            const T& at : Dice que se devuelve una referencia constante al elemento
            operator[]: permite el acceso al elemento, como en un array 
            const después de los parentesis: quiere decir que la funcion no modifica el estado del objeto 
        */
        assert(index < size_); // Verifica que el indice sea valido 
        return storage_[index]; // Retorna el elemento que se encuenta en la posicion index
    }

    void push_back1(const T& elem) {// Coloca un elemento al final 
        // El valor elem no se modificara a lo largo de la funcion por const
        if (size_ == capacity_) { //Si se alcanzo la capacidad maxima primero se hace un resize
            resizeP1();
        }
        storage_[size_] = elem; // Se agrega el elemento en la posicion size, sabiendo que siempre esta en una posicion adelantada
        size_++; // Se avanza en el vector
    }

    void pop_back() { // Elimina el ultimo elemento 
        if (size_ > 0) { // Verifica que hayan elementos en el vector 
            size_--; // Elimina
        }
    }

    void print() { // Funcion que imprime un vector 
        for (unsigned int i = 0; i < size_; i++) { // Recorre todo el vector 
            cout << " " << storage_[i]; // Va imprimiendo cada elemento y separando por espacios 
        }
        cout << endl; // Salto de linea al final
    }

    public:
    unsigned int Size() const { return size_; }       // Método para obtener el tamaño
    unsigned int Capacity() const { return capacity_; } // Método para obtener la capacidad

};

class complex { // Clase complejos
private:
    double real; // Parte real de tipo double 
    double img; // Parte imaginaria de tipo double 

public:
    complex() {  // Constructor de la clase (Sin parametros )
        real = 0.0; // Parte real inicializada en 0
        img = 0.0; // Parte imaginaria inicializada en 0
    }

    friend ostream& operator<<(ostream& os, const complex& c); 
    /* Analisis:
        friend: permite que la funcion acceda a los atributos privados de la clase.
        La funcion devuelve una referencia a (ostream) que permite encadenar salidas.
    */
};

ostream& operator<<(ostream& os, const complex& c) {
    /* Analisis:
        ostream& os: Una referencia a un flujo de salida 
        const complex& c: referencia constante al objeto complex, no se permite que se modifique
    */
    os << "(" << c.real << ", " << c.img << "i)";
    // Escribe la representación del número complejo en el flujo de salida
    // Formato: (real, img i)
    return os; // Retorna el flujo de salida para permitir encadenamiento de operadores.
}

int main() {
    Vector<int> myVector;

    // Test push_back
    myVector.push_back1(10);
    myVector.push_back1(20);
    myVector.push_back1(30);
    
    cout << myVector.Size()<< endl; // Expected: 3
    cout << myVector.Capacity() << endl; // Expected: Initial capacity, e.g., 4 or 8

    // Test pop_back
    myVector.pop_back();
    cout << myVector.size() << endl; // Expected: 2

    // Test at with valid and invalid indices
    cout << myVector.at(0) << endl; // Expected: 10
    cout << myVector.at(1) << endl; // Expected: 20

    // Border case: Accessing an out-of-bounds index
    cout << myVector.at(2) << endl; // Should crash!

    // Border case: pop_back on empty vector
    Vector<int> emptyVector;
    emptyVector.pop_back(); // should crash!
    return 0; 
}
