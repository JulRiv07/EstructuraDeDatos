    #include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/**
 * Clase que representa un punto en 2D.
 * Contiene coordenadas x, y y el identificador del cluster al que pertenece.
 */
class Point {
public:
    double x, y;        // Coordenadas del punto
    int cluster_id;     // ID del cluster al que pertenece el punto

    Point(double x = 0.0, double y = 0.0) {
        this->x = x;
        this->y = y;
        cluster_id = -1; // -1 indica que aún no está asignado a un cluster
    }

    /**
     * Calcula la distancia Euclidiana entre este punto y otro.
     */
    double distanceTo(const Point& other) const {
        return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
    }

    /**
     * Muestra el punto en formato (x, y).
     */
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

/**
 * Clase que representa un cluster de puntos.
 * Contiene un centroide (punto central) y los puntos asignados al cluster.
 */
class Cluster {
public:
    Point centroid;             // Centroide del cluster
    vector<Point*> points;      // Punteros a los puntos que pertenecen al cluster

    /**
     * Constructor que inicializa el centroide con un punto dado.
     */
    Cluster(const Point& initial_centroid) {
        centroid = initial_centroid;
    }

    /**
     * Agrega un punto al cluster.
     */
    void addPoint(Point* p) {
        points.push_back(p);
    }

    /**
     * Limpia todos los puntos del cluster (antes de una nueva asignación).
     */
    void clearPoints() {
        points.clear();
    }

    /**
     * Recalcula el centroide como el promedio de los puntos asignados.
     */
    void updateCentroid() {
        if (points.empty()) return;

        double sum_x = 0.0, sum_y = 0.0;
        for (Point* p : points) {
            sum_x += p->x;
            sum_y += p->y;
        }
        centroid.x = sum_x / points.size();
        centroid.y = sum_y / points.size();
    }

    /**
     * Muestra el centroide y los puntos del cluster.
     */
    void printCluster() const {
        cout << "Centroid: ";
        centroid.print();
        cout << "\nPoints: ";
        for (Point* p : points) {
            p->print();
            cout << " ";
        }
        cout << "\n";
    }
};


/**
 * Clase que implementa el algoritmo de K-Means.
 * Controla la inicialización de centroides, asignación de puntos y actualización de clusters.
 */
class KMeans {
private:
    int K;                          // Número de clusters
    vector<Point> points;          // Todos los puntos de entrada
    vector<Cluster> clusters;      // Los clusters

public:

    /**
     * Constructor: recibe el número de clusters y los puntos de entrada.
     */
    KMeans(int k, const vector<Point>& data) : K(k), points(data) {}

    /**
     * Inicializa los centroides usando los primeros K puntos como centroides iniciales.
     */
    void initializeCentroids() {
        for (int i = 0; i < K; i++) {
            clusters.push_back(Cluster(points[i]));
        }
    }

    /**
     * Asigna cada punto al cluster cuyo centroide está más cerca.
     */
    void assignPointsToClusters() {
        for (Point& p : points) {
            double min_dist = 1e9;
            int best_cluster = -1;

            for (int i = 0; i < K; i++) {
                double dist = p.distanceTo(clusters[i].centroid);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = i;
                }
            }

            p.cluster_id = best_cluster;
            clusters[best_cluster].addPoint(&p);
        }
    }

    /**
     * Actualiza todos los centroides en función de los puntos asignados.
     */
    void updateCentroids() {
        for (Cluster& c : clusters) {
            c.updateCentroid();
        }
    }

    /**
     * Limpia los puntos de cada cluster antes de una nueva asignación.
     */
    void clearClusters() {
        for (Cluster& c : clusters) {
            c.clearPoints();
        }
    }

    /**
     * Ejecuta el algoritmo K-Means.
     * Repite hasta que los centroides no cambien (convergencia) o se alcanza el máximo de iteraciones.
     */
    void run(int max_iterations = 100) {
        initializeCentroids();

        for (int iter = 0; iter < max_iterations; iter++) {
            clearClusters();              // Limpia clusters anteriores
            assignPointsToClusters();     // Asigna puntos al cluster más cercano

            vector<Point> old_centroids;
            for (const Cluster& c : clusters) {
                old_centroids.push_back(c.centroid);
            }

            updateCentroids();            // Recalcula los centroides

            // Verifica si los centroides cambiaron
            bool converged = true;
            for (int i = 0; i < K; i++) {
                if (clusters[i].centroid.distanceTo(old_centroids[i]) > 1e-4) {
                    converged = false;
                    break;
                }
            }

            if (converged) {
                cout << "Convergió en la iteración " << iter + 1 << "\n";
                break;
            }
        }
    }

    /**
     * Muestra los resultados finales de los clusters y puntos.
     */
    void printResult() const {
        for (int i = 0; i < K; i++) {
            cout << "Cluster " << i + 1 << ":\n";
            clusters[i].printCluster();
            cout << "\n";
        }
    }
};

int main() {
    // Conjunto de puntos de prueba
    vector<Point> data = {
        {1.0, 2.0}, {1.5, 1.8}, {5.0, 8.0}, {8.0, 8.0},
        {1.0, 0.6}, {9.0, 11.0}, {8.0, 2.0}, {10.0, 2.0}
    };

    int k = 2; // Número de clusters

    // Ejecutamos KMeans
    KMeans kmeans(k, data);
    kmeans.run();              // Corre el algoritmo
    kmeans.printResult();      // Muestra resultados

    return 0;
}
