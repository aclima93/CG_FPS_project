#ifndef TEXTURES_HPP
#define TEXTURES_HPP


#include <GL/gl.h>
#include <RgbImage.h>

class Textures{
    public:

        GLuint groundTexture(){

            RgbImage  imag;
            GLuint    texture[1];

            glGenTextures(1, &texture[0]);
            glBindTexture(GL_TEXTURE_2D, texture[0]);
            imag.LoadBmpFile("textures/ground_tex.bmp");
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, 3,
                imag.GetNumCols(),
                imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                imag.ImageData()
            );

            return texture[0];
        }

};

#endif
