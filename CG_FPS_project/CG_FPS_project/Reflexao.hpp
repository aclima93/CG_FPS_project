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
void drawPlayer();
//const int ALTURA_REFLEXAO = 10;

class Reflexao {
    public:

        Reflexao() {}
        ~Reflexao() {}

        /* Draw objecto reflector */
        void drawObjectReflector(float alfa, float x, float y, float z, float halfW, float halfH, float halfL){
           /* Activar BLEND */
           glEnable(GL_BLEND);
           /* GL_SRC_ALPHA: define para o peso da cor do objecto a desenhar o valor do alfa da sua cor
            * GL_ONE_MINUS_SRC_ALPHA: define para o peso da cor que já está desenhado no ecran é de (1 - alfa),
            * onde alfa é o nível de transparência do objecto que está a ser desenhado */
           glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

               glBegin(GL_QUADS);	// Draw The Paralellogram Using quads
                   glColor4f(0.0f, 0.0f, 0.9f, alfa); // Defenir o nível de transparencia do vidro
                   glEnable(GL_DEPTH_TEST); // Ativar o teste de profundidade (z-buffer)
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

                   glVertex3f(x+ halfW, y+ halfH, z- halfL);	// Top Right Of The Quad (Right)
                   glVertex3f(x+ halfW, y+ halfH, z+ halfL);	// Top Left Of The Quad (Right)
                   glVertex3f(x+ halfW, y- halfH, z+ halfL);	// Bottom Left Of The Quad (Right)
                   glVertex3f(x+ halfW, y- halfH, z- halfL);	// Bottom Right Of The Quad (Right)

               glEnd();	// End Drawing The Paralellogram

           glDisable(GL_BLEND); /* Desactivar o BLEND */
        }

        void drawReflexao(){

            glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
            glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
            glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            //Coloca a 1 todos os pixels no stencil buffer que representam a superfície reflectora
            //DESENHAR SUPERFÍCIE REFLECTORA
            drawObjectReflector(1, -10, 40, -70, 10, 0, 10);

            glColorMask(1, 1, 1, 1); //Activa a escrita de cor
            glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade
            glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
            //Desenha o objecto com a reflexão onde stencil buffer é 1
            //DESENHAR OBJECTO REFLECTIDO
            // Homem
            glPushMatrix();
                glScalef(1,1,-1);
                glTranslatef(0.0,0.0,-70);
                //desenha homem
                drawPlayer();
            glPopMatrix();

            glDisable(GL_STENCIL_TEST); //Desactiva a utilização do stencil buffer
            //Blending
            glEnable(GL_BLEND);
            //DESENHAR SUPERFÍCIE REFLECTORA COM TRANSPARÊNCIA
            glColor4f(1.0,1.0,1.0,0.5);
            drawObjectReflector(0.7, -10, 40, -40, 10, 0, 10);
            glDisable(GL_BLEND);

        }
}
;
