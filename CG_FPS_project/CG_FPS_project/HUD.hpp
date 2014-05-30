#ifndef HUD_HPP
#define HUD_HPP

#include <GL/glut.h>
#include <math.h>

GLint wScreen=1366, hScreen=800;
GLfloat xC=50.0, yC=50.0, zC=50.0; // Sistema Coordenadas
int minutes = 0;
int secs = 0;
int miliseconds = 0;

const int msecCallback = 10;
const int msecDisplayCallback = msecCallback * 10;

const float widthHUDBlock = 200;
const float heightHUDBlock = 100;
const float crosshairThickness = 1.0;
const float crosshairLength = 30.0;
const float crosshairLengthFrac = crosshairLength/3;

const float wCenterScreen = wScreen/2;
const float hCenterScreen = hScreen/2;

float minimapViewHeight = 20;

char targetsInfoText[100];
char timerInfoText[100];
char bulletInfoText[100];
char extrasInfoText[100];
char scoreInfoText[100];
char clipsInfoText[100];

int numTargetsHit = 0;
int numExtrasHit = 0;

int score = 0;
int targetValues[6] = { 500, 350, 50, 50, 50, 50}; // head, torso, arms and legs
int extraValue = 750;

class HUD{

    public:

        HUD(){}

        void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z){
            glRasterPos3f(x,y,z);
            while(*string)
              glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
        }

        void drawCrosshair(){

            glPushMatrix();
                glColor3f(1.0f, 0.0f, 0.0);
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
            glPopMatrix();


        }

        void drawTargetsInfo(){

            glPushMatrix();
                glBegin(GL_QUADS);
                    glColor3f(1.0f, 0.0f, 0.0);

                    glVertex2f(wScreen - widthHUDBlock, 0.0);
                    glVertex2f(wScreen - widthHUDBlock, heightHUDBlock);
                    glVertex2f(wScreen, heightHUDBlock);
                    glVertex2f(wScreen, 0.0);

                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0);
                sprintf(targetsInfoText,"%d/%d", numTargetsHit, NUMTARGETS);
                desenhaTexto(targetsInfoText, wScreen - widthHUDBlock/2, heightHUDBlock/2, 0);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0);
                sprintf(extrasInfoText,"%d/%d", numExtrasHit, NUMEXTRAS);
                desenhaTexto(extrasInfoText, wScreen - widthHUDBlock/2, heightHUDBlock/2 + 10.0, 0);
            glPopMatrix();


        }

        void drawGunInfo(){

            glPushMatrix();
                glBegin(GL_QUADS);
                    glColor3f(1.0f, 0.0f, 0.0);

                    glVertex2f(0.0, 0.0);
                    glVertex2f(widthHUDBlock, 0.0);
                    glVertex2f(widthHUDBlock, heightHUDBlock);
                    glVertex2f(0.0, heightHUDBlock);

                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0);
                sprintf(bulletInfoText,"%d bullets loaded", bulletsInGun);
                desenhaTexto(bulletInfoText, widthHUDBlock/4, heightHUDBlock/2-10, 0);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0);
                sprintf(clipsInfoText,"%d bullets left", bulletsLeft);
                desenhaTexto(clipsInfoText, widthHUDBlock/4, heightHUDBlock/2+10, 0);
            glPopMatrix();
        }

        void drawMiniMap(float x, float y, float z){

            glClearColor(BLACK);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glViewport (0, 0, wScreen/8, hScreen/8);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-xC, xC, -yC, yC, zC, -zC);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
                      //onde está           para onde está a olhar     vector up
            gluLookAt( x, minimapViewHeight, z,          x, 0, z,                   0, 0, -1);

            if(y){}

        }

        void drawTimeInfo(){

            glPushMatrix();
                glColor3f(1.0f, 0.0f, 0.0);
                glBegin(GL_QUADS);

                    glVertex2f(wCenterScreen - widthHUDBlock, 0.0);
                    glVertex2f(wCenterScreen - widthHUDBlock, (2*heightHUDBlock)/3);
                    glVertex2f(wCenterScreen + widthHUDBlock, (2*heightHUDBlock)/3);
                    glVertex2f(wCenterScreen + widthHUDBlock, 0.0);

                glEnd();

                glBegin(GL_QUADS);

                    glVertex2f(wCenterScreen - widthHUDBlock, 0.0);
                    glVertex2f(wCenterScreen - widthHUDBlock, (2*heightHUDBlock)/3);
                    glVertex2f(wCenterScreen + widthHUDBlock, (2*heightHUDBlock)/3);
                    glVertex2f(wCenterScreen + widthHUDBlock, 0.0);

                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0);
                sprintf(timerInfoText,"Score: %d", score);
                desenhaTexto(timerInfoText, wCenterScreen, heightHUDBlock/3 -10 ,0);
            glPopMatrix();

            glPushMatrix();
                glColor3f(0,0,0);
                sprintf(scoreInfoText,"%d:%d:%d", minutes, secs, miliseconds);
                desenhaTexto(scoreInfoText, wCenterScreen, heightHUDBlock/3 +10 ,0);
            glPopMatrix();


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
