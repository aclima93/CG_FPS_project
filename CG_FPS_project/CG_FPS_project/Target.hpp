#ifndef TARGET_HPP
#define TARGET_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <iostream>
#include "BoundingBox.hpp"
#include "Model.hpp"
#include <vector>

#define NUMTARGETS 21 //10
#define NUMEXTRAS 3 // civillians
#define NUMPOSSIBLE 24
#define NUMBOUNDINGBOXES 6

std::vector< std::vector<float> > possiblePositions(NUMPOSSIBLE, std::vector<float>(4));

class Target{

    public:

        float x, y, z;
        int numBoundingBoxes;
        float w, l, h; // BB and scaling factors
        float rotation;
        float r, g, b;
        float halfW, halfL, halfH;

        BoundingBox boundingBoxes[NUMBOUNDINGBOXES];
        Model model;

        Target(){}
        ~Target(){}

        void Init(float xx, float yy, float zz,
                  float ww, float hh, float ll,
                  int numBB, float posBB[][3], float sizesBB[][3],
                  float rot, float rr, float gg, float bb,
                  const char* objFile, const char* textureFile ){

            x = xx;
            y = yy;
            z = zz;

            //if(rot == 0){
                w = ww;
                h = hh;
                l = ll;

                halfW = 6/2;
                halfH = 16/2;
                halfL = 0.5/2;

            /*}

            else if(rot == 90){
                w = ll;
                h = hh;
                l = ww;

                halfW = 0.5/2;
                halfH = 16/2;
                halfL = 6/2;
            }*/

            rotation = rot;

            r = rr;
            g = gg;
            b = bb;

            numBoundingBoxes = numBB;

            for(int i=0; i<numBoundingBoxes; i++){
                boundingBoxes[i].Init( i, posBB[i][0], posBB[i][1], posBB[i][2], sizesBB[i][0], sizesBB[i][1], sizesBB[i][2], rotation);

            }

            model.Init(objFile, textureFile);

        }

        void drawTarget(){


            glPushMatrix();
                glTranslatef(0, -y, 0);
                model.drawModel(x, y, z, w, h, l, 0/*rotation*/, r, g, b );
            glPopMatrix();

            if(DEBUG_MODE){
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw in wireframe
                glPushMatrix();

                    glBegin(GL_QUADS);	// Draw The Paralellogram Using quads

                        glColor3f(1, 0, 0);	// Color RED

                        glVertex3f(x+ halfW, y+ halfH, z- halfL );	// Top Right Of The Quad (Top)
                        glVertex3f(x- halfW, y+ halfH, z- halfL);	// Top Left Of The Quad (Top)
                        glVertex3f(x- halfW, y+ halfH, z+ halfL);	// Bottom Left Of The Quad (Top)
                        glVertex3f(x+ halfW, y+ halfH, z+ halfL);	// Bottom Right Of The Quad (Top)

                        glVertex3f(x+ halfW, y- halfH, z+ halfL);	// Top Right Of The Quad (Bottom)
                        glVertex3f(x- halfW, y- halfH, z+ halfL);	// Top Left Of The Quad (Bottom)
                        glVertex3f(x- halfW, y- halfH, z- halfL);	// Bottom Left Of The Quad (Bottom)
                        glVertex3f(x+ halfW, y- halfH, z- halfL);	// Bottom Right Of The Quad (Bottom)

                        glVertex3f(x+ halfW, y+ halfH, z+ halfL);	// Top Right Of The Quad (Front)
                        glVertex3f(x- halfW, y+ halfH, z+ halfL);	// Top Left Of The Quad (Front)
                        glVertex3f(x- halfW, y- halfH, z+ halfL);	// Bottom Left Of The Quad (Front)
                        glVertex3f(x+ halfW, y- halfH, z+ halfL);	// Bottom Right Of The Quad (Front)

                        glVertex3f(x+ halfW, y- halfH, z- halfL);	// Top Right Of The Quad (Back)
                        glVertex3f(x- halfW, y- halfH, z- halfL);	// Top Left Of The Quad (Back)
                        glVertex3f(x- halfW, y+ halfH, z- halfL);	// Bottom Left Of The Quad (Back)
                        glVertex3f(x+ halfW, y+ halfH, z- halfL);	// Bottom Right Of The Quad (Back)

                        glVertex3f(x- halfW, y+ halfH, z+ halfL);	// Top Right Of The Quad (Left)
                        glVertex3f(x- halfW, y+ halfH, z- halfL);	// Top Left Of The Quad (Left)
                        glVertex3f(x- halfW, y- halfH, z- halfL);	// Bottom Left Of The Quad (Left)
                        glVertex3f(x- halfW, y- halfH, z+ halfL);	// Bottom Right Of The Quad (Left)

                        glVertex3f(x+ halfW,y+ halfH,z- halfL);	// Top Right Of The Quad (Right)
                        glVertex3f(x+ halfW,y+ halfH,z+ halfL);	// Top Left Of The Quad (Right)
                        glVertex3f(x+ halfW,y- halfH,z+ halfL);	// Bottom Left Of The Quad (Right)
                        glVertex3f(x+ halfW,y- halfH,z- halfL);	// Bottom Right Of The Quad (Right)

                    glEnd();	// End Drawing The Paralellogram


                glPopMatrix();
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

        }

        void drawBoundingBoxes(){


            //glRotatef(rotation, 0, 1, 0);
            //glTranslatef(0, 0, 0);

                for(int i=0; i<numBoundingBoxes; i++){
                    boundingBoxes[i].drawBoundingBox();
                }


        }


        float checkCollision(float ox, float oy, float oz, //origin of ray
                             float dx, float dy, float dz){ // direction of ray

            // AABB = Axis Aligned Bounding Box

            float xFrac = 1.0f / dx;
            float yFrac = 1.0f / dy;
            float zFrac = 1.0f / dz;

            float xMinCorner, yMinCorner, zMinCorner;
            float xMaxCorner, yMaxCorner, zMaxCorner;
            float minDistanceToCorner = FLT_MAX;
            float maxDistanceToCorner = FLT_MIN;

            float distanceToCorner;
            float xCorner, yCorner, zCorner;

            //find the farthest and closest corner of the AABB

            for(float i=-1; i<3; i+=2){
                for(float j=-1; j<3; j+=2){
                    for(float l=-1; l<3; l+=2){

                        xCorner = x + (i*halfW);
                        yCorner = y + (j*halfH);
                        zCorner = z + (l*halfL);

                        distanceToCorner = sqrt(
                                                  (ox-xCorner)*(ox-xCorner)
                                                + (oy-yCorner)*(oy-yCorner)
                                                + (oz-zCorner)*(oz-zCorner)
                                           );

                        if( distanceToCorner < minDistanceToCorner ){
                            minDistanceToCorner = distanceToCorner;
                            xMinCorner = xCorner;
                            yMinCorner = yCorner;
                            zMinCorner = zCorner;
                        }

                        if( distanceToCorner > maxDistanceToCorner ){
                            maxDistanceToCorner = distanceToCorner;
                            xMaxCorner = xCorner;
                            yMaxCorner = yCorner;
                            zMaxCorner = zCorner;
                        }

                    }
                }
            }

            // check for collision (intersection)

            float t1 = (xMinCorner - ox)*xFrac;
            float t2 = (xMaxCorner - ox)*xFrac;
            float t3 = (yMinCorner - oy)*yFrac;
            float t4 = (yMaxCorner - oy)*yFrac;
            float t5 = (zMinCorner - oz)*zFrac;
            float t6 = (zMaxCorner - oz)*zFrac;

            float tmin = std::max( std::max( std::min(t1, t2), std::min( t3, t4)), std::min( t5, t6) );
            float tmax = std::min( std::min( std::max(t1, t2), std::max( t3, t4)), std::max( t5, t6) );

            // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
            if (tmax < 0)
            {
                return -1;
            }

            // if tmin > tmax, ray doesn't intersect AABB
            if (tmin > tmax)
            {
                return -1;
            }

            return tmin;

        }


};

#endif
