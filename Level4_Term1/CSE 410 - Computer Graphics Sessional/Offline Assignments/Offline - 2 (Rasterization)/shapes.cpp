#ifndef SHAPES_CPP
#define SHAPES_CPP

#include "vector3D.cpp"
#include "utils.cpp"
#include "Matrix.cpp"

#include <vector>


class Triangle {

public:
    vector<Vector3D> vertices;
    Color color;

    Triangle() : vertices(vector<Vector3D>(3)) {}  //member initializer
    Triangle(vector<Vector3D> vertices) : vertices(vector<Vector3D>(3)) {
        for (int i = 0; i < 3; i++) {
            this->vertices[i] = vertices[i];
        }
    }

    void fillColor() {
        color.randomize();
    }

};



istream &operator>>(istream &input, Triangle &t) {
    for (Vector3D &v : t.vertices) input >> v;
    return input;
}
ostream &operator<<(ostream &out_stream, const Triangle &t) {
    for (const Vector3D &v : t.vertices) out_stream << v << "\n";
    return out_stream;
}




#endif // SHAPES_CPP