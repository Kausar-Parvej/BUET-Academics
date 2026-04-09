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

struct Point2D {
    float x, y;
};

vector<int> occupied(9, 0);   // 0: empty, 1: player1, 2: player2

int turn = 1;
float sign_radius = 0.15;

float offset_val = 0.70;

vector<Point2D> offset = {
    {-offset_val, offset_val}, {0.0, offset_val}, {offset_val, offset_val},
    {-offset_val, 0.0}, {0.0, 0.0}, {offset_val, 0.0},
    {-offset_val, -offset_val}, {0.0, -offset_val}, {offset_val, -offset_val}
};



int game_state = 0;   // 0: in progress, 1: player1 win, 2: player2 win, 3: draw

void drawText(const string& text, float x, float y) { 
    glRasterPos2f(x,y); 
    for (char c: text) 
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, c); 
}


void checkGameState() {
    for(int i=0; i<9; i+=3){ // check rows
        if (occupied[i] == 0) continue;
        if(occupied[i] == occupied[i+1]  && occupied[i] == occupied[i+2]) game_state = occupied[i];
    }
    for(int i=0; i<3; i++){ // check columns
        if (occupied[i] == 0) continue;
        if(occupied[i] == occupied[i+3] && occupied[i] == occupied[i+6]) game_state = occupied[i];
    }
    if(occupied[4] != 0){ // check diagonals
        if(occupied[0] == occupied[4] && occupied[0] == occupied[8]) game_state = occupied[0];
        else if(occupied[2] == occupied[4] && occupied[2] == occupied[6]) game_state = occupied[2];
    }
        

    bool draw = true;
    for(int i=0; i<9; i++){
        if(occupied[i] == 0){ draw = false; break;}
    }

    if(draw && game_state == 0){
        game_state = 3;
        glColor3f(1, 0, 0);
        drawText("Draw!", -0.15, -1.07);
    }

    if(game_state == 0){
        if(turn == 1){
            glColor3f(1.0, 0.0, 0.0);
            drawText("Player X's Turn", -0.25, 1.05);
        }
        else{
            glColor3f(0.0, 1.0, 0.0);
            drawText("Player O's Turn", -0.25, 1.05);
        }
    }
    else if(game_state == 1){
        glColor3f(1.0, 0.0, 0.0);
        drawText("Player X Wins!", -0.25, -1.07);
    }
    else if(game_state == 2){
        glColor3f(0.0, 1.0, 0.0);
        drawText("Player O Wins!", -0.25, -1.07);
    }
    
}

void drawLine(Point2D p1, Point2D p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void drawRectangle(Point2D p1, Point2D p2) {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p1.x, p2.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p2.x, p1.y);
    glEnd();
}

void drawAxes(){
    glColor3f(1.0, 0.0, 0.0);
    drawLine({-0.95, 0}, {0.95, 0}); // X-axis

    glColor3f(0.0, 1.0, 0.0);
    drawLine({0, -0.95}, {0, 0.95}); // Y-axis
}


void drawGridLine() {
    glColor3f(0.5, 0.5, 0.5);
    drawLine({(offset[0].x+offset[1].x)/2, 1.0}, {(offset[0].x+offset[1].x)/2, -1.0});
    drawLine({(offset[1].x+offset[2].x)/2, 1.0}, {(offset[1].x+offset[2].x)/2, -1.0});
    drawLine({-1.0, (offset[0].y+offset[3].y)/2}, {1.0, (offset[0].y+offset[3].y)/2});
    drawLine({-1.0, (offset[3].y+offset[6].y)/2}, {1.0, (offset[3].y+offset[6].y)/2}); 
}


void drawCircle(float radius, Point2D centre) {
    glLineWidth(2.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * PI * i / 100;
        float x = radius * cos(angle) + centre.x;
        float y = radius * sin(angle) + centre.y;
        glVertex2f(x, y);
    }
    glEnd();
   
}


void drawCross(float half_len, Point2D centre) {
    glLineWidth(2.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(centre.x - half_len, centre.y - half_len);
    glVertex2f(centre.x + half_len, centre.y + half_len);

    glVertex2f(centre.x - half_len, centre.y + half_len);
    glVertex2f(centre.x + half_len, centre.y - half_len);
    glEnd();
    
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, upX, upY, upZ);

    //drawAxes();
    drawRectangle({-1.0, -1.0}, {1.0, 1.0});
    drawGridLine();

    for(int i=0; i<9; i++){
        if(occupied[i] == 1) drawCross(sign_radius, offset[i]);
        else if(occupied[i] == 2) drawCircle(sign_radius, offset[i]);
    }

    checkGameState();




    glFlush();
    glutSwapBuffers();
}


void keyboard(unsigned char key, int, int) {        //joss!
    int index = key - '1';
    if(index < 0 || index > 8){    // Invalid key
        printf("invalid Key\n");
        glColor3f(1, 1, 0);
        drawText("Invalid Key", -0.25, -1.07);
        return;
    }

    if(occupied[index] == 0 && game_state == 0) {
        occupied[index] = turn;
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
