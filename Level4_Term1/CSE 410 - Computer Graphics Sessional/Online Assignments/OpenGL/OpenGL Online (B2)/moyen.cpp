#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

const float pi = 3.14159265358979323846f;
GLfloat angle = 10.0f;
GLfloat v = 0.1f;
GLfloat cubeHalfSize = 2.0f; 
GLfloat ballRadius = 0.1f;
GLfloat velocityChange = 0.05; 
int prevTime = 0;
GLfloat speed=1.0f;
GLfloat angle1=0;
GLfloat t = 0;
class Vector
{
public:
    GLfloat x, y, z;
    Vector(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
    Vector() : x(0), y(0), z(0) {} 

    
    Vector operator+(const Vector &v) const { return Vector(x + v.x, y + v.y, z + v.z); }

    
    Vector operator-(const Vector &v) const { return Vector(x - v.x, y - v.y, z - v.z); }

    
    Vector operator*(GLfloat s) const { return Vector(x * s, y * s, z * s); }

    
    Vector operator-() const { return Vector(-x, -y, -z); }

    
    Vector crossProduct(const Vector &v) const
    {
        return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    
    GLfloat dotProduct(const Vector &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    
    Vector normalize() const
    {
        GLfloat length = sqrt(x * x + y * y + z * z);
        if (length == 0)
            return Vector(0, 0, 0);
        return Vector(x / length, y / length, z / length);
    }
};

class Point
{
public:
    GLfloat x, y, z;
    Point(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
    Point() : x(0), y(0), z(0) {} 
    Vector operator-(const Point &p) const { return Vector(x - p.x, y - p.y, z - p.z); } 
};


Point translate(const Point &p, const Vector &dir, GLfloat dist)
{
    return Point(p.x + dir.x * dist, p.y + dir.y * dist, p.z + dir.z * dist);
}

Vector rotateVector(Vector v, Vector axis, GLfloat angle)
{
    GLfloat radianAngle = angle * pi / 180.0f;
    GLfloat cosAngle = cos(radianAngle);
    GLfloat sinAngle = sin(radianAngle);

    
    Vector cross = axis.crossProduct(v);

    
    GLfloat dot = axis.x * v.x + axis.y * v.y + axis.z * v.z;

    
    Vector rotated;
    rotated.x = v.x * cosAngle + cross.x * sinAngle + axis.x * dot * (1 - cosAngle);
    rotated.y = v.y * cosAngle + cross.y * sinAngle + axis.y * dot * (1 - cosAngle);
    rotated.z = v.z * cosAngle + cross.z * sinAngle + axis.z * dot * (1 - cosAngle);

    return rotated;
}



struct Ball {
    Point position;
    Vector velocity;
    GLfloat radius;
    GLfloat bounceFactor;
    Vector rotationAxis;
    GLfloat rotationAngle;
    GLfloat boundary;
    bool displayVelocityVector;
    bool isSimulationActive;
    bool canChangeVelocity;
};



void resetBallState(Ball &ball) {
    ball.position = Point(
        (rand() % 100) / 50.0f - 1.0f,
        -cubeHalfSize+ ball.radius,
        (rand() % 100) / 50.0f - 1.0f
    );

    ball.velocity = Vector(
        (rand() % 100) / 10.0f - 5.0f,       
        ((rand() % 100) / 10.0f), 
        (rand() % 100) / 10.0f - 5.0f   
    );
} 

void initializeBall(Ball &ball, GLfloat radius, GLfloat boundary) {
    ball.radius = radius;
    ball.bounceFactor = 0.8f;
    ball.rotationAngle = 0.0f;
    ball.boundary = boundary;
    ball.displayVelocityVector = true;
    ball.isSimulationActive = false;
    ball.canChangeVelocity = true;
    resetBallState(ball);
}


void resolveCollision(Ball &ball) {
    GLfloat R = ball.radius;
    GLfloat L = ball.boundary;

    
    if (ball.position.x + R > L || ball.position.x - R < -L) {
        ball.velocity.x = -ball.velocity.x * ball.bounceFactor;
        ball.position.x = ball.position.x > 0 ? L - R : -L + R;

        if(fabs(ball.velocity.x) < 0.0005f && ball.position.x - R <= -L + 0.001f)
            ball.velocity.x = 0;
    }

    
    if (ball.position.y + R > L || ball.position.y - R < -L) {
        ball.velocity.y = -ball.velocity.y * ball.bounceFactor;
        ball.position.y = ball.position.y > 0 ? L - R : -L + R;

        if (fabs(ball.velocity.y) < 0.0005f && ball.position.y - R <= -L + 0.001f)
            ball.velocity.y = 0;
    }

    
    if (ball.position.z + R > L || ball.position.z - R < -L) {
        ball.velocity.z = -ball.velocity.z * ball.bounceFactor;
        ball.position.z = ball.position.z > 0 ? L - R : -L + R;

        if(fabs(ball.velocity.z) < 0.0005f && ball.position.z - R <= -L + 0.001f)
            ball.velocity.z = 0;
    }
}

void updateBall(Ball &ball, GLfloat deltaTime) {
    ball.velocity.y -= 9.8f * deltaTime;

    ball.position.x += ball.velocity.x * deltaTime;
    ball.position.y += ball.velocity.y * deltaTime;
    ball.position.z += ball.velocity.z * deltaTime;

    Vector horizontalVelocity(ball.velocity.x, 0, ball.velocity.z);
    GLfloat speed = sqrt(horizontalVelocity.x * horizontalVelocity.x + horizontalVelocity.z * horizontalVelocity.z);
    GLfloat distance = speed * deltaTime;

    if (distance > 0.0001f) {
        Vector moveDir = Vector(horizontalVelocity.x / speed, 0, horizontalVelocity.z / speed);
        ball.rotationAxis = Vector(moveDir.z, 0, -moveDir.x);
        ball.rotationAngle += (distance / ball.radius) * (180.0f / pi);
    }

    resolveCollision(ball);
}



void renderBall(const Ball &ball) {
    int slices = 20;
    int stacks = 20;

    glPushMatrix();
    glTranslatef(ball.position.x, ball.position.y, ball.position.z);

    if (ball.rotationAngle != 0.0f)
        glRotatef(ball.rotationAngle, ball.rotationAxis.x, ball.rotationAxis.y, ball.rotationAxis.z);

    for (int i = 0; i < slices; ++i) {
        float theta1 = (i * 2.0f * pi) / slices;
        float theta2 = ((i + 1) * 2.0f * pi) / slices;

        glColor3f(i % 2 == 0 ? 1.0f : 0.0f, 0.0f, i % 2 != 0 ? 1.0f : 0.0f);
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; ++j) {
            float phi = (j * pi) / stacks;
            float y = ball.radius * cos(phi);
            float r = ball.radius * sin(phi);

            float x1 = r * cos(theta1);
            float z1 = r * sin(theta1);
            float x2 = r * cos(theta2);
            float z2 = r * sin(theta2);

            glVertex3f(x1, y, z1);
            glVertex3f(x2, y, z2);
        }
        glEnd();
    }

    glPopMatrix();

    if (ball.displayVelocityVector) {
        GLfloat scaleFactor = 0.1f;
        glPushMatrix();
        glBegin(GL_LINES);
        glColor3f(0, 1, 0);
        glVertex3f(ball.position.x, ball.position.y, ball.position.z);
        glVertex3f(
            ball.position.x + ball.velocity.x * scaleFactor,
            ball.position.y + ball.velocity.y * scaleFactor,
            ball.position.z + ball.velocity.z * scaleFactor
        );
        glEnd();
        glPopMatrix();
    }
    
}




Point eye(20, 20, 20);
Point center(0, 0, 0);
Vector up(0, 1, 0);


Ball ball;


void initGL();
void display();
void reshapeListener(GLsizei width, GLsizei height);
void keyboardListener(unsigned char key, int x, int y);
void specialKeyListener(int key, int x, int y);
void timerFunction(int value);
void drawAxes();
void drawCube();
void drawPyramid();
void drawPin();
void draw3D(GLfloat, GLfloat);
void draw3D1(GLfloat, GLfloat);
void drawHand(GLfloat, GLfloat);


void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glEnable(GL_DEPTH_TEST);              
    
    
    prevTime = glutGet(GLUT_ELAPSED_TIME);
    
}

/**
 * Main display function
 * Sets up the camera and renders visible objects
 */
void display()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    gluLookAt(eye.x, eye.y, eye.z,          
              center.x, center.y, center.z, 
              up.x, up.y, up.z); 


    double seconds =t;
    float secAngle = (seconds* speed * 60)*pi / 180.0;
    // double centerX=cubeHalfSize*1.50;
    // double centerY=5;

    // glColor3f(1, 1, 1);
    // drawHand(5.0f, secAngle, centerX, centerY, 0);
    drawAxes();           

    
    // drawCube();
    // drawPin();
    // glPushMatrix();
    // draw3D();
    // glPopMatrix();

    GLfloat radius= 7;
    GLfloat height =2*radius*cos(67.5*pi/180);
    for(int i=0;i<8;i++)
    {
        glPushMatrix();
        glRotatef(angle1, 1, 0, 0);
        glColor3f(0.0f, (i%2)*1.0f, 1.0f);
        glRotatef(45*i, 0, 1, 0);
        draw3D1(radius, height/2);
        glPopMatrix();
    }

    for(int i=0;i<8;i++)
    {
        glPushMatrix();
        glRotatef(angle1, 1, 0, 0);
        glColor3f((i%2)*1.0f, 1, 0);
        glRotatef(45*i, 0, 1, 0);
        draw3D(radius/7, height/2);
        glPopMatrix();
    }

    glColor3f(1, 0, 0);

    for(int i=0;i<6;i++)
    {
        glPushMatrix();
        glRotatef(angle1, 1, 0, 0);
        glTranslatef(0, height/2, 0);
        drawHand(6, secAngle+60*i*pi/180);
        
        glPopMatrix();
    }
    



        
    
    
    renderBall(ball);

    
    glutSwapBuffers();
}

/**
 * Window reshape callback
 * Handles window resizing and maintains aspect ratio
 */
void reshapeListener(GLsizei width, GLsizei height)
{
    
    if (height == 0)
        height = 1;

    
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    
    glViewport(0, 0, width, height);

    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/**
 * Timer function for animation and physics updates
 */
void timerFunction(int value)
{
    
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float dt = (currentTime - prevTime) / 1000.0f; 
    prevTime = currentTime;
    
    
    if (ball.isSimulationActive)
    {
        updateBall(ball, dt);
    }
    
    
    glutPostRedisplay();
    t += 0.067;
    glutTimerFunc(16, timerFunction, 0); 
}

/**
 * Keyboard input handler for standard keys
 * Manages camera position, object visibility, and program exit
 */
void keyboardListener(unsigned char key, int x, int y)
{
    Vector look = (center - eye).normalize();
    Vector right = (look.crossProduct(up)).normalize();

    switch (key)
    {
    
    case '1':
        
        look = rotateVector(look, up, -angle);  
        look = look.normalize();
        center = translate(eye, look, 1);
        break;

    case '2':
        
        look = rotateVector(look, up, angle);   
        look = look.normalize();
        center = translate(eye, look, 1);
        break;

    case '3':
        look = rotateVector(look, right, -angle); 
        look = look.normalize();
        center = translate(eye, look, 1);
        up = right.crossProduct(look).normalize();
        break;
        
    case '4':
        look = rotateVector(look, right, angle); 
        look = look.normalize();
        center = translate(eye, look, 1);
        up = right.crossProduct(look).normalize(); 
        break;

    case '5':
        up = rotateVector(up, look, -angle);
        up = up.normalize();
        center = translate(eye, look, 1);
        break;
        
    case '6':
        up = rotateVector(up, look, angle);
        up = up.normalize();
        center = translate(eye, look, 1);
        break;


    case 'w':
        // eye=translate(eye, up, v);
        speed += 0.1;
        break;
    case 's':
        // eye=translate(eye, up, -v);
        speed -= 0.1;
        speed = std::max(0.0f, speed);
        break; 

    case 'a':
        // eye=translate(eye, up, v);
        angle1 +=10;
        break;
    case 'd':
        // eye=translate(eye, up, -v);
        angle1 -= 10;
        break; 
    
    // case '3':
    //     look = rotateVector(look, right, -angle); 
    //     look = look.normalize();
    //     center = translate(eye, look, 1);
    //     up = right.crossProduct(look).normalize();
    //     break;



    
    case 'r':
        if(!ball.isSimulationActive)
        {
            resetBallState(ball);
            ball.canChangeVelocity = true;
        }
        break;
        
    case ' ':
        ball.isSimulationActive = !ball.isSimulationActive;
        if(ball.isSimulationActive)
            ball.canChangeVelocity = false;
        break; 
        
    case 'v':
        ball.displayVelocityVector = !ball.displayVelocityVector;
        break;
        
    case '+':
        if(ball.canChangeVelocity)
        {
            ball.velocity = ball.velocity*(1+velocityChange);
        }

        break;
        
    case '-':
        if(ball.canChangeVelocity)
        {
            ball.velocity = ball.velocity*(1-velocityChange);
        }
        break;

    
    case 27:
        exit(0);
        break; 
    }

    glutPostRedisplay(); 
}

/**
 * Special key input handler (arrow keys, function keys)
 * Provides camera orbit functionality
 */
void specialKeyListener(int key, int x, int y)
{
    
    Vector forward = (center - eye).normalize();
    Vector right = (forward.crossProduct(up)).normalize(); 

    switch (key)
    {
        case GLUT_KEY_UP:
            eye = translate(eye, forward, v);
            center = translate(center, forward, v);
            break;

        case GLUT_KEY_DOWN:
            eye = translate(eye, forward, -v);
            center = translate(center, forward, -v);
            break;

        case GLUT_KEY_RIGHT:
            eye = translate(eye, right, v);
            center = translate(center, right, v);
            break;

        case GLUT_KEY_LEFT:
            eye = translate(eye, right, -v);
            center = translate(center, right, -v);
            break;

        case GLUT_KEY_PAGE_UP:
            eye = translate(eye, up, v);
            center = translate(center, up, v);
            break;

        case GLUT_KEY_PAGE_DOWN:
            eye = translate(eye, up, -v);
            center = translate(center, up, -v);
            break;
    }

    glutPostRedisplay(); 
}

/**
 * Draw coordinate axes
 * X axis: red, Y axis: green, Z axis: blue
 */
void drawAxes()
{
    glLineWidth(3); 

    glBegin(GL_LINES);

    
    glColor3f(1, 1, 1);
    glVertex3f(-10, 0, 0);
    glVertex3f(10, 0, 0);

    
    // glColor3f(0, 1, 0);
    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0);

    
    // glColor3f(0, 0, 1);
    glVertex3f(0, 0, -10);
    glVertex3f(0, 0, 10);

    glEnd();
}

/**
 * Draw a colored cube centered at the origin
 * Each face has a different color
 */
 void drawCube()
 {
     GLfloat s = cubeHalfSize;  

    glBegin(GL_QUADS);
     
     glColor3f(0.0f, 0.0f, 1.0f);
     glVertex3f( s,  cubeHalfSize*4,  s);
     glVertex3f(-s,  cubeHalfSize*4,  s);
     glVertex3f(-s, -cubeHalfSize*4,  s);
     glVertex3f( s, -cubeHalfSize*4,  s);
 

     glVertex3f( s, -cubeHalfSize*4, -s);
     glVertex3f(-s, -cubeHalfSize*4, -s);
     glVertex3f(-s,  cubeHalfSize*4, -s);
     glVertex3f( s,  cubeHalfSize*4, -s);
 
     
     glColor3f(0.0f, 1.0f, 0.0f);
     glVertex3f(-s,  cubeHalfSize*4,  s);
     glVertex3f(-s,  cubeHalfSize*4, -s);
     glVertex3f(-s, -cubeHalfSize*4, -s);
     glVertex3f(-s, -cubeHalfSize*4,  s);
 
     glVertex3f( s,  cubeHalfSize*4, -s);
     glVertex3f( s,  cubeHalfSize*4,  s);
     glVertex3f( s, -cubeHalfSize*4,  s);
     glVertex3f( s, -cubeHalfSize*4, -s);
 
     glEnd();
 }


 void draw3D(GLfloat radius, GLfloat height)
 {

    GLfloat s = radius;
    GLfloat a = height;
    glBegin(GL_QUADS);
    glVertex3f( s,  0,  0);
    glVertex3f( s,  a,  0);
    glVertex3f( s*cos(45*pi/180), a,  s*sin(45*pi/180));
    glVertex3f( s*cos(45*pi/180), 0,  s*sin(45*pi/180));
    glEnd();

 }

 void draw3D1(GLfloat radius, GLfloat height)
 {

    GLfloat s = radius;
    GLfloat a = height;
    glBegin(GL_QUADS);
    glVertex3f( s,  -a,  0);
    glVertex3f( s,  a,  0);
    glVertex3f( s*cos(45*pi/180), a,  s*sin(45*pi/180));
    glVertex3f( s*cos(45*pi/180), -a,  s*sin(45*pi/180));
    glEnd();

 }

 void drawPin()
 {
    GLfloat s = cubeHalfSize/6;  

    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glTranslatef(5, 0, 0);

    glBegin(GL_QUADS);
     
     glColor3f(1.0f, 0.0f, 1.0f);
     glVertex3f( s,  cubeHalfSize*1.50,  s);
     glVertex3f(-s,  cubeHalfSize*1.50,  s);
     glVertex3f(-s, -cubeHalfSize*1.50,  s);
     glVertex3f( s, -cubeHalfSize*1.50,  s);
 
     
    //  glColor3f(1.0f, 1.0f, 0.0f);
     glVertex3f( s, -cubeHalfSize*1.50, -s);
     glVertex3f(-s, -cubeHalfSize*1.50, -s);
     glVertex3f(-s,  cubeHalfSize*1.50, -s);
     glVertex3f( s,  cubeHalfSize*1.50, -s);
 
     

    //  glColor3f(0.0f, 0.0f, 1.0f);
     glVertex3f(-s,  cubeHalfSize*1.50,  s);
     glVertex3f(-s,  cubeHalfSize*1.50, -s);
     glVertex3f(-s, -cubeHalfSize*1.50, -s);
     glVertex3f(-s, -cubeHalfSize*1.50,  s);
 
     
    //  glColor3f(1.0f, 0.0f, 1.0f);
     glVertex3f( s,  cubeHalfSize*1.50, -s);
     glVertex3f( s,  cubeHalfSize*1.50,  s);
     glVertex3f( s, -cubeHalfSize*1.50,  s);
     glVertex3f( s, -cubeHalfSize*1.50, -s);
 
     glEnd();

     glPopMatrix();
 }
 

void drawHand(float length, float angleRad){
    glPushMatrix(); // Save the current transformation matrix
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0+length * cos(angleRad), 0, 0+length * sin(angleRad));
    glEnd();
    glPopMatrix(); // Restore the original transformation matrix
}

/**
 * Draw a pyramid with color gradients
 * Base at y=-1, apex at y=1
 */
void drawPyramid()
{
    glBegin(GL_TRIANGLES);

    
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(1.0f, -1.0f, 1.0f);

    
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(1.0f, -1.0f, -1.0f);

    
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(-1.0f, -1.0f, -1.0f);

    
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
}

/**
 * Main function: Program entry point
 */
int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);

    
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("OpenGL 3D Drawing with Ball Physics");

    
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeListener);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutTimerFunc(16, timerFunction, 0); 

    
    initGL();

    
    initializeBall(ball, 0.1f, cubeHalfSize); 

    glutMainLoop();

    return 0;
}