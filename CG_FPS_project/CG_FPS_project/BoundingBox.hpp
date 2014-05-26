#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <iostream>
#include <algorithm>
#include <math.h>
#include <float.h>

class BoundingBox{

    public:

        float x, y, z;
        float w, l, h;
        float halfW, halfH, halfL;
        int id;


        BoundingBox(){}

        void Init(int idd, float xx, float yy, float zz, float ww, float ll, float hh){
            id = idd;
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

                    glColor3f(1, 0, 1);	// Color Red

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

                glEnd();			// End Drawing The Paralellogram


            glPopMatrix();
        }

        float checkCollision(float ox, float oy, float oz,  //origin of ray
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

            //find the farthest and closes corner of the AABB

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
