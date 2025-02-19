#include <iostream>

using namespace std; 
// ------------ Programacion orientada a objetos "POO" ------------
class RGBcolor {
    private: 
    int red;
    int green;
    int blue;

    public:
    RGBcolor(){
        cout << "Constructor 1 called: " << endl;
        red = 0;
        green = 0;
        blue = 0;
    }

    RGBcolor(int c){
        cout << "Constructor 2 called: " << endl;
        red = c;
        //Comment
        green = c;
        blue = c;
    }

    RGBcolor(int r, int g, int b){
        cout << "Constructor 2 called: " << endl;
        red = r;    
        green = g;
        blue = b;
    }

    void print(){
        cout << "(" << red << "," << green << "," << blue << "," << ")" << endl;
    }

    void setRed(int r){
        red = r; 
    }

};