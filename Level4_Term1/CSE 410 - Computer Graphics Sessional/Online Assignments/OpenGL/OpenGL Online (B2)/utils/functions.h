#ifndef UTILS_H
#define UTILS_H
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define pi (2 * acos(0.0))

struct Color
{
    float r, g, b;
};

struct point
{
    double x, y, z;
};

struct Ball
{
    float x, y, z;   
    float radius;     
    float vx, vy, vz;
    float angle;
    float angularVelocity; 
    float rotationAxisX, rotationAxisY, rotationAxisZ;
};

struct Camera
{
    float eyex, eyey, eyez; 
    float dirx, diry, dirz; 
    float upx, upy, upz;   
};

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glEnable(GL_DEPTH_TEST);              
}

void reshapeListener(GLsizei width, GLsizei height)
{
    if (height == 0)
        height = 1;

    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(80.0f, aspect, 0.1f, 100.0f);
}

vector<float> CrossProduct(vector<float> &a, vector<float> &b)
{
    vector<float> result(3);
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    return result;
}

vector<float> normalizeVector(vector<float> &v)
{
    float length = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (length == 0)
        return {0, 0, 0}; 
    return {v[0] / length, v[1] / length, v[2] / length};
}

void drawCircleOutline(double x, double y, double radius, int segments, Color color)
{
    int i;
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_LINE_LOOP); 
    for (i = 0; i < segments; i++)
    {
        double angle = (2 * pi * i) / segments;
        glVertex3f(x + radius * cos(angle), y + radius * sin(angle), 0);
    }
    glEnd();
}

float convertToRadians(float degrees)
{
    return degrees * (pi / 180.0f);
}

float convertToDegrees(float radians)
{
    return radians * (180.0f / pi);
}

void drawCircleFilled(double x, double y, double radius, int segments, Color color)
{
    int i;
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0);
    for (i = 0; i <= segments; i++)
    {
        double angle = (2 * pi * i) / segments;
        glVertex3f(x + radius * cos(angle), y + radius * sin(angle), 0);
    }
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0);
    glVertex3f(x2, y2, 0);
    glEnd();
}

void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
}


void drawColoredSphere(float radius, int slices, int stacks)
{
    int colorSwitch = 1;

    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < stacks; j++)
        {
            float theta1 = (i) * 2 * pi / slices;
            float theta2 = (i + 1) * 2 * pi / slices;
            float phi1 = (j)*pi / stacks;
            float phi2 = (j + 1) * pi / stacks;

            if (colorSwitch)
                glColor3f(255.0f / 255.0f, 165.0f / 255.0f, 0.0f); // Yellow
            else
                glColor3f(1.0f, 0.0f, 1.0f); // Lemon

            colorSwitch++;
            colorSwitch %= 2; 

            glBegin(GL_TRIANGLES);
            glVertex3f(radius * sin(phi1) * cos(theta1), radius * cos(phi1), radius * sin(phi1) * sin(theta1));
            glVertex3f(radius * sin(phi2) * cos(theta1), radius * cos(phi2), radius * sin(phi2) * sin(theta1));
            glVertex3f(radius * sin(phi2) * cos(theta2), radius * cos(phi2), radius * sin(phi2) * sin(theta2));

            if (colorSwitch)
                glColor3f(1.0f, 1.0f, 0.0f); 
            else
                glColor3f(0.0f, 1.0f, 0.0f); 
            glVertex3f(radius * sin(phi1) * cos(theta1), radius * cos(phi1), radius * sin(phi1) * sin(theta1));
            glVertex3f(radius * sin(phi2) * cos(theta2), radius * cos(phi2), radius * sin(phi2) * sin(theta2));
            glVertex3f(radius * sin(phi1) * cos(theta2), radius * cos(phi1), radius * sin(phi1) * sin(theta2));
            glEnd();
        }
    }
}

void drawStripedSphere(float radius, int slices, int stacks)
{
    glShadeModel(GL_FLAT);
    for (int i = 0; i < stacks; ++i)
    {
        float lat0 = pi * (-0.5 + (float)i / stacks);
        float lat1 = pi * (-0.5 + (float)(i + 1) / stacks);
        float z0 = sin(lat0), zr0 = cos(lat0);
        float z1 = sin(lat1), zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j)
        {
            float lng = 2 * pi * (float)(j) / slices;
            float x = cos(lng), y = sin(lng);

            bool topHalf = (i < stacks / 2);
            bool isEvenSlice = (j % 2 == 0);

            if ((topHalf && isEvenSlice) || (!topHalf && !isEvenSlice))
                glColor3f(1.0, 0.0, 0.0); 
            else
                glColor3f(0.0, 1.0, 0.0); 

            glVertex3f(x * zr0 * radius, y * zr0 * radius, z0 * radius);
            glVertex3f(x * zr1 * radius, y * zr1 * radius, z1 * radius);
        }
        glEnd();
    }
    glShadeModel(GL_SMOOTH);
}

void drawCube(float sideLength, float x, float y, float z)
{
    glBegin(GL_QUADS);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(sideLength, sideLength, -sideLength);
    glVertex3f(-sideLength, sideLength, -sideLength);
    glVertex3f(-sideLength, sideLength, sideLength);
    glVertex3f(sideLength, sideLength, sideLength);

    float tileSize = 2.0f;                         
    int numTiles = int(2 * sideLength / tileSize); 

    for (int i = 0; i < numTiles; i++)
    {
        for (int j = 0; j < numTiles; j++)
        {
            if ((i + j) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f); 
            else
                glColor3f(0.0f, 0.0f, 0.0f); 

            glVertex3f(x + (i * tileSize) - sideLength, y - sideLength, z + (j * tileSize) - sideLength);             
            glVertex3f(x + ((i + 1) * tileSize) - sideLength, y - sideLength, z + (j * tileSize) - sideLength);       
            glVertex3f(x + ((i + 1) * tileSize) - sideLength, y - sideLength, z + ((j + 1) * tileSize) - sideLength);
            glVertex3f(x + (i * tileSize) - sideLength, y - sideLength, z + ((j + 1) * tileSize) - sideLength);      
        }
    }

    // Front face  (z = sideLength) - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(sideLength, sideLength, sideLength);
    glVertex3f(-sideLength, sideLength, sideLength);
    glVertex3f(-sideLength, -sideLength, sideLength);
    glVertex3f(sideLength, -sideLength, sideLength);

    // Back face (z = -sideLength) - Yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(sideLength, -sideLength, -sideLength);
    glVertex3f(-sideLength, -sideLength, -sideLength);
    glVertex3f(-sideLength, sideLength, -sideLength);
    glVertex3f(sideLength, sideLength, -sideLength);

    // Left face (x = -sideLength) - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-sideLength, sideLength, sideLength);
    glVertex3f(-sideLength, sideLength, -sideLength);
    glVertex3f(-sideLength, -sideLength, -sideLength);
    glVertex3f(-sideLength, -sideLength, sideLength);

    // Right face (x = sideLength) - Magenta
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(sideLength, sideLength, -sideLength);
    glVertex3f(sideLength, sideLength, sideLength);
    glVertex3f(sideLength, -sideLength, sideLength);
    glVertex3f(sideLength, -sideLength, -sideLength);

    glEnd();
}

#endif // UTILS_H
