#ifndef TARGET_HPP
#define TARGET_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <iostream>
#include "BoundingBox.hpp"
#include <vector>

#define NUMTARGETS 10
#define NUMEXTRAS 3 // balloons
#define NUMPOSSIBLE 50

std::vector< std::vector<float> > possiblePositions(NUMPOSSIBLE, std::vector<float>(3));

class Target{

    public:

        float x, y, z;
        int numBoundingBoxes;
        int w, l, h; // to be used?

        std::vector< BoundingBox> boundingBoxes; // array de bounding boxes para detectar as collisions

        Target(){}
        ~Target(){
            //TODO: delete the boundingboxes
            boundingBoxes.clear ();
        }

        void Init(float xx, float yy, float zz, int numBB, float **posBB){

            x = xx;
            y = yy;
            z = zz;

            numBoundingBoxes = numBB;
            boundingBoxes.resize( numBB, BoundingBox() );

            for(int i=0; i<numBB; i++){
                //boundingBoxes[i].Init( posBB[i][0], posBB[i][1], posBB[i][2] );
            }
        }

        void drawTarget(){

            glPushMatrix();
                glTranslatef( x, y, z);
                glColor3f (1, 0, 0);
                glutWireCube(1);

                /*
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
                */

            glPopMatrix();
        }

        void drawBoundingBoxes(){
            for(int i=0; i<numBoundingBoxes; i++){
                boundingBoxes[i].drawBoundingBox();
            }
        }

};

#endif
