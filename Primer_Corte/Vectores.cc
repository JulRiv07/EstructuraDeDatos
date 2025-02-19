#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

vector<int> generateRandomArray(int size){

    // Obtain a random seed from the operating system's entropy source.
    random_device rd;
    // Standard mersenne_twister_engine seeded with rd().
    mt19937 gen(rd());

    // Generate random numbers between 0 and 100 (inclusive).
    uniform_int_distribution<> distrib(0, 100);
    
    // Create a vector of the specified size.
    vector<int> randomArray(size);

    for(int i = 0; i < size; ++i){
        randomArray[i] = distrib(gen); //Generate and store random number 
    }

    return randomArray;
}

string generateRandomString(int size) {
    string randomString(size, ' '); // Initialize with spaces

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib('A', 'z'); // Characters from A to z (including uppercase and lowercase)

    // Use std::generate to fill the string with random characters
    generate(randomString.begin(), randomString.end(), [&]() { return distrib(gen); });

    return randomString;
}

int main(){
    cout << "Vector examples: " << endl;
    vector<int> a;
    cout << "Size: " << a.size() << endl;
    cout << "Vector examples: " << endl;
    vector<int> b;
    b = generateRandomArray(100);

    for (int i = 0; i < b.size(); i++){
        cout << " " << b.at(i); 
    }

    cout << "Vector examples: " << endl;
    vector<string> cadenas;

    cout << endl;

    for (int i = 0; i < 100; i++){
        cadenas.push_back(generateRandomString(5));
    }

    cout << endl;

    return 0;
}