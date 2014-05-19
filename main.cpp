#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "materiais.hpp"

//==================================================================== Definir cores
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
GLint    wScreen=800, hScreen=600;
char     texto[30];

//------------------------------------------------------------ Observador
GLfloat  PI = 3.14159;
GLfloat  rVisao=3.0, aVisao=0.5*PI, incVisao=0.1;
GLfloat  obsPini[] ={0, 5, 0};
GLfloat  obsPfin[] ={obsPini[0]-rVisao*cos(aVisao), obsPini[1], obsPini[2]-rVisao*sin(aVisao)};

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

    foco = false;
    colorMaterial = false;
    iluminacao = false;
}


//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
    glRasterPos3f(x,y,z);
    while(*string)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}

void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3,
                     GLfloat x4, GLfloat y4, GLfloat z4,
                     GLfloat n1, GLfloat n2, GLfloat n3,
                     GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    glPushMatrix();
        glColor4f(r, g, b, a);
        glBegin(GL_QUADS);
            glNormal3d(n1, n2, n3);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x4, y4, z4); // 3 troca com o 4 because Quads suck
            glVertex3f(x3, y3, z3);

        glEnd();
    glPopMatrix();
}

void drawWalls(){

    //parede esquerda1
    desenhaQuadrado(
        -field_width/2, wall_height, 0,                         // A
        -field_width/2, wall_height, -field_height*(0.4f),      // B
        -field_width/2, 0, 0,                                   // C
        -field_width/2, 0, -field_height*(0.4f),                // D
         1, 0, 0,                                               // normal
         VERDE                                                  // r g b a
    );

    //parede esquerda2
    desenhaQuadrado(
        -field_width/2, wall_height, -field_height*(0.45f),      // A
        -field_width/2, wall_height, -field_height*(0.55f),      // B
        -field_width/2, 0, -field_height*(0.45f),                // C
        -field_width/2, 0, -field_height*(0.55f),                // D
         1, 0, 0,                                                // normal
         AZUL                                                    // r g b a
    );

    //parede esquerda3
    desenhaQuadrado(
        -field_width/2, wall_height, -field_height*(0.60f),      // top left
        -field_width/2, wall_height, -field_height,              // top right
        -field_width/2, 0, -field_height*(0.60f),                // bottom left
        -field_width/2, 0, -field_height,                        // bottom right
         1, 0, 0,                                                // normal
         AMARELO                                                 // r g b a
    );

    //parede direita1
    desenhaQuadrado(
        field_width/2, wall_height, 0,                         // A
        field_width/2, wall_height, -field_height*(0.4f),      // B
        field_width/2, 0, 0,                                   // C
        field_width/2, 0, -field_height*(0.4f),                // D
         1, 0, 0,                                               // normal
         VERDE                                                  // r g b a
    );

    //parede direita2
    desenhaQuadrado(
        field_width/2, wall_height, -field_height*(0.45f),      // A
        field_width/2, wall_height, -field_height*(0.55f),      // B
        field_width/2, 0, -field_height*(0.45f),                // C
        field_width/2, 0, -field_height*(0.55f),                // D
         1, 0, 0,                                                // normal
         AZUL                                                    // r g b a
    );

    //parede direita3
    desenhaQuadrado(
        field_width/2, wall_height, -field_height*(0.60f),      // top left
        field_width/2, wall_height, -field_height,              // top right
        field_width/2, 0, -field_height*(0.60f),                // bottom left
        field_width/2, 0, -field_height,                        // bottom right
         1, 0, 0,                                                // normal
         AMARELO                                                 // r g b a
    );

}

void drawScene()
{
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


    //************************************************** Poligono
    //  Construir um poligono de uma dada cor
    //************************************************** Poligono

    /*Desenhar chão*/

    GLint field_width = 5; // 50
    GLint field_height = 5; // 1000
    GLint wall_height = 5; // 25


    //chão
    desenhaQuadrado(
        -field_width/2, 0, -field_height,   // A
         field_width/2, 0, -field_height,   // B
        -field_width/2, 0, 0,               // C
         field_width/2, 0, 0,               // D
         1, 0, 0,                           // normal
         VERMELHO                              // r g b a
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
    /*Posicao inicial do observador??*/
    glPushMatrix();
        glColor4f(VERDE);
        glTranslatef (obsPini[0],obsPini[1],obsPini[2]);
        glutSolidCube(0.75);
    glPopMatrix();

    /*Posicao final do observador??*/
    glPushMatrix();
        glColor4f(LARANJA);
        glTranslatef (obsPfin[0],obsPfin[1],obsPfin[2]);
        glutSolidCube(0.5);
    glPopMatrix();

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
    gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);

    //--------------------- desenha objectos
    drawScene();
    drawOrientacao();

    //--------------------- Informacao
    glColor3f(1,0,0);
    if (noite == 1)
        sprintf(texto,"%d - Noite", noite);
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
    gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);

    drawScene();
    glutSwapBuffers();
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        //--------------------------- Direccao da Lanterna
        //****************************************************************************
        //  A lanterna pode-se movimentar usando as teclas 'S', 'D', 'E', 'C'
        //****************************************************************************
        case 's':
        case 'S':
            spot_position[0] = spot_position[0] - increment_spot_position;/*Esquerda*/
            activateLight();
            break;
        case 'd':
        case 'D':
            spot_position[0] = spot_position[0] + increment_spot_position;/*Direita*/
            activateLight();
            break;
        case 'e':
        case 'E':
            spot_position[2] = spot_position[2] + increment_spot_position;/*Cima*/
            activateLight();
            break;
        case 'c':
        case 'C':
            spot_position[2] = spot_position[2] - increment_spot_position;/*Baixo*/
            activateLight();
            break;

        //--------------------------- Dia/noite : definir intensidades da luz
        case 'n':
        case 'N':
            noite=!noite;
            if (noite)
            {
                luzGlobalCor[0]=1.0;
                luzGlobalCor[1]=1.0;
                luzGlobalCor[2]=1.0;
            }
            else
            {
                luzGlobalCor[0]=0.3;
                luzGlobalCor[1]=0.3;
                luzGlobalCor[2]=0.3;
            }

            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
            glutPostRedisplay();
            break;

        //--------------------------- Iluminacao da sala
        case 't':
        case 'T':
            /*Alternar entre local e global*/
            iluminacao = !iluminacao;
            activateAmbientIllumination();
            break;

        //--------------------------- Foco
        case 'f':
        case 'F':
            foco = !foco;
            break;

        //--------------------------- ColorMaterial
        case 'm':
        case 'M':
            colorMaterial = !colorMaterial;
            break;

        //--------------------------- Escape
        case 27:
            exit(0);
            break;

    }
}

void updateVisao()
{
    obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
    obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
    glutPostRedisplay();
}

void teclasNotAscii(int key, int x, int y)
{
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
}

//======================================================= MAIN
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (400, 100);
    glutCreateWindow ("{jh,pm,ja}@dei.uc.pt-CG  (left,right,up,down) - (N,T,F,M) - (s,d-e,c) ");

    init();
    glutSpecialFunc(teclasNotAscii);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
