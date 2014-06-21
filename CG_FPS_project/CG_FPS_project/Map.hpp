#ifndef MAP_HPP
#define MAP_HPP

#include <GL/gl.h>

#include "Wall.hpp"
#include "Ground.hpp"
#include "Colors.hpp"
#include "Images.hpp"

#define DEBUG_MODE 1

#define NUMGROUNDS 2

const float mapWidth = 100; // 5
const float mapLength = 500; // 10
const float mapHeight = 25; // 1

#define XSCALE 25
#define YSCALE 25
#define ZSCALE 25
#define wallScale  XSCALE, YSCALE, ZSCALE
#define concreteWallModel "Test\\Wall\\Wall.obj"
#define concreteWallTexture "Test\\Wall\\Wall_texture.bmp"

const float firstGlassStart = 0.40f;
const float firstGlassEnd = 0.45f;

const float secondGlassStart = 0.55f;
const float secondGlassEnd = 0.60f;

const float wWallBB = 15;
const float hWallBB = mapHeight;
const float lWallBB = 4;

// walls and shits

#define numWallParams 14

#define numGlassWalls 2
float glassWalls[][numWallParams] = {
    {
        //vidro esquerda1
        -mapWidth/2, 0, -mapLength*( (firstGlassStart + firstGlassEnd)/2 ),
         XSCALE/4, YSCALE, ZSCALE*2,//wallScale,
         lWallBB/4, hWallBB, wWallBB*2,
         90,
         VIDRO                                                    // r g b a
    },
    {
        //vidro esquerda2
        -mapWidth/2, 0, -mapLength*( (secondGlassStart + secondGlassEnd)/2 ),
         XSCALE/4, YSCALE, ZSCALE*2,//wallScale,
         lWallBB/4, hWallBB, wWallBB*2,
         90,
         VIDRO                                                    // r g b a
    }
};


#define numVerticalWalls 5
float verticalWalls[][numWallParams]= {

    //-----------------
    //paredes verticais
    {
        //parede esquerda1
        -mapWidth/2, 0, -mapLength*(0.2f),
         XSCALE, YSCALE, ZSCALE*14.5,//wallScale,
         lWallBB, hWallBB, wWallBB*13,
         90,
         WHITE                                                  // r g b a
    },
    {
        //parede esquerda2
        -mapWidth/2, 0, -mapLength*(0.5f),
         XSCALE, YSCALE, ZSCALE*3.5,//wallScale,
         lWallBB, hWallBB, wWallBB*3,
         90,
         WHITE                                                    // r g b a
    },
    {
        //parede esquerda3
        -mapWidth/2, 0, -mapLength*(0.8f),
         XSCALE, YSCALE, ZSCALE*14.5,//wallScale,
         lWallBB, hWallBB, wWallBB*13,
         90,
         WHITE                                                // r g b a
    },
    {
        //parede esquerda4
        -mapWidth*(0.75f), 0, -mapLength*(0.5f),
         XSCALE, YSCALE, ZSCALE*3.5,//wallScale,
         lWallBB, hWallBB, wWallBB*3,
         -90,
         WHITE                                                         // r g b a
    },
    {
        //parede esquerda5
        -mapWidth, 0, -mapLength*(0.5f),
         XSCALE, YSCALE, ZSCALE*7.25,//wallScale,
         lWallBB, hWallBB, wWallBB*6,
         90,
         WHITE                                              // r g b a
    }
};

#define numHorizontalWalls 4
float horizontalWalls[][numWallParams] = {

    //-------------------
    //paredes horizontais
    {
        //parede esquerda6
        -(mapWidth + mapWidth/2)/2, 0, -mapLength*(firstGlassStart),
         XSCALE*3.5, YSCALE, ZSCALE,//wallScale,
         wWallBB*3, hWallBB, lWallBB,
         180,
         WHITE                                                  // r g b a
    },
    {
        //parede esquerda7
        -(mapWidth*(0.75f) + mapWidth/2)/2 , 0, -mapLength*(firstGlassEnd),
         XSCALE*1.75, YSCALE, ZSCALE,//wallScale,
         wWallBB*1.25, hWallBB, lWallBB,
         0,
         WHITE                                                         // r g b a
    },
    {
        //parede esquerda8
        -(mapWidth*(0.75f) + mapWidth/2)/2 , 0, -mapLength*(secondGlassStart),
         XSCALE*1.75, YSCALE, ZSCALE,//wallScale,
         wWallBB*1.25, hWallBB, lWallBB,
         180,
         WHITE                                                         // r g b a
    },
    {
        //parede esquerda9
        -(mapWidth + mapWidth/2)/2, 0, -mapLength*(secondGlassEnd),
         XSCALE*3.5, YSCALE, ZSCALE,//wallScale,
         wWallBB*3, hWallBB, lWallBB,
         0,
         WHITE                                                  // r g b a
    }
};

#define NUMWALLS (numGlassWalls+numHorizontalWalls+numVerticalWalls)*2


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


            int wall_i = 0;
            for(int i=0; i<numHorizontalWalls; i++){
                walls[wall_i].Init( horizontalWalls[i][0], horizontalWalls[i][1], horizontalWalls[i][2], horizontalWalls[i][3],
                               horizontalWalls[i][4], horizontalWalls[i][5], horizontalWalls[i][6], horizontalWalls[i][7],
                               horizontalWalls[i][8], horizontalWalls[i][9], horizontalWalls[i][10],
                               horizontalWalls[i][11], horizontalWalls[i][12], horizontalWalls[i][13],
                               concreteWallModel, concreteWallTexture
                        );
                walls[wall_i+1].Init( -horizontalWalls[i][0], horizontalWalls[i][1], horizontalWalls[i][2], horizontalWalls[i][3],
                               horizontalWalls[i][4], horizontalWalls[i][5], horizontalWalls[i][6], horizontalWalls[i][7],
                               horizontalWalls[i][8], -horizontalWalls[i][9], horizontalWalls[i][10],
                               horizontalWalls[i][11], horizontalWalls[i][12], horizontalWalls[i][13],
                               concreteWallModel, concreteWallTexture
                        );
                wall_i+=2;
            }
            for(int j=0; j<numVerticalWalls; j++){
                walls[wall_i].Init( verticalWalls[j][0], verticalWalls[j][1], verticalWalls[j][2], verticalWalls[j][3],
                               verticalWalls[j][4], verticalWalls[j][5], verticalWalls[j][6], verticalWalls[j][7],
                               verticalWalls[j][8], verticalWalls[j][9], verticalWalls[j][10],
                               verticalWalls[j][11], verticalWalls[j][12], verticalWalls[j][13],
                               concreteWallModel, concreteWallTexture);

                walls[wall_i+1].Init( -verticalWalls[j][0], verticalWalls[j][1], verticalWalls[j][2], verticalWalls[j][3],
                               verticalWalls[j][4], verticalWalls[j][5], verticalWalls[j][6], verticalWalls[j][7],
                               verticalWalls[j][8], -verticalWalls[j][9], verticalWalls[j][10],
                               verticalWalls[j][11], verticalWalls[j][12], verticalWalls[j][13],
                               concreteWallModel, concreteWallTexture);
                wall_i+=2;
            }
            for(int k=0; k<numGlassWalls; k++){
                walls[wall_i].Init( glassWalls[k][0], glassWalls[k][1], glassWalls[k][2], glassWalls[k][3],
                               glassWalls[k][4], glassWalls[k][5], glassWalls[k][6], glassWalls[k][7],
                               glassWalls[k][8], glassWalls[k][9], glassWalls[k][10],
                               glassWalls[k][11], glassWalls[k][12], glassWalls[k][13],
                               concreteWallModel, concreteWallTexture );

                walls[wall_i+1].Init( -glassWalls[k][0], glassWalls[k][1], glassWalls[k][2], glassWalls[k][3],
                               glassWalls[k][4], glassWalls[k][5], glassWalls[k][6], glassWalls[k][7],
                               glassWalls[k][8], -glassWalls[k][9], glassWalls[k][10],
                               glassWalls[k][11], glassWalls[k][12], glassWalls[k][13],
                               concreteWallModel, concreteWallTexture );
                wall_i+=2;
            }

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

            for(int i=0; i<NUMWALLS; i++){
                walls[i].model.drawModel( walls[i].x, walls[i].y, walls[i].z,
                                          walls[i].xScale, walls[i].yScale, walls[i].zScale,
                                          walls[i].rotation,
                                          walls[i].color[0], walls[i].color[1], walls[i].color[2] );
            }

        }

        void drawBBWalls(){

            if(DEBUG_MODE){
                for(int i=0; i<NUMWALLS; i++){
                    walls[i].boundingBox.drawBoundingBox();
                }
            }
        }

        void drawMap(){

            drawGround();
            drawWalls();
            drawBBWalls();

        }


};

#endif

