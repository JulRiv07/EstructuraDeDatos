#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <random>

using namespace std;

// Clase KMeans para realizar clustering
class KMeans {
private:
    int k; // Número de clusters
    int maxIteraciones;
    vector<vector<double>> centroides;
    vector<int> etiquetas;

    // Calcula la distancia Euclidiana entre dos puntos
    double distanciaEuclidiana(const vector<double>& a, const vector<double>& b) {
        double suma = 0.0;
        for (size_t i = 0; i < a.size(); i++) {
            suma += pow(a[i] - b[i], 2);
        }
        return sqrt(suma);
    }

    // Inicializa los centroides aleatoriamente desde los datos
    void inicializarCentroides(const vector<vector<double>>& datos) {
        centroides.clear();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, datos.size() - 1);

        for (int i = 0; i < k; i++) {
            centroides.push_back(datos[distrib(gen)]);
        }
    }

public:
    // Constructor
    KMeans(int numClusters, int iteraciones) {
        k = numClusters;
        maxIteraciones = iteraciones;
    }

    // Método principal para ajustar el modelo a los datos
    void ajustar(const vector<vector<double>>& datos) {
        int n = datos.size();
        etiquetas.resize(n);

        inicializarCentroides(datos);

        for (int iter = 0; iter < maxIteraciones; iter++) {
            // Paso 1: Asignar cada punto al centroide más cercano
            for (int i = 0; i < n; i++) {
                double minDistancia = numeric_limits<double>::max();
                int etiqueta = 0;
                for (int j = 0; j < k; j++) {
                    double d = distanciaEuclidiana(datos[i], centroides[j]);
                    if (d < minDistancia) {
                        minDistancia = d;
                        etiqueta = j;
                    }
                }
                etiquetas[i] = etiqueta;
            }

            // Paso 2: Recalcular los centroides
            vector<vector<double>> nuevosCentroides(k, vector<double>(datos[0].size(), 0.0));
            vector<int> cuenta(k, 0);

            for (int i = 0; i < n; i++) {
                int etiqueta = etiquetas[i];
                for (size_t j = 0; j < datos[i].size(); j++) {
                    nuevosCentroides[etiqueta][j] += datos[i][j];
                }
                cuenta[etiqueta]++;
            }

            for (int j = 0; j < k; j++) {
                if (cuenta[j] == 0) continue;
                for (size_t d = 0; d < nuevosCentroides[j].size(); d++) {
                    nuevosCentroides[j][d] /= cuenta[j];
                }
            }

            centroides = nuevosCentroides;
        }
    }

    // Muestra los resultados del clustering
    void mostrarResultados() {
        cout << "Centroides encontrados:\n";
        for (int i = 0; i < k; i++) {
            cout << "Cluster " << i + 1 << ": ";
            for (double valor : centroides[i]) {
                cout << valor << " ";
            }
            cout << endl;
        }

        cout << "\nEtiquetas asignadas:\n";
        for (int etiqueta : etiquetas) {
            cout << etiqueta << " ";
        }
        cout << endl;
    }
};

// Función para leer CSV e ignorar columnas no numéricas (como el género)
vector<vector<double>> leerCSV(const string& nombreArchivo) {
    vector<vector<double>> datos;
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string celda;
        vector<string> columnas;
        vector<double> fila;

        while (getline(ss, celda, ',')) {
            columnas.push_back(celda);
        }

        if (columnas.size() >= 5) {
            try {
                double edad = stod(columnas[2]);
                double ingreso = stod(columnas[3]);
                double gasto = stod(columnas[4]);

                fila.push_back(edad);
                fila.push_back(ingreso);
                fila.push_back(gasto);
                datos.push_back(fila);
            } catch (...) {
                // Saltar si hay encabezado o datos inválidos
                continue;
            }
        }
    }

    archivo.close();
    return datos;
}

int main() {
    string archivo = "Mall_Customers.csv"; // Asegúrate de que este nombre coincida con tu archivo
    int k = 3; // Número de clusters deseados

    vector<vector<double>> datos = leerCSV(archivo);

    if (datos.empty()) {
        cerr << "No se pudieron cargar los datos. Verifica el archivo." << endl;
        return 1;
    }

    KMeans kmeans(k, 100);
    kmeans.ajustar(datos);
    kmeans.mostrarResultados();

    return 0;
}