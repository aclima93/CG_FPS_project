#ifndef MAIN_HPP
#define MAIN_HPP

#include <GL/gl.h>
#include <GL/glut.h>

#include <vector>

#include "Camera.hpp"
#include "Bullet.hpp"
#include "Textures.hpp"
#include "Map.hpp"
#include "Colors.hpp"
#include "Target.hpp"

//debug
#define DEBUG 1


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

std::vector<Target> targets;
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
