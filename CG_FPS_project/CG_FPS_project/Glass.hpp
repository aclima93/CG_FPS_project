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

#include "RgbImage.h"
GLuint  texture[1];
RgbImage imag;

string nome[1] = {"Vidro\\Vidro.bmp"};

class Glass {
    public:

        Glass() {}
        ~Glass() {}

        void createTexture(){
            //cout << "Textura Imagem: " << x << endl;
            glGenTextures(1, &texture[0]);
            glBindTexture(GL_TEXTURE_2D, texture[0]);
            imag.LoadBmpFile(nomes[x].c_str()); /* Passar a string para const char em C */
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexImage2D(GL_TEXTURE_2D, 0, 3,
                imag.GetNumCols(),
                imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                imag.ImageData());
        }

        void drawSkyBox(){

            /* Aplicar a textura no vidro */
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[0]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(5.0,5.0,0.0); /* Superior esquerdo */
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0,0.0,0.0); /* Inferior esquerdo */
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0,0.0,0.0); /* Inferior direito */
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0,5.0,0.0); /* Superior direito */

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);
}
;
