#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <IL/config.h>
#include <IL/devil_internal_exports.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <IL/ilut_config.h>
#include <IL/ilu_region.h>
//#include <IL/il_wrap.h>

#define BULLET_SHELL_IMAGE "textures/bullet_shell.png"
#define GROUND_IMAGE "textures/ground_tex.bmp"
#define numImages 3

const char* imageName[] = {BULLET_SHELL_IMAGE, GROUND_IMAGE, BULLET_SHELL_IMAGE};

class Images{

    public:

        // Height and width of textures
        GLsizei imageWidthHeight[numImages][2]; // 0: w, 1: h

        //  Checkerboard texture variables
        #define checkImageWidth 64
        #define checkImageHeight 64
        GLubyte checkImage[checkImageHeight][checkImageWidth][4];

        /* Texture variables */
        GLuint texName[numImages];					//OpenGL texture objects
        ILuint ilTexName[numImages];						//DevIL images objects
        ILubyte *imageData[numImages];                      //DevIL image data

        Images(){
            Init();
        }
        ~Images(){

            // deleting an image.
            for(int i=0; i<numImages; i++){
                ilDeleteImages(1, &ilTexName[i]);
            }
        }

        void Init(){

            // version control
            if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) {
                printf("DevIL version is different...exiting!\n");
                exit(0);
            }


            /*Initialize the DevIL library*/
            ilInit();
            iluInit();
            ilutRenderer(ILUT_OPENGL);

            ilGenImages(numImages, ilTexName);									//Generate DevIL image objects

            // Load textures from files
            for(int i=0; i<numImages; i++){
                loadImage( i );
                setupTexture(i);
            }

        }

        void loadImage(int imageIndex){

            ilBindImage(ilTexName[imageIndex]);                              //Binds the image to a DevIL image object
            ilutGLBindTexImage();                                            //Binds the image object to an OpenGL texture object
            ilLoadImage( imageName[imageIndex] );                            //Loads in brick texture from file
            imageWidthHeight[imageIndex][0] = ilGetInteger(IL_IMAGE_WIDTH);  //Finds the width of the image
            imageWidthHeight[imageIndex][1] = ilGetInteger(IL_IMAGE_HEIGHT); //Finds the height of the image
            imageData[imageIndex] = ilGetData();                             //Get image data from DevIL

        }

        void setupTexture(int imageIndex){

            ilBindImage(ilTexName[imageIndex]);                                 //Binds the image loaded in DevIL to an OpenGL texture
            glBindTexture(GL_TEXTURE_2D, texName[imageIndex]);                  //Binds the texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       //Handles the wrapping properties of the texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       //Handles the wrapping properties of the texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Puts a magnification filter on the texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Puts a minification filter on the texture
            ilutGLTexImage(0);                                                  //Draws the image loaded in DevIL

        }


};

#endif
