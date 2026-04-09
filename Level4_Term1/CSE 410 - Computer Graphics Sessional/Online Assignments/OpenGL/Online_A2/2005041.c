#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif /* !M_PI */

#define USING_NAMESPACE_IMK_LOG
#define USING_NAMESPACE_IMK_ASSERT

#include "log/IMK_assert.h"
#include "log/IMK_log.h"

#include "render_util/render_util.h"

enum {BLANK = 0, X = 1, O = 2};

typedef struct {
  u64 elapsed;
  s32 grid[3][3];
  u8 o_turn;
  u8 over;
  s32 won;
} SceneData;

static void Update(SceneData *data, u64 elapsed_time) {
  u64 delta_time = elapsed_time - data->elapsed;
  data->elapsed = elapsed_time;

  (void)delta_time;
}


static void drawText(const char * text, float x, float y)
{
  char const *c;
  glRasterPos2f(x,y);
  for (c = text; *c != '\0'; c++) {
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, *c);
  }
}

static void DrawGrid(void) {
  glBegin(GL_LINES);
  glVertex2d(200, 0);
  glVertex2d(200, 600);
  glVertex2d(400, 0);
  glVertex2d(400, 600);
  glVertex2d(0, 200);
  glVertex2d(600, 200);
  glVertex2d(0, 400);
  glVertex2d(600, 400);
  glEnd();
}


void DrawO(s32 i, s32 j) {
  f64 x = j * 200 + 100;
  f64 y = i * 200 + 100;
  DrawCircle(x, y, 80, 20);
}

void DrawX(s32 i, s32 j) {
  enum {OFFSET = 50};
  f64 x = j * 200 + 100;
  f64 y = i * 200 + 100;
  glBegin(GL_LINES);
  glVertex2d(x + OFFSET, y + OFFSET);
  glVertex2d(x - OFFSET, y - OFFSET);
  glVertex2d(x + OFFSET, y - OFFSET);
  glVertex2d(x - OFFSET, y + OFFSET);
  glEnd();
}

static void DisplayFunc(void) {
  SceneData *data = glutGetWindowData();
  u32 i = 0, j;
  u32 width = (u32)glutGet(GLUT_WINDOW_WIDTH);
  u32 height = (u32)glutGet(GLUT_WINDOW_HEIGHT);
  (void)width, (void)height;

  Update(data, (u64)glutGet(GLUT_ELAPSED_TIME));

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  DrawGrid();
  
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if(data->grid[i][j] == X) {
        DrawX(i, j);
      } else if (data->grid[i][j] == O) {
        DrawO(i, j);
      }
    }
  }

  if (data->o_turn) {
    drawText("Player O's turn", 250, 50);
  } else {

    drawText("Player X's turn", 250, 50);
  }

  if (data->won == O) {
    drawText("Player O won", 250, 500);
  } else {
    drawText("Player X won", 250, 500);
  }
  
  glutSwapBuffers();
}

static void KeyboardFunc(unsigned char key, int x, int y) {
  u8 i, j;
  enum { ESC = 27 };
  SceneData *data = glutGetWindowData();
  (void)x, (void)y;


  if (data->over) {
    return;
  }

  switch (key) {
    case ESC: {
      Log(LOG_INFO, "ESCAPE pressed");
      glutLeaveMainLoop();
      break;
    }
    case '1': {
      if (data->o_turn) {
        data->grid[0][0] = O;
      } else {
        data->grid[0][0] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
    }
    case '2': {
      if (data->o_turn) {
        data->grid[0][1] = O;
      } else {
        data->grid[0][1] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
    }
    case '3': {
      if (data->o_turn) {
        data->grid[0][2] = O;
      } else {
        data->grid[0][2] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
    }
    case '4': {
      if (data->o_turn) {
        data->grid[1][0] = O;
      } else {
        data->grid[1][0] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
    }
    case '5': {
      if (data->o_turn) {
        data->grid[1][1] = O;
      } else {
        data->grid[1][1] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
    }
    case '6': {
      if (data->o_turn) {
        data->grid[1][2] = O;
      } else {
        data->grid[1][2] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
      break;
    }
    case '7': {
      if (data->o_turn) {
        data->grid[2][0] = O;
      } else {
        data->grid[2][0] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
      break;
    }
    case '8': {
      if (data->o_turn) {
        data->grid[2][1] = O;
      } else {
        data->grid[2][1] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
      break;
    }
    case '9': {
      if (data->o_turn) {
        data->grid[2][2] = O;
      } else {
        data->grid[2  ][2] = X;
      }
      data->o_turn = 1 - data->o_turn;
      break;
    }
  }

  if (data->grid[0][0] != BLANK && data->grid[0][0] == data->grid[0][1] && data->grid[0][1] == data->grid[0][2]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }

  if (data->grid[1][0] != BLANK && data->grid[1][0] == data->grid[1][1] && data->grid[1][1] == data->grid[1][2]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }

  if (data->grid[2][0] != BLANK && data->grid[2][0] == data->grid[2][1] && data->grid[2][1] == data->grid[2][2]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }

  if (data->grid[0][0] != BLANK && data->grid[0][0] == data->grid[1][0] && data->grid[1][0] == data->grid[2][0]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }

  if (data->grid[0][1] != BLANK && data->grid[0][1] == data->grid[1][1] && data->grid[1][1] == data->grid[2][1]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }

  if (data->grid[0][2] != BLANK && data->grid[0][2] == data->grid[1][2] && data->grid[1][2] == data->grid[2][2]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }

  if (data->grid[0][0] != BLANK && data->grid[0][0] == data->grid[1][1] && data->grid[1][1] == data->grid[2][2]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }

  if (data->grid[2][0] != BLANK && data->grid[2][0] == data->grid[1][1] && data->grid[1][1] == data->grid[0][2]) {
    if (data->o_turn) {
      Log(LOG_INFO, "Player X won");
      data->won = X;

        drawText("Player X won", 250, 500);

    } else {
      data->won = O;
      Log(LOG_INFO, "Player O won");
      drawText("Player o won", 250, 500);
    }
    data->over = 1;
    glutPostRedisplay();
    return;
  }
  

  if (data->o_turn) {
    Log(LOG_INFO, "Player O's turn");
  } else {
    Log(LOG_INFO, "Player X's turn");
  }
}

static void TimerFunc(int value) {
  (void)value;
  glutPostRedisplay();
  glutTimerFunc(16, TimerFunc, 0);
}

static void Initialize(void) {
  SceneData *data = glutGetWindowData();
  (void)data;

  Log(LOG_INFO, "Player X's turn");
}

static void ReshapeFunc(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  glOrtho(0, w, h, 0, -1, 1);
}

int main(int argc, char **argv) {
  SceneData data = {0};
  int window;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(0, 0);
  glEnable(GL_DEPTH_TEST);

  ASSERT_MSG((window = glutCreateWindow("Clock")) > 0,
             "Failed to create window");
  Log(LOG_INFO, "Successfully created window");

  glutSetWindowData(&data);
  Initialize();

  glutDisplayFunc(DisplayFunc);
  glutKeyboardFunc(KeyboardFunc);
  glutReshapeFunc(ReshapeFunc);
  glutTimerFunc(16, TimerFunc, 0);

  Log(LOG_INFO, "Starting main loop");
  glutMainLoop();

  Log(LOG_INFO, "Cleaning up and quitting");
  glutDestroyWindow(window);

  return 0;
}
