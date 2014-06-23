#ifndef HUD_HPP
#define HUD_HPP

#include <GL/glut.h>
#include <math.h>
#include "RgbImage.h"
#include <string>


#define HUDColor 0.0f, 0.635f, 0.909f

GLint wScreen=1366, hScreen=800;
GLfloat xC=50.0, yC=50.0, zC=50.0; // Sistema Coordenadas
int minutes = 0;
int secs = 0;
int miliseconds = 0;

const int msecCallback = 250;
const int msecDisplayCallback = msecCallback * 10;

const float widthHUDBlock = 200;
const float heightHUDBlock = 100;
const float crosshairThickness = 1.0;
const float crosshairLength = 30.0;
const float crosshairLengthFrac = crosshairLength/3;

const float wCenterScreen = wScreen/2;
const float hCenterScreen = hScreen/2;

float minimapViewHeight = -35;

char targetsInfoText[100];
char gameOverText1[100];
char gameOverText2[100];
char timerInfoText[100];
char bulletInfoText[100];
char extrasInfoText[100];
char scoreInfoText[100];
char clipsInfoText[100];

int numTargetsHit = 0;
int numExtrasHit = 0;

int score = 0;
int targetValues[6] = { 500, 350, 50, 50, 50, 50}; // head, torso, arms and legs
int extraValue = -750;

#define numImages 3
RgbImage hudImag;
GLuint  hudTexture[numImages];
string hudImages[numImages] = {"textures\\esquerda.bmp", "textures\\central.bmp", "textures\\direita.bmp"};
bool gameOver = false;

class HUD{

    public:

        HUD(){
            createTextures();
        }

        void createTextures(){
            for(int x=0;x<numImages;x++){
                glGenTextures(1, &hudTexture[x]);
                glBindTexture(GL_TEXTURE_2D, hudTexture[x]);
                hudImag.LoadBmpFile(hudImages[x].c_str()); /* Passar a string para const char em C */
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                glTexImage2D(GL_TEXTURE_2D, 0, 3,
                    hudImag.GetNumCols(),
                    hudImag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                    hudImag.ImageData());
             }
        }

        void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z){
            glRasterPos3f(x,y,z);
            while(*string)
              glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
        }

        void drawCrosshair(){

            if(!gameOver){

                glDisable(GL_LIGHTING);
                glPushMatrix();
                    glColor3f(HUDColor);
                    // top segment
                    glBegin(GL_QUADS);

                        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen - crosshairLength);
                        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen - crosshairLengthFrac);
                        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen - crosshairLengthFrac);
                        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen - crosshairLength);

                    glEnd();
                    // bottom segment
                    glBegin(GL_QUADS);

                        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen + crosshairLength);
                        glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen + crosshairLengthFrac);
                        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen + crosshairLengthFrac);
                        glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen + crosshairLength);

                    glEnd();
                    // right segment
                    glBegin(GL_QUADS);

                        glVertex2f(wCenterScreen - crosshairLength, hCenterScreen - crosshairThickness);
                        glVertex2f(wCenterScreen - crosshairLength, hCenterScreen + crosshairThickness);
                        glVertex2f(wCenterScreen - crosshairLengthFrac, hCenterScreen + crosshairThickness);
                        glVertex2f(wCenterScreen - crosshairLengthFrac, hCenterScreen - crosshairThickness);

                    glEnd();
                    // left segment
                    glBegin(GL_QUADS);

                        glVertex2f(wCenterScreen + crosshairLength, hCenterScreen + crosshairThickness);
                        glVertex2f(wCenterScreen + crosshairLength, hCenterScreen - crosshairThickness);
                        glVertex2f(wCenterScreen + crosshairLengthFrac, hCenterScreen - crosshairThickness);
                        glVertex2f(wCenterScreen + crosshairLengthFrac, hCenterScreen + crosshairThickness);

                    glEnd();

                    // center
                    /*
                    int segments = 5;
                    float t;
                    int r = 2;

                    glBegin( GL_TRIANGLE_FAN );
                        glVertex2f(wCenterScreen, hCenterScreen);
                        for( int n = 0; n <= segments; n++ ) {
                            t = 2*M_PI*(float)n/(float)segments;
                            glVertex2f(wCenterScreen + sin(t)*r, hCenterScreen + cos(t)*r);
                        }
                    glEnd();
                    */

                glPopMatrix();
                glEnable(GL_LIGHTING);

            }
            else{

                glDisable(GL_LIGHTING);

                //GameOver segment in middle of screen
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, hudTexture[1]);
                    glPushMatrix();
                        glDisable(GL_LIGHTING);
                        glBegin(GL_QUADS);

                        glColor4f(WHITE);
                        glNormal3f(0.0f, 0.0f, 0.0f);
                        glTexCoord2f(0.0f, 1.0f); glVertex2f(wCenterScreen - widthHUDBlock, hCenterScreen - (2*heightHUDBlock)/3);
                        glTexCoord2f(0.0f, 0.0f); glVertex2f(wCenterScreen - widthHUDBlock, hCenterScreen + (2*heightHUDBlock)/3);
                        glTexCoord2f(1.0f, 0.0f); glVertex2f(wCenterScreen + widthHUDBlock, hCenterScreen + (2*heightHUDBlock)/3);
                        glTexCoord2f(1.0f, 1.0f); glVertex2f(wCenterScreen + widthHUDBlock, hCenterScreen - (2*heightHUDBlock)/3);

                        glEnd();
                        glEnable(GL_LIGHTING);
                    glPopMatrix();
                glDisable(GL_TEXTURE_2D);

                glPushMatrix();
                    glColor3f(HUDColor);
                    sprintf(gameOverText1,"Game Over");
                    desenhaTexto(gameOverText1, wCenterScreen - 15, hCenterScreen -10, 0);
                glPopMatrix();
                glPushMatrix();
                    glColor3f(HUDColor);
                    sprintf(gameOverText2,"Press Spacebar to Restart");
                    desenhaTexto(gameOverText2, wCenterScreen - 30, hCenterScreen + 10, 0);
                glPopMatrix();

                glEnable(GL_LIGHTING);
            }


        }

        void drawTargetsInfo(){


            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, hudTexture[2]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);
                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);

                        glTexCoord2f(0.0f, 1.0f); glVertex2f(wScreen - widthHUDBlock, 0.0);
                        glTexCoord2f(0.0f, 0.0f); glVertex2f(wScreen - widthHUDBlock, heightHUDBlock);
                        glTexCoord2f(1.0f, 0.0f); glVertex2f(wScreen, heightHUDBlock);
                        glTexCoord2f(1.0f, 1.0f); glVertex2f(wScreen, 0.0);

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
                glColor3f(HUDColor);
                sprintf(targetsInfoText,"%d/%d", numTargetsHit, NUMTARGETS);
                desenhaTexto(targetsInfoText, wScreen - widthHUDBlock/2 - 15, heightHUDBlock/2-10, 0);
            glPopMatrix();

            glPushMatrix();
                glColor3f(HUDColor);
                sprintf(extrasInfoText,"%d/%d", numExtrasHit, NUMEXTRAS);
                desenhaTexto(extrasInfoText, wScreen - widthHUDBlock/2 - 15, heightHUDBlock/2 +15, 0);
            glPopMatrix();


        }

        void drawGunInfo(){

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, hudTexture[0]);
                glPushMatrix();
                glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);
                        glColor4f(WHITE);
                        glNormal3f(0.0f, 0.0f, 0.0f);
                        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0, 0.0);
                        glTexCoord2f(0.0f, 0.0f); glVertex2f(widthHUDBlock, 0.0);
                        glTexCoord2f(1.0f, 0.0f); glVertex2f(widthHUDBlock, heightHUDBlock);
                        glTexCoord2f(1.0f, 1.0f); glVertex2f(0.0, heightHUDBlock);

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
                glColor3f(HUDColor);
                sprintf(bulletInfoText,"%d bullets in chamber", bulletsInGun);
                desenhaTexto(bulletInfoText, widthHUDBlock/4 -15, heightHUDBlock/2-10, 0);
            glPopMatrix();

            glPushMatrix();
                glColor3f(HUDColor);
                sprintf(clipsInfoText,"%d bullets remaining", bulletsLeft);
                desenhaTexto(clipsInfoText, widthHUDBlock/4 -15, heightHUDBlock/2+10, 0);
            glPopMatrix();

        }

        void drawMiniMap(float x, float y, float z, float dx, float dz){

            if(y){}

            glClearColor(BLACK);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glViewport (0, 0, wScreen/8, hScreen/8);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(xC, -xC, -yC, yC, zC, -zC);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
                      //onde está           para onde está a olhar          vector up
            gluLookAt( x, minimapViewHeight, z,          x, 0, z,           dx, 0, dz);

        }

        void drawTimeInfo(){

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, hudTexture[1]);
                glPushMatrix();
                    glDisable(GL_LIGHTING);
                    glBegin(GL_QUADS);

                    glColor4f(WHITE);
                    glNormal3f(0.0f, 0.0f, 0.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex2f(wCenterScreen - widthHUDBlock, 0.0);
                    glTexCoord2f(0.0f, 0.0f); glVertex2f(wCenterScreen - widthHUDBlock, (2*heightHUDBlock)/3);
                    glTexCoord2f(1.0f, 0.0f); glVertex2f(wCenterScreen + widthHUDBlock, (2*heightHUDBlock)/3);
                    glTexCoord2f(1.0f, 1.0f); glVertex2f(wCenterScreen + widthHUDBlock, 0.0);

                    glEnd();
                    glEnable(GL_LIGHTING);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
                glColor3f(HUDColor);
                sprintf(timerInfoText,"Score: %d", score);
                desenhaTexto(timerInfoText, wCenterScreen -15, heightHUDBlock/3 -10 ,0);
            glPopMatrix();

            glPushMatrix();
                glColor3f(HUDColor);
                sprintf(scoreInfoText,"%d:%d:%d", minutes, secs, miliseconds);
                desenhaTexto(scoreInfoText, wCenterScreen -15 , heightHUDBlock/3 +10 ,0);
            glPopMatrix();


        }

        void drawMiniMapBox(){

            glDisable(GL_LIGHTING);

            // top line
            glPushMatrix();
                glBegin(GL_QUADS);
                    glColor3f(HUDColor);

                    glVertex2f( 0, (hScreen*7)/8 );
                    glVertex2f( 0, (hScreen*7)/8+3 );
                    glVertex2f( wScreen/8, (hScreen*7)/8+3 );
                    glVertex2f( wScreen/8, (hScreen*7)/8);

                glEnd();
            glPopMatrix();

            // side line
            glPushMatrix();
                glBegin(GL_QUADS);
                    glColor3f(HUDColor);

                    glVertex2f( wScreen/8, (hScreen*7)/8 );
                    glVertex2f( wScreen/8, hScreen );
                    glVertex2f( wScreen/8+3, hScreen);
                    glVertex2f( wScreen/8+3, (hScreen*7)/8 );

                glEnd();
            glPopMatrix();

            glEnable(GL_LIGHTING);

        }

        //everything except the minimap
        void drawHUD(){

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
                glLoadIdentity();
                glOrtho(0.0, wScreen, hScreen, 0.0, -1.0, 10.0);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glDisable(GL_CULL_FACE);
                glClear(GL_DEPTH_BUFFER_BIT);

                drawGunInfo();
                drawTimeInfo();
                drawTargetsInfo();
                drawMiniMapBox();
                glPushMatrix();
                    glTranslatef(0, -crosshairLength, 0);
                    drawCrosshair();
                glPopMatrix();

                // Making sure we can render 3d again
                glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);


        }



};

#endif
