#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Camera
const double EYE_X = 0.0, EYE_Y = 0.0, EYE_Z = 20.0;
const double AT_X = 0.0, AT_Y = 0.0, AT_Z = 0.0;
const double UP_X = 0.0, UP_Y = 1.0, UP_Z = 0.0;

// Radial lines
const double RADIAL_LEN = 10.0;

// Axis length
const double AXIS_LENGTH = RADIAL_LEN;

// Number of squares
const int NUM_SQUARES = 8;

// Square size
const double SQUARE_SIZE = 0.5;

// Structure state (0-10 for 11 states)
int currentState = 0;

// Rotation angle
double rotationAngle = 0.0;

// Visibility toggles
bool showRadialLines = true;

// Rotation speed for each state
double rotationSpeeds[11] = {0.0, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8};

// Square distances from center for each state
double squareDistances[11] = {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0};

// Draw a square
void drawSquare()
{
    glBegin(GL_QUADS);
    glVertex3f(-SQUARE_SIZE / 2, -SQUARE_SIZE / 2, 0.0);
    glVertex3f(SQUARE_SIZE / 2, -SQUARE_SIZE / 2, 0.0);
    glVertex3f(SQUARE_SIZE / 2, SQUARE_SIZE / 2, 0.0);
    glVertex3f(-SQUARE_SIZE / 2, SQUARE_SIZE / 2, 0.0);
    glEnd();
}

// Draw the center hub
void drawCenterHub()
{
    glColor3f(1.0, 1.0, 1.0);

    // Draw the elliptical center
    glPushMatrix();
    glScalef(1.5, 0.5, 1.0);
    glutWireTorus(0.1, 1.0, 20, 20);
    glPopMatrix();
}

// Draw radial lines
void drawRadialLines()
{
    if (!showRadialLines)
        return; // Skip drawing if visibility is off

    glColor3f(1.0, 1.0, 1.0);

    // Draw three radial lines as shown in the image
    glBegin(GL_LINES);

    // Horizontal line
    glVertex3f(-RADIAL_LEN, 0.0, 0.0);
    glVertex3f(RADIAL_LEN, 0.0, 0.0);

    // Vertical line
    glVertex3f(0.0, -RADIAL_LEN / 2, 0.0);
    glVertex3f(0.0, RADIAL_LEN / 2, 0.0);

    // Diagonal line 1 (bottom-left to top-right)
    glVertex3f(-RADIAL_LEN * 0.7071, -RADIAL_LEN * 0.7071 / 2, 0.0);
    glVertex3f(RADIAL_LEN * 0.7071, RADIAL_LEN * 0.7071 / 2, 0.0);

    // Diagonal line 2 (top-left to bottom-right)
    glVertex3f(-RADIAL_LEN * 0.7071, RADIAL_LEN * 0.7071 / 2, 0.0);
    glVertex3f(RADIAL_LEN * 0.7071, -RADIAL_LEN * 0.7071 / 2, 0.0);

    glEnd();
}

// Draw hanging squares
void drawHangingSquares()
{
    double radius = squareDistances[currentState];
    double angle = 2.0 * M_PI / NUM_SQUARES;
    double stringLength = 3.0; // Fixed string length
    double ringRadius = 1.5;   // Radius of the center ring

    // Calculate string tilt based on state (0 = vertical, 10 = horizontal)
    double stringTiltFactor = currentState / 10.0;

    // Calculate square tilt based on state (0 = horizontal, 10 = vertical)
    double squareTiltFactor = currentState / 10.0;
    double squareTiltAngle = 90.0 * squareTiltFactor; // 0 to 90 degrees

    glColor3f(1.0, 1.0, 1.0);

    for (int i = 0; i < NUM_SQUARES; i++)
    {
        double currentAngle = i * angle + rotationAngle;

        // Calculate square position
        double xPos = radius * cos(currentAngle);
        double yPos = radius * sin(currentAngle) / 2.0; // Flatten y to create elliptical path

        // Calculate position for the square
        double squareX, squareY;

        if (currentState == 0)
        {
            // State 0: Squares hang vertically below their positions
            squareX = xPos;
            squareY = yPos - stringLength;
        }
        else
        {
            // Interpolate between vertical hanging and tilted positions
            squareX = xPos;
            squareY = yPos - stringLength * (1.0 - stringTiltFactor);
        }

        // Calculate two connection points on the ring (diagonally opposite)
        // Connection point 1 - on the ring close to the square's angle
        double ringPoint1X = ringRadius * cos(currentAngle - 0.2);
        double ringPoint1Y = ringRadius * sin(currentAngle - 0.2) / 2.0;

        // Connection point 2 - on the ring, diagonal from point 1
        double ringPoint2X = ringRadius * cos(currentAngle + 0.2);
        double ringPoint2Y = ringRadius * sin(currentAngle + 0.2) / 2.0;

        // Draw two diagonal strings from ring to square
        glBegin(GL_LINES);
        // String 1
        glVertex3f(ringPoint1X, ringPoint1Y, 0.0);
        glVertex3f(squareX - SQUARE_SIZE / 4, squareY, 0.0);

        // String 2
        glVertex3f(ringPoint2X, ringPoint2Y, 0.0);
        glVertex3f(squareX + SQUARE_SIZE / 4, squareY, 0.0);
        glEnd();

        // Draw square
        glPushMatrix();
        glTranslatef(squareX, squareY, 0.0);

        // Rotate square based on state (0 = horizontal, 10 = vertical)
        glRotatef(squareTiltAngle, 0.0, 0.0, 1.0);

        drawSquare();
        glPopMatrix();
    }
}

void display()
{
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set camera position and orientation
    gluLookAt(EYE_X, EYE_Y, EYE_Z,
              AT_X, AT_Y, AT_Z,
              UP_X, UP_Y, UP_Z);

    // Draw the structure
    drawCenterHub();
    drawRadialLines();
    drawHangingSquares();

    // Display state number
    char stateText[50];
    sprintf(stateText, "State: %d/10 | Left click: Toggle radial lines", currentState);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-RADIAL_LEN, -RADIAL_LEN / 2 - 1.0);
    for (int i = 0; stateText[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, stateText[i]);
    }

    // Swap the front and back buffers (double buffering)
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0)
        h = 1;
    float ar = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ar, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        // Move to next state
        if (currentState < 10)
            currentState++;
    }
    else if (key == '2')
    {
        // Move to previous state
        if (currentState > 0)
            currentState--;
    }
    else if (key == 27)
    { // ESC key
        exit(0);
    }
    glutPostRedisplay();
}

void timer(int value)
{
    // Update rotation based on current state
    rotationAngle += rotationSpeeds[currentState] * 0.01;
    if (rotationAngle > 2.0 * M_PI)
        rotationAngle -= 2.0 * M_PI;

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

// Mouse callback function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Toggle radial lines visibility
        showRadialLines = !showRadialLines;
        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Horizontal Ferris Wheel");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse); // Register mouse callback
    glutTimerFunc(10, timer, 0);

    glutMainLoop();
    return 0;
}