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
GLuint  texture[6];
RgbImage imag;

string nomes[6] = {"Skybox\\Back.bmp", "Skybox\\Bottom.bmp", "Skybox\\Left.bmp",
                   "Skybox\\Front.bmp", "Skybox\\Right.bmp", "Skybox\\Up.bmp"};

class SkyBox {
    public:

        SkyBox() {}
        ~SkyBox() {}

        void createTexture(){
            int x;
            for(x=0;x<6;x++){
                //cout << "Textura Imagem: " << x << endl;
                glGenTextures(1, &texture[x]);
                glBindTexture(GL_TEXTURE_2D, texture[x]);
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
        }

        void drawSkyBox(){

            /* Aplicar as texturas nas imegens da SkyBox */

            /* Back */
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[0]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(-300.0,300.0,295.0); /* Superior esquerdo */
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-300.0,-300.0,295.0); /* Inferior esquerdo */
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(300.0,-300.0,295.0); /* Inferior direito */
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(300.0,300.0,295.0); /* Superior direito */

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            /* Bottom */
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[1]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(300.0,-300.0,300.0); /* Superior esquerdo */
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-300.0,-300.0,300.0); /* Inferior esquerdo */
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-300.0,-300.0,-800.0); /* Inferior direito */
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(300.0,-300.0,-800.0); /* Superior direito */

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            /* Front */
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[2]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(-302.0,300.0,-795.0); /* Superior esquerdo */
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-302.0,-300.0,-795.0); /* Inferior esquerdo */
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(302.0,-300.0,-795.0); /* Inferior direito */
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(302.0,300.0,-795.0); /* Superior direito */

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            /* Left */
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[3]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(295.0,300.0,-800.0); /* Superior esquerdo */
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(295.0,-300.0,-800.0); /* Inferior esquerdo */
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(295.0,-300.0,300.0); /* Inferior direito */
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(295.0,300.0,300.0); /* Superior direito */

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            /* Right */
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[4]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(-295.0,300.0,-800.0); /* Superior esquerdo */
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-295.0,-300.0,-800.0); /* Inferior esquerdo */
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-295.0,-300.0,300.0); /* Inferior direito */
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-295.0,300.0,300.0); /* Superior direito */

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            /* Up */
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture[5]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(300.0,295.0,300.0); /* Superior esquerdo */
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-300.0,295.0,300.0); /* Inferior esquerdo */
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-300.0,295.0,-800.0); /* Inferior direito */
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(300.0,295.0,-800.0); /* Superior direito */

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        }
}
;
