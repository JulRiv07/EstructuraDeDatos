#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <chrono>
#include <fstream>

using namespace std;

void QuickSort(vector<unsigned char> *vector, int start, int end, int chose) {
    if (start >= end) return;

    int i = start, r = end;
    unsigned char pivote = 0;

    if (chose == 1) {
        pivote = vector->at(start);
    } else if (chose == 2) {
        pivote = vector->at((start + end) / 2);
    } else if (chose == 3) {
        pivote = vector->at(end);
        //Cambio
    }

    do {
        while (vector->at(i) < pivote) i++;
        while (vector->at(r) > pivote) r--;
        if (i <= r) {
            swap(vector->at(i), vector->at(r));
            i++;
            r--;
        }
    } while (i <= r);

    if (start < r) QuickSort(vector, start, r, chose);
    if (i < end) QuickSort(vector, i, end, chose);
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

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned char> dist(0, 255);

    int quantity = 0;
    int opc;
    vector<unsigned char> variables;
    vector<int> variablesInt;
    ofstream tiempos("tiempos.dat");
    if (!tiempos) {
        cout << "Error al abrir tiempos.dat\n";
        exit(EXIT_FAILURE);
    }

    auto start = chrono::high_resolution_clock::now();

    cout << "1. Quicksort\n2. MergeSort\nElija el ordenamiento que quiere probar: ";
    cin >> opc;

    if (opc == 1) {
        for (int pot = 1; pot <= 9; pot++) {
            quantity = pow(10, pot);
            variables.reserve(quantity);
            tiempos << endl << endl << "Potencia " << pot << endl;

            for (int pivot = 1; pivot <= 3; pivot++) {
                tiempos << endl << "Pivote " << pivot << endl;

                for (int times = 1; times <= 10; times++) {
                    variables.clear();
                    for (int l = 0; l < quantity; l++) {
                        variables.push_back(dist(gen));
                    }

                    auto inicio = chrono::high_resolution_clock::now();
                    QuickSort(&variables, 0, variables.size() - 1, pivot);
                    auto fin = chrono::high_resolution_clock::now();

                    auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
                    tiempos << times << ".\t" << duracion.count() << endl;
                }
            }
        }
    } else if (opc == 2) {
        for (int pot = 9; pot <= 9; pot++) {
            quantity = pow(10, pot);
            variablesInt.reserve(quantity);
            tiempos << endl << endl << "Potencia " << pot << endl;

            for (int times = 1; times <= 10; times++) {
                variablesInt.clear();
                for (int l = 0; l < quantity; l++) {
                    variablesInt.push_back(dist(gen));
                }

                auto inicio = chrono::high_resolution_clock::now();
                MergeSort(variablesInt, 0, variablesInt.size() - 1);
                auto fin = chrono::high_resolution_clock::now();

                auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
                tiempos << times << ".\t" << duracion.count() << endl;
            }
        }
    } else {
        cout << "Opción incorrecta" << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto totalDuracion = chrono::duration_cast<chrono::milliseconds>(end - start);
    tiempos << endl << "Duracion total en milisegundos: " << totalDuracion.count() << endl;

    return 0;
}