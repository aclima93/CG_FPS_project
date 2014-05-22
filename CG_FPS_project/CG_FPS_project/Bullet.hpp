#ifndef BULLET_HPP
#define BULLET_HPP


#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

class Bullet{
    public:
        float x, y, z, angle;
        int targetX, targetY, targetZ;
        bool isActive;

        Bullet(){
            isActive = false;
        }
        ~Bullet(){}

        void draw(){

            if(isActive){
                glPushMatrix();
                    glRotatef(angle, 0, 0.5, 1);
                    glTranslatef( x, y, z);
                    glColor3f (0.4, 0.4, 1);
                    glutWireCube(0.1f);
                glPopMatrix();
                z--; //TODO: update coords for next iteration using angle
                isActive = ( x == targetX && y == targetY && z < targetZ );
            }

        }
};

// -------------------------- gun specs

#define CLIPSIZE 5
#define NUMBULLETS 15
#define NUMCLIPS 2

int bulletsInGun = CLIPSIZE;
int bulletsLeft = CLIPSIZE * NUMCLIPS;
int bulletIndex = 0;
Bullet bullets[NUMBULLETS];


#endif
