
#include "main.hpp"


void drawTargets(){
    for(int i=0; i<NUMTARGETS; i++){
        targets[i].drawTarget();
        targets[i].drawBoundingBoxes();
    }
}

void createTargets(){

    for(int i=0; i<NUMPOSSIBLE; i++){
        possiblePositions[i][0] = 0;
        possiblePositions[i][1] = 1;
        possiblePositions[i][2] = -i +20;

        possibleExtraPositions[i][0] = -i +20;
        possibleExtraPositions[i][1] = 1;
        possibleExtraPositions[i][2] = 0;
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


    for(int i=0; i<NUMTARGETS; i++){

        pos = rand()%aux.size(); // randomly selects one of the available

        posBB[0][0] = aux[pos][0];      posBB[0][1] = aux[pos][1] +2; posBB[0][2] = aux[pos][2];  // head
        posBB[1][0] = aux[pos][0];      posBB[1][1] = aux[pos][1];    posBB[1][2] = aux[pos][2];  // torso
        posBB[2][0] = aux[pos][0] +5;   posBB[2][1] = aux[pos][1];    posBB[2][2] = aux[pos][2];  // right arm
        posBB[3][0] = aux[pos][0] -5;   posBB[3][1] = aux[pos][1];    posBB[3][2] = aux[pos][2];  // left arm
        posBB[4][0] = aux[pos][0] +5;   posBB[4][1] = aux[pos][1] -2; posBB[4][2] = aux[pos][2];  // right leg
        posBB[5][0] = aux[pos][0] -5;   posBB[5][1] = aux[pos][1] -2; posBB[5][2] = aux[pos][2];  // left leg


        sizesBB[0][0] = 0.1f;   sizesBB[0][1] = 0.2f;  sizesBB[0][2] = 0.3f;  // head
        sizesBB[1][0] = 0.1f;   sizesBB[1][1] = 0.2f;  sizesBB[1][2] = 0.3f;  // torso
        sizesBB[2][0] = 0.1f;   sizesBB[2][1] = 0.2f;  sizesBB[2][2] = 0.3f;  // right arm
        sizesBB[3][0] = 0.1f;   sizesBB[3][1] = 0.2f;  sizesBB[3][2] = 0.3f;  // left arm
        sizesBB[4][0] = 0.1f;   sizesBB[4][1] = 0.2f;  sizesBB[4][2] = 0.3f;  // right leg
        sizesBB[5][0] = 0.1f;   sizesBB[5][1] = 0.2f;  sizesBB[5][2] = 0.3f;  // left leg


        targets[i].Init( aux[pos][0], aux[pos][1], aux[pos][2], numBB, posBB, sizesBB);
        aux.erase( aux.begin()+ pos );
    }

    for(int i=0; i<NUMEXTRAS; i++){

        pos = rand()%aux2.size(); // randomly selects one of the available

        posBB2[0][0] = aux2[pos][0];     posBB2[0][1] = aux2[pos][1]+10;  posBB2[0][2] = aux2[pos][2];  // head
        sizesBB2[0][0] = 0.1f;   sizesBB2[0][1] = 0.2f;  sizesBB2[0][2] = 0.3f;  // head

        extras[i].Init( aux2[pos][0], aux2[pos][1], aux2[pos][2], numBB2, posBB2, sizesBB2);
        aux2.erase( aux2.begin()+ pos );
    }

}


void activateLight(void)
{
}

void activateAmbientIllumination(void)
{

    if (iluminacao)
    {
        /*Iluminacao local*/
        glLightfv(GL_LIGHT0, GL_POSITION, localPos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, localCor);
        glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
        glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin);
        glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua);
    }
    else
    {
        /*Iluminacao global*/
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);/*Activar modelo ambiente global*/
    }
}

//……………………………………………………………………………………………………………………………………………………… Iluminacao
void initLights(void)
{
    //…………………………………………………………………………………………………………………………………………… Ambiente
    activateAmbientIllumination();

    activateLight();
}

void init(void)
{

    //……………………………………………………………………………………………………………………………Lighting set up
    initLights();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);                                //luz ambiente

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations



}


//================================================================================
//======================================================================== DISPLAY

void drawGrid()
{

    for(float i = -100; i <= 100; i += 5)
    {
        glBegin(GL_LINES);
            glColor3ub(150, 190, 150);
            glVertex3f(-500, 0, i);
            glVertex3f(500, 0, i);
            glVertex3f(i, 0,-500);
            glVertex3f(i, 0, 500);
        glEnd();
    }

    //============================================Eixos
    glColor4f(WHITE);
    glBegin(GL_LINES);
        glVertex3i(0,0,-xC);
        glVertex3i(0,0, xC);
    glEnd();
    glBegin(GL_LINES);
        glVertex3i(0,-xC,0);
        glVertex3i(0,xC,0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3i(-xC,0,0);
        glVertex3i( xC,0,0);
    glEnd();

}

void drawBullets(){

    for(int i=0; i<NUMBULLETS; i++){
        bullets[i].draw();
    }
}

void drawScene()
{

    //grelha no chão
    drawGrid();

    glDisable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec); - Nao considerar a componente especular

    map.drawMap();
    drawTargets();

    g_camera.Refresh();
    drawBullets();

}


GLvoid resize(GLsizei width, GLsizei height){

    wScreen=width;
    hScreen=height;
}


void drawOrientacao(){

    // quadrado na posição da cãmara

    /*
    float x, y, z;
    g_camera.GetPos(x, y, z);

    glPushMatrix();
        glColor4f(VERDE);
        glTranslatef( x-2, y-2, y-2);
        glutSolidCube(1);
    glPopMatrix();
    */



    //  Direccao do FOCO=lanterna
    //glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_direction);/*Definir direccao do foco*/

}


void display(void){


    //================================================================= Viewport1 (minimap)
    hud.drawMiniMap();

    drawScene(); //--------------------- desenha objectos no viewport1
    drawOrientacao();


    //================================================================= Viewport2 (game)
    glEnable(GL_LIGHTING);
    glViewport (0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(99.0, wScreen/hScreen, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(wCenterScreen, hCenterScreen);

    drawScene();//--------------------- desenha objectos no viewport2
    drawOrientacao();


    //================================================================= Viewport3 (HUD)


    hud.drawHUD();


    //don't delete this!
    glutSwapBuffers();

}


// =========================================== Physics

void updateBullets(){

    for(int i=0; i<NUMBULLETS; i++){
        bullets[i].updatePosition();
    }
}


void reloadGun(){

    if(bulletsLeft){

        int loadingReq = CLIPSIZE - bulletsInGun;

        if(bulletsLeft >= loadingReq){
            bulletsInGun += loadingReq;
            bulletsLeft -= loadingReq;
        }
        else{
            bulletsInGun += bulletsLeft;
            bulletsLeft = 0;
        }
    }
}

void shootGun(){

    if(bulletsInGun){

        bulletsInGun--;

        float x, y, z;
        float dx, dy, dz;
        g_camera.GetDirectionVector(dx, dy, dz); // bullet direction
        g_camera.GetPos(x, y, z); // initial position

        bullets[bulletIndex].Init(x, y, z, dx, dy, dz, bulletSpeed, 0, 0, 0, true);

        bulletIndex++;

        float distance;



        for(int i=0; i<NUMTARGETS; i++){
            int jMax = targets[i].numBoundingBoxes;
            for(int j=0; j<jMax; j++){

                distance = targets[i].boundingBoxes[j].checkCollision(x, y, z, dx, dy, dz);

                if( distance != -1 ){
                    std::cout << " Acertei na BB " << j << " do alvo " << i << "\n";
                    numTargetsHit++;

                }

            }
        }

        for(int i=0; i<NUMEXTRAS; i++){
            int jMax = extras[i].numBoundingBoxes;
            for(int j=0; j<jMax; j++){

                distance = extras[i].boundingBoxes[j].checkCollision(x, y, z, dx, dy, dz);

                if( distance != -1 ){
                    std::cout << " Acertei na BB " << j << " do extra " << i << "\n";
                    numExtrasHit++;

                }

            }
        }




    }
}

void updateGameTimer(){

    miliseconds += msecCallback;

    if(miliseconds == 999){
        miliseconds = 0;
        seconds++;
    }
    if(seconds == 59){
        seconds = 0;
        minutes++;
    }

}

void Timer(int value){


    updateGameTimer();
    updateBullets();

    if(miliseconds%msecDisplayCallback == 0){ // só chama de dez em dez ciclos do physics timer
        //std::cout << "chamei o glutpostredisplay no timer\n";
        glutPostRedisplay(); // flag que chama a função de display na próxima iteração
    }

    glutTimerFunc(msecCallback, Timer, ++value);
}

//======================================================= MAIN
int main(int argc, char** argv){

    createTargets();

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("CG_FPS_PROJECT : (A, W, S, D) - (R, Left Mouse)");

    init();

    glutReshapeFunc(resize);

    glutDisplayFunc(display);

    glutTimerFunc(msecCallback, Timer, 0);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    glutMouseFunc(mouseClicks);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);


    glutMainLoop();

    return 0;
}

// =========================================== EVENTOS

void teclasNotAscii(int key, int x, int y){

    //using parameters just because
    if( x || y ){}

    switch(key){}

    glutPostRedisplay();

}

void mouseMotion(int x, int y){

    //if(DEBUG) std::cout << x << " - " << y << "\n";

    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

    int dx = x - wCenterScreen;
    int dy = -(y - hCenterScreen);

    if(dx) {
        g_camera.RotateYaw(g_rotation_speed*dx);
    }

    if(dy) {
        g_camera.RotatePitch(g_rotation_speed*dy);
    }

    glutWarpPointer(wCenterScreen, hCenterScreen);

    just_warped = true;

    glutPostRedisplay();

}

void mouseClicks(int button, int state, int x, int y) {

    if(button || state || x || y){}

    //if(DEBUG) std::cout << button << " " << state << " :::: " << x << " - " << y << "\n";

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        shootGun();
    }

    glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y){

    if(key||x||y){}

    //if(DEBUG) std::cout << key << " :::: " << x << " - " << y << "\n";

    switch (key){

        //--------------------------- forward
        case 'W':
        case 'w':
            g_camera.Move(g_translation_speed);
            break;

        //--------------------------- back
        case 'S':
        case 's':
            g_camera.Move(-g_translation_speed);
            break;

        //--------------------------- left
        case 'A':
        case 'a':
            g_camera.Strafe(g_translation_speed);
            break;

        //--------------------------- left
        case 'D':
        case 'd':
            g_camera.Strafe(-g_translation_speed);
            break;

        //--------------------------- reload
        case 'R':
        case 'r':
            reloadGun();
            break;



        // ------------------------------ move vertically for DEBUG
        //--------------------------- up
        case 'U':
        case 'u':
            g_camera.Fly(g_translation_speed);
            break;
        //--------------------------- down
        case 'J':
        case 'j':
            g_camera.Fly(-g_translation_speed);
            break;



        //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();

}

