#ifndef MAIN_HPP
#define MAIN_HPP

#include <GL/gl.h>
#include <GL/glut.h>

#include "Camera.hpp"
#include "Bullet.hpp"
#include "Textures.hpp"
#include "Map.hpp"
#include "Colors.hpp"

//debug
#define DEBUG 1

// gun
#define CLIPSIZE 5
#define NUMBULLETS 15
#define NUMCLIPS 2


//------------------------------------------------------------ Sistema Coordenadas
GLfloat xC=16.0, zC=15.0;
GLint wScreen=1350, hScreen=800;
char texto[100];


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
GLfloat PI = 3.1415926535;
const float g_translation_speed = 0.05;
const float g_rotation_speed = PI/180* 0.2;
Camera g_camera;


// -------------------------- gun specs
int bulletsInGun = CLIPSIZE;
int bulletsLeft = CLIPSIZE * NUMCLIPS;
int bulletIndex = 0;
Bullet bullets[NUMBULLETS];

// ------------------------- map
Map map;


void activateLight(void);
void activateAmbientIllumination(void);
void initLights(void);
void init(void);
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z);
void drawGrid();
void drawScene();
GLvoid resize(GLsizei width, GLsizei height);
void drawOrientacao();
void display(void);
void reloadWeapon();
void shootGun(int x, int y, int z);
void updateVisao();
int main(int argc, char** argv);


#endif
