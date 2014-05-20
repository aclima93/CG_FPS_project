#ifndef MAIN_HPP
#define MAIN_HPP

void activateLight(void);
void activateAmbientIllumination(void);
void initLights(void);
void init(void);
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z);
void drawGrid();
GLuint groundTexture();
void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3,
                     GLfloat x4, GLfloat y4, GLfloat z4,
                     GLfloat n1, GLfloat n2, GLfloat n3,
                     GLfloat r, GLfloat g, GLfloat b, GLfloat a,
                     GLuint texture
                     );
void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3,
                     GLfloat x4, GLfloat y4, GLfloat z4,
                     GLfloat n1, GLfloat n2, GLfloat n3,
                     GLfloat r, GLfloat g, GLfloat b, GLfloat a
                     );
void drawWalls();
void drawScene();
GLvoid resize(GLsizei width, GLsizei height);
void drawOrientacao();
void display(void);
void reloadWeapon();
void shootGun(int x, int y, int z);
void mouseMotion(int x, int y);
void mouseClicks(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void updateVisao();
void teclasNotAscii(int key, int x, int y);
int main(int argc, char** argv);


#endif
