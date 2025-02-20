#include <iostream> 
#include <cassert>
using namespace std;

template <typename T>

class Vector{
    private:

    T* storage_;
    unsigned int capacity_;
    unsigned int size_;

    void resize(){
        cout << "Resize" << endl;
        unsigned int capacity2 = capacity_ * 1.5;
        T* storage2 = new T[capacity2];
        for(unsigned int i = 0; i < size_; i++){
            storage2[i] = storage_[i];
        }

        delete[] storage_;
        storage_ = storage2;
        capacity_ = capacity2;
    }

    public:
    Vector(){
        capacity_ = 5;
        storage_ = new T[capacity_];
        size_ = 0;
    }

    Vector(unsigned int c, T elemen){
        capacity_ = c;
        storage_ = new T[capacity_];
        for(unsigned int i = 0; i < capacity_; i++){
            storage_[i] = elemen;
        }
        size_ = capacity_;
    }

    unsigned int size(){
        return size_;
    }

    T& at(unsigned int pos) {
        assert(pos >= 0 && pos < size_);
        return storage_[pos];
    }

    const T& at(unsigned int pos) const {
        assert(pos >= 0 && pos < size_);
        return storage_[pos];
        
    }

    const T& operator[](unsigned int index) const{
        return storage_[index];
    }

    void push_back(const T& elem) {
        if(size_ == capacity_){
            resize();
        }
        storage_[size_] = elem;
        size_++;
    }

    void pop_back(){
        size_--;
    }

    void print(){
        for(unsigned int i = 0; i < size_; i++){
            cout << " " << storage_[i];
        }
        cout << endl;
    }
};

class complex {
    private:
    double real;
    double img;

    public:
        complex(){
           real = 0.0;
           img = 0.0; 
        }
        friend std::ostream& operator<<(std::ostream& os, const complex& c);

};

std::ostream& operator<<(std::ostream& os, const complex& c){
    os <<"(" << c.real << ", " << c.img << "i";
    return os;
}

int main(){

    cout << "Ejecutando vectores!" << endl;

    Vector<int> x(10, 0);
    cout << "x " << x.size() << endl;
    x.print();
    x.at(5) = 100;
    x.print();

    return 0;
}