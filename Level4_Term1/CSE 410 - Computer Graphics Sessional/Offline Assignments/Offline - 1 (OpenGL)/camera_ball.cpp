
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

// Camera
float camX = 8, camY = 19, camZ = 8;
float lookX = 0, lookY = 7, lookZ = 0;
float upX = 0, upY = 1, upZ = 0;

// Camera Movement step
const float moveSpeed = 0.1f;
const float rotSpeed = 0.03f;



// Cube and Ball Settings
const float cubeSize = 12.0f;
const float half = cubeSize / 2.0f;
const float gravity = -9.8f;
const float dt = 0.016f; // 60 FPS
const float restitution = 0.75f;
const float radius = 0.4f;

// Ball state
float ballX = 0, ballY = 2, ballZ = 0;
float velX = 2, velY = 0, velZ = 1;

bool showVelocity = false;
float speedMultiplier = 1.0f;
float ballAngle = 0.0f;


bool simulationOn = false;



void crossProduct(float ax, float ay, float az,float bx, float by, float bz,float* outX, float* outY, float* outZ) {
    *outX = ay * bz - az * by;
    *outY = az * bx - ax * bz;
    *outZ = ax * by - ay * bx;
}

void normalize(float* x, float* y, float* z) {
    float length = sqrtf((*x)*(*x) + (*y)*(*y) + (*z)*(*z));
    if(length > 0) {
        *x /= length;
        *y /= length;
        *z /= length;
    }
}


void moveCamera(float dx, float dy, float dz) {
    //forward vector
    float forwardX = lookX - camX;
    float forwardY = lookY - camY;
    float forwardZ = lookZ - camZ;
    normalize(&forwardX, &forwardY, &forwardZ);
    
    //right vector (using world up (0,1,0))
    float rightX, rightY, rightZ;
    crossProduct(forwardX, forwardY, forwardZ, 0, 1, 0, &rightX, &rightY, &rightZ);
    normalize(&rightX, &rightY, &rightZ);
    
    //real up vector
    float upX, upY, upZ;
    crossProduct(rightX, rightY, rightZ,forwardX, forwardY, forwardZ,&upX, &upY, &upZ);

    // Apply movement
    camX += rightX * dx + upX * dy + forwardX * dz;
    camY += rightY * dx + upY * dy + forwardY * dz;
    camZ += rightZ * dx + upZ * dy + forwardZ * dz;

    // Move look-at point to maintain view direction
    lookX += rightX * dx + upX * dy + forwardX * dz;
    lookY += rightY * dx + upY * dy + forwardY * dz;
    lookZ += rightZ * dx + upZ * dy + forwardZ * dz;
}


void rotateCamera(float yaw, float pitch, float roll) {
    float dirX = lookX - camX;
    float dirY = lookY - camY;
    float dirZ = lookZ - camZ;

    // Yaw (around Y axis)
    if (yaw != 0) {
        float cosA = cos(yaw);
        float sinA = sin(yaw);
        float nx = dirX * cosA - dirZ * sinA;
        float nz = dirX * sinA + dirZ * cosA;
        lookX = camX + nx;
        lookZ = camZ + nz;
    }

    // Pitch (around X axis)
    if (pitch != 0) {
        float cosA = cos(pitch);
        float sinA = sin(pitch);
        float ny = dirY * cosA - dirZ * sinA;
        float nz = dirY * sinA + dirZ * cosA;
        lookY = camY + ny;
        lookZ = camZ + nz;
    }

    // Roll (around Z axis)
    if (roll != 0) {
        float cosA = cos(roll);
        float sinA = sin(roll);
        float nx = dirX * cosA - dirY * sinA;
        float ny = dirX * sinA + dirY * cosA;
        lookX = camX + nx;
        lookY = camY + ny;
    }

    // Normalize the look vector
    float length = sqrt((lookX - camX) * (lookX - camX) + (lookY - camY) * (lookY - camY) + (lookZ - camZ) * (lookZ - camZ));
    if (length > 0) {
        lookX = camX + (lookX - camX) / length;
        lookY = camY + (lookY - camY) / length;
        lookZ = camZ + (lookZ - camZ) / length;
    }
}






void drawCheckeredFloor(int count = 10) {
    float step = cubeSize / count;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if ((i + j) % 2 == 0) glColor3f(1, 1, 1);
            else glColor3f(0, 0, 0);
            float x = -half + i * step;
            float z = -half + j * step;
            glBegin(GL_QUADS);
            glVertex3f(x, 0, z);
            glVertex3f(x + step, 0, z);
            glVertex3f(x + step, 0, z + step);
            glVertex3f(x, 0, z + step);
            glEnd();
        }
    }
}

void drawCubeWalls() {
    // Front
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex3f(-half, 0, half); glVertex3f(half, 0, half);
    glVertex3f(half, cubeSize, half); glVertex3f(-half, cubeSize, half);
    glEnd();

    // Back
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(half, 0, -half); glVertex3f(-half, 0, -half);
    glVertex3f(-half, cubeSize, -half); glVertex3f(half, cubeSize, -half);
    glEnd();

    // Left
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3f(-half, 0, -half); glVertex3f(-half, 0, half);
    glVertex3f(-half, cubeSize, half); glVertex3f(-half, cubeSize, -half);
    glEnd();

    // Right
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(half, 0, half); glVertex3f(half, 0, -half);
    glVertex3f(half, cubeSize, -half); glVertex3f(half, cubeSize, half);
    glEnd();

    // Ceiling
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex3f(-half, cubeSize, half); glVertex3f(half, cubeSize, half);
    glVertex3f(half, cubeSize, -half); glVertex3f(-half, cubeSize, -half);
    glEnd();
}

void drawBall() {
    glPushMatrix();

    glTranslatef(ballX, ballY, ballZ);


    // Axis of rotation = perpendicular to velocity in XZ plane
    float axisX = -velZ;
    float axisZ = velX;
    float axisLen = sqrt(axisX * axisX + axisZ * axisZ);
    if (axisLen > 0.001f) {
        axisX /= axisLen;
        axisZ /= axisLen;
        glRotatef(ballAngle, axisX, 0.0f, axisZ);
    }


    const int slices = 20;
    const int stacks = 10;
    for (int i = 0; i < stacks; ++i) {
        float lat0 = M_PI * (-0.5 + (float)i / stacks);
        float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        glColor3f(i % 2 == 0 ? 1.0f : 1.0f, i % 2 == 0 ? 0.5f : 1.0f, 0.0f); // Orange/White

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * M_PI * (float)j / slices;
            float x = cos(lng);
            float y = sin(lng);
            glVertex3f(x * zr0, z0, y * zr0);
            glVertex3f(x * zr1, z1, y * zr1);
        }
        glEnd();
    }

    if (showVelocity) {
        float val = sqrt(velX * velX + velY * velY + velZ * velZ);
        float dir_x = (velX / val)*1.5f;
        float dir_y = (velY / val)*1.5f;
        float dir_z = (velZ / val)*1.5f;

        glColor3f(1, 0, 0);
        glLineWidth(3.5f);
        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(dir_x, dir_y, dir_z);
        glEnd();

        glColor3f(0.6f, 0.2f, 0.8f);
        glBegin(GL_TRIANGLES);
        glVertex3f(dir_x * 1.12f, dir_y * 1.12f, dir_z * 1.12f);
        glVertex3f(dir_x + 0.1f, dir_y - 0.1f, dir_z);
        glVertex3f(dir_x - 0.1f, dir_y + 0.1f, dir_z);
        glEnd();
    }

    glPopMatrix();
}

void updateBall() {
    if (!simulationOn) return;

    velY += gravity * dt;
    ballX += velX * dt;
    ballY += velY * dt;
    ballZ += velZ * dt;


    float dx = velX * dt;
    float dz = velZ * dt;
    float moveDist = sqrt(dx * dx + dz * dz);
    ballAngle += (moveDist / radius) * 180 / M_PI;


    // Collisions with cube boundaries
    if (ballY - radius <= 0 && velY < 0) {
        ballY = radius;
        velY *= -restitution;
    } else if (ballY + radius >= cubeSize && velY > 0) {
        ballY = cubeSize - radius;
        velY *= -restitution;
    }

    if ((ballX - radius <= -half && velX < 0) || (ballX + radius >= half && velX > 0)) {
        ballX = (ballX < 0) ? -half + radius : half - radius;
        velX *= -restitution;
    }

    if ((ballZ - radius <= -half && velZ < 0) || (ballZ + radius >= half && velZ > 0)) {
        ballZ = (ballZ < 0) ? -half + radius : half - radius;
        velZ *= -restitution;
    }

    // Stop bouncing if it's almost still
    if (fabs(velY) < 0.01 && ballY - radius <= 0.01) {
        velY = 0;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, upX, upY, upZ);

    drawCheckeredFloor();
    drawCubeWalls();
    drawBall();

    glutSwapBuffers();
}

void timer(int value) {
    updateBall();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, aspect, 0.1, 110.0);
    glMatrixMode(GL_MODELVIEW);
}




void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': camY += moveSpeed; break; // upward without changing reference point
        case 's': camY -= moveSpeed; break; // downward without changing reference point
        case '1': rotateCamera(-rotSpeed, 0, 0); break; // Look left
        case '2': rotateCamera(rotSpeed, 0, 0); break;  // Look right
        case '3': rotateCamera(0, rotSpeed, 0); break;  // Look up
        case '4': rotateCamera(0, -rotSpeed, 0); break; // Look down
        case '5': rotateCamera(0, 0, rotSpeed); break;  // Roll right
        case '6': rotateCamera(0, 0, -rotSpeed); break; // Roll left
        
        case ' ': simulationOn = !simulationOn; break; // Toggle
        case 'r': // Reset
            ballX = rand() % (int)half;
            ballY = radius + 0.1f;
            ballZ = rand() % (int)half;

            velX = speedMultiplier * (rand() % 5); // Random speed in X direction
            velY = speedMultiplier * (rand() % 10); // Random speed in Y direction
            velZ = speedMultiplier * (rand() % 5); // Random speed in Z direction
            velZ = speedMultiplier;
            ballAngle = 0.0f;
            printf("Ball reset with speedMultiplier: %.2f\n", speedMultiplier);
            break;

        case '+': speedMultiplier += 0.1f; printf("Speed multiplier: %.2f\n", speedMultiplier); break;
        case '-': speedMultiplier = std::max(0.1f, speedMultiplier-0.1f); printf("Speed multiplier: %.2f\n", speedMultiplier); break;
        case 'v': showVelocity = !showVelocity; break; 


        case 27: exit(0); break; // ESC to quit

        default: printf("Key %c pressed(no function)\n", key); break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y){
    switch (key){
        case GLUT_KEY_UP: moveCamera(0, 0, moveSpeed); break;
        case GLUT_KEY_DOWN: moveCamera(0, 0, -moveSpeed); break;
        case GLUT_KEY_LEFT: moveCamera(-moveSpeed, 0, 0); break;
        case GLUT_KEY_RIGHT: moveCamera(moveSpeed, 0, 0); break;
        case GLUT_KEY_PAGE_UP: moveCamera(0, moveSpeed, 0); break;
        case GLUT_KEY_PAGE_DOWN: moveCamera(0, -moveSpeed, 0); break;
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Task 1 + 3: Bouncing Ball in 3D Cube");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(16, timer, 0);

    
    printf("Arrow Keys: Move camera\n");
    printf("1-4: Look left/right/up/down\n");
    printf("5/6: Tilt camera roll\n");
    printf("w/s: Float camera up/down\n");
    printf("Space: Start/stop simulation\n");
    printf("r: Reset ball with current speed\n");
    printf("+/-: Adjust speed before reset\n");
    printf("v: Toggle velocity arrow\n");
    printf("ESC: Exit\n");
    printf("===============================\n");

    glutMainLoop();

    return 0;
}
