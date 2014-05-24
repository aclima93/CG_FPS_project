#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

class BoundingBox{

    public:

        float x, y, z;
        float w, l, h;
        float halfW, halfH, halfL;


        BoundingBox(){}

        void Init(float xx, float yy, float zz, float ww, float ll, float hh){
            x = xx;
            y = yy;
            z = zz;
            w = ww;
            h = hh;
            l = ll;
            halfW = w/2;
            halfH = h/2;
            halfL = l/2;
        }

        void drawBoundingBox(){

            glPushMatrix();

                /*
                glTranslatef( x, y, z);
                glColor3f (1, 0, 1);
                glutWireCube(w);
                */


                glBegin(GL_QUADS);		// Draw The Paralellogram Using quads

                    //glTranslatef(x, y, z);
                    glColor3f(1, 0, 1);	// Color Red

                    glVertex3f(x+ halfW,y+ halfH,z- halfL );	// Top Right Of The Quad (Top)
                    glVertex3f(x- halfW,y+ halfH,z- halfL);	// Top Left Of The Quad (Top)
                    glVertex3f(x- halfW,y+ halfH,z+ halfL);	// Bottom Left Of The Quad (Top)
                    glVertex3f(x+ halfW,y+ halfH,z+ halfL);	// Bottom Right Of The Quad (Top)

                    glVertex3f(x+ halfW,y- halfH,z+ halfL);	// Top Right Of The Quad (Bottom)
                    glVertex3f(x- halfW,y- halfH,z+ halfL);	// Top Left Of The Quad (Bottom)
                    glVertex3f(x- halfW,y- halfH,z- halfL);	// Bottom Left Of The Quad (Bottom)
                    glVertex3f(x+ halfW,y- halfH,z- halfL);	// Bottom Right Of The Quad (Bottom)

                    glVertex3f(x+ halfW,y+ halfH,z+ halfL);	// Top Right Of The Quad (Front)
                    glVertex3f(x- halfW,y+ halfH,z+ halfL);	// Top Left Of The Quad (Front)
                    glVertex3f(x- halfW,y- halfH,z+ halfL);	// Bottom Left Of The Quad (Front)
                    glVertex3f(x+ halfW,y- halfH,z+ halfL);	// Bottom Right Of The Quad (Front)

                    glVertex3f(x+ halfW,y- halfH,z- halfL);	// Top Right Of The Quad (Back)
                    glVertex3f(x- halfW,y- halfH,z- halfL);	// Top Left Of The Quad (Back)
                    glVertex3f(x- halfW,y+ halfH,z- halfL);	// Bottom Left Of The Quad (Back)
                    glVertex3f(x+ halfW,y+ halfH,z- halfL);	// Bottom Right Of The Quad (Back)

                    glVertex3f(x- halfW,y+ halfH,z+ halfL);	// Top Right Of The Quad (Left)
                    glVertex3f(x- halfW,y+ halfH,z- halfL);	// Top Left Of The Quad (Left)
                    glVertex3f(x- halfW,y- halfH,z- halfL);	// Bottom Left Of The Quad (Left)
                    glVertex3f(x- halfW,y- halfH,z+ halfL);	// Bottom Right Of The Quad (Left)

                    glVertex3f(x+ halfW,y+ halfH,z- halfL);	// Top Right Of The Quad (Right)
                    glVertex3f(x+ halfW,y+ halfH,z+ halfL);	// Top Left Of The Quad (Right)
                    glVertex3f(x+ halfW,y- halfH,z+ halfL);	// Bottom Left Of The Quad (Right)
                    glVertex3f(x+ halfW,y- halfH,z- halfL);	// Bottom Right Of The Quad (Right)

                glEnd();			// End Drawing The Paralellogram


            glPopMatrix();
        }


};

#endif
