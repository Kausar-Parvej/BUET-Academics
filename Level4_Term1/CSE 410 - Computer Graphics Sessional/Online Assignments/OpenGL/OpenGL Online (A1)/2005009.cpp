/**
 * OpenGL 3D Drawing Demo
 *
 * This program demonstrates basic 3D rendering with OpenGL and GLUT including:
 * - Camera positioning with gluLookAt
 * - Drawing 3D shapes (cube and pyramid)
 * - Keyboard navigation for camera control
 * - Perspective projection
 * - Object toggling
 */

// --- Includes ---
// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// OpenGL / GLUT Headers
#ifdef __APPLE__
#include <GLUT/glut.h> // Use GLUT framework on macOS
#else
#include <GL/glut.h> // Use standard GLUT location on Linux/Windows
#endif

#define ANGLE_STEP 5.0f // Angle step for camera rotation
#define M_PI 3.14159265358979323846 // Define PI if not already defined
#define TRANSLATE_STEP 0.25f // Step size for camera translation

struct point
{
    GLfloat x, y, z;
    point(float x, float y, float z) : x(x), y(y), z(z) {}
    // operator overloacding
    point operator+(const point &p) const
    {
        return point(x + p.x, y + p.y, z + p.z);
    }
    point operator-(const point &p) const
    {
        return point(x - p.x, y - p.y, z - p.z);
    }
    point operator*(float scalar) const
    {
        return point(x * scalar, y * scalar, z * scalar);
    }
    void normalize()
    {
        float length = sqrt(x * x + y * y + z * z);
        if (length > 0)
        {
            x /= length;
            y /= length;
            z /= length;
        }
    }
    point crossProduct(const point &p) const
    {
        return point(y * p.z - z * p.y,
                     z * p.x - x * p.z,
                     x * p.y - y * p.x);
    }
    float length() const
    {
        return sqrt(x * x + y * y + z * z);
    }
};

typedef struct point point;

// --- Global Variables ---
// Camera position and orientation
point eye(4, 2, 4);          // Camera position coordinates
point center(0, 0, 0);       // Look-at point coordinates
point up(0, 1, 0);           // Up vector coordinates

// Object visibility flags
bool isAxes = false;        // Toggle for coordinate axes
float v=1;
float rotationAngle=0.0f;

// --- Function Declarations ---
void initGL();
void display();
void reshapeListener(GLsizei width, GLsizei height);
void keyboardListener(unsigned char key, int x, int y);
void specialKeyListener(int key, int x, int y);
void drawAxes();
void drawBase();
void drawBase2();
void drawFan();


/**
 * Initialize OpenGL settings
 * Sets up background color and enables depth testing
 */
void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
}

/**
 * Main display function
 * Sets up the camera and renders visible objects
 */
void display()
{
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Position camera using the eye, center and up vectors
    gluLookAt(eye.x, eye.y, eye.z,          // Camera position
              center.x, center.y, center.z, // Look-at point
              up.x, up.y, up.z);            // Up vector
    
    // Draw objects based on visibility flags
    // if (isAxes)
        drawAxes();
    // if (!isAxes)
        drawBase();
        drawBase2();
		drawFan();


    glutSwapBuffers();
}

/**
 * Window reshape callback
 * Handles window resizing and maintains aspect ratio
 */
void reshapeListener(GLsizei width, GLsizei height)
{
    // Prevent division by zero
    if (height == 0)
        height = 1;

    // Calculate aspect ratio
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set viewport to cover entire window
    glViewport(0, 0, width, height);

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 45-degree field of view, aspect ratio, near and far clipping planes
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/**
 * Keyboard input handler for standard keys
 * Manages camera position, object visibility, and program exit
 */
void keyboardListener(unsigned char key, int x, int y)
{
    float ang = ANGLE_STEP * M_PI / 180; // degree to radian conversion

    point look = point(center.x - eye.x, center.y - eye.y, center.z - eye.z);
    look.normalize();
    
    point right = look.crossProduct(up);
    right.normalize();

    switch (key)
    {
    case 'a':
	look = look * -cos(ang) - right * -sin(ang);
	eye = center + look * (center - eye).length();
	break;

	case 'd':
		look = look * -cos(ang) + right * -sin(ang);
		eye = center + look * (center - eye).length();
		break;
    case 'w':
        // eye = eye + up * TRANSLATE_STEP;
        v++;
        break;

    case 's':
        // eye = eye - up * TRANSLATE_STEP;
        v--;
		if (v<1) v=1;
        break;

    // --- Program Control ---
    case 27:
        exit(0);
        break; // ESC key: exit program
    }

    glutPostRedisplay(); // Request a screen refresh
}

/**
 * Special key input handler (arrow keys, function keys)
 * Provides camera orbit functionality
 */
void specialKeyListener(int key, int x, int y)
{
    // point look = center - eye;
    // look.normalize();
    
    // point right = look.crossProduct(up);
    // right.normalize();

    // switch (key)
    // {
    // case GLUT_KEY_LEFT:
    //     eye = eye - right * TRANSLATE_STEP;
    //     center = center - right * TRANSLATE_STEP;
    //     break;

    // case GLUT_KEY_RIGHT:
    //     eye = eye + right * TRANSLATE_STEP;
    //     center = center + right * TRANSLATE_STEP;
    //     break;

    // case GLUT_KEY_UP:
    //     eye = eye + look * TRANSLATE_STEP;
    //     // center = center + look * TRANSLATE_STEP;
    //     break;

    // case GLUT_KEY_DOWN:
    //     eye = eye - look * TRANSLATE_STEP;
    //     // center = center - look * TRANSLATE_STEP;
    //     break;
    
    // case GLUT_KEY_PAGE_UP:
    //     eye = eye + up * TRANSLATE_STEP;
    //     center = center + up * TRANSLATE_STEP;
    //     break;

    // case GLUT_KEY_PAGE_DOWN:
    //     eye = eye - up * TRANSLATE_STEP;
    //     center = center - up * TRANSLATE_STEP;
    //     break;
    // }

    // glutPostRedisplay(); // Request a screen refresh
}

/**
 * Draw coordinate axes
 * X axis: red, Y axis: green, Z axis: blue
 */
void drawAxes()
{
    glLineWidth(3); // Set line thickness

    glBegin(GL_LINES);

    // X axis (red)
    glColor3f(1, 0, 0);
    glVertex3f(-5, 0, 0);
    glVertex3f(5, 0, 0);

    // Y axis (green)
    glColor3f(0, 1, 0);
    glVertex3f(0, -5, 0);
    glVertex3f(0, 5, 0);

    // Z axis (blue)
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -5);
    glVertex3f(0, 0, 5);

    glEnd();
}


/**
 * Draw a colored cube centered at the origin
 * Each face has a different color
 */
void drawBase()
{
    glBegin(GL_QUADS);

    // // Top face (y = 1.0f) - Green
    // glColor3f(0.0f, 1.0f, 0.0f);
    // glVertex3f(1.0f, 1.0f, -1.0f);
    // glVertex3f(-1.0f, 1.0f, -1.0f);
    // glVertex3f(-1.0f, 1.0f, 1.0f);
    // glVertex3f(1.0f, 1.0f, 1.0f);

    // // Bottom face (y = -1.0f) - Orange
    // glColor3f(1.0f, 0.5f, 0.0f);
    // glVertex3f(1.0f, -1.0f, 1.0f);
    // glVertex3f(-1.0f, -1.0f, 1.0f);Draw
    // glVertex3f(-1.0f, -1.0f, -1.0f);
    // glVertex3f(1.0f, -1.0f, -1.0f);

    // Front face  (z = 1.0f) - Red
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.4f, 1.2f, 0.4f);
    glVertex3f(-0.4f, 1.2f, 0.4f);
    glVertex3f(-0.3f, -1.0f, 0.3f);
    glVertex3f(0.3f, -1.0f, 0.3f);

    // Back face (z = -0.3f) - Yellow
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.3f, -1.0f, -0.3f);
    glVertex3f(-0.3f, -1.0f, -0.3f);
    glVertex3f(-0.4f, 1.2f, -0.4f);
    glVertex3f(0.4f, 1.2f, -0.4f);

    // Left face (x = -0.3f) - Blue
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.4f, 1.2f, 0.4f);
    glVertex3f(-0.4f, 1.2f, -0.4f);
    glVertex3f(-0.3f, -1.0f, -0.3f);
    glVertex3f(-0.3f, -1.0f, 0.3f);

    // Right face (x = 0.3f) - Magenta
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.4f, 1.2f, -0.4f);
    glVertex3f(0.4f, 1.2f, 0.4f);
    glVertex3f(0.3f, -1.0f, 0.3f);
    glVertex3f(0.3f, -1.0f, -0.3f);

    glEnd();
}

void drawBase2()
{
	glPushMatrix();

	glTranslatef(0.4f, 1.0f, 0.0f);
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, 0.05f);
    glVertex3f(0.2f, 0.05f, 0.05f);

    // Bottom face (y = -0.05f) - Orange
    // glColor3f(0.2f, 0.5f, 0.0f);
    glVertex3f(0.2f, -0.05f, 0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);
    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(0.2f, -0.05f, -0.05f);

    // Front face  (z = 0.05f) - Red
    // glColor3f(0.2f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.05f, 0.05f);
    glVertex3f(-0.05f, 0.05f, 0.05f);
    glVertex3f(-0.05f, -0.05f, 0.05f);
    glVertex3f(0.2f, -0.05f, 0.05f);

    // Back face (z = -0.05f) - Yellow
    // glColor3f(0.2f, 0.05f, 0.0f);
    glVertex3f(0.2f, -0.05f, -0.05f);
    glVertex3f(-0.05f, -0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);
    glVertex3f(0.2f, 0.05f, -0.05f);

    // // Left face (x = -0.2f) - Blue
    // glColor3f(0.0f, 0.0f, 0.2f);
    // glVertex3f(-0.2f, 0.2f, 0.2f);
    // glVertex3f(-0.2f, 0.2f, -0.2f);
    // glVertex3f(-0.2f, -0.2f, -0.2f);
    // glVertex3f(-0.2f, -0.2f, 0.2f);

    // // Right face (x = 0.2f) - Magenta
    // glColor3f(0.2f, 0.0f, 0.2f);
    // glVertex3f(0.2f, 0.2f, -0.2f);
    // glVertex3f(0.2f, 0.2f, 0.2f);
    // glVertex3f(0.2f, -0.2f, 0.2f);
    // glVertex3f(0.2f, -0.2f, -0.2f);

    glEnd();
	glPopMatrix();

}

void drawFan()
{
	glPushMatrix();
	glColor3f(0.0f, 0.5f, 1.0f);
	glTranslatef(0.6f, 1.0f, 0.0f);
	glRotatef(rotationAngle, 1, 0, 0);
    for(float i=0; i<360; i+=120){
		float angle = 1.0f*i*M_PI/180.0f;
		glPushMatrix();
		glRotatef(i, 1, 0, 0);
		glBegin(GL_TRIANGLE_FAN); {
			glVertex3f(0,0,0);
			glVertex3f(0,1.0f,0.2f);
			glVertex3f(0,1.0f,-0.2f);
		}
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();

}

void update(int val) {
	rotationAngle+=v;
	glutPostRedisplay();

	glutTimerFunc(16,update,0);
	
}

/**
 * Main function: Program entry point
 */
int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Configure display mode and window
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Cube");

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeListener);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
	glutTimerFunc(16,update,0);

    // Initialize OpenGL settings
    initGL();

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}