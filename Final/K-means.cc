#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class point {
    public:
        double x, y;
        int grupo;

        point(double m, double n){
            x = m;
            y = n;
            grupo = -1;
        }
};

class cluster {
    public:
        double cx, cy;

        cluster(double m, double n){
            cx = m;
            cy = n;
        }

        void actualizate(const vector<point> &puntos, int group){
            double sumX = 0, sumY = 0;
            int count = 0;

            for (const auto& p : puntos){
                if (p.grupo = group){
                    sumX += p.x;
                    sumY = p.y;
                    count++;
                }
            }
        }
};