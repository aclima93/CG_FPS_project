#ifndef MAP_HPP
#define MAP_HPP

#include <GL/gl.h>

#include "Wall.hpp"
#include "Ground.hpp"
#include "Colors.hpp"
#include <string.h>

#define NUMGROUNDS 4

const float mapWidth = 100; // 5
const float mapLength = 500; // 10
const float mapHeight = 25; // 1

#define XSCALE 7.5f
#define YSCALE 20
#define ZSCALE 45
#define wallScale XSCALE, YSCALE, ZSCALE
#define concreteWallModel "Test\\Wall\\Wall.obj"
#define concreteWallTexture "Test\\Wall\\Wall_texture.bmp"
#define groundTexture "textures\\ground_tex.bmp"


GLuint textureMap[1];
RgbImage imagMap;

const float firstGlassStart = 0.40f;
const float firstGlassEnd = 0.45f;

const float secondGlassStart = 0.55f;
const float secondGlassEnd = 0.60f;

const float wWallBB = 15;
const float hWallBB = mapHeight;
const float lWallBB = 4;


#define numWallParams 14

#define numGlassWalls 2
float glassWalls[][numWallParams] = {
    {
        //vidro esquerda1
        -mapWidth/2, mapHeight/2, -mapLength*( (firstGlassStart + firstGlassEnd)/2 ),
         XSCALE/4, YSCALE, ZSCALE*2,//wallScale,
         wWallBB*2, hWallBB, lWallBB/4,
         0,
         VIDRO // r g b a
    },
    {
        //vidro esquerda2
        -mapWidth/2, mapHeight/2, -mapLength*( (secondGlassStart + secondGlassEnd)/2 ),
         XSCALE/4, YSCALE, ZSCALE*2,//wallScale,
         wWallBB*2, hWallBB, lWallBB/4,
         0,
         VIDRO // r g b a
    }
};


#define numMiddleWalls 4
float middleWalls[][numWallParams]= {

    //-----------------
    //paredes verticais no centro
    {
        //parede central1
        0, 0, -mapLength*(0.375f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5f, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede central2
        0, 0, -mapLength*(0.425f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5f, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede central3
        0, 0, -mapLength*(0.675f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5f, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede central4
        0, 0, -mapLength*(0.725f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5f, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    }
};

#define numVerticalWalls 24
float verticalWalls[][numWallParams]= {

    //-----------------
    //paredes verticais
    {
        //parede esquerda1.1
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.0625f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda1.2
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.1875f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda1.3
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.3125f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda1.4
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.4375f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda1.5
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.5625f),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda1.6
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.6875f),
         XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda1.7
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.8125f),
         XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda1.8
        -mapWidth/2, 0, -mapLength*(0.4f)*(0.9375f),
         XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda2.1
        -mapWidth/2, 0, -mapLength*(0.475f),
         XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda2.2
        -mapWidth/2, 0, -mapLength*(0.525f),
         XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.1
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.0625f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.2
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.1875f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.3
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.3125f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.4
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.4375f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.5
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.5625f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.6
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.6875f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.7
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.8125f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda3.8
        -mapWidth/2, 0, -(mapLength*(0.6f) + mapLength*(0.4f)*(0.9375f)),
        XSCALE, YSCALE, ZSCALE*1.75f,//wallScale,
        wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda4.1
        -mapWidth*(0.75f), 0, -mapLength*(0.475f),
         XSCALE, YSCALE, ZSCALE*1.75,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         -0,
         WHITE // r g b a
    },
    {
        //parede esquerda4.2
        -mapWidth*(0.75f), 0, -mapLength*(0.525f),
         XSCALE, YSCALE, ZSCALE*1.75,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         -0,
         WHITE // r g b a
    },
    {
        //parede esquerda5.1
        -mapWidth, 0, -mapLength*(0.425f),
         XSCALE, YSCALE, ZSCALE*1.75,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda5.2
        -mapWidth, 0, -mapLength*(0.475f),
         XSCALE, YSCALE, ZSCALE*1.75,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda5.3
        -mapWidth, 0, -mapLength*(0.525f),
         XSCALE, YSCALE, ZSCALE*1.75,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    },
    {
        //parede esquerda5.4
        -mapWidth, 0, -mapLength*(0.575f),
         XSCALE, YSCALE, ZSCALE*1.75,//wallScale,
         wWallBB*1.5, hWallBB, lWallBB,
         0,
         WHITE // r g b a
    }
};

#define numHorizontalWalls 14
float horizontalWalls[][numWallParams] = {

    //-------------------
    //paredes horizontais
    {
        //parede esquerda6.1
        -mapWidth*(0.625f), 0, -mapLength*(firstGlassStart),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         -90,
         WHITE // r g b a
    },
    {
        //parede esquerda6.2
        -mapWidth*(0.875f), 0, -mapLength*(firstGlassStart),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         -90,
         WHITE // r g b a
    },
    {
        //parede esquerda7
        -(mapWidth*(0.75f) + mapWidth/2)/2 , 0, -mapLength*(firstGlassEnd),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda8
        -(mapWidth*(0.75f) + mapWidth/2)/2 , 0, -mapLength*(secondGlassStart),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         -90,
         WHITE // r g b a
    },
    {
        //parede esquerda9.1
        -mapWidth*(0.625f), 0, -mapLength*(secondGlassEnd),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda9.2
        -mapWidth*(0.875f), 0, -mapLength*(secondGlassEnd),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },

    // --------------------------------------
    // --------------------------------------
    // --------------------------------------

    {
        //parede esquerda10.1
        -mapWidth*(0.125f), 0, 0,
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda10.2
        -mapWidth*(0.375f), 0, 0,
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda11.1
        -mapWidth*(0.375f), 0, -mapLength*(0.15f),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda11.2
        -mapWidth*(0.125f), 0, -mapLength*(0.35f),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda12.1
        -mapWidth*(0.125f), 0, -mapLength*(0.65f),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda12.2
        -mapWidth*(0.375f), 0, -mapLength*(0.85f),
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda13.1
        -mapWidth*(0.125f), 0, -mapLength,
        ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
        lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    },
    {
        //parede esquerda13.2
        -mapWidth*(0.375f), 0, -mapLength,
         ZSCALE*1.75, YSCALE, XSCALE,//wallScale,
         lWallBB*1.5, hWallBB, wWallBB,
         90,
         WHITE // r g b a
    }
};

#define NUMWALLS numMiddleWalls+(numHorizontalWalls+numVerticalWalls)*2
#define NUMGLASS numGlassWalls*2
#define factor 50

class Map{
    public:

        Ground ground[NUMGROUNDS];

        Wall walls[NUMWALLS];
        Wall glass[NUMGLASS];
        bool isGlassActive[NUMGLASS];



        Map(){}

        void Init(){

            //chão
            ground[0].Init(
                -mapWidth/4, -mapLength/2, //center
                 mapWidth/2, mapLength, // w, l
                 0, 1, 0, // normal
                 WHITE, // r g b a
                 factor/2, factor*2
            );
            ground[1].Init(
                -mapWidth*(0.75f), -mapLength/2, //center
                 mapWidth/2, mapLength*(0.2f), // w, l
                 0, 1, 0, // normal
                 WHITE, // r g b a
                 factor/2, factor*2
            );
            ground[2].Init(
                 mapWidth/4, -mapLength/2, //center
                 mapWidth/2, mapLength, // w, l
                 0, 1, 0, // normal
                 WHITE, // r g b a
                 factor/2, factor*2
            );
            ground[3].Init(
                 mapWidth*(0.75f), -mapLength/2, //center
                 mapWidth/2, mapLength*(0.2f), // w, l
                 0, 1, 0, // normal
                 WHITE, // r g b a
                 factor/2, factor*2
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
            for(int l=0; l<numMiddleWalls; l++){
                walls[wall_i].Init( middleWalls[l][0], middleWalls[l][1], middleWalls[l][2], middleWalls[l][3],
                               middleWalls[l][4], middleWalls[l][5], middleWalls[l][6], middleWalls[l][7],
                               middleWalls[l][8], middleWalls[l][9], middleWalls[l][10],
                               middleWalls[l][11], middleWalls[l][12], middleWalls[l][13],
                               concreteWallModel, concreteWallTexture);
                wall_i++;
            }

            int glassWall_i = 0;
            for(int k=0; k<numGlassWalls; k++){
                glass[glassWall_i].Init( glassWalls[k][0], glassWalls[k][1], glassWalls[k][2], glassWalls[k][3],
                               glassWalls[k][4], glassWalls[k][5], glassWalls[k][6], glassWalls[k][7],
                               glassWalls[k][8], glassWalls[k][9], glassWalls[k][10],
                               glassWalls[k][11], glassWalls[k][12], glassWalls[k][13],
                               concreteWallModel, concreteWallTexture );

                glass[glassWall_i+1].Init( -glassWalls[k][0], glassWalls[k][1], glassWalls[k][2], glassWalls[k][3],
                               glassWalls[k][4], glassWalls[k][5], glassWalls[k][6], glassWalls[k][7],
                               glassWalls[k][8], -glassWalls[k][9], glassWalls[k][10],
                               glassWalls[k][11], glassWalls[k][12], glassWalls[k][13],
                               concreteWallModel, concreteWallTexture );
                glassWall_i+=2;
            }

        }

        void createTexture(){
            glGenTextures(1, &textureMap[0]);
            glBindTexture(GL_TEXTURE_2D, textureMap[0]);
            imagMap.LoadBmpFile(groundTexture); /* Passar a string para const char em C */
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexImage2D(GL_TEXTURE_2D, 0, 3,
                imagMap.GetNumCols(),
                imagMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                imagMap.ImageData());
        }

        void desenhaQuadrado(GLfloat x1, GLfloat y1, GLfloat z1,
                             GLfloat x2, GLfloat y2, GLfloat z2,
                             GLfloat x3, GLfloat y3, GLfloat z3,
                             GLfloat x4, GLfloat y4, GLfloat z4,
                             GLfloat n1, GLfloat n2, GLfloat n3,
                             GLfloat r, GLfloat g, GLfloat b, GLfloat a
                             ){

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureMap[0]);
            glPushMatrix();

                glBegin(GL_QUADS);

                    glColor4f(r, g, b, a);
                    glNormal3d(n1, n2, n3);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z1); // top left
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x2, y2, z2); // bottom left
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x4, y4, z4); // bottom right
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x3, y3, z3); // top right


                glEnd();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        }

        void drawGround(){


            float halfW, halfL;
            float limitX, limitZ, startX, startZ;


            for(int i=0; i<NUMGROUNDS; i++){

                halfW = ground[i].wFactor/2;
                halfL = ground[i].lFactor/2;
                int counter = 0;
                limitX = ground[i].centerX + ground[i].width/2 ;//- ground[i].wFactor;
                limitZ = ground[i].centerZ + ground[i].length/2 ;//- ground[i].lFactor;

                startZ = ground[i].centerZ - ground[i].length/2 + ground[i].lFactor;
                startX = ground[i].centerX - ground[i].width/2 + ground[i].wFactor;

                for(int cz = startZ; cz <= limitZ; cz += ground[i].lFactor ){

                    for(int cx = startX; cx <= limitX; cx += ground[i].wFactor ){

                        desenhaQuadrado(
                            cx - halfW, 0, cz + halfL,
                            cx - halfW, 0, cz - halfL,
                            cx + halfW, 0, cz + halfL,
                            cx + halfW, 0, cz - halfL,
                            ground[i].normal[0], ground[i].normal[1], ground[i].normal[2],
                            ground[i].color[0], ground[i].color[1], ground[i].color[2], ground[i].color[3]
                        );

                        counter++;

                    }
                }
            }

        }

        void drawWalls(){

            for(int i=0; i<NUMWALLS; i++){
                walls[i].model.drawModel( walls[i].x, walls[i].y, walls[i].z,
                                          walls[i].xScale, walls[i].yScale, walls[i].zScale,
                                          walls[i].rotation,
                                          walls[i].color[0], walls[i].color[1], walls[i].color[2] );

                if(DEBUG_MODE){
                    walls[i].boundingBox.drawBoundingBox();
                }
            }
        }

        void drawGlass(){

            for(int i=0; i<NUMGLASS; i++){

                float halfW = 0.1;
                float halfH = mapHeight/2;
                float halfL = mapLength*(0.05)/2;

                if( isGlassActive[i] ){


                    glEnable(GL_BLEND); /* Activar BLEND */
                    /* GL_SRC_ALPHA: define para o peso da cor do objecto a desenhar o valor do alfa da sua cor
                     * GL_ONE_MINUS_SRC_ALPHA: define para o peso da cor que já está desenhado no ecran é de (1 - alfa),
                     * onde alfa é o nível de transparência do objecto que está a ser desenhado */
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    /* Desenhar o quadrado em si */
                    glBegin (GL_QUADS);

                        glColor4f(VIDRO); // Defenir o nível de transparencia do vidro
                        glEnable(GL_DEPTH_TEST); // Ativar o teste de profundidade (z-buffer)

                        glNormal3f(0.0f, 0.0f, 0.0f);

                        glVertex3f(glass[i].x+ halfW, glass[i].y+ halfH, glass[i].z- halfL );	// Top Right Of The Quad (Top)
                        glVertex3f(glass[i].x- halfW, glass[i].y+ halfH, glass[i].z- halfL);	// Top Left Of The Quad (Top)
                        glVertex3f(glass[i].x- halfW, glass[i].y+ halfH, glass[i].z+ halfL);	// Bottom Left Of The Quad (Top)
                        glVertex3f(glass[i].x+ halfW, glass[i].y+ halfH, glass[i].z+ halfL);	// Bottom Right Of The Quad (Top)

                        glVertex3f(glass[i].x+ halfW, glass[i].y- halfH, glass[i].z+ halfL);	// Top Right Of The Quad (Bottom)
                        glVertex3f(glass[i].x- halfW, glass[i].y- halfH, glass[i].z+ halfL);	// Top Left Of The Quad (Bottom)
                        glVertex3f(glass[i].x- halfW, glass[i].y- halfH, glass[i].z- halfL);	// Bottom Left Of The Quad (Bottom)
                        glVertex3f(glass[i].x+ halfW, glass[i].y- halfH, glass[i].z- halfL);	// Bottom Right Of The Quad (Bottom)

                        glVertex3f(glass[i].x+ halfW, glass[i].y+ halfH, glass[i].z+ halfL);	// Top Right Of The Quad (Front)
                        glVertex3f(glass[i].x- halfW, glass[i].y+ halfH, glass[i].z+ halfL);	// Top Left Of The Quad (Front)
                        glVertex3f(glass[i].x- halfW, glass[i].y- halfH, glass[i].z+ halfL);	// Bottom Left Of The Quad (Front)
                        glVertex3f(glass[i].x+ halfW, glass[i].y- halfH, glass[i].z+ halfL);	// Bottom Right Of The Quad (Front)

                        glVertex3f(glass[i].x+ halfW, glass[i].y- halfH, glass[i].z- halfL);	// Top Right Of The Quad (Back)
                        glVertex3f(glass[i].x- halfW, glass[i].y- halfH, glass[i].z- halfL);	// Top Left Of The Quad (Back)
                        glVertex3f(glass[i].x- halfW, glass[i].y+ halfH, glass[i].z- halfL);	// Bottom Left Of The Quad (Back)
                        glVertex3f(glass[i].x+ halfW, glass[i].y+ halfH, glass[i].z- halfL);	// Bottom Right Of The Quad (Back)

                        glVertex3f(glass[i].x- halfW, glass[i].y+ halfH, glass[i].z+ halfL);	// Top Right Of The Quad (Left)
                        glVertex3f(glass[i].x- halfW, glass[i].y+ halfH, glass[i].z- halfL);	// Top Left Of The Quad (Left)
                        glVertex3f(glass[i].x- halfW, glass[i].y- halfH, glass[i].z- halfL);	// Bottom Left Of The Quad (Left)
                        glVertex3f(glass[i].x- halfW, glass[i].y- halfH, glass[i].z+ halfL);	// Bottom Right Of The Quad (Left)

                        glVertex3f(glass[i].x+ halfW, glass[i].y+ halfH, glass[i].z- halfL);	// Top Right Of The Quad (Right)
                        glVertex3f(glass[i].x+ halfW, glass[i].y+ halfH, glass[i].z+ halfL);	// Top Left Of The Quad (Right)
                        glVertex3f(glass[i].x+ halfW, glass[i].y- halfH, glass[i].z+ halfL);	// Bottom Left Of The Quad (Right)
                        glVertex3f(glass[i].x+ halfW, glass[i].y- halfH, glass[i].z- halfL);	// Bottom Right Of The Quad (Right)
                    glEnd();

                    glDisable(GL_BLEND); /* Desactivar o BLEND */



                    if(DEBUG_MODE){
                        glass[i].boundingBox.drawBoundingBox();
                    }

                }

            }
        }


        void drawMap(){

            drawGround();

            drawWalls();
            drawGlass();

        }

};

#endif
