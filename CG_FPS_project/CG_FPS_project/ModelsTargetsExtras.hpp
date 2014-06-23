void drawExtras(){
    for(unsigned int i=0; i<extras.size(); i++){
        extras[i].drawTarget();
        extras[i].drawBoundingBoxes();
    }
}

void drawTargets(){
    for(unsigned int i=0; i<targets.size(); i++){
        targets[i].drawTarget();
        targets[i].drawBoundingBoxes();
    }
}

#define TARGET_HEIGHT 8

void initPositions(){

    // position 1
    possiblePositions[0][0] = -mapWidth*(0.375f); // -0.125
    possiblePositions[0][1] = TARGET_HEIGHT;
    possiblePositions[0][2] = -mapLength*(0.1625f); // +0.0125
    possiblePositions[0][3] = 0;

    possiblePositions[1][0] = -mapWidth*(0.475f); // -0.015
    possiblePositions[1][1] = TARGET_HEIGHT;
    possiblePositions[1][2] = -mapLength*(0.175f); // +0.025
    possiblePositions[1][3] = 90;

    // position 2
    possiblePositions[2][0] = -mapWidth*(0.875f);
    possiblePositions[2][1] = TARGET_HEIGHT;
    possiblePositions[2][2] = -mapLength*(0.4125f);
    possiblePositions[2][3] = 0;

    possiblePositions[3][0] = -mapWidth*(0.985f);
    possiblePositions[3][1] = TARGET_HEIGHT;
    possiblePositions[3][2] = -mapLength*(0.425f);
    possiblePositions[3][3] = 90;

    // position 3
    possiblePositions[4][0] = -mapWidth*(0.125f);
    possiblePositions[4][1] = TARGET_HEIGHT;
    possiblePositions[4][2] = -mapLength*(0.3625f);
    possiblePositions[4][3] = 0;

    possiblePositions[5][0] = -mapWidth*(0.025f);
    possiblePositions[5][1] = TARGET_HEIGHT;
    possiblePositions[5][2] = -mapLength*(0.375f);
    possiblePositions[5][3] = 90;

    // position 4
    possiblePositions[6][0] = -mapWidth*(0.875f);
    possiblePositions[6][1] = TARGET_HEIGHT;
    possiblePositions[6][2] = -mapLength*(0.5875f);
    possiblePositions[6][3] = 0;

    possiblePositions[7][0] = -mapWidth*(0.975f);
    possiblePositions[7][1] = TARGET_HEIGHT;
    possiblePositions[7][2] = -mapLength*(0.575f);
    possiblePositions[7][3] = 90;

    // position 5
    possiblePositions[8][0] = -mapWidth*(0.125f);
    possiblePositions[8][1] = TARGET_HEIGHT;
    possiblePositions[8][2] = -mapLength*(0.6625f);
    possiblePositions[8][3] = 0;

    possiblePositions[9][0] = -mapWidth*(0.025f);
    possiblePositions[9][1] = TARGET_HEIGHT;
    possiblePositions[9][2] = -mapLength*(0.675f);
    possiblePositions[9][3] = 90;

    // position 6
    possiblePositions[10][0] = -mapWidth*(0.375f);
    possiblePositions[10][1] = TARGET_HEIGHT;
    possiblePositions[10][2] = -mapLength*(0.8625f);
    possiblePositions[10][3] = 0;

    possiblePositions[11][0] = -mapWidth*(0.475f);
    possiblePositions[11][1] = TARGET_HEIGHT;
    possiblePositions[11][2] = -mapLength*(0.875f);
    possiblePositions[11][3] = 90;

    //do the other side by symmetry
    int half = NUMPOSSIBLE/2;
    for(int i=half; i<NUMPOSSIBLE; i++){
        possiblePositions[i][0] = - possiblePositions[i-half][0];
        possiblePositions[i][1] =   possiblePositions[i-half][1];
        possiblePositions[i][2] =   possiblePositions[i-half][2];
        possiblePositions[i][3] =   possiblePositions[i-half][3];
    }

}


#define CAMO_CITY_TEXTURE "Test\\Camo3\\Camo3.bmp"
#define CAMO_CITY_OBJ "Test\\Camo3\\camo3.obj"

#define CAMO_JUNGLE_TEXTURE "Test\\Camo2\\Camo-Wallpaper-Picture.bmp"
#define CAMO_JUNGLE_OBJ "Test\\Camo2\\camo2.obj"

#define CAMO_SNOW_TEXTURE "Test\\Camo1\\Camo-Wallpaper.bmp"
#define CAMO_SNOW_OBJ "Test\\Camo1\\camo1.obj"

#define lol1 "Test\\test.obj"
#define lol2 "Test\\Wall\\Wall_texture.bmp"

void createTargetsAndExtras(){


    initPositions();


    std::vector< std::vector<float> > aux = possiblePositions;

    int pos;
    int numBB = NUMBOUNDINGBOXES;
    float posBB[numBB][3];
    float sizesBB[numBB][3];

    float scaleX = 4.0f;
    float scaleY = 4.0f;
    float scaleZ = 4.0f;

    float rotation;

    float numSnow = 0;
    float numJungle = 0;
    float numCity = 0;
    float numPerTarget = targets.size()/3;


    for(unsigned int i=0; i<targets.size(); i++){

        srand(time(NULL));
        pos = rand()%aux.size(); // randomly selects one of the available positions

        posBB[0][0] = aux[pos][0];      posBB[0][1] = aux[pos][1] +6.1;   posBB[0][2] = aux[pos][2];  // head
        posBB[1][0] = aux[pos][0];      posBB[1][1] = aux[pos][1] +1.5;      posBB[1][2] = aux[pos][2];  // torso
        posBB[2][0] = aux[pos][0] +2.2;   posBB[2][1] = aux[pos][1] +2;      posBB[2][2] = aux[pos][2];  // right arm
        posBB[3][0] = aux[pos][0] -2.2;   posBB[3][1] = aux[pos][1] +2;      posBB[3][2] = aux[pos][2];  // left arm
        posBB[4][0] = aux[pos][0] +0.75;   posBB[4][1] = aux[pos][1] -4.4;   posBB[4][2] = aux[pos][2];  // right leg
        posBB[5][0] = aux[pos][0] -0.75;   posBB[5][1] = aux[pos][1] -4.4;   posBB[5][2] = aux[pos][2];  // left leg


        sizesBB[0][0] = 2.7f;   sizesBB[0][1] = 0.5f;  sizesBB[0][2] = 2.9f;  // head
        sizesBB[1][0] = 3.5f;   sizesBB[1][1] = 0.5f;  sizesBB[1][2] = 6.25f;  // torso
        sizesBB[2][0] = 1.0f;   sizesBB[2][1] = 0.5f;  sizesBB[2][2] = 5.3f;  // right arm
        sizesBB[3][0] = 1.0f;   sizesBB[3][1] = 0.5f;  sizesBB[3][2] = 5.3f;  // left arm
        sizesBB[4][0] = 1.5f;   sizesBB[4][1] = 0.5f;  sizesBB[4][2] = 5.5f;  // right leg
        sizesBB[5][0] = 1.5f;   sizesBB[5][1] = 0.5f;  sizesBB[5][2] = 5.5f;  // left leg

        rotation = aux[pos][3];

        if( numSnow < numPerTarget){
            targets[i].Init( aux[pos][0], aux[pos][1], aux[pos][2], scaleX, scaleY, scaleZ, numBB, posBB, sizesBB, rotation, 1, 1, 1, CAMO_SNOW_OBJ, CAMO_SNOW_TEXTURE);
            numSnow++;
        }
        else if( numCity < numPerTarget){
            targets[i].Init( aux[pos][0], aux[pos][1], aux[pos][2], scaleX, scaleY, scaleZ, numBB, posBB, sizesBB, rotation, 1, 1, 1, CAMO_CITY_OBJ, CAMO_CITY_TEXTURE);
            numCity++;
        }
        else{
            targets[i].Init( aux[pos][0], aux[pos][1], aux[pos][2], scaleX, scaleY, scaleZ, numBB, posBB, sizesBB, rotation, 1, 1, 1, CAMO_JUNGLE_OBJ, CAMO_JUNGLE_TEXTURE);
            numJungle++;
        }

        aux.erase( aux.begin()+ pos );

    }

    for(unsigned int i=0; i<extras.size(); i++){

        srand(time(NULL));
        pos = rand()%aux.size(); // randomly selects one of the available positions

        posBB[0][0] = aux[pos][0];      posBB[0][1] = aux[pos][1] +6.1;   posBB[0][2] = aux[pos][2];  // head
        posBB[1][0] = aux[pos][0];      posBB[1][1] = aux[pos][1] +1.5;      posBB[1][2] = aux[pos][2];  // torso
        posBB[2][0] = aux[pos][0] +2.2;   posBB[2][1] = aux[pos][1] +2;      posBB[2][2] = aux[pos][2];  // right arm
        posBB[3][0] = aux[pos][0] -2.2;   posBB[3][1] = aux[pos][1] +2;      posBB[3][2] = aux[pos][2];  // left arm
        posBB[4][0] = aux[pos][0] +0.75;   posBB[4][1] = aux[pos][1] -4.4;   posBB[4][2] = aux[pos][2];  // right leg
        posBB[5][0] = aux[pos][0] -0.75;   posBB[5][1] = aux[pos][1] -4.4;   posBB[5][2] = aux[pos][2];  // left leg


        sizesBB[0][0] = 2.7f;   sizesBB[0][1] = 0.5f;  sizesBB[0][2] = 2.9f;  // head
        sizesBB[1][0] = 3.5f;   sizesBB[1][1] = 0.5f;  sizesBB[1][2] = 6.25f;  // torso
        sizesBB[2][0] = 1.0f;   sizesBB[2][1] = 0.5f;  sizesBB[2][2] = 5.3f;  // right arm
        sizesBB[3][0] = 1.0f;   sizesBB[3][1] = 0.5f;  sizesBB[3][2] = 5.3f;  // left arm
        sizesBB[4][0] = 1.5f;   sizesBB[4][1] = 0.5f;  sizesBB[4][2] = 5.5f;  // right leg
        sizesBB[5][0] = 1.5f;   sizesBB[5][1] = 0.5f;  sizesBB[5][2] = 5.5f;  // left leg

        rotation = aux[pos][3];

        extras[i].Init( aux[pos][0], aux[pos][1], aux[pos][2], scaleX, scaleY, scaleZ, numBB, posBB, sizesBB, rotation, 1, 1, 1, lol1, lol2);
        aux.erase( aux.begin()+ pos );
    }

}


void drawBullets(){

    for(int i=0; i<NUMBULLETS; i++){
        bullets[i].draw();
    }
}
