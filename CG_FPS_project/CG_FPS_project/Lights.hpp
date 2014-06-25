//……………………………………………………………………………………………………………………………………………………… Iluminacao
void initLights(void){

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE); //Have OpenGL automatically normalize our normals


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //Iluminacao global
    if( dayTime){
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
    }
    if( nightTime){

        /*
        for(int i=1; i<=numLights; i++){
        //int i=0;

            glEnable(GL_LIGHT0+i);
            GLfloat position [] = {extras[i].x, extras[i].y, extras[i].z, 1};

            glLightfv(GL_LIGHT0+i, GL_AMBIENT, light_ambient[i]);
            glLightfv(GL_LIGHT0+i, GL_DIFFUSE, light_diffuse[i]);
            glLightfv(GL_LIGHT0+i, GL_SPECULAR, light_specular[i]);
            glLightfv(GL_LIGHT0+i, GL_POSITION, position);

        }
        */

    }

}


void drawFlashlightLight(){


    if(nightTime){

        //  Direccao do FOCO=lanterna
        float dx, dy, dz;
        GLfloat lightpos[] = {xCamera, yCamera, zCamera, 1}; // o 1 indica luz no ponto e não no infinito
        camera.GetDirectionVector(dx, dy, dz);
        GLfloat spotDirection[] = {dx, dy, dz};

        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient[0]);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse[0]);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular[0]);
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15); // angulo de corte do foco
        glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, spotDirection ); //Definir direccao do foco
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);


        GLfloat otherSpotDirection[] = {0, -1, 0};

        for(int i=1; i<=numLights; i++){

            GLfloat position [] = {extras[i-1].x, mapHeight*(1.5f), extras[i-1].z, 1};
            glEnable(GL_LIGHT0+i);
            glLightfv(GL_LIGHT0+i, GL_AMBIENT, light_ambient[i]);
            glLightfv(GL_LIGHT0+i, GL_DIFFUSE, light_diffuse[i]);
            glLightfv(GL_LIGHT0+i, GL_SPECULAR, light_specular[i]);
            glLightfv(GL_LIGHT0+i, GL_POSITION, position);
            glLightf(GL_LIGHT0+i, GL_SPOT_CUTOFF, 5); // angulo de corte do foco
            glLightfv(GL_LIGHT0+i,GL_SPOT_DIRECTION, otherSpotDirection ); //Definir direccao do foco
            glLightf(GL_LIGHT0+i, GL_CONSTANT_ATTENUATION, 2.0);
        }



    }

}


void drawFog(){

    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
    //GLfloat distanceFromOrigin = sqrt( xCamera*xCamera + yCamera*yCamera + zCamera*zCamera );
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fogColor);

    glFogi(GL_FOG_MODE, GL_EXP2); glFogf(GL_FOG_DENSITY, 0.0015f);
    //glFogi(xCamera, yCamera);//GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);        // Set Fog Based On Vertice Coordinates
    glFogf(GL_FOG_START, 0);
    glFogf(GL_FOG_END, -mapLength);
    glHint (GL_FOG_HINT, GL_FASTEST);


}
