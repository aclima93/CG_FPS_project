#ifndef BULLET_HPP
#define BULLET_HPP


#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

// -------------------------- gun specs

#define CLIPSIZE 5
#define NUMBULLETS 15
#define NUMCLIPS 2

int bulletsInGun = CLIPSIZE;
int bulletsLeft = CLIPSIZE * NUMCLIPS;
int bulletIndex = 0;
float bulletSpeed = 1; //304; // 303.986 m/s
float maxTravelDistance = 5000;
float maxTravelDistanceSQR = maxTravelDistance*maxTravelDistance;

class Bullet{
    public:
        float x, y, z;
        float vx, vy, vz;
        float tx, ty, tz;
        bool isActive;

        Bullet(){
            isActive = false;
        }
        ~Bullet(){}

        void Init(float xx, float yy, float zz,
                  float vxx, float vyy, float vzz, float speed,
                  float txx, float tyy, float tzz, bool act){

            x = xx;
            y = yy;
            z = zz;

            vx = vxx*speed;
            vy = vyy*speed;
            vz = vzz*speed;

            tx = txx;
            ty = tyy;
            tz = tzz;

            isActive = act;

        }

        void draw(){


            if(isActive){

                glPushMatrix();
                    glBegin(GL_LINES);
                        glColor3f(0, 1, 0);     // green
                        glVertex3f(x, y, z);	// position
                        glVertex3f(0, 0, 0 );	// origin
                    glEnd();
                glPopMatrix();

                /*
                glPushMatrix();
                    glTranslatef( x, y, z);
                    glColor3f (0.4, 0.4, 1);
                    glutWireCube(0.05f);
                glPopMatrix();
                */
            }


        }


        void updatePosition(){

            x += vx;
            y += vy;
            z += vz;

            isActive = ( (x*x) + (y*y) + (z*z) <= maxTravelDistanceSQR  );
        }

};


#endif
