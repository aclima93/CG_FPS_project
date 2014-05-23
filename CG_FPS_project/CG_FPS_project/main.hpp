#ifndef MAIN_HPP
#define MAIN_HPP

#include <GL/gl.h>
#include <GL/glut.h>

#include <vector>

#include "materiais.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Textures.hpp"
#include "Map.hpp"
#include "Colors.hpp"
#include "Target.hpp"
#include "HUD.hpp"

//debug
#define DEBUG 1

Bullet bullets[NUMBULLETS];
Camera g_camera;
HUD hud;
Map map;


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
