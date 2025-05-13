#include <iostream>
#include <vector>
using namespace std;

int docprod(const vector<int> &a, const vector<int> &b){
    int result = 0;

    for(size_t i = 0; i < a.size(); i++){
        result += a[i] * b[i];
    }
 
    return result;
}

int main(){

    int n;

    cout << "Hi! if you want calculate the dot product your vectors must have the same cardinality..."
          << "So, how many elements you want to add in the vectors?: ";

    cin >> n;

    vector<int> vec1(n);    
    cout << "Add the elements to vec1 (1 for 1)" << endl;
    for(int i = 0; i < n; i++){
        cout << "Enter the element " << i + 1 << ":" ;
        cin >> vec1[i];
    }

    vector<int> vec2(n);   
    cout << "Add the elements to vec2 (1 for 1)" << endl;
    for(int i = 0; i < n; i++){
        cout << "Enter the element " << i + 1 << ":" ;
        cin >> vec2[i];
    }

    cout << "The dot product between (vec1) y (vec2) es: " << docprod(vec1, vec2) << endl;

    return 0;
}