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

// Camera
float eyeX = 4, eyeY = 4, eyeZ = 4;
float centerX = 0, centerY = 0, centerZ = 0;

// ---- Initialization ----
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    printf("3D Template Initialized\n");
}

// ---- Axes ----
void drawAxes(float length = 1.0f) {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(length, 0, 0); // X
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, length, 0); // Y
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, length); // Z
    glEnd();
}

// ---- Example Shape ----
void drawCube(float size = 1.0f) {
    glutWireCube(size);
}

// ---- Display ----
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0);

    drawAxes(1.5);
    glColor3f(1, 0.5, 0); drawCube(); // Example cube

    glutSwapBuffers();
}

// ---- Timer ----
void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(refreshRate, timer, 0);
}

// ---- Reshape ----
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ---- Keyboard (optional camera control) ----
void keyboard(unsigned char key, int, int) {
    float delta = 0.2f;
    switch (key) {
    case 'w': eyeY += delta; break;
    case 's': eyeY -= delta; break;
    case 'a': eyeX -= delta; break;
    case 'd': eyeX += delta; break;
    case 'q': eyeZ -= delta; break;
    case 'e': eyeZ += delta; break;
    case 27: exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D OpenGL Template");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(refreshRate, timer, 0);
    glutMainLoop();
    return 0;
}
