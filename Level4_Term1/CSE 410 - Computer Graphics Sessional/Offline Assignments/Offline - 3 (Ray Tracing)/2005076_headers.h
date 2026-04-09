#ifndef _Headers_H
#define _Headers_H


#ifdef __linux__
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#elif _WIN32
#include <windows.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <bits/stdc++.h>
#include <cmath>
#include <iomanip>
#include "bitmap_image.hpp"
#include "stb_image.h"


using namespace std;

#define M_PI 3.14159265
#define _USE_MATH_DEFINES

class Vec3D{
public:
    double x, y, z;
    Vec3D();
    Vec3D(double x, double y, double z);
    Vec3D(const Vec3D &p);
    Vec3D operator+(const Vec3D &b) const;
    Vec3D operator+=(Vec3D b);
    Vec3D operator-(const Vec3D &b) const;
    Vec3D operator-=(Vec3D b);
    Vec3D operator-();
    Vec3D operator*(double b) const;
    Vec3D operator/(double b);
    Vec3D operator/(Vec3D b);
    Vec3D operator/=(Vec3D b);
    Vec3D operator*(const Vec3D &b) const;
    Vec3D operator*=(Vec3D b);
    double angle(Vec3D b);
    Vec3D perpRotate(Vec3D axis, double radian);
    Vec3D rotate(Vec3D axis, double radian);
    double magnitude();
    Vec3D normalize();
    double dot(const Vec3D &b) const;

    friend ostream &operator<<(ostream &os, const Vec3D &dt);
};

ostream &operator<<(ostream &os, const Vec3D &v);


class Vec2D : public Vec3D{
public:
    Vec2D();
    Vec2D(double x, double y);
    Vec2D(const Vec2D &v);

    Vec2D operator+(Vec2D b);
    Vec2D operator+=(Vec2D b);
    Vec2D operator-(Vec2D b);
    Vec2D operator-();
    Vec2D operator-=(Vec2D b);
    Vec2D operator*(double b);
    Vec2D operator/(double b);
    Vec2D operator/(Vec2D b);
    Vec2D operator/=(Vec2D b);

    double magnitude();
    Vec2D normalize();
    Vec2D perp();
    Vec2D rotate(double radian);
    Vec2D reflect(Vec2D r);
    double angle(Vec2D b);

    bool operator==(Vec2D b);
    double dot(Vec2D b);
};

class Matrix{
public:
    vector<vector<double>> data;
    Matrix(int, int);
    Matrix(vector<vector<double>> data);
    ~Matrix();
    void identity();
    Matrix operator*(const Matrix &other) const;
    Matrix operator*=(const Matrix &other);
    double determinant();
    static double determinant(vector<vector<double>> data);
};

//-------------------------------------------------------------------------//


class Ray{
public:
    Vec3D start;
    Vec3D dir; // noramalized
   
    Ray();
    Ray(Vec3D, Vec3D);
};



class Color
{
public:
    double r, g, b;
    Color();
    Color(double, double, double);
    void randomize();

    Color operator*(double);
    Color operator*(const Color &);
    Color operator+=(const Color &);

    friend ostream &operator<<(ostream &os, const Color &c);
    friend istream &operator>>(istream &os, const Color &c);
};
ostream &operator<<(ostream &os, const Color &c);
istream &operator>>(istream &is, Color &c);



class PointLight{
public:
    Vec3D light_pos;
    Color color;

    PointLight();
    PointLight(Vec3D, Color);
    void draw();
};

class SpotLight
{
public:
    PointLight *point_light;
    Vec3D light_direction;
    double cutoff_angle;

    SpotLight(PointLight, Vec3D, double);
    ~SpotLight();
    void draw();
};


//-----------------------------------------------------------------//


class Object{
public:
    Vec3D reference_point; 
    double height, width, length;
    Color color;
    vector<double> materialCoefficients; // ambient, diffuse, specular, reflection coefficients
    int shine;                   // exponent term of specular component

    Object();
    ~Object();
    virtual void draw() = 0;
    void setColor(Color);
    void setShine(int);
    void setMaterialCoefficients(vector<double>);
    void colorSpotLight(PointLight *, Color *, Vec3D, Color *, Ray *, double);
    void colorSurface(PointLight *, Color *, Vec3D, Color *, Ray *);
    virtual Color getColorAt(Vec3D);
    virtual double findIntersection(Ray *) = 0;
    virtual Ray getNormal(Vec3D, Ray *) const = 0;
    virtual double intersect(Ray *, Color *color, int level);
};


class Triangle : public Object{
public:
    Triangle();
    Triangle(vector<Vec3D> vertices);
    void fillColor();
    void draw();
    friend ostream &operator<<(ostream &os, const Triangle &v);
    friend istream &operator>>(istream &os, const Triangle &v);

    double findIntersection(Ray *ray);
    Ray getNormal(Vec3D point, Ray *incident) const;

    vector<Vec3D> vertices;
};

ostream &operator<<(ostream &os, const Triangle &v);
istream &operator>>(istream &is, Triangle &v);



class Sphere : public Object{
public:
    Sphere();
    Sphere(Vec3D center, double radius);
    void draw();

    friend ostream &operator<<(ostream &os, const Sphere &s);
    friend istream &operator>>(istream &os, const Sphere &s);

    double findIntersection(Ray *ray);
    Ray getNormal(Vec3D point, Ray *incident) const;
};

ostream &operator<<(ostream &os, const Sphere &s);
istream &operator>>(istream &is, Sphere &s);


class General : public Object{
public:
    double A, B, C, D, E, F, G, H, I, J;

    General();
    General(Vec3D reference_point, double length, double width, double height, vector<double> materialCoefficients);
    void draw();
    friend ostream &operator<<(ostream &os, const General &g);
    friend istream &operator>>(istream &os, const General &g);

    bool shouldDraw(Vec3D point);
    double findIntersection(Ray *r);
    Ray getNormal(Vec3D point, Ray *incident) const;
};
ostream &operator<<(ostream &os, const General &g);
istream &operator>>(istream &is, General &g);


class Floor : public Object{
public:
    int tileCount;
    bool useTexture;
    unsigned char* textureData;
    int textureWidth, textureHeight, textureChannels;
    unsigned int glTextureId;
    bool glTextureLoaded;

    Floor(double floorWidth, double tileWidth);
    ~Floor();
    void draw();
    void loadTexture(const string& filename);
    void setUseTexture(bool use);
    bool isUsingTexture() const;
    Color sampleTexture(double u, double v);
    void loadGLTexture();
    double findIntersection(Ray *r);
    Ray getNormal(Vec3D point, Ray *incident) const;
    Color getColorAt(Vec3D point);
};


//-------------------------------------------------------------------------//



class Camera{
public:
    Vec3D pos, up, right, look;
    double focal_length;

    Camera();
    void init(Vec3D p, Vec3D u, Vec3D r, Vec3D l);
    void set();
    void rotateAroundUp(double radian);
    void rotateLeft();
    void rotateRight();
    void rotateAroundRight(double radian);
    void rotateUp();
    void rotateDown();
    void rotateAroundLook(double radian);
    void tiltClock();
    void tiltCounterClock();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveAroundRef(int dir);
    void moveUpRef();
    void moveDownRef();
    void drawReference();
    void keyPress(unsigned char);
    void specialKeyPress(int);
    void mouseScroll(int);
};


class GraphicsManager
{
public:
    static GLint windowHeight, windowWidth;
    static double viewAngle, nearPlane, farPlane;

public:
    static void keyHandler(unsigned char, int, int);
    static void specialKeyHandler(int, int, int);
    static void keyboard(unsigned char);
    static void specialKeyboard(int);

    static void displayHandler();
    static void display();

    static void resize(int, int);
    static void resize2D(int, int);

    static void mouseClickHandler(int, int, int, int);
    static void mouseScroll(int);

    static void initialize(int, int, char *, int = 2);
    static void init();

    static void drawPolygon(vector<Vec2D>, double r, double g, double b);
    static void drawFilledPolygon(vector<Vec2D>, double r, double g, double b);

    static void draw2DLine(Vec2D p, Vec2D q, double r, double g, double b);
    static void draw3DLine(Vec3D p, Vec3D q, double r, double g, double b);

    static void drawCheckerboard();
    static void drawCircle(double radius, double r, double g, double b, int segments = 100);
    static void drawFilledCircle(double radius, double r, double g, double b, int segments = 100);

    static void drawSquare(double a, double r, double g, double b);
    static void drawFilledSquare(double a, double r, double g, double b);

    static void drawEllipse(double x, double y, double a, double b, int slices = 100);
    static void drawFilledEllipse(double x, double y, double a, double b, int slices = 100);

    static void drawAxis();
    static void draw2DAxis();
    static void drawCube();
    static void drawCylinder(float radius, float height);
    static void drawCone(float radius, float height);
    static void drawArrow(double length);
};


//-------------------------------------------------------------------------//


double radians(double degrees);
double degrees(double radians);

double distancePointToPoint2D(Vec2D a, Vec2D b);
double distancePointToPoint3D(Vec3D a, Vec3D b);

Vec2D getIntersectionPoint(Vec2D a_point, Vec2D a_dir, Vec2D b_point, Vec2D b_dir);

bool haveSameDirection(Vec2D a, Vec2D b);
bool doRayIntersectLine(Vec2D ray_p, Vec2D ray_d, Vec2D line_p, Vec2D line_d);
bool doIntersect(Vec2D a_dir, Vec2D b_dir);




#endif