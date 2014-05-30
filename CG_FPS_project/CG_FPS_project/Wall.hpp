#ifndef WALL_HPP
#define WALL_HPP

#include "Model.hpp"

class Wall{

    public:

        float x, y, z;
        float xScale, yScale, zScale;
        float color[4]; // r g b a
        Model model;

        Wall(){}

        void Init(float xx, float yy, float zz,
             float xs, float ys, float zs,
             float c0, float c1, float c2, float c3,
             const char* filename, const char* texturename){

            x = xx;
            y = yy;
            z = zz;

            xScale = xs;
            yScale = ys;
            zScale = zs;

            color[0] = c0;
            color[1] = c1;
            color[2] = c2;
            color[3] = c3;

            model.Init(filename, texturename);

        }

};

#endif

