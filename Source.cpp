/*********
   CTIS164 - Template Source Program
----------
STUDENT : Cavit Mert Ergül
SECTION : 2.section
HOMEWORK: CTIS-164-222-Homework-1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES: 1-) Sun can be contolled by using "w, a, s, d"
                     2-) speed of rocket can be adjusted by using '+' and '-'
                     3-) when the speed of rocket increases, the flame expands
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define PI 3.1415

#define TIMER_PERIOD  50 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false, activeTimer = true;
int  winWidth, winHeight; // current Window width and height
int y = -120; //initial position of rocket
int sunx = -90, suny = -90; //initial position of sun 
int speed = 2; //start speed
int flame = 0;

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void window()
{
    glColor3f(1, 1, 1);
    circle(0, 0, 222);
    glColor3f(0.22, 0.69, 0.87);
    circle(0, 0, 220);
    glColor3f(1, 1, 1);
    circle_wire(0, 0, 200);
    glColor3f(25 / 255.0, 0, 51 / 255.0);
    circle(0, 0, 200);
}
void air()
{
    glColor3f(12 / 255.0, 2 / 255.0, 154 / 255.0);
    glRectf(-390, -285, -380, -210);
    glRectf(-370, -285, -360, -210);
    glRectf(-350, -285, -340, -210);
    glRectf(-330, -285, -320, -210);

    glRectf(390, -285, 380, -210);
    glRectf(370, -285, 360, -210);
    glRectf(350, -285, 340, -210);
    glRectf(330, -285, 320, -210);
}

void straightlines()
{
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    // line 1
    glVertex2f(-400, -200);
    glVertex2f(-300, -200);
    // line 2
    glVertex2f(-300, -200);
    glVertex2f(-260, -270);
    // line 3
    glVertex2f(-260, -270);
    glVertex2f(-260, -300);
    // line 1
    glVertex2f(400, -200);
    glVertex2f(300, -200);
    // line 2
    glVertex2f(300, -200);
    glVertex2f(260, -270);
    // line 3
    glVertex2f(260, -270);
    glVertex2f(260, -300);

    glEnd();
    glLineWidth(2.0f);
}

void rectangles()
{
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    // line 1
    glVertex2f(-370, 100);
    glVertex2f(-370, -100);
    // line 2
    glVertex2f(-370, 100);
    glVertex2f(-270, 100);
    // line 3
    glVertex2f(-270, 100);
    glVertex2f(-270, -100);
    // line 4
    glVertex2f(-270, -100);
    glVertex2f(-370, -100);


    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    // line 1
    glVertex2f(370, 100);
    glVertex2f(370, -100);
    // line 2
    glVertex2f(370, 100);
    glVertex2f(270, 100);
    // line 3
    glVertex2f(270, 100);
    glVertex2f(270, -100);
    // line 4
    glVertex2f(270, -100);
    glVertex2f(370, -100);




    glEnd();

    glLineWidth(2.0f);

    glColor3f(153 / 255.0, 1, 204 / 255.0);
    glRectf(-370, -100, -270, 100);
    glRectf(370, -100, 270, 100);


}

void space()
{
    glColor3f(102 / 255.0, 0, 0);
    circle(60, 150, 30);

    glColor3f(160 / 255.0, 160 / 255.0, 160 / 255.0);
    circle(-10, 170, 15);

}
void sun() {

    glColor3f(1, 128 / 255., 0);
    circle(sunx, suny, 65);

    glColor3f(1, 188 / 255., 0);
    circle(sunx, suny, 60);

    glColor3f(1, 231 / 255., 0);
    circle(sunx, suny, 45);


}
void human()
{
    glColor3f(1, 1, 1);
    circle(320, 50, 18);

    glRectf(285, 30, 355, -10);

}
void star()
{
    glColor3f(1, 1, 1);
    circle(0, 0, 3);
    glBegin(GL_LINES);
    glVertex2f(0, 5);
    glVertex2f(0, -5);
    glVertex2f(5, 0);
    glVertex2f(-5, 0);
    glEnd();

    glColor3f(1, 1, 1);

    circle(70, 70, 3);
    glBegin(GL_LINES);
    glVertex2f(70, 65);
    glVertex2f(70, 75);
    glVertex2f(75, 70);
    glVertex2f(65, 70);
    glEnd();



    circle(70, -150, 3);
    glBegin(GL_LINES);
    glVertex2f(70, -145);
    glVertex2f(70, -155);
    glVertex2f(75, -150);
    glVertex2f(65, -150);
    glEnd();

    circle(-50, 100, 3);
    glBegin(GL_LINES);
    glVertex2f(-50, 95);
    glVertex2f(-50, 105);
    glVertex2f(-55, 100);
    glVertex2f(-45, 100);
    glEnd();

    circle(100, -50, 3);
    glBegin(GL_LINES);
    glVertex2f(100, -55);
    glVertex2f(100, -45);
    glVertex2f(95, -50);
    glVertex2f(105, -50);

    glEnd();
}

void rocket()
{
    glColor3f(1, 128 / 255., 0);
    circle(9, y - 56, 6 + flame);
    glColor3f(1, 102 / 255., 102 / 255.);
    circle(9, y - 56, 2 + flame);

    glColor3f(198 / 255.0, 35 / 255.0, 35 / 255.0);
    circle(9, y, 9);
    glColor3f(235 / 255.0, 235 / 255.0, 235 / 255.0);
    glRectf(0, y, 12, y - 50);
    glColor3f(1, 1, 1);
    glRectf(12, y, 18, y - 50);

    glColor3f(198 / 255.0, 35 / 255.0, 35 / 255.0);
    glBegin(GL_QUADS);
    glVertex2f(0, y - 35);
    glVertex2f(-15, y - 45);
    glVertex2f(-15, y - 55);
    glVertex2f(0, y - 50);
    glVertex2f(18, y - 35);
    glVertex2f(33, y - 45);
    glVertex2f(33, y - 55);
    glVertex2f(18, y - 50);
    glEnd();

    glColor3f(0, 51 / 255.0, 52 / 255.0);
    circle(9, y - 20, 6);
    glColor3f(0, 128 / 255.0, 1);
    circle(9, y - 20, 4);

    glColor3f(0, 51 / 255., 102 / 255.);
    glBegin(GL_QUADS);
    glVertex2f(5, y - 50);
    glVertex2f(13, y - 50);
    glVertex2f(15, y - 55);
    glVertex2f(3, y - 55);
    glEnd();




    glColor3f(0, 51 / 255., 102 / 255.);
    glBegin(GL_QUADS);
    glVertex2f(5, y - 50);
    glVertex2f(13, y - 50);
    glVertex2f(15, y - 55);
    glVertex2f(3, y - 55);
    glEnd();



}
void display()
{


    glClearColor(0, 122 / 255.0, 204 / 255.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);






    window();
    air();
    straightlines();
    rectangles();
    space();
    sun();
    human();
    star();
    rocket();

    glColor3f(0, 0, 0);
    vprint(-345, 60, GLUT_BITMAP_TIMES_ROMAN_24, "UFO");
    vprint(-335, 30, GLUT_BITMAP_TIMES_ROMAN_24, "IN");
    vprint(-345, 0, GLUT_BITMAP_TIMES_ROMAN_24, "THE");
    vprint(-355, -30, GLUT_BITMAP_TIMES_ROMAN_24, "SPACE");

    vprint(290, -40, GLUT_BITMAP_TIMES_ROMAN_10, "DESIGNED BY ");
    vprint(275, -60, GLUT_BITMAP_9_BY_15, "CAVIT MERT");
    vprint(300, -80, GLUT_BITMAP_9_BY_15, "ERGUL");

    if (y > 270)  // to be able to loop the coordinate of the rocket
        y = -270;





    // to fix the rocket going outside the window
    glColor3f(0, 122 / 255.0, 204 / 255.0);
    glRectf(200, 222, -200, 300);
    glRectf(200, -222, -200, -300);


    glColor3f(1, 1, 1);
    circle_wire(0, 0, 222);
    circle_wire(0, 0, 221);

    glColor3f(0.22, 0.69, 0.87);
    for (int a = 0; a < 19; a++)
        circle_wire(0, 0, 220 - a);

    glColor3f(0, 122 / 255.0, 204 / 255.0);
    for (int a = 0; a < 3; a++)
        circle_wire(0, 0, 224 + a);





    glutSwapBuffers();
}


//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    if (key == 'w')
        suny += 5;
    if (key == 's')
        suny -= 5;
    if (key == 'a')
        sunx -= 5;
    if (key == 'd')
        sunx += 5;




    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    if (key == ' ')
        activeTimer = !activeTimer;
    if (key == '-')
    {
        if (speed > 1)
        {
            speed -= 1;
            flame -= 1;
        }
    }
    if (key == '+')
    {
        if (speed < 10)
        {
            speed += 1;
            flame += 1;
        }
    }



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = true;
        break;
    case GLUT_KEY_DOWN:
        down = true;
        break;
    case GLUT_KEY_LEFT:
        left = true;
        break;
    case GLUT_KEY_RIGHT:
        right = true;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = false;
        break;
    case GLUT_KEY_DOWN:
        down = false;
        break;
    case GLUT_KEY_LEFT:
        left = false;
        break;
    case GLUT_KEY_RIGHT:
        right = false;
        break;

    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (activeTimer)
        y += speed;


    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("SKY ROCKET");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

#endif

    Init();

    glutMainLoop();
}