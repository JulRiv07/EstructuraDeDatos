#include <iostream>
#include <string>
using namespace std;

class Tape {
private:
    std::string cells;
public:
    void write(long long x) {
        cells = "_" + to_string(x) + "_";
    }
    long long read() const {
        string num;
        for (char c : cells) {
            if (c != '_') num.push_back(c);
        }
        return num.empty() ? 0 : stoll(num);
    }
    void print() const {
        cout << "tape=\"" << cells << "\"";
    }
};

class TuringMachine {
private:
    Tape tape;
    long long value;
    int step_limit;
public:
    TuringMachine(int limit = 1000) : value(0), step_limit(limit) {}

    void init(long long start) {
        if (start <= 0) start = 1;
        value = start;
        tape.write(value);
    }

    long long rule(long long n) {
        return (n % 2 == 0) ? n / 2 : 3 * n + 1;
    }

    void run() {
        cout << "== MT con bug en transición (impar->3n-1, par->n/2) ==\n";
        cout << "[step 0] value=" << value << " "; tape.print(); cout << "\n";

        long long tort = value;
        long long hare = value;

        for (int step = 1; step <= step_limit; step++) {
            
            value = rule(value);
            tape.write(value);

            cout << "[step " << step << "] value=" << value << " ";
            tape.print();
            cout << "\n";

            tort = rule(tort);                
            hare = rule(rule(hare));         

            if (tort == hare) {
                cout << "\n[ALERTA] Se detectó ciclo en valor " << tort << ".\n";
                cout << "Causa: bug en transición que aplica 3n-1 / n/2 indefinidamente.\n";
                return;
            }
        }
        cout << "\n[FIN] Alcanzado límite de pasos (" << step_limit << ").\n";
    }
};

int main() {
    long long n;
    cout << "Ingresa un numero positivo: ";
    cin >> n;

    TuringMachine mt(200);
    mt.init(n);
    mt.run();

    return 0;
}

