#ifndef MAP_HPP
#define MAP_HPP

#include <GL/gl.h>

#include "Wall.hpp"
#include "Ground.hpp"
#include "Colors.hpp"
#include "Images.hpp"

#define NUMWALLS 11
#define NUMGROUNDS 2

const float mapWidth = 50; // 5
const float mapLength = 500; // 10
const float mapHeight = 25; // 1

#define wallScale  25, 25, 25
#define concreteWallModel "Test\\concrete_wall.obj"
#define concreteWallTexture "Test\\concrete_wall.bmp"

const float firstGlassStart = 0.40f;
const float firstGlassEnd = 0.45f;

const float secondGlassStart = 0.55f;
const float secondGlassEnd = 0.60f;

class Map{
    public:

        //Textures textures;
        Images image;

        Ground ground[NUMGROUNDS];

        Wall walls[NUMWALLS];


        Map(){

            //chão
            ground[0].Init(
                -mapWidth/2, 0, -mapLength,   // A
                -mapWidth/2, 0, 0,   // B
                 0, 0, -mapLength,               // C
                 0, 0, 0,               // D
                 0, 1, 0,                           // normal
                 VERDE                          // r g b a
            );
            ground[1].Init(
                -mapWidth, 0, -mapLength*(secondGlassEnd),   // A
                -mapWidth, 0, -mapLength*(firstGlassStart),   // B
                -mapWidth/2, 0, -mapLength*(secondGlassEnd),               // C
                -mapWidth/2, 0, -mapLength*(firstGlassStart),               // D
                 0, 1, 0,                           // normal
                 VERDE                          // r g b a
            );


            //-----------------
            //paredes verticais
            walls[0].Init(
                //parede esquerda1
                -mapWidth/2, 0, -mapLength*(firstGlassStart/2),
                 wallScale,
                 90,
                 WHITE,                                                  // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[1].Init(
                //vidro esquerda1
                -mapWidth/2, 0, -mapLength*( (firstGlassStart + firstGlassEnd)/2 ),
                 wallScale,
                 90,
                 VIDRO,                                                    // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[2].Init(
                //parede esquerda2
                -mapWidth/2, 0, -mapLength*( (firstGlassEnd + secondGlassStart)/2 ),
                 wallScale,
                 90,
                 WHITE,                                                    // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[3].Init(
                //vidro esquerda2
                -mapWidth/2, 0, -mapLength*( (secondGlassStart + secondGlassEnd)/2 ),
                 wallScale,
                 90,
                 VIDRO,                                                    // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[4].Init(
                //parede esquerda3
                -mapWidth/2, 0, -mapLength*((mapLength + secondGlassEnd)/2 ),
                 wallScale,
                 90,
                 WHITE,                                                // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[5].Init(
                //parede esquerda4
                -mapWidth*(0.75f), 0, -mapLength*( (firstGlassEnd + secondGlassStart)/2 ),
                 wallScale,
                 -90,
                 WHITE,                                                         // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[6].Init(
                //parede esquerda5
                -mapWidth, 0, -mapLength*( (firstGlassStart + secondGlassEnd)/2 ),
                 wallScale,
                 90,
                 WHITE,                                              // r g b a
                 concreteWallModel, concreteWallTexture
            );

            //-------------------
            //paredes horizontais
            walls[7].Init(
                //parede esquerda6
                -(mapWidth + mapWidth/2)/2, 0, -mapLength*(firstGlassStart),
                 wallScale,
                 180,
                 WHITE,                                                  // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[8].Init(
                //parede esquerda7
                -(mapWidth*(0.75f) + mapWidth/2)/2, 0, -mapLength*(firstGlassEnd),
                 wallScale,
                 0,
                 WHITE,                                                         // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[9].Init(
                //parede esquerda8
                -(mapWidth*(0.75f) + mapWidth/2)/2, 0, -mapLength*(secondGlassStart),
                 wallScale,
                 180,
                 WHITE,                                                         // r g b a
                 concreteWallModel, concreteWallTexture
            );
            walls[10].Init(
                //parede esquerda9
                -(mapWidth + mapWidth/2)/2, 0, -mapLength*(secondGlassEnd),
                 wallScale,
                 0,
                 WHITE,                                                  // r g b a
                 concreteWallModel, concreteWallTexture
            );

        }

        void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                             GLfloat x2, GLfloat y2, GLfloat z2,
                             GLfloat x3, GLfloat y3, GLfloat z3,
                             GLfloat x4, GLfloat y4, GLfloat z4,
                             GLfloat n1, GLfloat n2, GLfloat n3,
                             GLfloat r, GLfloat g, GLfloat b, GLfloat a,
                             int texIndex, int repeat
                             ){

            glEnable(GL_TEXTURE_2D);
            glPushMatrix();

                if(texIndex != -1){
                    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		//Handles how the texture is applied
                    glBindTexture(GL_TEXTURE_2D, image.texName[texIndex]);
                }

                glBegin(GL_QUADS);

                    glColor4f(r, g, b, a);
                    glNormal3d(n1, n2, n3);

                    if(texIndex != -1){

                        glTexCoord2f(0.0f, 0.0f);               glVertex3f(x1, y1, z1); // top left
                        glTexCoord2f(0.0f, repeat*1.0f);        glVertex3f(x2, y2, z2); // bottom left
                        glTexCoord2f(repeat*1.0f, repeat*1.0f); glVertex3f(x4, y4, z4); // bottom right
                        glTexCoord2f(repeat*1.0f, 0.0f);        glVertex3f(x3, y3, z3); // top right
                    }
                    else{
                        glVertex3f(x1, y1, z1); // top left
                        glVertex3f(x2, y2, z2); // bottom left
                        glVertex3f(x4, y4, z4); // bottom right
                        glVertex3f(x3, y3, z3); // top right
                    }


                glEnd();
            glPopMatrix();
        }

        void drawGround(){

            //draw left side and right side by symmetry
            for(int i=0; i<NUMGROUNDS; i++){
                desenhaQuadrado(

                    ground[i].topLeft[0], ground[i].topLeft[1], ground[i].topLeft[2],
                    ground[i].bottomLeft[0], ground[i].bottomLeft[1], ground[i].bottomLeft[2],
                    ground[i].topRight[0], ground[i].topRight[1], ground[i].topRight[2],
                    ground[i].bottomRight[0], ground[i].bottomRight[1], ground[i].bottomRight[2],

                    ground[i].normal[0], ground[i].normal[1], ground[i].normal[2],
                    ground[i].color[0], ground[i].color[1], ground[i].color[2], ground[i].color[3],
                    1, 1 // ground texture
                );
                desenhaQuadrado(
                    - ground[i].topLeft[0], ground[i].topLeft[1], ground[i].topLeft[2],
                    - ground[i].bottomLeft[0], ground[i].bottomLeft[1], ground[i].bottomLeft[2],
                    - ground[i].topRight[0], ground[i].topRight[1], ground[i].topRight[2],
                    - ground[i].bottomRight[0], ground[i].bottomRight[1], ground[i].bottomRight[2],

                    ground[i].normal[0], ground[i].normal[1], ground[i].normal[2],
                    ground[i].color[0], ground[i].color[1], ground[i].color[2], ground[i].color[3],
                    1, 1 // ground texture
                );
            }

        }

        void drawWalls(){

            //draw left side and right side by symmetry
            for(int i=0; i<NUMWALLS; i++){
                walls[i].model.drawModel( walls[i].x, walls[i].y, walls[i].z,
                                          walls[i].xScale, walls[i].yScale, walls[i].zScale,
                                          walls[i].rotation,
                                          walls[i].color[0], walls[i].color[1], walls[i].color[2] );

                walls[i].model.drawModel( -walls[i].x, walls[i].y, walls[i].z,
                                          walls[i].xScale, walls[i].yScale, walls[i].zScale,
                                          -walls[i].rotation,
                                          walls[i].color[0], walls[i].color[1], walls[i].color[2] );

            }


        }

        void drawMap(){

            drawGround();
            drawWalls();

        }


};

#endif

