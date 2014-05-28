#ifndef WALL_HPP
#define WALL_HPP

class Wall{

    public:

        float topLeft[3];
        float topRight[3];
        float bottomLeft[3];
        float bottomRight[3];
        float normal[3];
        float color[4]; // r g b a

        Wall(){}

        void Init(float tl0, float tl1, float tl2,
             float tr0, float tr1, float tr2,
             float bl0, float bl1, float bl2,
             float br0, float br1, float br2,
             float n0, float n1, float n2,
             float c0, float c1, float c2, float c3){

            topLeft[0] = tl0;
            topLeft[1] = tl1;
            topLeft[2] = tl2;

            topRight[0] = tr0;
            topRight[1] = tr1;
            topRight[2] = tr2;

            bottomLeft[0] = bl0;
            bottomLeft[1] = bl1;
            bottomLeft[2] = bl2;

            bottomRight[0] = br0;
            bottomRight[1] = br1;
            bottomRight[2] = br2;

            normal[0] = n0;
            normal[1] = n1;
            normal[2] = n2;

            color[0] = c0;
            color[1] = c1;
            color[2] = c2;
            color[3] = c3;

        }

};

#endif

