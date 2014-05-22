
#include "GL/gl.h"
#include <iostream>
#include "BoundingBox.hpp"
#include <vector>

#define NUMTARGETS 10
#define NUMEXTRAS 3 // balloons

class Target{

    public:

        float x, y, z;
        int numBoundingBoxes;
        int w, l, h; // to be used?

        std::vector< BoundingBox > boundingboxes; // array de bounding boxes para detectar as collisions

        Target(float xx, float yy, float zz, int numBB, float posBB[][3]){
                    x = xx;
                    y = yy;
                    z = zz;

                    numBoundingBoxes = numBB;

                    for(int i=0; i<numBB; i++){
                        boundingboxes[i] = BoundingBox( posBB[i][0], posBB[i][1], posBB[i][2] );
                    }
        }

        void drawTarget(){

            glPushMatrix();
                glBegin(GL_QUADS);		// Draw The Cube Using quads

                  glColor3f(0.0f,1.0f,0.0f);	// Color Blue
                  glVertex3f( x, y,-z);	// Top Right Of The Quad (Top)
                  glVertex3f(-x, y,-z);	// Top Left Of The Quad (Top)
                  glVertex3f(-x, y, z);	// Bottom Left Of The Quad (Top)
                  glVertex3f( x, y, z);	// Bottom Right Of The Quad (Top)

                  glColor3f(1.0f,0.5f,0.0f);	// Color Orange
                  glVertex3f( x,-y, z);	// Top Right Of The Quad (Bottom)
                  glVertex3f(-x,-y, z);	// Top Left Of The Quad (Bottom)
                  glVertex3f(-x,-y,-z);	// Bottom Left Of The Quad (Bottom)
                  glVertex3f( x,-y,-z);	// Bottom Right Of The Quad (Bottom)

                  glColor3f(1.0f,0.0f,0.0f);	// Color Red
                  glVertex3f( x, y, z);	// Top Right Of The Quad (Front)
                  glVertex3f(-x, y, z);	// Top Left Of The Quad (Front)
                  glVertex3f(-x,-y, z);	// Bottom Left Of The Quad (Front)
                  glVertex3f( x,-y, z);	// Bottom Right Of The Quad (Front)

                  glColor3f(1.0f,1.0f,0.0f);	// Color Yellow
                  glVertex3f( x,-y,-z);	// Top Right Of The Quad (Back)
                  glVertex3f(-x,-y,-z);	// Top Left Of The Quad (Back)
                  glVertex3f(-x, y,-z);	// Bottom Left Of The Quad (Back)
                  glVertex3f( x, y,-z);	// Bottom Right Of The Quad (Back)

                  glColor3f(0.0f,0.0f,1.0f);	// Color Blue
                  glVertex3f(-x, y, z);	// Top Right Of The Quad (Left)
                  glVertex3f(-x, y,-z);	// Top Left Of The Quad (Left)
                  glVertex3f(-x,-y,-z);	// Bottom Left Of The Quad (Left)
                  glVertex3f(-x,-y, z);	// Bottom Right Of The Quad (Left)

                  glColor3f(1.0f,0.0f,1.0f);	// Color Violet
                  glVertex3f( x, y,-z);	// Top Right Of The Quad (Right)
                  glVertex3f( x, y, z);	// Top Left Of The Quad (Right)
                  glVertex3f( x,-y, z);	// Bottom Left Of The Quad (Right)
                  glVertex3f( x,-y,-z);	// Bottom Right Of The Quad (Right)

                glEnd();			// End Drawing The Cube
            glPopMatrix();
        }

        void drawBoundingBoxes(){
            for(int i=0; i<numBoundingBoxes; i++){
                boundingboxes[i].drawBoundingBox();
            }
        }

};
