#ifndef VECTOR3D_CPP
#define VECTOR3D_CPP

#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

class Vector3D {

public:
    double x, y, z;

    Vector3D(){
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Vector3D(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vector3D(const Vector3D &vec){
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }

    
    Vector3D operator+(Vector3D vec2){
        return Vector3D(this->x + vec2.x, this->y + vec2.y, this->z + vec2.z);
    }
    Vector3D operator-(Vector3D vec2){
        return Vector3D(this->x - vec2.x, this->y - vec2.y, this->z - vec2.z);
    }
    Vector3D operator*(double scalar){
        return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
    }
    
    double dot(Vector3D vec2) {
        return this->x * vec2.x + this->y * vec2.y + this->z * vec2.z;
    }
    double magnitude() {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }



    Vector3D operator=(const Vector3D &vec2);
    Vector3D operator/(double scaler);
    Vector3D normalize();
    Vector3D cross(Vector3D vec2);
    double angle(Vector3D vec2);
    
    Vector3D rotate(Vector3D axis, double radian); // Counter Clockwise rotation around any axis
    Vector3D perpRotate(Vector3D axis, double radian); // vector lies in a plane perpendicular to the axis


};



Vector3D Vector3D::operator=(const Vector3D &vec2) {
    this->x = vec2.x;
    this->y = vec2.y;
    this->z = vec2.z;
    return *this;
}


Vector3D Vector3D :: operator/(double scaler){
    if(scaler == 0) {printf("Error: Division by zero in Vector3D::operator/\n"); exit(1);}
    return Vector3D(this->x / scaler, this->y / scaler, this->z / scaler);
}

Vector3D Vector3D::normalize() {
    double mag = this->magnitude();
    if (mag == 0) {
        printf("Error: Cannot normalize a zero vector in Vector3D::normalize\n");
        exit(1);
    }
    return *this / mag;
}

Vector3D Vector3D::cross(Vector3D vec2) {
    return Vector3D(
        this->y * vec2.z - this->z * vec2.y,
        this->z * vec2.x - this->x * vec2.z,
        this->x * vec2.y - this->y * vec2.x
    );
}

double Vector3D::angle(Vector3D vec2) {   // Returns angle in radians
    double dotProduct = this->dot(vec2);
    double magnitudes = this->magnitude() * vec2.magnitude();
    if (magnitudes == 0) {
        printf("Error: Cannot calculate angle with zero vector in Vector3D::angle\n");
        exit(1);
    }
    double cosAngle = dotProduct / magnitudes;
    if (cosAngle < -1.0) cosAngle = -1.0;  // to avoid precision errors
    if (cosAngle > 1.0) cosAngle = 1.0;
    return acos(cosAngle);      
}



Vector3D Vector3D::perpRotate(Vector3D axis, double radian){
    Vector3D vec = *this;
    Vector3D r = axis.normalize();
    Vector3D prep_vec = r.cross(vec);

    return vec*cos(radian) + prep_vec*sin(radian);
}

Vector3D Vector3D::rotate(Vector3D axis, double radian) {
    Vector3D vec = *this;
    Vector3D r = axis.normalize();
    double cosTheta = cos(radian);
    double sinTheta = sin(radian);
    
    return vec * cosTheta + r * (1 - cosTheta) * vec.dot(r) + r.cross(vec) * sinTheta;   //Rodrigues' rotation formula
}



istream &operator>>(istream &in_stream, Vector3D &vec) {
    in_stream >> vec.x >> vec.y >> vec.z;
    return in_stream;
}

ostream &operator<<(ostream &os, const Vector3D &vec) {
    os << fixed << setprecision(7);
    os << vec.x << " " << vec.y << " " << vec.z;
    os << std::resetiosflags(ios_base::fixed);
    return os;
}



#endif // VECTOR3D_CPP
