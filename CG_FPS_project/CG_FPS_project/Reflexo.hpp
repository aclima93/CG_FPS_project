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


class Reflexo {
    public:

        Reflexo() {}
        ~Reflexo() {}

        float alfa = 1.0f;
        float x = -10;
        float y = 10;
        float z = -40;
        float halfW = 20;
        float halfH = 10;
        float halfL = 1;

        void drawMirror(){


            // Reflexao
            glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
            glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
            glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
            glStencilFunc(GL_ALWAYS, 1, 1);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            //Coloca a 1 todos os pixels no stencil buffer que representam o chão
            glColorMask(1, 1, 1, 1); //Activa a escrita de cor
            glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade

            glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only

            //Desenha o objecto com uma reflexão vertical ond stencil buffer é 1
            glEnable(GL_NORMALIZE);

            glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,  5.5);



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

            glDisable(GL_NORMALIZE);
            glDisable(GL_STENCIL_TEST);
            glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,  0.5);

            //glDisable(GL_BLEND); /* Desactivar o BLEND */
        }
}
;
#endif
