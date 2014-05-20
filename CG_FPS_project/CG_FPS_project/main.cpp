#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "materiais.hpp"
#include "RgbImage.h"
#include "Camera.hpp"

//==================================================================== Definir cores

GLfloat field_width = 5; // 50
GLfloat field_height = 10; // 1000
GLfloat wall_height = 1; // 25

#define VIDRO    0.0, 0.0, 0.5, 0.1
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define VERDE    0.0, 1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY1    0.2, 0.2, 0.2, 1.0
#define GRAY2    0.93, 0.93, 0.93, 1.0

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat  xC=16.0, zC=15.0;
GLint    wScreen=1350, hScreen=800;
char     texto[30];

//------------------------------------------------------------ Observador
GLfloat  PI = 3.14159;

//------------------------------------------------------------ Iluminacao
GLfloat spot_direction[4]={0.0,0.0,1.0,1.0};
bool foco;
GLfloat spot_position[]={1,0.25,10};
GLint increment_spot_position = 5;

//------------------------------------------------------------ Global (ambiente)
GLint   noite=1;
GLfloat luzGlobalCor[4]={1.0,1.0,1.0,1.0};
bool iluminacao;

/*Definir posicao iluminacao local*/
GLfloat localCor[4] ={0.1, 0.1, 0.1, 1.0};
GLfloat localPos[4]={0.7, 1.0, 0.5, 1.0};

/*Atenuacoes iluminacao local*/
GLfloat localAttCon = 1.0;
GLfloat localAttLin = 0.05;
GLfloat localAttQua = 0.0;

//…………………………………………………………………………………………………………………………………………… Esfera
GLfloat matAmbiente[] = {1.0,1.0,1.0,1.0};
GLfloat matDifusa[]   = {1.0,1.0,1.0,1.0};
GLfloat matEspecular[]= {1.0, 1.0, 1.0, 1.0};
GLint   especMaterial = 20;


//…………………………………………………………………………………………………………………………………………… Color Material
bool colorMaterial;

//================================================================================
//=========================================================================== INIT
//================================================================================

#define CAMERASPEED	0.03f				// The Camera Speed


CCamera objCamera; // the camera

// -------------------------- gun specs
int CLIPSIZE = 5;
int bulletsInGun = CLIPSIZE;
int bulletsLeft = CLIPSIZE*2;

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


void activateLight(void)
{
    //…………………………………………………………………………………………………………………………………………… Restantes luzes
    glLightfv(GL_LIGHT0, GL_POSITION, spot_position);/*Definir posicao do foco*/

    //……………………………………………………………………………………………………………………………Lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, esmeraldAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, esmeraldDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, esmeraldSpec);
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
    glClearColor(WHITE);
    glShadeModel(GL_SMOOTH);

    //……………………………………………………………………………………………………………………………Lighting set up
    initLights();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);/*Vamos so trabalhar com uma luz*/
    glEnable(GL_DEPTH_TEST);


    ShowCursor(FALSE);		// Do NOT Show Mouse Pointer
                            // Position      View(target)  Up
    objCamera.Position_Camera(0, 2.5f, 5,	0, 2.5f, 0,   0, 1, 0);
    objCamera.Mouse_Move(640,480);

    foco = false;
    colorMaterial = false;
    iluminacao = false;
}


//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
    //----
    //char* string_temp = "ich bin ein rübe";
    //string = string_temp;

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
            glTexCoord2f(1.0f,0.0f); glVertex3f(x2, y2, z2); // bottom left
            glTexCoord2f(1.0f,1.0f); glVertex3f(x4, y4, z4); // bottom right
            glTexCoord2f(0.0f,1.0f); glVertex3f(x3, y3, z3); // top right

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

    //============================================Eixos
    if (noite)
        glColor4f(AMARELO);
    else
        glColor4f(BLACK);
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

    if (foco)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    //************************************************** Poligono
    //  As cores dos objectos devem ser definidas:
    //		1. Cor usando o glColorMaterial
    //		2. Propriedades materiais (a implementar)
    //************************************************** Poligno

    if (colorMaterial)
    {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT);
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        //glColorMaterial(GL_FRONT, GL_SPECULAR); - Nao considerar a componente especular
    }
    else
    {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
        glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
        //glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec); - Nao considerar a componente especular
    }


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

    glutPostRedisplay();
}


GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen=width;
    hScreen=height;
    drawScene();
}


void drawOrientacao()
{

    //****************************************************************************
    //  Direccao do FOCO=lanterna
    //****************************************************************************
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_direction);/*Definir direccao do foco*/
}

void display(void)
{
    if (noite)
        glClearColor(GRAY1);
    else
        glClearColor(GRAY2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //================================================================= Viewport1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport (0, hScreen/4, wScreen/4, hScreen/4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-xC,xC, -xC,xC, -zC,zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);
    gluLookAt(objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,
              objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
              objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);

    //--------------------- desenha objectos
    drawScene();
    drawOrientacao();

    //--------------------- Informacao
    glColor3f(1,0,0);
    if (noite == 1)
        sprintf(texto,"%d - in gun ; %d - left", bulletsInGun, bulletsLeft);
    else
        sprintf(texto,"%d - Dia", noite);
    desenhaTexto(texto,-12,1,-6);

    //================================================================= Viewport2
    glEnable(GL_LIGHTING);
    glViewport (wScreen/4, hScreen/4, 0.75*wScreen, 0.75*hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, wScreen/hScreen, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    objCamera.Position_Camera(0, 2.5f, 5,	0, 2.5f, 0,   0, 1, 0);

    drawScene();
    glutSwapBuffers();
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{

    //using parameters just because
    x++;
    y++;


    switch (key)
    {
        //--------------------------- forward
        case 'W':
        case 'w':
            objCamera.Move_Camera( CAMERASPEED);
            break;

        //--------------------------- back
        case 'S':
        case 's':
            objCamera.Move_Camera(-CAMERASPEED);
            break;

        //--------------------------- left
        case 'A':
        case 'a':
            objCamera.Strafe_Camera(-CAMERASPEED);
            break;

        //--------------------------- left
        case 'D':
        case 'd':
            objCamera.Strafe_Camera(CAMERASPEED);
            break;

        //--------------------------- reload
        case 'R':
        case 'r':
            reloadWeapon();
            break;

        //--------------------------- Escape
        case 27:
            exit(0);
            break;

    }
}

void updateVisao()
{
    /*
    obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
    obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
    */
    glutPostRedisplay();
}

void teclasNotAscii(int key, int x, int y)
{

    //using parameters just because
    x++;
    y++;

    /*
    if(key == GLUT_KEY_UP) {
        obsPini[0]=obsPini[0]+incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]-incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_DOWN) {
        obsPini[0]=obsPini[0]-incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_LEFT) {
        aVisao = (aVisao + 0.1) ;
    }
    if(key == GLUT_KEY_RIGHT) {
        aVisao = (aVisao - 0.1) ;
    }
    updateVisao();
    */
}

//======================================================= MAIN
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("{CG_FPS  (left,right,up,down) - (FlashLight, NightVision, Reload) - (LC) ");

    init();
    glutSpecialFunc(teclasNotAscii);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
