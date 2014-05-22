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

        BoundingBox(){}

        void Init(float xx, float yy, float zz){
            x = xx;
            y = yy;
            z = zz;
        }

        void drawBoundingBox(){

            glPushMatrix();
                glBegin(GL_QUADS);		// Draw The Cube Using quads

                  glColor3f(1.0f,0.0f,0.0f);	// Color Red

                  glVertex3f( x, y,-z);	// Top Right Of The Quad (Top)
                  glVertex3f(-x, y,-z);	// Top Left Of The Quad (Top)
                  glVertex3f(-x, y, z);	// Bottom Left Of The Quad (Top)
                  glVertex3f( x, y, z);	// Bottom Right Of The Quad (Top)

                  glVertex3f( x,-y, z);	// Top Right Of The Quad (Bottom)
                  glVertex3f(-x,-y, z);	// Top Left Of The Quad (Bottom)
                  glVertex3f(-x,-y,-z);	// Bottom Left Of The Quad (Bottom)
                  glVertex3f( x,-y,-z);	// Bottom Right Of The Quad (Bottom)

                  glVertex3f( x, y, z);	// Top Right Of The Quad (Front)
                  glVertex3f(-x, y, z);	// Top Left Of The Quad (Front)
                  glVertex3f(-x,-y, z);	// Bottom Left Of The Quad (Front)
                  glVertex3f( x,-y, z);	// Bottom Right Of The Quad (Front)

                  glVertex3f( x,-y,-z);	// Top Right Of The Quad (Back)
                  glVertex3f(-x,-y,-z);	// Top Left Of The Quad (Back)
                  glVertex3f(-x, y,-z);	// Bottom Left Of The Quad (Back)
                  glVertex3f( x, y,-z);	// Bottom Right Of The Quad (Back)

                  glVertex3f(-x, y, z);	// Top Right Of The Quad (Left)
                  glVertex3f(-x, y,-z);	// Top Left Of The Quad (Left)
                  glVertex3f(-x,-y,-z);	// Bottom Left Of The Quad (Left)
                  glVertex3f(-x,-y, z);	// Bottom Right Of The Quad (Left)

                  glVertex3f( x, y,-z);	// Top Right Of The Quad (Right)
                  glVertex3f( x, y, z);	// Top Left Of The Quad (Right)
                  glVertex3f( x,-y, z);	// Bottom Left Of The Quad (Right)
                  glVertex3f( x,-y,-z);	// Bottom Right Of The Quad (Right)

                glEnd();			// End Drawing The Cube
            glPopMatrix();
        }


};

#endif
