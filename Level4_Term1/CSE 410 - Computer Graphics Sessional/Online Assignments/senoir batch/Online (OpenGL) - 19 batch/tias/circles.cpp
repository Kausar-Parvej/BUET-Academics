#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>

double cameraHeight = 150.0;
double cameraAngle = 1.0;
int drawaxes = 0;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int WINDOW_POS_X = 0;
const int WINDOW_POS_Y = 0;

const double CAMERA_POS_Z = 200.0;
const double CAMERA_LOOK_AT_X = 0.0;
const double CAMERA_LOOK_AT_Y = 0.0;
const double CAMERA_LOOK_AT_Z = 0.0;
const double CAMERA_UP_X = 0.0;
const double CAMERA_UP_Y = 1.0;
const double CAMERA_UP_Z = 0.0;

const double FIELD_OF_VIEW = 80.0;
const double NEAR_PLANE = 1.0;
const double FAR_PLANE = 1000.0;
const double ASPECT_RATIO = 1.0;

const int CIRCLE_SEGMENTS = 50;
const double B_CIRCLE_RADIUS = 60.0;
const double R_CIRCLE_RADIUS = 25.0;
const double Y_CIRCLE_RADIUS = 5.0;
const double AXIS_LENGTH = 100.0;
const double PI = 2 * acos(0.0);

struct point
{
    double x, y, z;
};

double radiusAngle = 0.0;     // The radius line starts at 0 degrees
double angleIncrement = 0.01; // Increment angle for rotation

void drawAxes()
{
    if (drawaxes == 1)
    {
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glVertex3f(AXIS_LENGTH, 0, 0);
            glVertex3f(-AXIS_LENGTH, 0, 0);

            glVertex3f(0, -AXIS_LENGTH, 0);
            glVertex3f(0, AXIS_LENGTH, 0);

            glVertex3f(0, 0, AXIS_LENGTH);
            glVertex3f(0, 0, -AXIS_LENGTH);
        }
        glEnd();
    }
}

void drawCircle(double radius, int segments)
{
    int i;
    struct point points[100];

    for (i = 0; i <= segments; i++)
    {
        points[i].x = radius * cos(((double)i / (double)segments) * 2 * PI);
        points[i].y = radius * sin(((double)i / (double)segments) * 2 * PI);
    }
    for (i = 0; i < segments; i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(points[i].x, points[i].y, 0);
            glVertex3f(points[i + 1].x, points[i + 1].y, 0);
        }
        glEnd();
    }
}

void drawCircleAtPoint(double radius, int segments, double centerX, double centerY)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i)
    {
        float angle = 2.0f * PI * float(i) / float(segments);
        float x = centerX + radius * cosf(angle);
        float y = centerY + radius * sinf(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
}

void reshape(int width, int height)
{
    // Prevent division by zero
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)width / (float)height;
    gluPerspective(80, aspectRatio, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, CAMERA_POS_Z,
              CAMERA_LOOK_AT_X, CAMERA_LOOK_AT_Y, CAMERA_LOOK_AT_Z,
              CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z);

    glMatrixMode(GL_MODELVIEW);

    drawAxes();

    // Draw the blue circle
    glColor3f(0.0, 0.0, 1.0);
    drawCircle(B_CIRCLE_RADIUS, CIRCLE_SEGMENTS);

    // Calculate positions of all circles and radii
    
    // Blue circle - main circle at the center
    double blueCenterX = 0.0;
    double blueCenterY = 0.0;
    
    // Rotating radius endpoint for blue circle
    double blueRadiusEndX = blueCenterX + B_CIRCLE_RADIUS * cos(radiusAngle);
    double blueRadiusEndY = blueCenterY + B_CIRCLE_RADIUS * sin(radiusAngle);
    
    // Red circle - centered at the end of the blue radius
    double redCenterX = blueRadiusEndX;
    double redCenterY = blueRadiusEndY;
    
    // Calculate the angle for the red circle's rotating radius
    // Using different speed for more interesting motion
    double redAngle = radiusAngle * 3.0;
    
    // Rotating radius endpoint for red circle
    double redRadiusEndX = redCenterX + R_CIRCLE_RADIUS * cos(redAngle);
    double redRadiusEndY = redCenterY + R_CIRCLE_RADIUS * sin(redAngle);
    
    // Yellow circle - centered at the end of the red radius
    double yellowCenterX = redRadiusEndX;
    double yellowCenterY = redRadiusEndY;
    
    // Calculate the angle for the yellow circle's rotating radius
    // Using different speed for more interesting motion
    double yellowAngle = radiusAngle * 5.0;
    
    // Rotating radius endpoint for yellow circle
    double yellowRadiusEndX = yellowCenterX + Y_CIRCLE_RADIUS * cos(yellowAngle);
    double yellowRadiusEndY = yellowCenterY + Y_CIRCLE_RADIUS * sin(yellowAngle);
    
    // Draw blue radius line
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    {
        glVertex3f(blueCenterX, blueCenterY, 0.0f);
        glVertex3f(blueRadiusEndX, blueRadiusEndY, 0.0f);
    }
    glEnd();
    
    // Draw red circle
    glColor3f(1.0, 0.0, 0.0);
    drawCircleAtPoint(R_CIRCLE_RADIUS, CIRCLE_SEGMENTS, redCenterX, redCenterY);
    
    // Draw red radius line
    glBegin(GL_LINES);
    {
        glVertex3f(redCenterX, redCenterY, 0.0f);
        glVertex3f(redRadiusEndX, redRadiusEndY, 0.0f);
    }
    glEnd();
    
    // Draw yellow circle
    glColor3f(1.0, 1.0, 0.0);
    drawCircleAtPoint(Y_CIRCLE_RADIUS, CIRCLE_SEGMENTS, yellowCenterX, yellowCenterY);
    
    // // Draw yellow radius line
    // glBegin(GL_LINES);
    // {
    //     glVertex3f(yellowCenterX, yellowCenterY, 0.0f);
    //     glVertex3f(yellowRadiusEndX, yellowRadiusEndY, 0.0f);
    // }
    // glEnd();

    glutSwapBuffers();
}

void init()
{
    cameraHeight = 150.0;
    cameraAngle = 1.0;

    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(FIELD_OF_VIEW, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
}

void idle()
{
    radiusAngle += angleIncrement;
    if (radiusAngle > 2 * PI)
    {
        radiusAngle -= 2 * PI; // Keep angle within 0 to 2*PI
    }
    glutPostRedisplay(); // Request a redraw
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("Rotating Circle");

    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}