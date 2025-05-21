#include <iostream>     // For input and output operations
#include <vector>       // For using the vector container
#include <fstream>      // For file reading
#include <sstream>      // For string stream manipulation
#include <cmath>        // For mathematical functions like pow and sqrt
#include <limits>       // For numeric limits (e.g., max double value)
#include <random>       // For random number generation

using namespace std;

// KMeans clustering algorithm class
class KMeans {
private:
    int k; // Number of clusters
    int maxIterations; // Maximum number of iterations to run the algorithm
    vector<vector<double>> centroids; // Coordinates of cluster centroids
    vector<int> labels; // Cluster assignments for each data point

    // Calculates the Euclidean distance between two points (vectors)
    double euclideanDistance(const vector<double>& a, const vector<double>& b) {
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); i++) {
            sum += pow(a[i] - b[i], 2);
        }
        return sqrt(sum);
    }

    void initializeCentroids(const vector<vector<double>>& data) {
        centroids.clear();
        random_device rd; // Obtain a seed for the random number engine
        mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        uniform_int_distribution<> distrib(0, data.size() - 1); // Uniform distribution over data size

        // Pick k random data points as initial centroids
        for (int i = 0; i < k; i++) {
            centroids.push_back(data[distrib(gen)]);
        }
    }

public:

    KMeans(int numClusters, int iterations) {
        k = numClusters;
        maxIterations = iterations;
    }

    void fit(const vector<vector<double>>& data) {
        int n = data.size(); // Number of data points
        labels.resize(n); // Resize label array to match number of points

        initializeCentroids(data); // Randomly initialize centroids

        for (int iter = 0; iter < maxIterations; iter++) {
            for (int i = 0; i < n; i++) {
                double minDistance = numeric_limits<double>::max(); // Initialize to maximum double
                int label = 0;

                // Check distance to each centroid
                for (int j = 0; j < k; j++) {
                    double d = euclideanDistance(data[i], centroids[j]);
                    if (d < minDistance) {
                        minDistance = d;
                        label = j;
                    }
                }
                labels[i] = label; // Assign closest centroid
            }

            vector<vector<double>> newCentroids(k, vector<double>(data[0].size(), 0.0));
            vector<int> count(k, 0); // Count of points in each cluster

            // Sum all data points in each cluster
            for (int i = 0; i < n; i++) {
                int label = labels[i];
                for (size_t j = 0; j < data[i].size(); j++) {
                    newCentroids[label][j] += data[i][j];
                }
                count[label]++;
            }

            for (int j = 0; j < k; j++) {
                if (count[j] == 0) continue; 
                for (size_t d = 0; d < newCentroids[j].size(); d++) {
                    newCentroids[j][d] /= count[j];
                }
            }

            // Update centroids for the next iteration
            centroids = newCentroids;
        }
    }

    void showResults() {
        cout << "Centroids found:\n";
        for (int i = 0; i < k; i++) {
            cout << "Cluster " << i + 1 << ": ";
            for (double value : centroids[i]) {
                cout << value << " ";
            }
            cout << endl;
        }

        cout << "\nAssigned labels:\n";
        for (int label : labels) {
            cout << label << " ";
        }
        cout << endl;
    }
};

vector<vector<double>> readCSV(const string& filename) {
    vector<vector<double>> data;
    ifstream file(filename);
    string line;

    // Read each line from the CSV
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> columns;
        vector<double> row;

        // Split line by commas
        while (getline(ss, cell, ',')) {
            columns.push_back(cell);
        }

        if (columns.size() >= 5) {
            try {
                double age = stod(columns[2]);       
                double income = stod(columns[3]);    
                double spending = stod(columns[4]);

                row.push_back(age);
                row.push_back(income);
                row.push_back(spending);
                data.push_back(row);
            } catch (...) {
                continue;
            }
        }
    }

    file.close(); // Close the file
    return data;
}

int main() {
    string filename = "Mall_Customers.csv";  
    int k = 3; 

    vector<vector<double>> data = readCSV(filename);
    if (data.empty()) {
        cerr << "Failed to load data. Please check the file." << endl;
        return 1;
    }

    KMeans kmeans(k, 100);
    kmeans.fit(data);
    kmeans.showResults();

    return 0;
}
