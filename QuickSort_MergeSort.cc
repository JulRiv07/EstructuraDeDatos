#include <iostream>
#include <vector>
#include <random>


using namespace std;

// Funcion que crea un vector aleatorio!
vector<int> randomVec(int size){

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distrib(0, 100);
    vector<int> Vector(size);

    for(int i = 0; i < size; i++){
        Vector[i] = distrib(gen);
    }

    return Vector;
}


int randomParticion(vector<int> &vec, int start, int end){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(start, end);

    int random = distrib(gen);
    swap(vec[random], vec[start]);
    int pivote = vec[start];
    int i = start + 1;


    for(int j = i; j <= end; j++){
        if(vec[j] < pivote){
            int temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
             i++;
        }
    }
    swap(vec[start], vec[i - 1]);
    return i - 1;

}

int particion(vector<int>&vec, int start, int end){

    int mid = start + (end - start) / 2;
    swap(vec[start], vec[mid]);
    int pivote = vec[start];
    int i = start + 1;
    
    for(int j = i; j <= end; j++){
        if(vec[j] < pivote){
            int temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
        }
    }
    swap(vec[start], vec[i - 1]);
    return i - 1;
}

void QuikSort1(vector<int> &vec, int start, int end){

    //Usando Pivote en la mitad!
    if(start < end){
        int pivote = particion(vec, start, end);
        QuikSort1(vec, start, pivote - 1);
        QuikSort1(vec, pivote + 1, end);
    }

}

void QuikSort2(vector<int> &vec, int start, int end){

    //Usando Pivote aleatorio!
    if(start < end){
        int pivote = randomParticion(vec, start, end);
        QuikSort2(vec, start, pivote - 1);
        QuikSort2(vec, pivote + 1, end);
    }

}

void Merge(vector<int> &vec, int start, int middle, int end) {
    int left = middle - start + 1;
    int right = end - middle; 

    vector<int> Vleft(left);
    vector<int> Vright(right);

    for (int i = 0; i < left; i++) {
       Vleft[i] = vec[start + i];
    }

    for (int j = 0; j < right; j++) {
       Vright[j] = vec[middle + 1 + j]; 
    }

    int i = 0, j = 0, k = start;

    while (i < left && j < right) {
        if (Vleft[i] <= Vright[j]) {
            vec[k] = Vleft[i];
            i++;
        } else {
            vec[k] = Vright[j];
            j++;
        }
        k++;
    }

    while (j < right) {
        vec[k] = Vright[j];
        j++;
        k++;
    }

    while (i < left) {
        vec[k] = Vleft[i];
        i++;
        k++;
    }
}

void MergeSort(vector<int> &vec, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        MergeSort(vec, start, mid);
        MergeSort(vec, mid + 1, end);
        Merge(vec, start, mid, end);
    }
}


void print(vector<int> vec){

    for(int i = 0; i < vec.size(); i++){
        cout << vec[i] << " " ;
    }

    cout << endl;
}

int main(){


    cout << "Ordenamiento QuickSort: " << endl;
    vector<int> vect = randomVec(10);
    print(vect);
    QuikSort2(vect,0, vect.size()-1);
    print(vect);


    cout << "Ordenamiento MergeSort: " << endl;
    vector<int> vect2 = randomVec(10);
    print(vect2);
    MergeSort(vect2,0, vect.size()-1);
    print(vect2);

    return 0;
}