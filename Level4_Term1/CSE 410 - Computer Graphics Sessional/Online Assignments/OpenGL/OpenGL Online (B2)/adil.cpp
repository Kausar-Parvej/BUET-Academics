#include "utils/functions.h"
#include <bits/stdc++.h>
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Camera camera = {
    25, 25, 25,
    -25, -25, -25,
    0, 0, 1};

const float VELOCITY_THRESHOLD = 0.001f;
const float CAMERA_MOVE_SPEED = 1.0f;
const float CAMERA_ROTATE_SPEED = 0.05f;
const float SIDE_LENGTH = 16.0f;
const float BALL_RADIUS = 0.8f;
const float GRAVITY = 0.1f;
float fan_angle = 0.0f;
float fan_speed = 0.0f;
float body_angle = 0;

Ball ball = {
    0, -SIDE_LENGTH + BALL_RADIUS, 0,
    BALL_RADIUS,
    0, 0, 0};

bool isMoving = false;
bool SHOW_VELOCITY_ARROW = false;
bool isInitialized = false;

void rotateYaw(float direction_speed)
{
    vector<float> forward = {camera.dirx, camera.diry, camera.dirz};
    vector<float> up = {camera.upx, camera.upy, camera.upz};
    vector<float> right = CrossProduct(forward, up);
    right = normalizeVector(right);
    camera.dirx = direction_speed * right[0] + camera.dirx;
    camera.diry = direction_speed * right[1] + camera.diry;
    camera.dirz = direction_speed * right[2] + camera.dirz;
    vector<float> normalizedDir = {camera.dirx, camera.diry, camera.dirz};
    normalizedDir = normalizeVector(normalizedDir);
    camera.dirx = normalizedDir[0];
    camera.diry = normalizedDir[1];
    camera.dirz = normalizedDir[2];
}

void rotatePitch(float direction_speed)
{
    camera.dirx = direction_speed * camera.upx + camera.dirx;
    camera.diry = direction_speed * camera.upy + camera.diry;
    camera.dirz = direction_speed * camera.upz + camera.dirz;
    vector<float> normalizedDir = {camera.dirx, camera.diry, camera.dirz};
    normalizedDir = normalizeVector(normalizedDir);
    camera.dirx = normalizedDir[0];
    camera.diry = normalizedDir[1];
    camera.dirz = normalizedDir[2];
    vector<float> forward = {camera.dirx, camera.diry, camera.dirz};
    vector<float> up = {camera.upx, camera.upy, camera.upz};
    vector<float> right = CrossProduct(forward, up);

    vector<float> newUp = CrossProduct(right, forward);
    newUp = normalizeVector(newUp);
    camera.upx = newUp[0];
    camera.upy = newUp[1];
    camera.upz = newUp[2];
}

void rotateRoll(float direction_speed)
{
    vector<float> forward = {camera.dirx, camera.diry, camera.dirz};
    vector<float> up = {camera.upx, camera.upy, camera.upz};
    vector<float> right = CrossProduct(forward, up);
    right = normalizeVector(right);
    camera.upx = direction_speed * right[0] + camera.upx;
    camera.upy = direction_speed * right[1] + camera.upy;
    camera.upz = direction_speed * right[2] + camera.upz;
    vector<float> normalizedUp = {camera.upx, camera.upy, camera.upz};
    normalizedUp = normalizeVector(normalizedUp);
    camera.upx = normalizedUp[0];
    camera.upy = normalizedUp[1];
    camera.upz = normalizedUp[2];
}

void moveUpWardWithoutChangingReference(float direction_speed)
{
    vector<float> center = {camera.eyex + camera.dirx, camera.eyey + camera.diry, camera.eyez + camera.dirz};
    camera.eyex += camera.upx * direction_speed * 0.1;
    camera.eyey += camera.upy * direction_speed * 0.1;
    camera.eyez += camera.upz * direction_speed * 0.1;
    camera.dirx = center[0] - camera.eyex;
    camera.diry = center[1] - camera.eyey;
    camera.dirz = center[2] - camera.eyez;
    vector<float> dir = {camera.dirx, camera.diry, camera.dirz};
    vector<float> up = {camera.upx, camera.upy, camera.upz};
    vector<float> right = CrossProduct(dir, up);
    vector<float> newUp = CrossProduct(right, dir);
    newUp = normalizeVector(newUp);
    camera.upx = newUp[0];
    camera.upy = newUp[1];
    camera.upz = newUp[2];
}

void keyboardListener(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        rotateYaw(-CAMERA_ROTATE_SPEED);
        break;

    case '2':
        rotateYaw(CAMERA_ROTATE_SPEED);
        break;

    case '3':
        rotatePitch(CAMERA_ROTATE_SPEED);
        break;

    case '4':
        rotatePitch(-CAMERA_ROTATE_SPEED);
        break;

    case '6':
        rotateRoll(-CAMERA_ROTATE_SPEED);
        break;

    case '5':
        rotateRoll(CAMERA_ROTATE_SPEED);
        break;

    case 'w':
        fan_speed += 5;
        break;
    case 's':
        fan_speed -= 5;
        if(fan_speed < 0)
        {
            fan_speed = 0;
        }
        break;
    case 'a':
        body_angle += 10;
        break;
    case 'b':
        body_angle -= 10;
        break;

    case 32:
        isMoving = !isMoving;
        if (!isInitialized)
        {
            isInitialized = true;
        }
        break;

    case 'v':
        SHOW_VELOCITY_ARROW = !SHOW_VELOCITY_ARROW;
        break;

    case 'r':
        isMoving = false;
        isInitialized = false;
        ball.x = rand() % (int)(SIDE_LENGTH * 2) - SIDE_LENGTH + 1;
        ball.y = rand() % (int)(SIDE_LENGTH * 2) - SIDE_LENGTH + 1;
        ball.z = rand() % (int)(SIDE_LENGTH * 2) - SIDE_LENGTH + 1;
        ball.vx = (rand() % 100) / 100.0f;
        ball.vy = (rand() % 100) / 100.0f;
        ball.vz = (rand() % 100) / 100.0f;
        break;

    case '+':
        if (!isInitialized)
        {
            ball.vx += 0.1f;
            ball.vy += 0.1f;
            ball.vz += 0.1f;
            cout << "Velocity: " << ball.vx << " " << ball.vy << " " << ball.vz << endl;
        }
        break;

    case '-':
        if (!isInitialized)
        {
            ball.vx -= 0.1f;
            ball.vy -= 0.1f;
            ball.vz -= 0.1f;
            cout << "Velocity: " << ball.vx << " " << ball.vy << " " << ball.vz << endl;
        }
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

void specialKeyListener(int key, int x, int y)
{
    float forwardX = camera.dirx;
    float forwardY = camera.diry;
    float forwardZ = camera.dirz;
    float length = sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    forwardX /= length;
    forwardY /= length;
    forwardZ /= length;

    float rightX = camera.upy * forwardZ - camera.upz * forwardY;
    float rightY = camera.upz * forwardX - camera.upx * forwardZ;
    float rightZ = camera.upx * forwardY - camera.upy * forwardX;

    length = sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    rightX /= length;
    rightY /= length;
    rightZ /= length;

    switch (key)
    {
    case GLUT_KEY_UP:
        camera.eyex += forwardX * CAMERA_MOVE_SPEED;
        camera.eyey += forwardY * CAMERA_MOVE_SPEED;
        camera.eyez += forwardZ * CAMERA_MOVE_SPEED;
        break;

    case GLUT_KEY_DOWN:
        camera.eyex -= forwardX * CAMERA_MOVE_SPEED;
        camera.eyey -= forwardY * CAMERA_MOVE_SPEED;
        camera.eyez -= forwardZ * CAMERA_MOVE_SPEED;
        break;

    case GLUT_KEY_RIGHT:
        camera.eyex -= rightX * CAMERA_MOVE_SPEED;
        camera.eyey -= rightY * CAMERA_MOVE_SPEED;
        camera.eyez -= rightZ * CAMERA_MOVE_SPEED;
        break;

    case GLUT_KEY_LEFT:
        camera.eyex += rightX * CAMERA_MOVE_SPEED;
        camera.eyey += rightY * CAMERA_MOVE_SPEED;
        camera.eyez += rightZ * CAMERA_MOVE_SPEED;
        break;

    case GLUT_KEY_PAGE_UP:
        camera.eyex += camera.upx * CAMERA_MOVE_SPEED;
        camera.eyey += camera.upy * CAMERA_MOVE_SPEED;
        camera.eyez += camera.upz * CAMERA_MOVE_SPEED;
        break;

    case GLUT_KEY_PAGE_DOWN:
        camera.eyex -= camera.upx * CAMERA_MOVE_SPEED;
        camera.eyey -= camera.upy * CAMERA_MOVE_SPEED;
        camera.eyez -= camera.upz * CAMERA_MOVE_SPEED;
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

void calculateAngle()
{
    float speed = sqrt(ball.vx * ball.vx + ball.vy * ball.vy + ball.vz * ball.vz);
    float maxX = SIDE_LENGTH;
    float minX = -SIDE_LENGTH;
    float maxY = SIDE_LENGTH;
    float minY = -SIDE_LENGTH;
    float maxZ = SIDE_LENGTH;
    float minZ = -SIDE_LENGTH;
    bool collisionDetected = false;
    vector<float> normal({0, 0, 0});
    vector<float> velocity({ball.vx, ball.vy, ball.vz});

    if ((ball.x + ball.radius >= (maxX - 0.5f)))
    {
        normal = {1, 0, 0};
        collisionDetected = true;
    }

    if ((ball.x - ball.radius <= (minX + 0.5f)))
    {
        normal = {-1, 0, 0};
        collisionDetected = true;
    }

    if ((ball.y + ball.radius >= (maxY - 0.5f)))
    {
        normal = {0, 1, 0};
        collisionDetected = true;
    }

    if ((ball.y - ball.radius <= (minY + 0.5f)))
    {
        normal = {0, -1, 0};
        collisionDetected = true;
    }
    if ((ball.z + ball.radius >= (maxZ - 0.5f)))
    {
        normal = {0, 0, 1};
        collisionDetected = true;
    }
    if ((ball.z - ball.radius <= (minZ + 0.5f)))
    {
        normal = {0, 0, -1};
        collisionDetected = true;
    }
    if (collisionDetected)
    {
        vector<float> roatationAxis = CrossProduct(velocity, normal);
        roatationAxis = normalizeVector(roatationAxis);
        ball.rotationAxisX = roatationAxis[0];
        ball.rotationAxisY = roatationAxis[1];
        ball.rotationAxisZ = roatationAxis[2];
        if (speed > 0.01f)

            ball.angularVelocity = (speed / ball.radius) * 30.0f;
        else
            ball.angularVelocity = 0.0f;
    }
}

void checkCollisionWithCube()
{
    float maxX = SIDE_LENGTH;
    float minX = -SIDE_LENGTH;
    float maxY = SIDE_LENGTH;
    float minY = -SIDE_LENGTH;
    float maxZ = SIDE_LENGTH;
    float minZ = -SIDE_LENGTH;
    bool collisionDetected = false;

    if ((ball.x + ball.radius >= (maxX - 0.5f)) && (ball.vx > 0))
    {
        ball.vx = -ball.vx;
        ball.x = maxX - ball.radius;
        collisionDetected = true;
    }

    if ((ball.x - ball.radius <= (minX + 0.5f)) && (ball.vx < 0))
    {
        ball.vx = -ball.vx;
        ball.x = minX + ball.radius;
        collisionDetected = true;
    }

    if ((ball.y + ball.radius >= (maxY - 0.5f)) && (ball.vy > 0))
    {
        ball.vy = -ball.vy;
        ball.y = maxY - ball.radius;
        collisionDetected = true;
    }

    if ((ball.y - ball.radius <= (minY + 0.5f)) && (ball.vy <= 0))
    {
        ball.vy = -ball.vy;
        ball.y = minY + ball.radius;
        collisionDetected = true;
        if (ball.vy < 0.1f)
        {
            ball.vy = 0.0f;
        }
    }

    if ((ball.z + ball.radius >= (maxZ - 0.5f)) && (ball.vz > 0))
    {
        ball.vz = -ball.vz;
        ball.z = maxZ - ball.radius;
        collisionDetected = true;
    }

    if ((ball.z - ball.radius <= (minZ + 0.5f)) && (ball.vz < 0))
    {
        ball.vz = -ball.vz;
        ball.z = minZ + ball.radius;
        collisionDetected = true;
    }

    if (collisionDetected)
    {
        ball.vx *= 0.8f;
        ball.vy *= 0.75f;
        ball.vz *= 0.8f;
        cout << "Collision detected!" << endl;
        cout << "----------------------------------------------------------------------" << endl;
    }
    else if (ball.y != minY + ball.radius || ball.vy != 0.0f)
    {
        ball.vy -= GRAVITY;
    }

    if (abs(ball.vx) < VELOCITY_THRESHOLD)
    {
        ball.vx = 0.0f;
    }
    if (abs(ball.vy) < VELOCITY_THRESHOLD)
    {
        ball.vy = 0.0f;
    }
    if (abs(ball.vz) < VELOCITY_THRESHOLD)
    {
        ball.vz = 0.0f;
    }
}

void checkPhysics(int value)
{
    fan_angle += fan_speed;
    glutPostRedisplay();
    glutTimerFunc(50, checkPhysics, 0);
}

void drawRectangle(float width, float height)
{
    glBegin(GL_QUADS);
    glVertex3f(-width / 2, -height / 2, 0);
    glVertex3f(width / 2, -height / 2, 0);
    glVertex3f(width / 2, height / 2, 0);
    glVertex3f(-width / 2, height / 2, 0);
    glEnd();
}

void drawAxes()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    {
        glVertex3f(1000, 0, 0);
        glVertex3f(-1000, 0, 0);

        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);

        glVertex3f(0, 0, 1000);
        glVertex3f(0, 0, -1000);
    }
    glEnd();
}

void drawSide()
{
    glPushMatrix();
    {
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(18.1, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 15);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void drawStick()
{
    glPushMatrix();
    {
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(1,0,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
        glRotatef(45, 0, 0, 1);
        glPushMatrix();
        {
            glTranslatef(1.81, 0, 0);
            glRotatef(90, 0,1,0);
            glColor3f(0,1,0);
            drawRectangle(15, 1.5);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera.eyex, camera.eyey, camera.eyez,
              camera.eyex + camera.dirx,
              camera.eyey + camera.diry,
              camera.eyez + camera.dirz,
              camera.upx, camera.upy, camera.upz);

    drawAxes();
    glRotatef(90, 0, 0, 1);
    glRotatef(body_angle, 1, 0, 0);
    glTranslatef(0,0,7.5);
    drawSide();
    drawStick();
    glColor3f(0,1,1);
    glTranslatef(0, 0, 7.5);
    glRotatef(fan_angle, 0, 0, 1);
    drawRectangle(1, 30);
    glRotatef(120, 0, 0, 1);
    drawRectangle(1, 30);
    glRotatef(120, 0, 0, 1);
    drawRectangle(1, 30);
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    srand(time(0));
    ball.vx = (1.0f * (1 + rand() % 200)) / 75;
    ball.vz = (1.0f * (1 + rand() % 200)) / 75;
    ball.vy = abs(1.0f * (1 + rand() % 200)) / 75;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("OpenGL 3D Drawing");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeListener);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutTimerFunc(0, checkPhysics, 0);

    glutMainLoop();

    return 0;
}
