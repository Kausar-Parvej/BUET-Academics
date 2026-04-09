#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <ctime>
#include <cmath>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

#define PI 3.14159265358979323846


float camX = 0.0, camY = 0.0, camZ = 2.0;
float centerX = 0.0, centerY = 0.0, centerZ = 0.0;
float upX = 0.0, upY = 1.0, upZ = 0.0;

vector<int> occupied(9, 0);
int turn = 1;
vector<pair<float, float>> offset = {
    {-0.8, 0.8}, {0.0, 0.8}, {0.8, 0.8},
    {-0.8, 0.0}, {0.0, 0.0}, {0.8, 0.0},
    {-0.8, -0.8}, {0.0, -0.8}, {0.8, -0.8}
};

enum GameState {
    IN_PROGRESS = 0,
    PLAYER1_WIN = 1,
    PLAYER2_WIN = 2,
    DRAW = 3
};

GameState gameState = IN_PROGRESS;

void checkGameState() {
    for (int i = 0; i < 3; ++i) {
        if (occupied[i * 3] == occupied[i * 3 + 1] && occupied[i * 3] == occupied[i * 3 + 2]) {
            if (occupied[i * 3] != 0) {
                gameState = (GameState)occupied[i * 3];
                return;
            }
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (occupied[i] == occupied[i + 3] && occupied[i] == occupied[i + 6]) {
            if (occupied[i] != 0) {
                gameState = (GameState)occupied[i];
                return;
            }
        }
    }

    if ((occupied[0] == occupied[4] && occupied[0] == occupied[8]) || 
        (occupied[2] == occupied[4] && occupied[2] == occupied[6])) {
        if (occupied[4] != 0) {
            gameState = (GameState)occupied[4];
            return;
        }
    }

    bool draw = true;

    for (int i = 0; i < 9; ++i) {
        if (occupied[i] == 0) {
            draw = false;
            break;
        }
    }

    if (draw)
        gameState = DRAW;
}


void drawAxes() {
    glPushMatrix();

    glLineWidth(2.0);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES); {
        glVertex3f(0.4, 30.0, 0.0);
        glVertex3f(0.4, -30.0, 0.0);
    }glEnd();

    glBegin(GL_LINES); {
        glVertex3f(-0.4, 30.0, 0.0);
        glVertex3f(-0.4, -30.0, 0.0);
    }glEnd();

    glBegin(GL_LINES); {
        glVertex3f(30.0, 0.4, 0.0);
        glVertex3f(-30.0, 0.4, 0.0);
    }glEnd();

    glBegin(GL_LINES); {
        glVertex3f(30.0, -0.4, 0.0);
        glVertex3f(-30.0, -0.4, 0.0);
    }glEnd();

    glPopMatrix();
}


void drawCircle(float radius) {
    glColor3f(0, 1, 0);
    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        float theta = 2.0f * PI * i / 100;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}


void drawCross(float len) {
    glPushMatrix();

    glColor3f(1, 0, 0);
    glLineWidth(2.0);

    glRotatef(45, 0, 0, 1);
    glTranslatef(0, -len / 2, 0);

    glBegin(GL_LINES);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, len, 0.0);
    
    glEnd();

    glPopMatrix();

    glPushMatrix();

    glColor3f(1, 0, 0);
    glLineWidth(2.0);

    glRotatef(-45, 0, 0, 1);
    glTranslatef(0, -len / 2, 0);

    glBegin(GL_LINES);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, len, 0.0);
    
    glEnd();
    glPopMatrix();
}


void drawText(const string& text, float x, float y) { 
    glRasterPos2f(x,y); 
    for (char c: text) 
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, c);
} 


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, upX, upY, upZ);

    drawAxes();

    for(int i = 0; i < 9; ++i) {
        glPushMatrix();

        glTranslatef(offset[i].first, offset[i].second, 0);

        if(occupied[i] == 1)
            drawCross(0.4);
        else if(occupied[i] == 2)
            drawCircle(0.2);

        glPopMatrix();
    }

    switch(gameState) {
        case PLAYER1_WIN:
            glColor3f(1.0, 0.0, 0.0);
            drawText("Player X Wins!", -0.25, -1.1);
            break;
        case PLAYER2_WIN:
            glColor3f(0.0, 1.0, 0.0);
            drawText("Player O Wins!", -0.25, -1.1);
            break;
        case DRAW:
            glColor3f(1, 1, 1);
            drawText("Draw!", -0.1, -1.1);
            break;
    }

    glutSwapBuffers();
}


void keyboard(unsigned char key, int, int) {
    if(occupied[key - '1'] == 0 && gameState == IN_PROGRESS) {
        occupied[key - '1'] = turn;
        turn = (turn == 1) ? 2 : 1;
        checkGameState();
    }

    glutPostRedisplay();
}


void timer(int value) {
    glutPostRedisplay();            
    glutTimerFunc(16, timer, 0);  
}


void init() {
    glClearColor(0, 0, 0, 1);       
    glEnable(GL_DEPTH_TEST);        
}


void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, aspect, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tic Tac Toe");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
