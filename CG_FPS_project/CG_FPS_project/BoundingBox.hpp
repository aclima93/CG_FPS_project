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
        int id;


        BoundingBox(){}

        void Init(int idd, float xx, float yy, float zz, float ww, float ll, float hh){
            id = id;
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

        float checkCollision(float ox, float oy, float oz,  //origin of ray
                             float dx, float dy, float dz){ // direction of ray

            // AABB = Axis Aligned Bounding Box

            float xFrac = 1.0f / dx;
            float yFrac = 1.0f / dy;
            float zFrac = 1.0f / dz;

            // lb is the corner of AABB with minimal coordinates, rt is maximal corner

            /// TODO: ver em tempo real qual é o ponto mais afastado e o mais próximo
            /// (são só quatro pontos e calcular a distância a cada um deles)

            float t1 = (lb.x - ox)*xFrac;
            float t2 = (rt.x - ox)*xFrac;
            float t3 = (lb.y - oy)*yFrac;
            float t4 = (rt.y - oy)*yFrac;
            float t5 = (lb.z - oz)*zFrac;
            float t6 = (rt.z - oz)*zFrac;

            float tmin = max( max( min(t1, t2), min( t3, t4)), min( t5, t6) );
            float tmax = min( min( max(t1, t2), max( t3, t4)), max( t5, t6) );

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
