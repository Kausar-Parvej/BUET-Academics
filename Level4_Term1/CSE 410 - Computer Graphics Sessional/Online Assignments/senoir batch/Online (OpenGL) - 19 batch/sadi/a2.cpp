#include <bits/stdc++.h>
#include <chrono>
using namespace std;

#ifdef __linux__
#include <GL/glut.h>
#elif WIN32
#include <windows.h>
#include <GL/glut.h>
#endif

#define PI 3.14159265f
#define DRAWAXES 1
#define GRAVITY -9.8f

double *getColor(int i);
void moveTowardsCenter(float stepSize);
void moveRight(float distance);
void moveUpWard(float stepSize);
void rotateRight(float angle);
float *rotateVector3d(float lX, float lY, float lZ, float axisX, float axisY, float axisZ, float angle);
void lookUp(float angle);
void tilt(float angle);
void directUp(float stepSize);
void drawStripedSphere(float radius, int slices, int stacks);
void drawThickLineQuad(float x1, float y1, float z1, float x2, float y2, float z2, float thickness);
void setRandomPosition();
void setRandomVelocity();
void setRandomRotation();
void setRotationAxis();
void normalize(float &x, float &y, float &z);
void circleOutline(double x, double y, double r, int segments);

float eyeX = 100;
float eyeY = 100;
float eyeZ = 100;
float centerX = 0;
float centerY = 0;
float centerZ = 0;
float upX = 0;
float upY = 0;
float upZ = 1;

float posX = 0, posY = 0, posZ = 0;
float velX = 10, velY = 5, velZ = 0;
float rotX = 0, rotY = 1, rotZ = 1;
float accX = 0, accY = 0, accZ = GRAVITY;
float deltaTime = 0.016f;
float radius = 4;
float bounceFactor = 0.8f;

bool pauseAnimation = true;
bool showArrow = false;

float velocity = 20;
float omega = 1.0f;
int ballAngle = 0;

float startAngle = 0;
float speedAngle = 0.3;

int eyeAngle = 0;

int arr[5] = {0, 15, 30, 60, 90};
float speed[5] = {0, 0.3, 0.55, 0.8, 1};
int angleIndex = 0;

void seedRandom()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

float randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void drawAxes()
{
    if (DRAWAXES)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glVertex3f(100, 0, 0);
            glVertex3f(-100, 0, 0);

            glVertex3f(0, -100, 0);
            glVertex3f(0, 100, 0);

            glVertex3f(0, 0, 100);
            glVertex3f(0, 0, -100);
        }
        glEnd();
    }
}

void drawSquare(double a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f(0, a, a);
        glVertex3f(0, a, -a);
        glVertex3f(0, -a, -a);
        glVertex3f(0, -a, a);
    }
    glEnd();
}

void drawLine(double x1, double y1, double z1, double x2, double y2, double z2)
{
    glBegin(GL_LINES);
    {
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
    }
    glEnd();
}

void init()
{
    printf("Do your initialization here\n");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(80, 1, 1, 1000.0);

    seedRandom();
    setRandomPosition();
    setRandomVelocity();
    setRandomRotation();
}

void display()
{
    // glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Set background color to black and opaque
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    eyeX = 100 * cosf(PI * eyeAngle / 180);
    eyeY = 100 * sinf(PI * eyeAngle / 180);
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    drawAxes();

    glPushMatrix();
    glRotatef(int(round(startAngle)) % 360, 0, 0, 1);
    circleOutline(0, 0, 50, 20);
    glPopMatrix();

    for (int i = 0; i < 6; i++)
    {
        glPushMatrix();
        glRotatef(int(round(startAngle + i * 60)) % 360, 0, 0, 1);
        glTranslatef(0, 50, 0);
        glRotatef(arr[angleIndex], 1, 0, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(5, 5, -10);
            glVertex3f(-5, 5, -10);
            glVertex3f(-5, -5, -10);
            glVertex3f(5, -5, -10);
        }
        glEnd();

        drawLine(0, 0, 0, 0, -5, -10);
        drawLine(0, 0, 0, 0, 5, -10);
        glPopMatrix();
    }

    glutSwapBuffers();
}

void drawStripedSphere(float radius, int slices, int stacks)
{
    glShadeModel(GL_FLAT);

    for (int i = 0; i < stacks; ++i)
    {
        float lat0 = PI * (-0.5 + (float)i / stacks);
        float lat1 = PI * (-0.5 + (float)(i + 1) / stacks);
        float z0 = sin(lat0), zr0 = cos(lat0);
        float z1 = sin(lat1), zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j)
        {
            float lng = 2 * PI * (float)(j) / slices;
            float x = cos(lng), y = sin(lng);

            // Hemisphere-based flipping of colors per stripe
            bool topHalf = (i < stacks / 2);
            bool isEvenSlice = (j % 2 == 0);

            if ((topHalf && isEvenSlice) || (!topHalf && !isEvenSlice))
                glColor3f(1.0, 0.0, 0.0); // red
            else
                glColor3f(0.0, 1.0, 0.0); // green

            glVertex3f(x * zr0 * radius, y * zr0 * radius, z0 * radius);
            glVertex3f(x * zr1 * radius, y * zr1 * radius, z1 * radius);
        }
        glEnd();
    }
    glShadeModel(GL_SMOOTH);
}
double *getColor(int i)
{
    static double color[3];
    if (i == 0)
    {
        color[0] = 1;
        color[1] = 0;
        color[2] = 0;
    }
    else if (i == 1)
    {
        color[0] = 0;
        color[1] = 1;
        color[2] = 0;
    }
    else if (i == 2)
    {
        color[0] = 0;
        color[1] = 0;
        color[2] = 1;
    }
    else
    {
        color[0] = 1;
        color[1] = 1;
        color[2] = 0;
    }
    return color;
}

void keyboardListener(unsigned char key, int x, int y)
{
    // printf("Key pressed: %c\n", key);
    switch (key)
    {
    case '1':
        /* code */
        // rotateRight(-1);
        angleIndex++;
        if (angleIndex >= 4)
            angleIndex = 4;
        break;
    case '2':
        /* code */
        angleIndex--;
        if (angleIndex <= 0)
            angleIndex = 0;
        break;
    case '3':
        /* code */
        lookUp(-1);
        break;
    case '4':
        /* code */
        lookUp(1);
        break;
    case '5':
        /* code */
        tilt(1);
        break;
    case '6':
        /* code */
        tilt(-1);
        break;
    case 'w':
        /* code */
        directUp(1);
        break;
    case 's':
        /* code */
        directUp(-1);
        break;
    case ' ':
        pauseAnimation = !pauseAnimation;
        break;
    case 'v':
        showArrow = !showArrow;
        break;
    case 'r':
        if (pauseAnimation)
        {
            setRandomPosition();
            setRandomVelocity();
            setRandomRotation();
            omega = 1.0f;
        }
        break;
    case '+':
        if (pauseAnimation)
        {
            velocity += 1;
            normalize(velX, velY, velZ);
            velX *= velocity;
            velY *= velocity;
            velZ *= velocity;
            printf("Velocity: %f\n", velocity);
        }
        break;
    case '-':
        if (pauseAnimation)
        {
            velocity -= 1;
            normalize(velX, velY, velZ);
            velX *= velocity;
            velY *= velocity;
            velZ *= velocity;
            printf("Velocity: %f\n", velocity);
        }
        break;

    case 'd':
        eyeAngle += 1;
        break;
    case 'a':
        eyeAngle -= 1;
        break;
    default:
        printf("We don't know what you pressed\n");
        break;
    }

    glutPostRedisplay();
}

void specialKeyboardListener(int key, int x, int y)
{
    // Pageup -> 104
    // Pagedown -> 105
    // Arrow Up -> 101
    // Arrow Down -> 103
    // Arrow Left -> 100
    // Arrow Right -> 102
    // printf("Key pressed: %d\n", key);
    switch (key)
    {
    case 104:
        moveUpWard(1);
        break;
    case 105:
        moveUpWard(-1);
        break;
    case 102:
        moveRight(1);
        break;
    case 100:
        moveRight(-1);
        break;
    case 101:
        moveTowardsCenter(1);
        break;
    case 103:
        moveTowardsCenter(-1);
        break;

    default:
        printf("We don't know what you pressed\n");
        break;
    }
    glutPostRedisplay();
}

void rotateBall()
{
    float angle = (omega * deltaTime) * (180 / PI);
    glPushMatrix();
    glRotatef(angle, rotX, rotY, rotZ);
    glPopMatrix();
}

void idle()
{
    startAngle += speed[angleIndex];
    // Update velocity with acceleration
    // if (pauseAnimation)
    //     return;

    // velZ += accZ * deltaTime;

    // // Update position with velocity
    // posX += velX * deltaTime;
    // posY += velY * deltaTime;
    // posZ += velZ * deltaTime;

    // float pos[3] = {posX, posY, posZ};
    // float vel[3] = {velX, velY, velZ};
    // const float bounds = 50.0f;

    // for (int i = 0; i < 3; ++i)
    // {
    //     if (pos[i] - radius <= -bounds)
    //     {
    //         pos[i] = -bounds + radius;
    //         vel[i] *= -bounceFactor;
    //         // omega = omega >= 0.5 ? 0.95 * omega : 0.5;
    //         if (i == 2 && vel[i] <= 0.1)
    //         {
    //             vel[i] = 0;
    //             // pos[i] = -50 + 0.001;
    //         }
    //     }
    //     else if (pos[i] + radius >= bounds)
    //     {
    //         pos[i] = bounds - radius;
    //         vel[i] *= -bounceFactor;
    //         // if (i == 2 && vel[i] <= 0.1)
    //         // {
    //         //     vel[i] = 0;
    //         //     pos[i] = -50 + 0.001;
    //         // }
    //         // omega = omega >= 0.5 ? 0.95 * omega : 0.5;
    //     }
    // }

    // // Update original variables if needed
    // posX = pos[0];
    // posY = pos[1];
    // posZ = pos[2];
    // velX = vel[0];
    // velY = vel[1];
    // velZ = vel[2];
    // // Update rotation axis
    // setRotationAxis();

    // // Add wall collisions similarly...
    // ballAngle = (ballAngle + int(round((omega * deltaTime) * (180 / PI)))) % 360;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);     // Set the window's initial width & height
    glutInitWindowPosition(750, 250); // Position the window's initial top-left corner
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Test");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyboardListener);
    glutIdleFunc(idle);
    init();

    glutMainLoop();
    return 0;
}

void moveTowardsCenter(float stepSize)
{
    // Calculate direction vector from eye to center
    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;

    // Normalize the direction vector
    float length = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    dirX /= length;
    dirY /= length;
    dirZ /= length;

    // Move eye position along this direction
    // printf("Prev Eye position: (%d, %d, %d)\n", eyeX, eyeY, eyeZ);
    eyeX += dirX * stepSize;
    eyeY += dirY * stepSize;
    eyeZ += dirZ * stepSize;

    // Move center position along this direction
    centerX += dirX * stepSize;
    centerY += dirY * stepSize;
    centerZ += dirZ * stepSize;
    // printf("Eye position: (%d, %d, %d)\n", eyeX, eyeY, eyeZ);
}

void moveRight(float distance)
{
    // Calculate normalized direction vector (from eye to center)
    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;

    // Calculate right vector (cross product of direction and up)
    float rightX = dirY * upZ - dirZ * upY;
    float rightY = dirZ * upX - dirX * upZ;
    float rightZ = dirX * upY - dirY * upX;

    // Normalize right vector
    float length = sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    rightX /= length;
    rightY /= length;
    rightZ /= length;

    // Move eye and center point
    eyeX += rightX * distance;
    eyeY += rightY * distance;
    eyeZ += rightZ * distance;

    centerX += rightX * distance;
    centerY += rightY * distance;
    centerZ += rightZ * distance;
}

void moveUpWard(float stepSize)
{
    // Normalize the direction vector
    float length = sqrt(upX * upX + upY * upY + upZ * upZ);

    // Move eye position along this direction
    eyeX += (upX / length) * stepSize;
    eyeY += (upY / length) * stepSize;
    eyeZ += (upZ / length) * stepSize;

    centerX += (upX / length) * stepSize;
    centerY += (upY / length) * stepSize;
    centerZ += (upZ / length) * stepSize;
    // printf("Eye position: (%d, %d, %d)\n", eyeX, eyeY, eyeZ);
}

void rotateRight(float angle)
{
    float angleInRadians = angle * PI / 180.0f;

    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;

    // printf("Prev Center position: (%f, %f, %f)\n", centerX, centerY, centerZ);
    float *res = rotateVector3d(dirX, dirY, dirZ, upX, upY, upZ, angle);
    centerX = res[0] + eyeX;
    centerY = res[1] + eyeY;
    centerZ = res[2] + eyeZ;
    // printf("Center position: (%f, %f, %f)\n", centerX, centerY, centerZ);
}

void tilt(float angle)
{
    float angleInRadians = angle * PI / 180.0f;

    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;

    // printf("Prev Center position: (%f, %f, %f)\n", centerX, centerY, centerZ);
    float *res = rotateVector3d(upX, upY, upZ, dirX, dirY, dirZ, angle);
    upX = res[0];
    upY = res[1];
    upZ = res[2];
    // printf("Center position: (%f, %f, %f)\n", centerX, centerY, centerZ);
}

void lookUp(float angle)
{
    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;

    float crossX = dirY * upZ - dirZ * upY;
    float crossY = dirZ * upX - dirX * upZ;
    float crossZ = dirX * upY - dirY * upX;

    // printf("Prev Center position: (%f, %f, %f)\n", centerX, centerY, centerZ);
    float *res = rotateVector3d(dirX, dirY, dirZ, crossX, crossY, crossZ, angle);
    centerX = res[0] + eyeX;
    centerY = res[1] + eyeY;
    centerZ = res[2] + eyeZ;
    // printf("Center position: (%f, %f, %f)\n", centerX, centerY, centerZ);

    float *res2 = rotateVector3d(upX, upY, upZ, crossX, crossY, crossZ, angle);
    upX = res2[0];
    upY = res2[1];
    upZ = res2[2];
    // printf("Up position: (%f, %f, %f)\n", upX, upY, upZ);
}

float *rotateVector3d(float lX, float lY, float lZ, float axisX, float axisY, float axisZ, float angle)
{
    float lengthL = sqrt(lX * lX + lY * lY + lZ * lZ);
    lX /= lengthL;
    lY /= lengthL;
    lZ /= lengthL;

    float uX = lY * axisZ - lZ * axisY;
    float uY = lZ * axisX - lX * axisZ;
    float uZ = lX * axisY - lY * axisX;

    float lengthU = sqrt(uX * uX + uY * uY + uZ * uZ);
    uX /= lengthU;
    uY /= lengthU;
    uZ /= lengthU;

    float angleInRadians = angle * PI / 180.0f;

    static float result[3];
    result[0] = lengthL * (lX * cos(angleInRadians) + uX * sin(angleInRadians));
    result[1] = lengthL * (lY * cos(angleInRadians) + uY * sin(angleInRadians));
    result[2] = lengthL * (lZ * cos(angleInRadians) + uZ * sin(angleInRadians));

    return result;
}

// void directUp(float stepSize)
// {
//     // Normalize the direction vector
//     float length = sqrt(upX * upX + upY * upY + upZ * upZ);

//     // Move eye position along this direction
//     eyeX += (upX / length) * stepSize;
//     eyeY += (upY / length) * stepSize;
//     eyeZ += (upZ / length) * stepSize;
// }

void normalize(float &x, float &y, float &z)
{
    float len = sqrt(x * x + y * y + z * z);
    if (len != 0.0f)
    {
        x /= len;
        y /= len;
        z /= len;
    }
}

void directUp(float stepSize)
{
    float dirX = centerX - eyeX;
    float dirY = centerY - eyeY;
    float dirZ = centerZ - eyeZ;
    normalize(dirX, dirY, dirZ);

    // 2. Compute right vector (dir x up)
    float rightX = dirY * upZ - dirZ * upY;
    float rightY = dirZ * upX - dirX * upZ;
    float rightZ = dirX * upY - dirY * upX;
    normalize(rightX, rightY, rightZ);

    // Update eyeZ
    eyeZ += stepSize;

    // 1. Recompute direction vector
    dirX = centerX - eyeX;
    dirY = centerY - eyeY;
    dirZ = centerZ - eyeZ;
    normalize(dirX, dirY, dirZ);

    // 3. Compute new up vector (right x dir)
    upX = rightY * dirZ - rightZ * dirY;
    upY = rightZ * dirX - rightX * dirZ;
    upZ = rightX * dirY - rightY * dirX;
    normalize(upX, upY, upZ);
}
void drawThickLineQuad(float x1, float y1, float z1, float x2, float y2, float z2, float thickness)
{
    // Compute direction of the line
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;

    float dlen = sqrt(dx * dx + dy * dy + dz * dz);

    // Arbitrary vector not parallel to the line
    float ax = 0, ay = 1, az = 0;
    if (fabs(dy) > 0.99f)
        ax = 1, ay = 0, az = 0; // avoid colinearity

    // Compute perpendicular vector via cross product
    float px = dy * az - dz * ay;
    float py = dz * ax - dx * az;
    float pz = dx * ay - dy * ax;

    // Normalize
    float plen = sqrt(px * px + py * py + pz * pz);
    px = (px / plen) * thickness * 0.5f;
    py = (py / plen) * thickness * 0.5f;
    pz = (pz / plen) * thickness * 0.5f;

    // Draw quad (two points offset in +perp and -perp direction)
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex3f(x1 + px, y1 + py, z1 + pz);
    glVertex3f(x1 - px, y1 - py, z1 - pz);
    glVertex3f(x2 - px, y2 - py, z2 - pz);
    glVertex3f(x2 + px, y2 + py, z2 + pz);
    glEnd();

    float tmpX = x2 - (dx / dlen);
    float tmpY = y2 - (dy / dlen);
    float tmpZ = z2 - (dz / dlen);

    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex3f(tmpX + 4 * px, tmpY + 4 * py, tmpZ + 4 * pz);
        glVertex3f(tmpX - 4 * px, tmpY - 4 * py, tmpZ - 4 * pz);
        glVertex3f(x2 + (dx / dlen), y2 + (dy / dlen), z2 + (dz / dlen));
    }
    glEnd();
}

void setRandomVelocity()
{
    // seedRandom();

    float x, y, z;
    x = randomFloat(-50, 50);
    y = randomFloat(-50, 50);
    z = randomFloat(-50, 50);

    printf("x %f y %f z %f\n", x, y, z);
    float dirX = x - posX;
    float dirY = y - posY;
    float dirZ = z - posZ;
    float length = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    printf("dirX %f dirY %f dirZ %f\n", dirX, dirY, dirZ);
    velX = (dirX / length) * velocity;
    velY = (dirY / length) * velocity;
    velZ = (dirZ / length) * velocity;
    printf("velX %f velY %f velz %f\n", velX, velY, velZ);
}

void setRotationAxis()
{
    // Compute the cross product of velX, velY, velZ with Z axis and set the unit vector as rotation axis
    float crossX = velY * 0 - velZ * 1;
    float crossY = velZ * 0 - velX * 1;
    float crossZ = velX * 1 - velY * 0;
    float length = sqrt(crossX * crossX + crossY * crossY + crossZ * crossZ);
    crossX /= length;
    crossY /= length;
    crossZ /= length;
    rotX = crossX;
    rotY = crossY;
    rotZ = crossZ;
}

void setRandomRotation()
{
    // seedRandom();

    float x, y, z;
    x = randomFloat(-50, 50);
    y = randomFloat(-50, 50);
    z = randomFloat(-50, 50);

    printf("x %f y %f z %f\n", x, y, z);
    float dirX = x - posX;
    float dirY = y - posY;
    float dirZ = z - posZ;
    float length = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
    // printf("dirX %f dirY %f dirZ %f\n", dirX, dirY, dirZ);
    rotX = (dirX / length);
    rotY = (dirY / length);
    rotZ = (dirZ / length);
    // printf("rotX %f rotY %f rotz %f\n", rotX, rotY, rotZ);
}

void setRandomPosition()
{
    // seedRandom();

    posX = randomFloat(-50 + radius, 50 - radius);
    posY = randomFloat(-50 + radius, 50 - radius);
    posZ = -50 + radius;
}

void circleOutline(double x, double y, double r, int segments)
{

    glPushMatrix();
    glBegin(GL_LINE_LOOP); // Use line loop for border only
    for (int i = 0; i < segments; i++)
    {
        double theta = 2.0f * PI * double(i) / double(segments);
        double x = r * cosf(theta);
        double y = r * sinf(theta);
        glVertex3f(x, y, 0);
    }
    glEnd();
    glPopMatrix();
}
