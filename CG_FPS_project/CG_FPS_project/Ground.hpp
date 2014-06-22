#ifndef GROUND_HPP
#define GROUND_HPP

class Ground{

    public:

        float centerX, centerZ;
        float width, length;
        float normal[3];
        float color[4]; // r g b a
        float segmentationFactorW, segmentationFactorL;
        float wFactor, lFactor;

        Ground(){}

        void Init(float cx, float cz,
             float w, float l,
             float n0, float n1, float n2,
             float c0, float c1, float c2, float c3,
             float SFW, float SFL){

            centerX = cx;
            centerZ = cz;

            width = w;
            length = l;

            normal[0] = n0;
            normal[1] = n1;
            normal[2] = n2;

            color[0] = c0;
            color[1] = c1;
            color[2] = c2;
            color[3] = c3;

            segmentationFactorW = SFW;
            segmentationFactorL = SFL;

            wFactor = width/SFW;
            lFactor = length/SFL;

        }

};

#endif

