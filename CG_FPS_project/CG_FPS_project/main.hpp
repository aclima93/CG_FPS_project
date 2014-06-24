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

//debug
#define DEBUG 1
#define DEBUG_MODE 1

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include "materiais.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "Colors.hpp"
#include "Target.hpp"
#include "HUD.hpp"
#include "Sounds.hpp"
#include "Model.hpp"
#include "SkyBox.hpp"

// our defined elements
Bullet bullets[NUMBULLETS];
Camera camera;
HUD hud;
Map map;
Sounds sounds;
Model player;

bool paused = false;

float xStart = 0;
float yStart = mapHeight/2;
float zStart = -7.5;

float playerRadius = 5;

float xCamera;
float yCamera;
float zCamera;
float dxCamera;
float dyCamera;
float dzCamera;

/* Sky Box */
SkyBox skybox;

int mainMenu;
bool isMenuActive = false;
int numGameModes = 5;
const char* gameModes[] = { "Time Attack", "No Bullet Left Behind", "Zen", "Highscores", "Quit Game" };

std::vector<Target> targets(NUMTARGETS);
std::vector<Target> extras(NUMEXTRAS);


//------------------------------------------------------------ Global (ambiente)

GLfloat  mat1[] = {0.5f, .97f, 1.f, .5f};		// 'cor' da 1ª
GLfloat  mat2[] = {1.f, .5f, 0.f, .5f};			// 'cor' da 2ª
GLfloat  raioEsf   = 1.75;						// raio das esferas

int numLights = 0;//4;
GLfloat light_ambient[][4] = {
    { 0.0, 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 0.0, 1.0 }
    };
GLfloat light_diffuse[][4] = {
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 }
    };
GLfloat light_specular[][4] = {
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 }
    };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };

GLfloat luzGlobalCor[4]={1.0,1.0,1.0,1.0};
bool iluminacao;
bool dayTime = false;
bool nightTime = true;

/*Definir posicao iluminacao local*/
GLfloat localCor[4] ={1, 1, 1, 1.0};
GLfloat localPos[][4]={
    {0, mapHeight*2, (-mapLength*1)/8, 1.0},
    {0, mapHeight*2, (-mapLength*3)/8, 1.0},
    {0, mapHeight*2, (-mapLength*5)/8, 1.0},
    {0, mapHeight*2, (-mapLength*7)/8, 1.0}
    };

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
void shootGun();
void updateGameTimer();
void Timer(int value);
int main(int argc, char** argv);
void createMainMenu();
void mainMenuEvents(int value);
void teclasNotAscii(int key, int x, int y);
void mouseMotion(int x, int y);
void mouseClicks(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);


#endif
