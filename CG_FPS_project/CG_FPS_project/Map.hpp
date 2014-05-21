#ifndef MAP_HPP
#define MAP_HPP

#include <GL/gl.h>
#include "Wall.hpp"
#include "Colors.hpp"
#include "Textures.hpp"

#define NUMWALLS 11

class Map{
    public:

        float mapWidth;
        float mapLength;
        float mapHeight;

        Wall ground;

        Wall walls[NUMWALLS];


        Map(){

            mapWidth = 5; // 50
            mapLength = 10; // 1000
            mapHeight = 1; // 25

            ground.Init(
                -mapWidth/2, 0, -mapLength,   // A
                 mapWidth/2, 0, -mapLength,   // B
                -mapWidth/2, 0, 0,               // C
                 mapWidth/2, 0, 0,               // D
                 1, 0, 0,                           // normal
                 WHITE                          // r g b a
            );



            //-----------------
            //paredes verticais
            walls[0].Init(
                //parede esquerda1
                -mapWidth/2, mapHeight, 0,                         // A
                -mapWidth/2, mapHeight, -mapLength*(0.4f),      // B
                -mapWidth/2, 0, 0,                                   // C
                -mapWidth/2, 0, -mapLength*(0.4f),                // D
                 1, 0, 0,                                               // normal
                 WHITE                                                  // r g b a
            );
            walls[1].Init(
                //vidro esquerda1
                -mapWidth/2, mapHeight, -mapLength*(0.40f),      // A
                -mapWidth/2, mapHeight, -mapLength*(0.45f),      // B
                -mapWidth/2, 0, -mapLength*(0.40f),                // C
                -mapWidth/2, 0, -mapLength*(0.45f),                // D
                 1, 0, 0,                                                // normal
                 VIDRO                                                    // r g b a
            );
            walls[2].Init(
                //parede esquerda2
                -mapWidth/2, mapHeight, -mapLength*(0.45f),      // A
                -mapWidth/2, mapHeight, -mapLength*(0.55f),      // B
                -mapWidth/2, 0, -mapLength*(0.45f),                // C
                -mapWidth/2, 0, -mapLength*(0.55f),                // D
                 1, 0, 0,                                                // normal
                 WHITE                                                    // r g b a
            );
            walls[3].Init(
                //vidro esquerda2
                -mapWidth/2, mapHeight, -mapLength*(0.55f),      // A
                -mapWidth/2, mapHeight, -mapLength*(0.60f),      // B
                -mapWidth/2, 0, -mapLength*(0.55f),                // C
                -mapWidth/2, 0, -mapLength*(0.60f),                // D
                 1, 0, 0,                                                // normal
                 VIDRO                                                    // r g b a
            );
            walls[4].Init(
                //parede esquerda3
                -mapWidth/2, mapHeight, -mapLength*(0.60f),      // top left
                -mapWidth/2, mapHeight, -mapLength,              // top right
                -mapWidth/2, 0, -mapLength*(0.60f),                // bottom left
                -mapWidth/2, 0, -mapLength,                        // bottom right
                 1, 0, 0,                                                // normal
                 WHITE                                                // r g b a
            );
            walls[5].Init(
                //parede esquerda4
                -mapWidth*(0.75f), mapHeight, -mapLength*(0.45f),      // A
                -mapWidth*(0.75f), mapHeight, -mapLength*(0.55f),      // B
                -mapWidth*(0.75f), 0, -mapLength*(0.45f),                // C
                -mapWidth*(0.75f), 0, -mapLength*(0.55f),                // D
                 1, 0, 0,                                                      // normal
                 WHITE                                                         // r g b a
            );
            walls[6].Init(
                //parede esquerda5
                -mapWidth, mapHeight, -mapLength*(0.40f),      // A
                -mapWidth, mapHeight, -mapLength*(0.60f),      // B
                -mapWidth, 0, -mapLength*(0.40f),                // C
                -mapWidth, 0, -mapLength*(0.60f),                // D
                 1, 0, 0,                                              // normal
                 WHITE                                              // r g b a
            );

            //-------------------
            //paredes horizontais
            walls[7].Init(
                //parede esquerda6
                -mapWidth, mapHeight, -mapLength*(0.40f),      // A
                -mapWidth/2, mapHeight, -mapLength*(0.40f),    // B
                -mapWidth, 0, -mapLength*(0.40f),                // C
                -mapWidth/2, 0, -mapLength*(0.40f),              // D
                 1, 0, 0,                                              // normal
                 WHITE                                                  // r g b a
            );
            walls[8].Init(
                //parede esquerda7
                -mapWidth*(0.75f), mapHeight, -mapLength*(0.45f),        // A
                -mapWidth/2, mapHeight, -mapLength*(0.45f),              // B
                -mapWidth*(0.75f), 0, -mapLength*(0.45f),                  // C
                -mapWidth/2, 0, -mapLength*(0.45f),                        // D
                 1, 0, 0,                                                        // normal
                 WHITE                                                         // r g b a
            );
            walls[9].Init(
                //parede esquerda8
                -mapWidth*(0.75f), mapHeight, -mapLength*(0.55f),        // A
                -mapWidth/2, mapHeight, -mapLength*(0.55f),              // B
                -mapWidth*(0.75f), 0, -mapLength*(0.55f),                  // C
                -mapWidth/2, 0, -mapLength*(0.55f),                        // D
                 1, 0, 0,                                                        // normal
                 WHITE                                                         // r g b a
            );
            walls[10].Init(
                //parede esquerda9
                -mapWidth, mapHeight, -mapLength*(0.60f),      // A
                -mapWidth/2, mapHeight, -mapLength*(0.60f),    // B
                -mapWidth, 0, -mapLength*(0.60f),                // C
                -mapWidth/2, 0, -mapLength*(0.60f),              // D
                 1, 0, 0,                                              // normal
                 WHITE                                                  // r g b a
            );

        }

        void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                             GLfloat x2, GLfloat y2, GLfloat z2,
                             GLfloat x3, GLfloat y3, GLfloat z3,
                             GLfloat x4, GLfloat y4, GLfloat z4,
                             GLfloat n1, GLfloat n2, GLfloat n3,
                             GLfloat r, GLfloat g, GLfloat b, GLfloat a,
                             GLuint texture
                             ){

            glEnable(GL_TEXTURE_2D);
            if(texture)
                glBindTexture(GL_TEXTURE_2D, texture);
            glPushMatrix();
                glColor4f(r, g, b, a);
                glBegin(GL_QUADS);

                    glNormal3d(n1, n2, n3);

                    if(texture){
                        glTexCoord2f(0.0f,0.0f);
                        glTexCoord2f(0.0f,10.0f);
                        glTexCoord2f(10.0f,10.0f);
                        glTexCoord2f(0.0f,10.0f);
                    }

                    glVertex3f(x1, y1, z1); // top left
                    glVertex3f(x2, y2, z2); // bottom left
                    glVertex3f(x4, y4, z4); // bottom right
                    glVertex3f(x3, y3, z3); // top right

                glEnd();
            glPopMatrix();
        }

        void drawWalls(){

            //draw left side and right side by symmetry
            for(int i=0; i<NUMWALLS; i++){
                    desenhaQuadrado(
                        walls[i].topLeft[0], walls[i].topLeft[1], walls[i].topLeft[2],
                        walls[i].bottomLeft[0], walls[i].bottomLeft[1], walls[i].bottomLeft[2],
                        walls[i].topRight[0], walls[i].topRight[1], walls[i].topRight[2],
                        walls[i].bottomRight[0], walls[i].bottomRight[1], walls[i].bottomRight[2],

                        walls[i].normal[0], walls[i].normal[1], walls[i].normal[2],
                        walls[i].color[0], walls[i].color[1], walls[i].color[2], walls[i].color[3],
                        0 // no texture
                    );
                    desenhaQuadrado(

                        - walls[i].topLeft[0], walls[i].topLeft[1], walls[i].topLeft[2],
                        - walls[i].bottomLeft[0], walls[i].bottomLeft[1], walls[i].bottomLeft[2],
                        - walls[i].topRight[0], walls[i].topRight[1], walls[i].topRight[2],
                        - walls[i].bottomRight[0], walls[i].bottomRight[1], walls[i].bottomRight[2],

                        walls[i].normal[0], walls[i].normal[1], walls[i].normal[2],
                        walls[i].color[0], walls[i].color[1], walls[i].color[2], walls[i].color[3],
                        0 // no texture
                    );

            }


        }

        void drawMap(){

            //ground
            desenhaQuadrado(

                - ground.topLeft[0], ground.topLeft[1], ground.topLeft[2],
                - ground.bottomLeft[0], ground.bottomLeft[1], ground.bottomLeft[2],
                - ground.topRight[0], ground.topRight[1], ground.topRight[2],
                - ground.bottomRight[0], ground.bottomRight[1], ground.bottomRight[2],

                ground.normal[0], ground.normal[1], ground.normal[2],
                ground.color[0], ground.color[1], ground.color[2], ground.color[3],
                textures.groundTexture() // no texture
            );

            drawWalls();

        }


};

// ------------------------- map
Map map;

#endif

