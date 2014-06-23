#ifndef GLASS_HPP
#define GLASS_HPP

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

/* Alfa de transparencia a aplicar ao vidro */
float alfaVidro = 0.5f;

class Glass {
    public:

        Glass() {}
        ~Glass() {}

        void drawGlass(){

            //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glEnable(GL_BLEND); /* Activar BLEND */
            /* GL_SRC_ALPHA: define para o peso da cor do objecto a desenhar o valor do alfa da sua cor */
            /* GL_ONE_MINUS_SRC_ALPHA: define para o peso da cor que já está desenhado no ecran é de (1 - alfa),
             * onde alfa é o nível de transparência do objecto que está a ser desenhado */
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            /* Desenhar o quadrado em si */
            glBegin (GL_QUADS);
                /* Defenir o nível de transparencia do vidro */
                glColor4f(0.0f,0.0f,1.0f, alfaVidro);
                /* Ativar o teste de profundidade (z-buffer) */
                glEnable(GL_DEPTH_TEST);

                glNormal3f(0.0f, 0.0f, 0.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0,20.0,-10.0); /* Superior esquerdo */
                glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0,10.0,-10.0); /* Inferior esquerdo */
                glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0,10.0,-10.0); /* Inferior direito */
                glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0,20.0,-10.0); /* Superior direito */
            glEnd();

            glDisable(GL_BLEND); /* Desactivar o BLEND */
        }
}
;
#endif
