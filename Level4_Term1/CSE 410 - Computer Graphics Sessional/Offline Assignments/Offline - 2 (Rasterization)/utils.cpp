#ifndef UTILS_CPP
#define UTILS_CPP

#include <cmath>
#include <cstdlib>


using namespace std;

class Color {

public:
    int r;
    int g;
    int b;

    Color(){
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }

    Color(int red, int gteen, int blue){
        this->r = red;
        this->g = gteen;
        this->b = blue;
    }

    void randomize(){
        this->r = rand() % 256;
        this->g = rand() % 256;
        this->b = rand() % 256;
    }
};



double radians(double degrees) {
    return degrees * M_PI / 180.0;
}

double degrees(double radians) {
    return radians * 180.0 / M_PI;
}


#endif // UTILS_CPP