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

#include "materiais.hpp"
#include "RgbImage.h"
#include "Camera.hpp"
#include "Bullet.hpp"

#include "main.hpp"

#define DEBUG 1

//==================================================================== Definir cores

#define VIDRO    0.0, 0.0, 0.5, 0.1
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define VERDE    0.0, 1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY1    0.2, 0.2, 0.2, 1.0
#define GRAY2    0.9, 0.9, 0.9, 1.0


//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat  xC=16.0, zC=15.0;
GLint    wScreen=1350, hScreen=800;
char     texto[100];


//------------------------------------------------------------ Global (ambiente)
GLfloat luzGlobalCor[4]={1.0,1.0,1.0,1.0};
bool iluminacao;

/*Definir posicao iluminacao local*/
GLfloat localCor[4] ={0.1, 0.1, 0.1, 1.0};
GLfloat localPos[4]={0.7, 1.0, 0.5, 1.0};

/*Atenuacoes iluminacao local*/
GLfloat localAttCon = 1.0;
GLfloat localAttLin = 0.05;
GLfloat localAttQua = 0.0;


//------------------------------------------------------------ Observador
GLfloat  PI = 3.14159;
//GLfloat  rVisao=3.0, aVisao=0.5*PI, incVisao=0.1;
//GLfloat  obsPini[] ={1, 0.25, 0.5*xC};
//GLfloat  obsPfin[] ={obsPini[0]-rVisao*cos(aVisao), obsPini[1], obsPini[2]-rVisao*sin(aVisao)};

// ------------------------- camera
const float g_translation_speed = 0.05;
const float g_rotation_speed = PI/180* 0.2;
Camera g_camera;

// ------------------------- map sizes
GLfloat field_width = 5; // 50
GLfloat field_height = 10; // 1000
GLfloat wall_height = 1; // 25

// -------------------------- gun specs
#define CLIPSIZE 5
#define NUMBULLETS 15
#define NUMCLIPS 2
int bulletsInGun = CLIPSIZE;
int bulletsLeft = CLIPSIZE * NUMCLIPS;
int bulletIndex = 0;
Bullet bullets[NUMBULLETS];


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
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
    //"ich bin ein rübe"

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

GLuint groundTexture(){

    RgbImage  imag;
    GLuint    texture[1];

    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    imag.LoadBmpFile("textures/ground_tex.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
        imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData()
    );

    return texture[0];
}


void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3,
                     GLfloat x4, GLfloat y4, GLfloat z4,
                     GLfloat n1, GLfloat n2, GLfloat n3,
                     GLfloat r, GLfloat g, GLfloat b, GLfloat a,
                     GLuint texture
                     ){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPushMatrix();
        glColor4f(r, g, b, a);
        glBegin(GL_QUADS);

            glNormal3d(n1, n2, n3);

            glTexCoord2f(0.0f,0.0f); glVertex3f(x1, y1, z1); // top left
            glTexCoord2f(0.0f,100.0f); glVertex3f(x2, y2, z2); // bottom left
            glTexCoord2f(100.0f,100.0f); glVertex3f(x4, y4, z4); // bottom right
            glTexCoord2f(0.0f,100.0f); glVertex3f(x3, y3, z3); // top right

        glEnd();
    glPopMatrix();
}

void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3,
                     GLfloat x4, GLfloat y4, GLfloat z4,
                     GLfloat n1, GLfloat n2, GLfloat n3,
                     GLfloat r, GLfloat g, GLfloat b, GLfloat a
                     ){
    glPushMatrix();
        glColor4f(r, g, b, a);
        glBegin(GL_QUADS);

            glNormal3d(n1, n2, n3);

            glVertex3f(x1, y1, z1); // top left
            glVertex3f(x2, y2, z2); // bottom left
            glVertex3f(x4, y4, z4); // bottom right
            glVertex3f(x3, y3, z3); // top right

        glEnd();
    glPopMatrix();
}

void drawWalls(){

    GLint numWalls = 11;
    GLfloat walls [11][19] = {

        //paredes verticais
        {
            //parede esquerda1
            -field_width/2, wall_height, 0,                         // A
            -field_width/2, wall_height, -field_height*(0.4f),      // B
            -field_width/2, 0, 0,                                   // C
            -field_width/2, 0, -field_height*(0.4f),                // D
             1, 0, 0,                                               // normal
             WHITE                                                  // r g b a
        },
        {
            //vidro esquerda1
            -field_width/2, wall_height, -field_height*(0.40f),      // A
            -field_width/2, wall_height, -field_height*(0.45f),      // B
            -field_width/2, 0, -field_height*(0.40f),                // C
            -field_width/2, 0, -field_height*(0.45f),                // D
             1, 0, 0,                                                // normal
             VIDRO                                                    // r g b a
        },
        {
            //parede esquerda2
            -field_width/2, wall_height, -field_height*(0.45f),      // A
            -field_width/2, wall_height, -field_height*(0.55f),      // B
            -field_width/2, 0, -field_height*(0.45f),                // C
            -field_width/2, 0, -field_height*(0.55f),                // D
             1, 0, 0,                                                // normal
             WHITE                                                    // r g b a
        },
        {
            //vidro esquerda2
            -field_width/2, wall_height, -field_height*(0.55f),      // A
            -field_width/2, wall_height, -field_height*(0.60f),      // B
            -field_width/2, 0, -field_height*(0.55f),                // C
            -field_width/2, 0, -field_height*(0.60f),                // D
             1, 0, 0,                                                // normal
             VIDRO                                                    // r g b a
        },
        {
            //parede esquerda3
            -field_width/2, wall_height, -field_height*(0.60f),      // top left
            -field_width/2, wall_height, -field_height,              // top right
            -field_width/2, 0, -field_height*(0.60f),                // bottom left
            -field_width/2, 0, -field_height,                        // bottom right
             1, 0, 0,                                                // normal
             WHITE                                                // r g b a
        },
        {
            //parede esquerda4
            -field_width*(0.75f), wall_height, -field_height*(0.45f),      // A
            -field_width*(0.75f), wall_height, -field_height*(0.55f),      // B
            -field_width*(0.75f), 0, -field_height*(0.45f),                // C
            -field_width*(0.75f), 0, -field_height*(0.55f),                // D
             1, 0, 0,                                                      // normal
             WHITE                                                         // r g b a
        },
        {
            //parede esquerda5
            -field_width, wall_height, -field_height*(0.40f),      // A
            -field_width, wall_height, -field_height*(0.60f),      // B
            -field_width, 0, -field_height*(0.40f),                // C
            -field_width, 0, -field_height*(0.60f),                // D
             1, 0, 0,                                              // normal
             WHITE                                              // r g b a
        },

        //paredes horizontais
        {
            //parede esquerda6
            -field_width, wall_height, -field_height*(0.40f),      // A
            -field_width/2, wall_height, -field_height*(0.40f),    // B
            -field_width, 0, -field_height*(0.40f),                // C
            -field_width/2, 0, -field_height*(0.40f),              // D
             1, 0, 0,                                              // normal
             WHITE                                                  // r g b a
        },
        {
            //parede esquerda7
            -field_width*(0.75f), wall_height, -field_height*(0.45f),        // A
            -field_width/2, wall_height, -field_height*(0.45f),              // B
            -field_width*(0.75f), 0, -field_height*(0.45f),                  // C
            -field_width/2, 0, -field_height*(0.45f),                        // D
             1, 0, 0,                                                        // normal
             WHITE                                                         // r g b a
        },
        {
            //parede esquerda8
            -field_width*(0.75f), wall_height, -field_height*(0.55f),        // A
            -field_width/2, wall_height, -field_height*(0.55f),              // B
            -field_width*(0.75f), 0, -field_height*(0.55f),                  // C
            -field_width/2, 0, -field_height*(0.55f),                        // D
             1, 0, 0,                                                        // normal
             WHITE                                                         // r g b a
        },
        {
            //parede esquerda9
            -field_width, wall_height, -field_height*(0.60f),      // A
            -field_width/2, wall_height, -field_height*(0.60f),    // B
            -field_width, 0, -field_height*(0.60f),                // C
            -field_width/2, 0, -field_height*(0.60f),              // D
             1, 0, 0,                                              // normal
             WHITE                                                  // r g b a
        }



    };

    //draw left side and right side by symmetry
    for(int i=0; i<numWalls; i++){
            desenhaQuadrado(
                walls[i][0], walls[i][1], walls[i][2],
                walls[i][3], walls[i][4], walls[i][5],
                walls[i][6], walls[i][7], walls[i][8],
                walls[i][9], walls[i][10], walls[i][11],
                walls[i][12], walls[i][13], walls[i][14],
                walls[i][15], walls[i][16], walls[i][17], walls[i][18]
            );
            desenhaQuadrado(
                - walls[i][0], walls[i][1], walls[i][2],
                - walls[i][3], walls[i][4], walls[i][5],
                - walls[i][6], walls[i][7], walls[i][8],
                - walls[i][9], walls[i][10], walls[i][11],
                walls[i][12], walls[i][13], walls[i][14],
                walls[i][15], walls[i][16], walls[i][17], walls[i][18]
            );

    }


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

    //chão
    desenhaQuadrado(
        -field_width/2, 0, -field_height,   // A
         field_width/2, 0, -field_height,   // B
        -field_width/2, 0, 0,               // C
         field_width/2, 0, 0,               // D
         1, 0, 0,                           // normal
         WHITE,                          // r g b a
         groundTexture()                    // texture
    );

    drawWalls();

    updateVisao();
}


GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    //glViewport( 0, 0, wScreen,hScreen );
    drawScene();
}


void drawOrientacao()
{
}

void display(void)
{


    //================================================================= Viewport1
    glClearColor(BLACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (0, hScreen/4, wScreen/4, hScreen/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);


    //--------------------- desenha objectos no viewport1
    drawScene();
    drawOrientacao();

    //================================================================= Viewport2
    glEnable(GL_LIGHTING);
    glViewport (wScreen/4, hScreen/4, 0.75*wScreen, 0.75*hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, wScreen/hScreen, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(wScreen/2, hScreen/2);
    gluPerspective (60, (GLfloat)wScreen / (GLfloat)hScreen, 0.1 , 100.0); //set the perspective (angle of sight, width, height, ,depth)

    glLoadIdentity();

    ShowCursor(FALSE);		// Do NOT Show Mouse Pointer

    //gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);

    //--------------------- desenha objectos no viewport2
    drawScene();
    drawOrientacao();

    glutSwapBuffers();
    glutPostRedisplay();
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
        bullets[bulletIndex].targetZ = z;

        bullets[bulletIndex].angle = 0; //TODO: calculate(?)

        bullets[bulletIndex].x = x;
        bullets[bulletIndex].y = y;
        bullets[bulletIndex].z = z-200;

        bulletIndex++;

    }
}

void mouseMotion(int x, int y){

    if(DEBUG) std::cout << x << " - " << y << "\n";

    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

    int dx = x - wScreen/2;
    int dy = -(y - hScreen/2);

    if(dx) {
        g_camera.RotateYaw(g_rotation_speed*dx);
    }

    if(dy) {
        g_camera.RotatePitch(g_rotation_speed*dy);
    }

    glutWarpPointer(wScreen/2, hScreen/2);

    just_warped = true;

    updateVisao();


}

void mouseClicks(int button, int state, int x, int y) {

    if(DEBUG) std::cout << button << " " << state << " :::: " << x << " - " << y << "\n";

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        //TODO: calculate where x and y from screen are in world(?)

        shootGun(0, 0, -200);
    }

    updateVisao();

}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{

    if(DEBUG) std::cout << key << " :::: " << x << " - " << y << "\n";

    switch (key){

        //--------------------------- forward
        case 'W':
        case 'w':
            g_camera.Move(g_translation_speed);
            /*
            obsPini[0]=obsPini[0]+incVisao*cos(aVisao);
            obsPini[2]=obsPini[2]-incVisao*sin(aVisao);
            */
            break;

        //--------------------------- back
        case 'S':
        case 's':
            g_camera.Move(-g_translation_speed);
            /*
            obsPini[0]=obsPini[0]-incVisao*cos(aVisao);
            obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
            */
            break;

        //--------------------------- left
        case 'A':
        case 'a':
            g_camera.Strafe(g_translation_speed);
            /*
            aVisao = (aVisao + 0.1);
            */
            break;

        //--------------------------- left
        case 'D':
        case 'd':
            g_camera.Strafe(g_translation_speed);
            /*
            aVisao = (aVisao - 0.1);
            */
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
            //obsPini[1]++;
            break;
        //--------------------------- down
        case 'J':
        case 'j':
            g_camera.Fly(-g_translation_speed);
            //obsPini[1]--;
            break;


        //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }

    updateVisao();
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

void updateVisao(){

    g_camera.Refresh();

    drawBullets();

    glutPostRedisplay();
}

void teclasNotAscii(int key, int x, int y)
{

    //using parameters just because
    if( !x && !y ){
    }

    switch(key){
    }

}

void Timer(int value){

    if(value){}

    glutPostRedisplay();
}

//======================================================= MAIN
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("CG_FPS_PROJECT : (A, W, S, D) - (R, Left Mouse)");

    init();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutTimerFunc(10, Timer, 0);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    glutMouseFunc(mouseClicks);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);


    glutMainLoop();

    return 0;
}
