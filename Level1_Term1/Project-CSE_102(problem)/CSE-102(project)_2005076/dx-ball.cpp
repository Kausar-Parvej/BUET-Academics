#include <math.h>
#include <stdlib.h>
# include "iGraphics.h"
# include "gl.h"
//#include "dxHeader.h"

#define screenwidth 1500
#define screenheight 900
#define pi 3.14

float dx, dy;
int angle, v=11, v2=11;
int boardwidth=150, board_x=screenwidth/2-boardwidth/2, board_dx, board_y=141, boardhieght=12;
int baseline_y=140;
int ballr=9,ball_x, ball_y;
int block_x=140, block_y=(3*screenheight)/4, blockwidth=60, blockheight=15;
int r, g, b;
//int r=192, g=192, b=192;
int start=0,level=1;
int scores=0, lives=7;
char score[5];
char live[2];
int blocknum=240;
int call_bullet=0;
int callbullet=0;
int bullet_press=0;
bool on=true;
int level_check=1;

struct blocks
{
    int x;
    int y;
    int r;
    int g;
    int b;
    int seeblock;
    int width;
    int height;
};
blocks block[240];
blocks block2[140];

struct powers
{
    int x=screenwidth/2;
    int y=screenheight;
    int on;
    int seeimage;
};
powers power[2];        //power[0]=through ball; power[1]=shooting paddle;


/*struct bullets
{
    int x;
    int y;
    int height;
    int seebullet;
};
bullets bullet[30];

void set_bullet()
{
    for(int i=0; i<30; i+=2)
    {
        bullet[i].x=board_x+4;
        bullet[i].y=board_y+boardhieght+18;
        bullet[i].height=20;
        bullet[i].seebullet=1;

    }
    for(int i=1; i<30; i+=2)
    {
        bullet[i].x=board_x+boardwidth-5+4;
        bullet[i].y=board_y+boardhieght+18;
        bullet[i].height=20;
        bullet[i].seebullet=1;

    }
}*/



void blockproper()
{

    int ix=140;
    int iy=((3*screenheight)/4)-50;

    for(int i=0; i<blocknum; i++)
    {
        block[i].width=60;
        block[i].height=15;
        block[i].seeblock=1;

        block[i].x=ix;
        block[i].y=iy;

        block[i].r=255;
        block[i].g=0;
        block[i].b=0;

        if(ix==140 || ix==140+63*19 || iy==((3*screenheight)/4)-50+17*5)
        {
            block[i].r=0;
            block[i].g=100;
            block[i].b=0;
        }

        ix=ix+63;
        if(ix>=(screenwidth-block_x))
        {
            ix=140;
            iy=iy+17;
        }


        /*if(ix<=(screenwidth-block_x))
        {
            ix+=64;
        }

        if(iy<=(screenheight-50))
        {
            iy+=18;
        }*/

        /*if(ix==block_x || ix>=screenwidth-1.5*block_x || iy<block_y+2*18 || iy>screenheight-50-2*18)
        {
            block[i].r=0;
            block[i].g=100;
            block[i].b=0;
        }*/

    }
}
void blockproper2()
{

    for(int i=0; i<140; i++)
    {
        block2[i].width=58;
        block2[i].height=14;
        block2[i].seeblock=1;

        block2[i].r=rand()%255;
        block2[i].g=rand()%255;
        block2[i].b=rand()%255;

    }

    int ix=200;
    int iy=600;
    for(int i=0; i<35; i++)
    {

        block2[i].x=ix;
        block2[i].y=iy;

        ix=ix+60;
        if(ix>=200+5*60)
        {
            ix=200;
            iy=iy+15;
        }

    }
    ix=600;
    iy=750;
    for(int i=35; i<70; i++)
    {

        block2[i].x=ix;
        block2[i].y=iy;

        ix=ix+60;
        if(ix>=600+5*60)
        {
            ix=600;
            iy=iy+15;
        }

    }
    ix=600;
    iy=450;
    for(int i=70; i<105; i++)
    {

        block2[i].x=ix;
        block2[i].y=iy;

        ix=ix+60;
        if(ix>=600+5*60)
        {
            ix=600;
            iy=iy+15;
        }

    }
    ix=1000;
    iy=600;
    for(int i=105; i<140; i++)
    {

        block2[i].x=ix;
        block2[i].y=iy;

        ix=ix+60;
        if(ix>=1000+5*60)
        {
            ix=1000;
            iy=iy+15;
        }

    }
}


/*
	function iDraw() is called again and again by the system.
*/


void iDraw()
{
    //place your drawing codes here

    iClear();

    if(level==1)
    {
        iSetColor(255, 255, 255);
        iFilledRectangle(0, 0, screenwidth, screenheight);

        for(int i=0; i<blocknum; i++)
        {
            if(block[i].seeblock==1)
            {
                iSetColor(block[i].r,block[i].g,block[i].b);
                iFilledRectangle(block[i].x, block[i].y, block[i].width, block[i].height);
            }

        }
    }

    if(level==2)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 0, screenwidth, screenheight);

        for(int i=0; i<140; i++)
        {
            if(block2[i].seeblock==1)
            {
                iSetColor(block2[i].r,block2[i].g,block2[i].b);
                iFilledRectangle(block2[i].x, block2[i].y, block2[i].width, block2[i].height);
            }

        }
    }


    iSetColor(0, 0, 0);
    if(level==2)
    {
        iSetColor(255, 255, 255);
    }
    if(power[0].on==1)
    {
        iSetColor(0, 0, 255);
    }
    iFilledCircle(ball_x, ball_y, ballr);
    iSetColor(0, 0, 0);
    if(level==2)
    {
        iSetColor(255, 0, 0);
    }
    iFilledRectangle(board_x, board_y, boardwidth, boardhieght);
    iFilledCircle(board_x, board_y+boardhieght/2, boardhieght/2);
    iFilledCircle(board_x+boardwidth, board_y+boardhieght/2, boardhieght/2);

    //background


    /*if(power[1].on==1)
    {
        iSetColor(255, 223, 0);
        iFilledRectangle(board_x, board_y+boardhieght, 8, 18 );
        iFilledRectangle(board_x+boardwidth-5, board_y+boardhieght, 8, 18);
        iFilledRectangle(board_x-4, board_y+boardhieght+12,16,4);
        iFilledRectangle(board_x+boardwidth-9, board_y+boardhieght+12, 16, 4);


        iSetColor(255, 0, 0);
        for(int i =0; i<callbullet; i++)
        {
            if(bullet[i].seebullet==1)
            {
                iFilledRectangle(bullet[i].x, bullet[i].y, 2, bullet[i].height );
            }

        }
    }*/

    iSetColor(0, 0, 0);
    if(level==2)
    {
        iSetColor(0, 0, 255);
    }
    iText(50, 105, "press 'z' to catch the ball !",GLUT_BITMAP_HELVETICA_18);
    iText(50, 80, "press 'end' for exit and '1' or '2' to jump to the according level !",GLUT_BITMAP_HELVETICA_18);

    if(level==1)
    {
        iSetColor(0, 0, 255);
        iText(270, 863, "LEVEL:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1100, 876, "SCORES:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1100, 848, "LIVES:",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255, 0, 0);
        iText(270+84, 863, "01",GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(scores, score,10);
        itoa(lives, live,10);
        iText(1100+101, 876, score,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1100+78, 848, live,GLUT_BITMAP_TIMES_ROMAN_24);
    }

    if(level==2)
    {
        iSetColor(255, 0, 0);
        iText(270, 860, "LEVEL:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1100, 870, "SCORES: ",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1100, 840, "LIVES: ",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0, 0, 255);
        iText(270+84, 860, "02",GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(scores, score,10);
        itoa(lives, live,10);
        iText(1100+101, 870, score,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1100+78, 840, live,GLUT_BITMAP_TIMES_ROMAN_24);
    }

    iSetColor(0, 0, 0);
    if(level==2)
    {
        iSetColor(255, 0, 0);
    }
    iLine(0, baseline_y, screenwidth, baseline_y);



    if(power[0].seeimage==1)
    {
        iShowBMP(power[0].x, power[0].y, "Ball_Through_Brick.bmp");
    }
    /*if(power[1].seeimage==1)
    {
        iShowBMP(power[1].x, power[2].y, "Gun_Icon.bmp");
    }*/

    if(lives==0)
    {
        iSetColor(0, 0, 0);
        iFilledRectangle(30, 30, screenwidth-60, screenheight-60);
        iSetColor(255, 0, 0);
        iFilledRectangle(0, 0, screenwidth, 30);
        iFilledRectangle(0, 0, 30, screenheight);
        iFilledRectangle(0, screenheight-30, screenwidth, 30);
        iFilledRectangle(screenwidth-30, 0, 30,  screenheight);

        iSetColor(0, 0,255);
        iText(650, 470, "GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(630, 435, "YOUR SCORE:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(630+160, 435, score,GLUT_BITMAP_TIMES_ROMAN_24);

        iText(580, 410, "<<------------------>>",GLUT_BITMAP_TIMES_ROMAN_24);


    }


}

/*void iPassiveMouseMove(int mx, int my)
{
    /*if(mx>= boardwidth && mx<=screenwidth-boardwidth)
        board_x = mx;
    else if(mx<=boardwidth)
        board_x = boardwidth;
    else if(mx>=screenwidth-boardwidth)
        board_x =screenwidth-boardwidth;* /

         if(mx>=0 + boardwidth && mx<=screenwidth-boardwidth)
                board_x = mx;
            else if(mx<=0+boardwidth)
                board_x = 0 + boardwidth;
            else if(mx>=screenwidth-boardwidth)
                board_x =screenwidth-boardwidth;
}*/

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
    /*if(my<=(baseline_y+boardhieght));
    {
        board_x=mx-boardwidth/2;
    }*/

    //board_x=mx-boardwidth/2;
    if(mx>= boardwidth/2 && mx<=screenwidth-boardwidth)
        board_x = mx-boardwidth/2;
    else if(mx<=boardwidth/2)
        board_x = 0;
    else if(mx>=screenwidth-boardwidth)
        board_x =screenwidth-boardwidth;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        if(start==0)
        {
            start=1;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'p')
    {
        //do something with 'q'
        iPauseTimer(0);
    }
    if(key == 'r')
    {
        iResumeTimer(0);
    }
    /*if(key == ' ')
    {
        //start=1;
        if(power[1].on==1)
        {
            callbullet+=2;

            if(callbullet>=28)
            {
                set_bullet();
                callbullet=2;
            }
        }
    }*/
    if(key == '2')
    {
        level=2;
    }
    if(key == '1')
    {
        level=1;
    }
    if(key == 'z')
    {
        start=(start==0)?1:0;
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here

    if(key == GLUT_KEY_RIGHT)
    {
        board_x+=20;
    }
    if(key == GLUT_KEY_LEFT)
    {
        board_x-=20;
    }
}

void ballChange()
{
    if(ball_y<=baseline_y-100)
    {
        start=0;
        lives-=1;

        for(int i=0; i<2; i++)
        {
            if(power[i].on=1)
            {
                power[i].on=0;
            }
        }
    }

    if(start==1)
    {
        ball_x += dx;
        ball_y += dy;

        //if(((ball_x > board_x) && (ball_x < board_x+boardwidth)) && (ball_y == (board_y+boardhieght+ballr)))
        if(ball_x>=board_x-ballr && ball_x<=board_x+boardwidth+ballr)
            if(ball_y<=board_y+boardhieght+ballr && ball_y>=board_y-ballr)
            {
                angle=(board_x-ball_x+boardwidth)+15;
                dx=v*cos(pi*angle/180);
                dy=abs(v*sin(pi*angle/180));
            }


        /*if(ball_x>= block_x && ball_x<=block_x+636)
        {
            if(ball_y>= block_y && ball_y<=block_x+213)
            {
                dx=-dx;
                dy=-dy;
            }
        }*/



        if(ball_x > screenwidth || ball_x < 0)dx = -dx;
        //if(ball_y > screenheight || ball_y < baseline_y)dy = -dy;
        if(ball_y > screenheight)dy = -dy;
    }
    if(start==0)
    {
        ball_x=board_x+boardwidth/2;
        ball_y=board_y+boardhieght+ballr;
    }

    //collision
    if(level==1)
    {
        for(int i=0; i<blocknum; i++)
        {
            if(block[i].seeblock==1)
            {
                if(ball_x>=block[i].x && ball_x<=block[i].x+block[i].width+3)
                {
                    if(ball_y>=block[i].y && ball_y<=block[i].y+block[i].height+2)
                    {
                        if(power[0].on!=1)
                        {
                            dx=-dx;
                        }
                        block[i].seeblock=0;
                    }
                }
                if(ball_y>=block[i].y && ball_y<=block[i].y+block[i].height+2)
                {
                    if(ball_x>=block[i].x && ball_x<=block[i].x+block[i].width+3)
                    {

                        if(power[0].on!=1)
                        {
                            v2=-v2;
                            angle=(block[i].x-ball_x+block[i].width)+60;
                            dy=v2*sin(pi*angle/180);
                        }
                        block[i].seeblock=0;
                        scores+=5;
                    }
                }
                /*if(power[1].on==1)
                {
                    for(int j=0; i<callbullet; i++)
                    {
                        if(bullet[j].seebullet==1)
                        {
                            if(bullet[j].x>=block[i].x && bullet[j].x<=block[i].x+block[i].width)
                            {
                                if(bullet[j].y>=block[i].y-bullet[j].height)
                                {
                                    block[i].seeblock=0;
                                    bullet[j].seebullet=0;
                                    scores+=5;
                                }
                            }
                        }
                    }
                }*/

            }
        }

    }

    if(level==2)
    {
        for(int i=0; i<140; i++)
        {
            if(block2[i].seeblock==1)
            {
                if(ball_x>=block2[i].x && ball_x<=block2[i].x+block2[i].width+2)
                {
                    if(ball_y>=block2[i].y && ball_y<=block2[i].y+block2[i].height+1)
                    {
                        if(power[0].on!=1)
                        {
                            dx=-dx;
                        }
                        block2[i].seeblock=0;
                    }
                }
                if(ball_y>=block2[i].y && ball_y<=(block2[i].y+block2[i].height+1))
                {
                    if(ball_x>=block2[i].x && ball_x<=block2[i].x+block2[i].width+2)
                    {
                        if(power[0].on!=1)
                        {
                            v2=-v2;
                            angle=(block2[i].x-ball_x+block2[i].width)+60;
                            dy=v2*sin(pi*angle/180);
                        }
                        block2[i].seeblock=0;
                        scores+=5;
                    }
                    /*if(power[1].on==1)
                    {
                        for(int j=0; i<callbullet; i++)
                        {
                            if(bullet[j].seebullet==1)
                            {
                                if(bullet[j].x>=block2[i].x && bullet[j].x<=block2[i].x+block2[i].width)
                                {
                                    if(bullet[j].y>=block2[i].y-bullet[j].height)
                                    {
                                        block2[i].seeblock=0;
                                        bullet[j].seebullet=0;
                                        scores+=5;
                                    }
                                }
                            }
                        }
                    }*/
                    /*if(ball_y<=block2[i].y+block2[i].height+1)
                    {
                        if(ball_x>=block2[i].x && ball_x<=block2[i].x+block2[i].width+2)
                        {
                            angle=(block2[i].x-ball_x+block2[i].width)+60;
                            dy=-v*sin(pi*angle/180);
                            block2[i].seeblock=0;
                        }
                    }*/

                }
            }
        }
    }
    if(power[0].seeimage==1 || power[1].seeimage==1)
    {
        power[0].y-=4;
        power[1].y-=4;

        if(power[0].y<=baseline_y-10)
        {
            power[0].seeimage=0;
            power[0].y=screenheight;
        }
        if(power[1].y<=baseline_y-10)
        {
            power[1].seeimage=0;
            power[1].y=screenheight;
        }
        if(power[0].seeimage==1)
        {
            if(power[0].x>=board_x && power[0].x<=board_x+boardwidth)
            {
                if(power[0].y<=board_y+boardhieght)
                {
                    power[0].on=1;
                }
            }

        }
        if(power[1].seeimage==1)
        {
            if(power[1].x>=board_x && power[1].x<=board_x+boardwidth)
            {
                if(power[0].y<=board_y+boardhieght)
                {
                    power[1].on=1;
                }
            }

        }
    }
    for(int i=0;i<blocknum;i++)
    {
        if(block[i].seeblock==1)
        {
           level_check=0;
        }
    }
    if(level_check==1)
    {
        level=2;
    }



}
void get_power()
{
    //int i=rand()%2;
    power[0].seeimage=1;
}

int main()
{
  // PlaySound((LPCSTR) "C:\\KAUSAR\\CSE\\Project-CSE_102(problem)\\CSE-102(project)\\bgmusic.wav", NULL, SND_FILENAME | SND_ASYNC);
//    DWORD dwError = GetLastError();

    //place your own initialization codes here.

    //set_bullet();
    blockproper();
    blockproper2();

    dx = 10;
    dy = 8;

    iSetTimer(5, ballChange);
    iSetTimer(20000, get_power);

    //Playsound ("bgmusic.wav", NULL, SND_LOOP | SND_ASYNC);
    //PlaySound("bgmusic.wav", NULL, SND_LOOP | SND_ASYNC);


    iInitialize(screenwidth, screenheight, "DX-BALL(2022)");

    return 0;
}



