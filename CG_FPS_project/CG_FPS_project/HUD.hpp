#ifndef HUD_HPP
#define HUD_HPP

#include <GL/glut.h>

GLint wScreen=1350, hScreen=800;

//------------------------------------------------------------ Sistema Coordenadas
GLfloat xC=16.0, zC=15.0;

int minutes = 0;
int seconds = 0;
int miliseconds = 0;
const int msecCallback = 10;
const int msecDisplayCallback = msecCallback * 10;

float widthHUDBlock = 200;
float heightHUDBlock = 100;
float crosshairThickness = 1.0;

float wCenterScreen = wScreen/2;
float hCenterScreen = hScreen/2;

char targetsInfoText[100];
char timerInfoText[100];
char bulletInfoText[100];

int numTargetsHit = 0;

class HUD{

    public:

        HUD(){}

        void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z){
            glRasterPos3f(x,y,z);
            while(*string)
              glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
        }

        void drawCrosshair(){

            // top segment
            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0);

                glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen - 30.0);
                glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen - 10.0);
                glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen - 10.0);
                glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen - 30.0);

            glEnd();
            // bottom segment
            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0);

                glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen + 30.0);
                glVertex2f(wCenterScreen + crosshairThickness, hCenterScreen + 10.0);
                glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen + 10.0);
                glVertex2f(wCenterScreen - crosshairThickness, hCenterScreen + 30.0);

            glEnd();
            // right segment
            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0);

                glVertex2f(wCenterScreen - 30.0, hCenterScreen - crosshairThickness);
                glVertex2f(wCenterScreen - 30.0, hCenterScreen + crosshairThickness);
                glVertex2f(wCenterScreen - 10.0, hCenterScreen + crosshairThickness);
                glVertex2f(wCenterScreen - 10.0, hCenterScreen - crosshairThickness);

            glEnd();
            // left segment
            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0);

                glVertex2f(wCenterScreen + 30.0, hCenterScreen + crosshairThickness);
                glVertex2f(wCenterScreen + 30.0, hCenterScreen - crosshairThickness);
                glVertex2f(wCenterScreen + 10.0, hCenterScreen - crosshairThickness);
                glVertex2f(wCenterScreen + 10.0, hCenterScreen + crosshairThickness);

            glEnd();

            // center doghnut
            int segments = 5;
            float t;
            int r = 2;

            glBegin( GL_TRIANGLE_FAN );
                glVertex2f(wCenterScreen, hCenterScreen);
                for( int n = 0; n <= segments; n++ ) {
                    t = 2*PI*(float)n/(float)segments;
                    glVertex2f(wCenterScreen + sin(t)*r, hCenterScreen + cos(t)*r);
                }
            glEnd();


        }

        void drawTargetsInfo(){


            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0);

                glVertex2f(wScreen - widthHUDBlock, 0.0);
                glVertex2f(wScreen - widthHUDBlock, heightHUDBlock);
                glVertex2f(wScreen, heightHUDBlock);
                glVertex2f(wScreen, 0.0);

            glEnd();

            glColor3f(0,0,0);
            sprintf(targetsInfoText,"%d/%d", numTargetsHit, NUMTARGETS);
            desenhaTexto(targetsInfoText,wScreen - widthHUDBlock/2, heightHUDBlock/2, 0);


        }

        void drawGunInfo(){


            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0);

                glVertex2f(0.0, 0.0);
                glVertex2f(widthHUDBlock, 0.0);
                glVertex2f(widthHUDBlock, heightHUDBlock);
                glVertex2f(0.0, heightHUDBlock);

            glEnd();

            glColor3f(0,0,0);
            sprintf(bulletInfoText,"%d loaded - %d left", bulletsInGun, bulletsLeft);
            desenhaTexto(bulletInfoText, widthHUDBlock/2, heightHUDBlock/2,0);

        }

        void drawMiniMap(){

            glClearColor(BLACK);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            glViewport (0, 0, wScreen/8, hScreen/8);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho (-xC,xC, -xC,xC, -zC,zC);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);

        }

        void drawTimeInfo(){


            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0);

                glVertex2f(wCenterScreen - widthHUDBlock, 0.0);
                glVertex2f(wCenterScreen - widthHUDBlock, heightHUDBlock/2);
                glVertex2f(wCenterScreen + widthHUDBlock, heightHUDBlock/2);
                glVertex2f(wCenterScreen + widthHUDBlock, 0.0);


            glEnd();

            glColor3f(0,0,0);
            sprintf(timerInfoText,"%d:%d:%d", minutes, seconds, miliseconds/10);
            desenhaTexto(timerInfoText, wCenterScreen, heightHUDBlock/4 ,0);


        }

        void drawHUD(){

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0.0, wScreen, hScreen, 0.0, -1.0, 10.0);
            glMatrixMode(GL_MODELVIEW);
            //glPushMatrix();        ----Not sure if I need this
            glLoadIdentity();
            glDisable(GL_CULL_FACE);

            glClear(GL_DEPTH_BUFFER_BIT);


            drawGunInfo();
            drawTimeInfo();
            drawTargetsInfo();
            drawCrosshair();

            // Making sure we can render 3d again
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            //glPopMatrix();        ----and this?


        }



};

HUD hud;

#endif
