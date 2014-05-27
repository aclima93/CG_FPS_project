#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include "materiais.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Textures.hpp"
#include "Map.hpp"
#include "Colors.hpp"
#include "Target.hpp"
#include "HUD.hpp"
#include "FMOD.hpp"

//debug
#define DEBUG 1

// our defined elements
Bullet bullets[NUMBULLETS];
Camera g_camera;
HUD hud;
Map map;
FMOD sound;

float xStart = 0;
float yStart = 0;
float zStart = map.mapHeight/2;

std::vector<Target> targets(NUMTARGETS); //Target targets[NUMTARGETS];
std::vector<Target> extras(NUMEXTRAS); //Target extras[NUMEXTRAS];


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


void drawTargets();
void createTargets();
void activateLight(void);
void activateAmbientIllumination(void);
void initLights(void);
void init(void);
void drawGrid();
void drawBullets();
void drawScene();
GLvoid resize(GLsizei width, GLsizei height);
void drawOrientacao();
void display(void);
void updateBullets();
void reloadGun();
void shootGun(int x, int y, int z);
void updateGameTimer();
void Timer(int value);
int main(int argc, char** argv);
void teclasNotAscii(int key, int x, int y);
void mouseMotion(int x, int y);
void mouseClicks(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

#endif
