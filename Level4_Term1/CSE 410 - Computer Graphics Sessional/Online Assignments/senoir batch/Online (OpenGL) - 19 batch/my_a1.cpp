// Platform-specific includes
#ifdef __linux__
#include <GL/glut.h>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#include <GL/glut.h>
#elif defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <ctime>
#include <cstdio>


const float PI = 3.14159265358979323846f;
const int refreshRate = 16; //16ms -> ~60 FPS


float angle = 0;
float speed = 2.0f;


void drawAxes(float length);
void circleOutline(double x, double y, double r);
void drawLine(double x1, double y1, double x2, double y2);
void square(double a);
void squareOutline(double a);
void drawFilledCircle(float x, float y, float radius, int segments);
void drawTriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3);
void drawTriangleOutline(float x1, float y1, float x2, float y2, float x3, float y3);





void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
}

// ---- Axes (optional) ----
void drawAxes(float length = 1.0f) {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex2f(-length, 0); glVertex2f(length, 0); // X-axis
    glColor3f(0, 1, 0); glVertex2f(0, -length); glVertex2f(0, length); // Y-axis
    glEnd();
}

// ---- Example Shape ----
void drawCircle(float cx, float cy, float r, int segments = 100) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * PI * float(i) / float(segments);
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

// ---- Display ----
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glLineWidth(0.8f);

    //drawAxes();


    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(-0.6f, 0.0f, 0.0f);
    drawCircle(0, 0, 0.6f); 


    float theta = 2.0f * PI * angle / 360.0f;
    float x = 0.6f * cos(theta);
    float y = 0.6f * sin(theta);

    
    drawLine(0, 0, x, y);
    glColor3f(1, 0, 0);
    drawCircle(x, y, 0.02f, 100);

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(1.0f, y);

    x = 1.0f;
    for(int i=0; i<200; i++){
        x += 0.01f;
        float delta = 2.0f * PI * float(i) / float(120);    // 120 points => lamda
        y = 0.6f * sin(theta - delta);
        glVertex2f(x, y);
    }
    glEnd();



    glPopMatrix();

    glutSwapBuffers();
}

// ---- Timer ----
void timer(int) {

    if(angle > 360) angle -= 360;
    angle += speed;


    glutPostRedisplay();   // Request a redraw
    glutTimerFunc(refreshRate, timer, 0);
}

// ---- Reshape ----
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect >= 1)
        gluOrtho2D(-aspect, aspect, -1, 1);
    else
        gluOrtho2D(-1, 1, -1 / aspect, 1 / aspect);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("2D OpenGL Template");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(refreshRate, timer, 0);
    glutMainLoop();
    return 0;
}


//-----------------------------------------------------------------//









void drawFilledCircle(float x, float y, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for (int i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * M_PI * i / segments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void circleOutline(double x, double y, double r)
{

    glPushMatrix();
    int segments = 100;
    glBegin(GL_LINE_LOOP); // Use line loop for border only
    for (int i = 0; i < segments; i++)
    {
        double theta = 2.0f * PI * double(i) / double(segments);
        double x = r * cosf(theta);
        double y = r * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}

void drawLine(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINES);
    {
        glVertex3f(x1, y1, 0);
        glVertex3f(x2, y2, 0);
    }
    glEnd();
}

void square(double a)
{

    glBegin(GL_QUADS);
    {
        glVertex3f(a, a, 0);
        glVertex3f(a, -a, 0);
        glVertex3f(-a, -a, 0);
        glVertex3f(-a, a, 0);
    }
    glEnd();
}

void squareOutline(double a)
{

    glBegin(GL_LINE_LOOP);
    {
        glVertex3f(a, a, 0);
        glVertex3f(a, -a, 0);
        glVertex3f(-a, -a, 0);
        glVertex3f(-a, a, 0);
    }
    glEnd();
}

void drawTriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawTriangleOutline(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}
