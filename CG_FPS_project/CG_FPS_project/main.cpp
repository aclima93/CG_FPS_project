
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include "main.hpp"
#include "materiais.hpp"
#include "RgbImage.h"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Textures.hpp"

int minutes = 0;
int seconds = 0;
int miliseconds = 0;
const int msecCallback = 10;

float widthHUDBlock = 200;
float heightHUDBlock = 100;
float crosshairThickness = 1.0;

float wCenterScreen = wScreen/2;
float hCenterScreen = hScreen/2;

char timerInfoText[100];


void teclasNotAscii(int key, int x, int y){

    //using parameters just because
    if( x || y ){}

    switch(key){}

    updateVisao();

}

void mouseMotion(int x, int y){

    //if(DEBUG) std::cout << x << " - " << y << "\n";

    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

    int dx = x - wCenterScreen;
    int dy = -(y - hCenterScreen);

    if(dx) {
        g_camera.RotateYaw(g_rotation_speed*dx);
    }

    if(dy) {
        g_camera.RotatePitch(g_rotation_speed*dy);
    }

    glutWarpPointer(wCenterScreen, hCenterScreen);

    just_warped = true;

    updateVisao();

}

void mouseClicks(int button, int state, int x, int y) {

    if(button || state || x || y){}

    //if(DEBUG) std::cout << button << " " << state << " :::: " << x << " - " << y << "\n";

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        //TODO: calculate where x and y from screen are in world(?)

        shootGun(0, 0, 0);
    }

    updateVisao();

}

void keyboard(unsigned char key, int x, int y){

    if(key||x||y){}

    //if(DEBUG) std::cout << key << " :::: " << x << " - " << y << "\n";

    switch (key){

        //--------------------------- forward
        case 'W':
        case 'w':
            g_camera.Move(g_translation_speed);
            break;

        //--------------------------- back
        case 'S':
        case 's':
            g_camera.Move(-g_translation_speed);
            break;

        //--------------------------- left
        case 'A':
        case 'a':
            g_camera.Strafe(g_translation_speed);
            break;

        //--------------------------- left
        case 'D':
        case 'd':
            g_camera.Strafe(-g_translation_speed);
            break;

        //--------------------------- reload
        case 'R':
        case 'r':
            reloadWeapon();
            break;



        // ------------------------------ move vertically for DEBUG
        //--------------------------- up
        case 'U':
        case 'u':
            g_camera.Fly(g_translation_speed);
            break;
        //--------------------------- down
        case 'J':
        case 'j':
            g_camera.Fly(-g_translation_speed);
            break;



        //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }

    updateVisao();

}


void activateLight(void)
{
}

void activateAmbientIllumination(void)
{

    if (iluminacao)
    {
        /*Iluminacao local*/
        glLightfv(GL_LIGHT0, GL_POSITION, localPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, localCor);
        glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
        glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin);
        glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua);
    }
    else
    {
        /*Iluminacao global*/
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);/*Activar modelo ambiente global*/
    }
}

//……………………………………………………………………………………………………………………………………………………… Iluminacao
void initLights(void)
{
    //…………………………………………………………………………………………………………………………………………… Ambiente
    activateAmbientIllumination();

    activateLight();
}

void init(void)
{

    //……………………………………………………………………………………………………………………………Lighting set up
    initLights();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);                                //luz ambiente

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations



}


//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z){
    glRasterPos3f(x,y,z);
    while(*string)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void drawGrid()
{

    for(float i = -500; i <= 500; i += 5)
    {
        glBegin(GL_LINES);
            glColor3ub(150, 190, 150);
            glVertex3f(-500, 0, i);
            glVertex3f(500, 0, i);
            glVertex3f(i, 0,-500);
            glVertex3f(i, 0, 500);
        glEnd();
    }

    //============================================Eixos
    glColor4f(WHITE);
    glBegin(GL_LINES);
        glVertex3i(0,0,-xC);
        glVertex3i(0,0, xC);
    glEnd();
    glBegin(GL_LINES);
        glVertex3i(0,-xC,0);
        glVertex3i(0,xC,0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3i(-xC,0,0);
        glVertex3i( xC,0,0);
    glEnd();

}




void drawScene()
{

    //grelha no chão
    drawGrid();

    glDisable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec); - Nao considerar a componente especular

    map.drawMap();

    updateVisao();

}


GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    drawScene();
}


void drawOrientacao(){

    // quadrado na posição da cãmara

    /*
    float x, y, z;
    g_camera.GetPos(x, y, z);

    glPushMatrix();
        glColor4f(VERDE);
        glTranslatef( x-2, y-2, y-2);
        glutSolidCube(1);
    glPopMatrix();
    */



    //  Direccao do FOCO=lanterna
    //glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_direction);/*Definir direccao do foco*/

}

void drawCrosshair(){


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, wScreen, hScreen, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();        ----Not sure if I need this
    glLoadIdentity();
    glDisable(GL_CULL_FACE);

    glClear(GL_DEPTH_BUFFER_BIT);

    // top segment
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);

        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen - 30.0);
        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen - 10.0);
        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen - 10.0);
        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen - 30.0);

    glEnd();
    // bottom segment
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);

        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen + 30.0);
        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen + 10.0);
        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen + 10.0);
        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen + 30.0);

    glEnd();
    // right segment
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);

        glVertex2f(wCenterScreen - 30.0, hCenterScreen - crosshairThickness);
        glVertex2f(wCenterScreen - 30.0, hCenterScreen + crosshairThickness);
        glVertex2f(wCenterScreen - 10.0, hCenterScreen + crosshairThickness);
        glVertex2f(wCenterScreen - 10.0, hCenterScreen - crosshairThickness);

    glEnd();
    // left segment
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);

        glVertex2f(wCenterScreen + 30.0, hCenterScreen + crosshairThickness);
        glVertex2f(wCenterScreen + 30.0, hCenterScreen - crosshairThickness);
        glVertex2f(wCenterScreen + 10.0, hCenterScreen - crosshairThickness);
        glVertex2f(wCenterScreen + 10.0, hCenterScreen + crosshairThickness);

    glEnd();
    // center doghnut
    int segments = 100;
    float t;
    int r = 2;
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f(wCenterScreen, hCenterScreen);
        for( int n = 0; n <= segments; n++ ) {
            t = 2*M_PI*(float)n/(float)segments;
            glVertex2f(wCenterScreen + sin(t)*r, hCenterScreen + cos(t)*r);
        }
    glEnd();


    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();        ----and this?

}

void drawTargetsInfo(){


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, wScreen, hScreen, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();        ----Not sure if I need this
    glLoadIdentity();
    glDisable(GL_CULL_FACE);

    glClear(GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);

        glVertex2f(wScreen - widthHUDBlock, 0.0);
        glVertex2f(wScreen - widthHUDBlock, heightHUDBlock);
        glVertex2f(wScreen, heightHUDBlock);
        glVertex2f(wScreen, 0.0);

    glEnd();

    glColor3f(0,0,0);
    sprintf(texto,"%d:%d:%d", minutes, seconds, miliseconds);
    desenhaTexto(texto,wScreen - widthHUDBlock/2, heightHUDBlock/2, 0);

    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();        ----and this?

}

void drawGunInfo(){

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, wScreen, hScreen, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();        ----Not sure if I need this
    glLoadIdentity();
    glDisable(GL_CULL_FACE);

    glClear(GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);

        glVertex2f(0.0, 0.0);
        glVertex2f(widthHUDBlock, 0.0);
        glVertex2f(widthHUDBlock, heightHUDBlock);
        glVertex2f(0.0, heightHUDBlock);

    glEnd();

    glColor3f(0,0,0);
    sprintf(texto,"%d loaded - %d left", bulletsInGun, bulletsLeft);
    desenhaTexto(texto,0,0,0);

    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();        ----and this?
}

void drawMiniMap(){

    glClearColor(BLACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (0, 0, wScreen/8, hScreen/8);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);

}

void drawTimeInfo(){

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, wScreen, hScreen, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();        ----Not sure if I need this
    glLoadIdentity();
    glDisable(GL_CULL_FACE);

    glClear(GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);

        glVertex2f(wCenterScreen - widthHUDBlock, 0.0);
        glVertex2f(wCenterScreen - widthHUDBlock, heightHUDBlock/2);
        glVertex2f(wCenterScreen + widthHUDBlock, heightHUDBlock/2);
        glVertex2f(wCenterScreen + widthHUDBlock, 0.0);


    glEnd();

    glColor3f(0,0,0);
    sprintf(texto,"%d:%d:%d", minutes, seconds, miliseconds);
    desenhaTexto(texto, wCenterScreen, heightHUDBlock/4 ,0);

    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();        ----and this?


}

void drawHUD(){

    drawGunInfo();
    drawTimeInfo();
    drawTargetsInfo();
    drawCrosshair();


}

void display(void){


    //================================================================= Viewport1 (minimap)
    drawMiniMap();

    drawScene(); //--------------------- desenha objectos no viewport1
    drawOrientacao();


    //================================================================= Viewport2 (game)
    glEnable(GL_LIGHTING);
    glViewport (0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, wScreen/hScreen, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(wCenterScreen, hCenterScreen);

    drawScene();//--------------------- desenha objectos no viewport2
    drawOrientacao();


    //================================================================= Viewport3 (info box)


    drawHUD();


    //don't delete this!
    glutSwapBuffers();

}


void drawBullets(){

    for(int i=0; i<NUMBULLETS; i++){

        // until it reaches it's target
        if( bullets[i].isActive ){

            bullets[i].draw();
            if( bullets[i].deleteBullet() ){
                bullets[i].isActive = !bullets[i].isActive ;
            }
        }
    }
}

void reloadWeapon(){

    if(bulletsLeft){

        int loadingReq = CLIPSIZE - bulletsInGun;

        if(bulletsLeft >= loadingReq){
            bulletsInGun += loadingReq;
            bulletsLeft -= loadingReq;
        }
        else{
            bulletsInGun += bulletsLeft;
            bulletsLeft = 0;
        }
    }
}

void shootGun(int x, int y, int z){

    if(bulletsInGun){

        bulletsInGun--;

        bullets[bulletIndex].targetX = x;
        bullets[bulletIndex].targetY = y;
        bullets[bulletIndex].targetZ = z-200;

        bullets[bulletIndex].angle = 0; //TODO: calculate(?)

        bullets[bulletIndex].x = x;
        bullets[bulletIndex].y = y;
        bullets[bulletIndex].z = z;

        bulletIndex++;

    }
}

//======================================================= EVENTOS


void updateVisao(){

    //loop for things that need to be draw continuously
    g_camera.Refresh();
    drawBullets();

    glutPostRedisplay();
}

void Timer(int value){

    if(value){}

    miliseconds += msecCallback;

    if(miliseconds == 1000){
        miliseconds = 0;
        seconds++;
    }
    if(seconds == 60){
        seconds = 0;
        minutes++;
    }

    glutPostRedisplay();
}

//======================================================= MAIN
int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("CG_FPS_PROJECT : (A, W, S, D) - (R, Left Mouse)");

    init();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutTimerFunc(msecCallback, Timer, 0);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    glutMouseFunc(mouseClicks);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);


    glutMainLoop();

    return 0;
}
