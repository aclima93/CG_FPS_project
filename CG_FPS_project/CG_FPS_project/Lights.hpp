//……………………………………………………………………………………………………………………………………………………… Iluminacao
void initLights(void){

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);


    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //Iluminacao global
    if( dayTime){
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);
    }
    if( nightTime){

        for(int i=0; i<numLights; i++){

            glEnable(GL_LIGHT0+i);

            glLightfv(GL_LIGHT0+i, GL_AMBIENT, light_ambient[i]);
            glLightfv(GL_LIGHT0+i, GL_DIFFUSE, light_diffuse[i]);
            glLightfv(GL_LIGHT0+i, GL_SPECULAR, light_specular[i]);
            glLightfv(GL_LIGHT0+i, GL_POSITION, localPos[i]);
        }

    }


    /*
    //Iluminacao local
    glLightfv(GL_LIGHT0, GL_POSITION, localPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, localCor);
    glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
    glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin);
    glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua);
    */


}

void draw_esfera1( ){

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat1);
        glTranslatef(-raioEsf, 5, -raioEsf);
        glutSolidSphere(raioEsf, 50, 50);
    glPopMatrix();
}

void draw_esfera2( ){

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat2);
        glTranslatef(0, 5, 0);
        glutSolidSphere(raioEsf, 50, 50);
    glPopMatrix();
}

void draw_local_lights( ){

    for(int i=0; i<numLights; i++){
        glPushMatrix();
            glColor3f( localCor[0], localCor[1], localCor[2] );
            glTranslatef( localPos[i][0], localPos[i][1], localPos[i][2] );
            glutSolidSphere( raioEsf, 5, 5 );
        glPopMatrix();
    }
}

void drawFlashlightLight(){

    /*
    // quadrado na posição da cãmara
    glPushMatrix();
        glColor4f(VERMELHO);
        glTranslatef( xCamera, yCamera+3, zCamera);
        glutSolidCube(1);
    glPopMatrix();
    */

    if(nightTime){
        //  Direccao do FOCO=lanterna
        float dx, dy, dz;
        camera.GetDirectionVector(dx, dy, dz);
        GLfloat spotDirection[] = {dx, dy, dz};
        glEnable(GL_LIGHT0+numLights);
        glLightf(GL_LIGHT0+numLights, GL_SPOT_CUTOFF, 22.5); // angulo de corte do foco
        glLightfv(GL_LIGHT0+numLights,GL_SPOT_DIRECTION, spotDirection); //Definir direccao do foco
        /*
        glLightf(GL_LIGHT0+numLights, GL_CONSTANT_ATTENUATION, 2.0);
        glLightf(GL_LIGHT0+numLights, GL_LINEAR_ATTENUATION, 1.0);
        glLightf(GL_LIGHT0+numLights, GL_QUADRATIC_ATTENUATION, 0.5);
        */

    }

}


void drawFog(){

    /*

    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
    //GLfloat distanceFromOrigin = sqrt( xCamera*xCamera + yCamera*yCamera + zCamera*zCamera );
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fogColor);

    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogi(xCamera, yCamera);//GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);        // Set Fog Based On Vertice Coordinates
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 30.0f);
    glHint (GL_FOG_HINT, GL_FASTEST);


    //glFogi(GL_FOG_MODE, GL_EXP2);
    //glFogf(GL_FOG_DENSITY, 0.05f);
    //glHint (GL_FOG_HINT, GL_FASTEST);
    */


}
