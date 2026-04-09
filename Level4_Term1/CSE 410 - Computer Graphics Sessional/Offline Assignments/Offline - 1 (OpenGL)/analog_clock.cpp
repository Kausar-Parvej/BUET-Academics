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


void drawAxes(float length);
void drawClockFace();
void drawClockHands();


void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // White background
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);
    printf("Analog Clock Initialized\n");
}

void drawAxes(float length)
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); // X axis
    glVertex2f(-length, 0);
    glVertex2f(length, 0);

    glColor3f(0, 1, 0); // Y axis
    glVertex2f(0, -length);
    glVertex2f(0, length);
    glEnd();
}

void drawClockFace()
{
    // Outer circle
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float theta = i * PI / 180.0f;
        glVertex2f(cos(theta), sin(theta));
    }
    glEnd();

    // Hour markers
    glColor3f(1.0f, 0.3f, 0.0f); // Orange color
    for (int i = 0; i < 12; ++i)
    {
        float angle = i * PI / 6; // 30 degrees
        float x1 = 0.85f * cos(angle);
        float y1 = 0.85f * sin(angle);
        float x2 = cos(angle);
        float y2 = sin(angle);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    // Minute markers
    glColor3f(1, 1, 1);
    for (int i = 0; i < 60; ++i)
    {
        if (i % 5 == 0) continue;
        float angle = i * PI / 30; // 6 degrees
        float x1 = 0.92f * cos(angle);
        float y1 = 0.92f * sin(angle);
        float x2 = cos(angle);
        float y2 = sin(angle);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void drawClockHands()
{
    time_t now = time(0);
    struct tm *ltm = localtime(&now);

    int hours = ltm->tm_hour % 12;
    int minutes = ltm->tm_min;
    int seconds = ltm->tm_sec;

    float secAngle = (90 - seconds * 6) * PI / 180.0f;
    float minAngle = (90 - (minutes + seconds / 60.0f) * 6) * PI / 180.0f;
    float hourAngle = (90 - (hours + minutes / 60.0f) * 30) * PI / 180.0f;

    // Hour hand
    glColor3f(0.6f, 0.2f, 0.8f); // Purple color
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0.5f * cos(hourAngle), 0.5f * sin(hourAngle));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(1.045f * cos(hourAngle), 1.045f * sin(hourAngle));
    glVertex2f(cos(hourAngle + 0.045f), sin(hourAngle + 0.045f));
    glVertex2f(0.965f * cos(hourAngle), 0.965f * sin(hourAngle));
    glVertex2f(cos(hourAngle - 0.045f), sin(hourAngle - 0.045f));
    glEnd();

    // Minute hand
    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0.75f * cos(minAngle), 0.75f * sin(minAngle));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(1.045f * cos(minAngle), 1.045f * sin(minAngle));
    glVertex2f(cos(minAngle + 0.045f), sin(minAngle + 0.045f));
    glVertex2f(0.965f * cos(minAngle), 0.965f * sin(minAngle));
    glVertex2f(cos(minAngle - 0.045f), sin(minAngle - 0.045f));
    glEnd();

    // Second hand
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0.9f * cos(secAngle), 0.9f * sin(secAngle));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(1.045f * cos(secAngle), 1.045f * sin(secAngle));
    glVertex2f(cos(secAngle + 0.045f), sin(secAngle + 0.045f));
    glVertex2f(0.965f * cos(secAngle), 0.965f * sin(secAngle));
    glVertex2f(cos(secAngle - 0.045f), sin(secAngle - 0.045f));
    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Scale the clock view
    glScalef(0.8f, 0.8f, 1.0f);

    drawClockFace();
    drawClockHands();

    glutSwapBuffers();
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(refreshRate, timer, 0);
}


void reshape(int width, int height)
{
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)width / (float)height;
    if (aspect >= 1.0f)
        gluOrtho2D(-aspect, aspect, -1.0f, 1.0f);
    else
        gluOrtho2D(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Real-Time Analog Clock");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(refreshRate, timer, 0);

    glutMainLoop();
    return 0;
}
