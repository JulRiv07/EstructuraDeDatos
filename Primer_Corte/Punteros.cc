#include <iostream>

using namespace std;

/*

---------- Sin punteros ----------

typedef struct {
    double real;
    double img;
} ComplexNumber;

ComplexNumber csum(ComplexNumber a, ComplexNumber b){
    ComplexNumber r;
    r.real = a.real + b.real;
    r.img = a.img + b.img; 
    return r;
}

int main(){

    ComplexNumber m;
    ComplexNumber n;

    m.real = 10.0;
    m.img = 2.0;

    n.real = 100.0;
    n.img = 20.0;

    ComplexNumber w = csum(n, m);
    cout << "Result: " << w.real << "," << w.img << "i" << endl;

}

*/

// ---------- con punteros ----------

typedef struct {
    double real;
    double img;
} ComplexNumber;

ComplexNumber csum(ComplexNumber *a, ComplexNumber *b){
    ComplexNumber r;
    r.real = a->real + b->real;  // "x->" Es lo mismo que tener (*x)
    r.img = (*a).img + (*b).img;
    return r;
}

int main(){

    ComplexNumber m;
    ComplexNumber n;

    m.real = 10.0;
    m.img = 2.0;

    n.real = 100.0;
    n.img = 20.0;

    ComplexNumber w = csum(&n, &m);
    cout << "Result: " << w.real << ", " << w.img << "i" << endl;

}
