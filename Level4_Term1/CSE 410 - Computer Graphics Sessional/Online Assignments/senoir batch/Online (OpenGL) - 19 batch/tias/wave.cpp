#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

// Constants for physics
const double PI = 3.14159265358979323846;
const double AMPLITUDE = 80.0;        // Maximum displacement from equilibrium
const double ANGULAR_FREQUENCY = 0.01; // ω = 2π/T, where T is the time period
const double PHASE = 0.0;             // Initial phase

// Window parameters
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// Display parameters
const int CIRCLE_SEGMENTS = 50;
const int MAX_WAVE_POINTS = 500;
const double WAVE_X_SCALE = 0.25;
const double WAVE_START_GAP = 20.0;

// Wave tracking
double time = 0.0;                    // Time parameter for wave equation
double wavePoints[MAX_WAVE_POINTS];   // Array to store y-positions of wave
int wavePointCount = 0;               // Current number of wave points stored

// Simple Wave Function: y = A * sin(ωt + φ)
// Using modulo to ensure continuous rotation with extremely large t values
double simpleHarmonicMotion(double t) {
    // Calculate effective angle using modulo to keep it within bounds for continuous rotation
    double angle = fmod(ANGULAR_FREQUENCY * t + PHASE, 2 * PI);
    return AMPLITUDE * sin(angle);
}

// Draw a circle with given parameters
void drawCircle(double radius, int segments) {
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        double angle = 2.0 * PI * i / segments;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glVertex3f(x, y, 0.0);
    }
    glEnd();
}

// Draw the reference point on the circle
void drawReferencePoint(double radius, double t) {
    // Calculate position using physics formula with modulo for continuous rotation
    double angle = fmod(ANGULAR_FREQUENCY * t + PHASE, 2 * PI);
    double x = radius * cos(angle);
    double y = radius * sin(angle);
    
    // Draw small red circle at this position
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0); // Center
    for (int i = 0; i <= 20; i++) {
        double pointAngle = 2.0 * PI * i / 20;
        glVertex3f(x + 3.0 * cos(pointAngle), y + 3.0 * sin(pointAngle), 0.0);
    }
    glEnd();
    
    // Draw radius line
    glColor3f(1.0, 1.0, 1.0); // White color
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(x, y, 0.0);
    glEnd();
    
    return;
}

// Update the wave points array with newest value
void updateWavePoints(double y) {
    // Shift existing points to make room for new point
    if (wavePointCount < MAX_WAVE_POINTS) {
        for (int i = wavePointCount; i > 0; i--) {
            wavePoints[i] = wavePoints[i-1];
        }
        wavePoints[0] = y;
        wavePointCount++;
    } else {
        for (int i = MAX_WAVE_POINTS - 1; i > 0; i--) {
            wavePoints[i] = wavePoints[i-1];
        }
        wavePoints[0] = y;
    }
}

// Draw the wave points
void drawWave(double circleX, double circleRadius) {
    double waveStartX = circleX + circleRadius + WAVE_START_GAP;
    
    // Draw wave points
    glColor3f(1.0, 1.0, 1.0); // White color
    glBegin(GL_POINTS);
    for (int i = 0; i < wavePointCount; i++) {
        glVertex3f(waveStartX + i * WAVE_X_SCALE, wavePoints[i], 0.0);
    }
    glEnd();
    
    // Draw connecting line only if we have wave points
    if (wavePointCount > 0) {
        double currentY = wavePoints[0];
        double angle = ANGULAR_FREQUENCY * time + PHASE;
        double pointX = circleX + AMPLITUDE * cos(angle);
        
        glBegin(GL_LINES);
        glVertex3f(pointX, currentY, 0.0);
        glVertex3f(waveStartX, currentY, 0.0);
        glEnd();
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Set up view
    glLoadIdentity();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
    
    // Define circle position
    double circleX = -60.0;
    double circleY = 0.0;
    
    // Draw circle
    glPushMatrix();
    glTranslatef(circleX, circleY, 0.0);
    drawCircle(AMPLITUDE, CIRCLE_SEGMENTS);
    
    // Calculate current y-position using simple harmonic motion
    double y = simpleHarmonicMotion(time);
    
    // Draw reference point and radius line
    drawReferencePoint(AMPLITUDE, time);
    glPopMatrix();
    
    // Update and draw wave
    updateWavePoints(y);
    drawWave(circleX, AMPLITUDE);
    
    glutSwapBuffers();
}

// Reshape function
void reshape(int width, int height) {
    if (height == 0) height = 1;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspectRatio = (float)width / (float)height;
    gluPerspective(80, aspectRatio, 1, 1000.0);
    
    glMatrixMode(GL_MODELVIEW);
}

// Idle function for animation
void idle() {
    // Increment time (controls the speed of the simulation)
    time += 2.0;
    
    // Instead of resetting, we'll just use modular arithmetic in our calculations
    // This ensures the rotation is continuous without any observable resets
    
    glutPostRedisplay();
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, 1.0, 1.0, 1000.0);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Simple Wave Physics Simulation");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return 0;
}