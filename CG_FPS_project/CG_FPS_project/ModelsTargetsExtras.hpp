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

void createTargetsAndExtras(){

    for(int i=0; i<NUMPOSSIBLE; i++){
        possiblePositions[i][0] = 0;
        possiblePositions[i][1] = 5;
        possiblePositions[i][2] = -i*10 ;

        possibleExtraPositions[i][0] = 0;
        possibleExtraPositions[i][1] = 20;
        possibleExtraPositions[i][2] = -i*10;
    }

    std::vector< std::vector<float> > aux = possiblePositions;
    std::vector< std::vector<float> > aux2 = possibleExtraPositions;

    int pos;
    int numBB = NUMBOUNDINGBOXES;
    float posBB[numBB][3];
    float sizesBB[numBB][3];

    int numBB2 = 1;
    float posBB2[numBB2][3];
    float sizesBB2[numBB2][3];

    float w = 10.0f;
    float h = 10.0f;
    float l = 10.0f;


    for(unsigned int i=0; i<targets.size(); i++){

        srand(time(NULL));
        pos = rand()%aux.size(); // randomly selects one of the available

        posBB[0][0] = aux[pos][0];      posBB[0][1] = aux[pos][1] +2;   posBB[0][2] = aux[pos][2];  // head
        posBB[1][0] = aux[pos][0];      posBB[1][1] = aux[pos][1];      posBB[1][2] = aux[pos][2];  // torso
        posBB[2][0] = aux[pos][0] +2;   posBB[2][1] = aux[pos][1];      posBB[2][2] = aux[pos][2];  // right arm
        posBB[3][0] = aux[pos][0] -2;   posBB[3][1] = aux[pos][1];      posBB[3][2] = aux[pos][2];  // left arm
        posBB[4][0] = aux[pos][0] +1;   posBB[4][1] = aux[pos][1] -2;   posBB[4][2] = aux[pos][2];  // right leg
        posBB[5][0] = aux[pos][0] -1;   posBB[5][1] = aux[pos][1] -2;   posBB[5][2] = aux[pos][2];  // left leg


        sizesBB[0][0] = 2.0f;   sizesBB[0][1] = 2.0f;  sizesBB[0][2] = 2.0f;  // head
        sizesBB[1][0] = 2.0f;   sizesBB[1][1] = 2.0f;  sizesBB[1][2] = 2.0f;  // torso
        sizesBB[2][0] = 2.0f;   sizesBB[2][1] = 2.0f;  sizesBB[2][2] = 2.0f;  // right arm
        sizesBB[3][0] = 2.0f;   sizesBB[3][1] = 2.0f;  sizesBB[3][2] = 2.0f;  // left arm
        sizesBB[4][0] = 2.0f;   sizesBB[4][1] = 2.0f;  sizesBB[4][2] = 2.0f;  // right leg
        sizesBB[5][0] = 2.0f;   sizesBB[5][1] = 2.0f;  sizesBB[5][2] = 2.0f;  // left leg


        targets[i].Init( aux[pos][0], aux[pos][1], aux[pos][2], w, h, l, numBB, posBB, sizesBB);
        aux.erase( aux.begin()+ pos );

    }

    for(unsigned int i=0; i<extras.size(); i++){

        srand(time(NULL));
        pos = rand()%aux2.size(); // randomly selects one of the available

        posBB2[0][0] = aux2[pos][0];     posBB2[0][1] = aux2[pos][1];  posBB2[0][2] = aux2[pos][2];  // head
        sizesBB2[0][0] = 2.0f;   sizesBB2[0][1] = 2.0f;  sizesBB2[0][2] = 2.0f;  // head

        extras[i].Init( aux2[pos][0], aux2[pos][1], aux2[pos][2], w, h, l, numBB2, posBB2, sizesBB2);
        aux2.erase( aux2.begin()+ pos );
    }

}

void createModels(){
    for(int i=0; i<NUMMODELS; i++){
        models[i].Init( "Test\\test.obj", "Test\\grass_tex.bmp", -5, 0, -i-5, 1, 1, 1 );
    }
}

void drawModels(){
    for(int i=0; i<NUMMODELS; i++){
        models[i].drawModel();
    }
}

void createWalls(){
    for(int i=0; i<NUMMODELS*2; i++){
       walls[i].Init( "Test\\concrete_wall.obj", "Test\\concrete_wall.bmp", -20, 0, -i*2 -15, 20, 20, 20 );
    }
}

void drawWalls(){
    for(int i=0; i<NUMMODELS*2; i++){
        walls[i].drawModel();
    }
}

void drawBullets(){

    for(int i=0; i<NUMBULLETS; i++){
        bullets[i].draw();
    }
}
