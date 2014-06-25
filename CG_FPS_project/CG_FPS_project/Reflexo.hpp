#ifndef REFLEXO_HPP
#define REFLEXO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

using namespace std;

float alfa = 1;
float x = -10;
float y = 10;
float z = -30;
float halfW = 20;
float halfH = 10;
float halfL = 1;

float alfa2 = 1;
float x2 = -20;
float y2 = 10;
float z2 = -60;
float halfW2 = 1;
float halfH2 = 10;
float halfL2 = 20;

float alfa3 = 0.3;
float x3 = -10;
float y3 = 10;
float z3 = -70;
float halfW3 = 20;
float halfH3 = 10;
float halfL3 = 1;

const int ALTURA_REFLEXAO = 10;
const int LADO_CAPA = 60;

class Reflexo {
    public:

        Reflexo() {}
        ~Reflexo() {}

        void desenhaEspelho(float alfa, float x, float y, float z, float halfW, float halfH, float halfL){
           /* Desenhar o quadrado em si */
           glBegin (GL_QUADS);
               /* Defenir o nível de transparencia do vidro */
               glColor4f(0.0f,0.0f,1.0f, alfa);
               /* Ativar o teste de profundidade (z-buffer) */
               //glEnable(GL_DEPTH_TEST);

               glNormal3f(0.0f, 0.0f, 0.0f);

               glVertex3f(x+ halfW, y+ halfH, z- halfL );	// Top Right Of The Quad (Top)
               glVertex3f(x- halfW, y+ halfH, z- halfL);	// Top Left Of The Quad (Top)
               glVertex3f(x- halfW, y+ halfH, z+ halfL);	// Bottom Left Of The Quad (Top)
               glVertex3f(x+ halfW, y+ halfH, z+ halfL);	// Bottom Right Of The Quad (Top)

               glVertex3f(x+ halfW, y- halfH, z+ halfL);	// Top Right Of The Quad (Bottom)
               glVertex3f(x- halfW, y- halfH, z+ halfL);	// Top Left Of The Quad (Bottom)
               glVertex3f(x- halfW, y- halfH, z- halfL);	// Bottom Left Of The Quad (Bottom)
               glVertex3f(x+ halfW, y- halfH, z- halfL);	// Bottom Right Of The Quad (Bottom)

               glVertex3f(x+ halfW, y+ halfH, z+ halfL);	// Top Right Of The Quad (Front)
               glVertex3f(x- halfW, y+ halfH, z+ halfL);	// Top Left Of The Quad (Front)
               glVertex3f(x- halfW, y- halfH, z+ halfL);	// Bottom Left Of The Quad (Front)
               glVertex3f(x+ halfW, y- halfH, z+ halfL);	// Bottom Right Of The Quad (Front)

               glVertex3f(x+ halfW, y- halfH, z- halfL);	// Top Right Of The Quad (Back)
               glVertex3f(x- halfW, y- halfH, z- halfL);	// Top Left Of The Quad (Back)
               glVertex3f(x- halfW, y+ halfH, z- halfL);	// Bottom Left Of The Quad (Back)
               glVertex3f(x+ halfW, y+ halfH, z- halfL);	// Bottom Right Of The Quad (Back)

               glVertex3f(x- halfW, y+ halfH, z+ halfL);	// Top Right Of The Quad (Left)
               glVertex3f(x- halfW, y+ halfH, z- halfL);	// Top Left Of The Quad (Left)
               glVertex3f(x- halfW, y- halfH, z- halfL);	// Bottom Left Of The Quad (Left)
               glVertex3f(x- halfW, y- halfH, z+ halfL);	// Bottom Right Of The Quad (Left)

               glVertex3f(x+ halfW, y+ halfH,z- halfL);	// Top Right Of The Quad (Right)
               glVertex3f(x+ halfW, y+ halfH,z+ halfL);	// Top Left Of The Quad (Right)
               glVertex3f(x+ halfW, y- halfH,z+ halfL);	// Bottom Left Of The Quad (Right)
               glVertex3f(x+ halfW, y- halfH,z- halfL);	// Bottom Right Of The Quad (Right)
           glEnd();
        }


        void drawMirror(){

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glTranslatef(0.0, 0.0, -40.0);
            glRotatef(30, 1, 0, 0);

            GLfloat ambientLight[] = {0.2, 0.3, 0.3, 1.0};
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

            GLfloat lightColor[] = {0.7, 0.7, 0.7, 1.0};
            GLfloat lightPos[] = {-2 * LADO_CAPA, LADO_CAPA, 4 * LADO_CAPA, 1.0};
            glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

            glPushMatrix();
            glTranslatef(0, LADO_CAPA, 0);
            /* desenhar a superficie reflectora */
            desenhaEspelho(alfa, x, y, z, halfW, halfH, halfL);
            glPopMatrix();

            //ALUNOS: DESENHO REFLEXAO
            //REFLEXÃO
            //1. Activa o uso do stencil buffer
            glEnable(GL_STENCIL_TEST);

            //2. Nao escreve no color buffer
            glColorMask(0, 0, 0, 0);

            //3. Torna inactivo o teste de profundidade
            glDisable(GL_DEPTH_TEST);

            //4. Coloca a 1 todos os pixels no stencil buffer que representam o chão
            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

            //5. Desenhar o chão
            desenhaEspelho(alfa2, x2, y2, z2, halfW2, halfH2, halfL2);

            //6. Activa a escrita de cor
            glColorMask(1, 1, 1, 1);

            //7. Activa o teste de profundidade
            glEnable(GL_DEPTH_TEST);

            //8. O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
            glStencilFunc(GL_EQUAL, 1, 1);

            //9. Stencil buffer read-only
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

            //10. Desenha o objecto com a reflexão onde stencil buffer é 1
            glPushMatrix();
            glTranslatef(0,-ALTURA_REFLEXAO,0);
            glScalef(1,-1,1);
            desenhaEspelho(alfa3, x3, y3, z3, halfW3, halfW3, halfL3);
            glPopMatrix();


            //11. Desactiva a utilização do stencil buffer
            glDisable(GL_STENCIL_TEST);

           /* //Blending
            glEnable(GL_BLEND);
            glColor4f(1, 1, 1, 0.7);
            desenhaEspelho(alfa, x, y, z, halfW, halfH, halfL);
            glDisable(GL_BLEND);*/

            //FIM REFLEXÃO
           // glutSwapBuffers();
        }
}
;
#endif
