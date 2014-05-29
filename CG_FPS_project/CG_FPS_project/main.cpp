
#include "main.hpp"


void drawTargets(){
    for(unsigned int i=0; i<targets.size(); i++){
        targets[i].drawTarget();
        targets[i].drawBoundingBoxes();
    }
}

void createTargets(){

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

        posBB2[0][0] = aux2[pos][0];     posBB2[0][1] = aux2[pos][1]+10;  posBB2[0][2] = aux2[pos][2];  // head
        sizesBB2[0][0] = 2.0f;   sizesBB2[0][1] = 2.0f;  sizesBB2[0][2] = 2.0f;  // head

        extras[i].Init( aux2[pos][0], aux2[pos][1], aux2[pos][2], w, h, l, numBB2, posBB2, sizesBB2);
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



    glutWarpPointer(wCenterScreen, hCenterScreen);

    //camera starting position and orientation
    camera.SetYaw(-M_PI/2);
    camera.SetPitch(0.0);
    camera.SetPos( xStart, yStart, zStart);


    createTargets();



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

void drawFog(){

    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1};
    //GLfloat distanceFromOrigin = sqrt( xCamera*xCamera + yCamera*yCamera + zCamera*zCamera );
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fogColor);

    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 15.0f);
    glFogf(GL_FOG_END, 40.0f);
    glHint (GL_FOG_HINT, GL_FASTEST);

    /*
    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogf(GL_FOG_DENSITY, 0.05f);
    glHint (GL_FOG_HINT, GL_FASTEST);
    */

}

void drawScene(){


    //grelha no chão
    drawGrid();

    glDisable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec); - Nao considerar a componente especular

    drawFog();

    map.drawMap();
    drawTargets();

    camera.Refresh(); // não me tires daqui senão o minimapa fica diferente!
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
    camera.GetPos(x, y, z);

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
    hud.drawMiniMap(xCamera, yCamera, zCamera);

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

    if( bulletsLeft && bulletsInGun < 5 ){

        int loadingReq = 1; //int loadingReq = CLIPSIZE - bulletsInGun;

        if(bulletsLeft >= loadingReq){
            bulletsInGun += loadingReq;
            bulletsLeft -= loadingReq;
        }
        else{
            bulletsInGun += bulletsLeft;
            bulletsLeft = 0;
        }

        sounds.playReloadSound();

    }
}

int checkTargetCollisions(float x, float y, float z, float dx, float dy, float dz){

    for(int i=0; i<(int)targets.size(); i++){

        //if there's a collision inside this target's outer bounding box check the ones inside
        if( targets[i].checkCollision(x, y, z, dx, dy, dz) != -1 ){

            std::cout << " Acertei na OUTER BB do alvo " << i << "\n";

            int jMax = targets[i].numBoundingBoxes;
            float distance;

            for(int j=0; j<jMax; j++){

                distance = targets[i].boundingBoxes[j].checkCollision(x, y, z, dx, dy, dz);

                if( distance != -1 ){
                    std::cout << " Acertei na BB " << j << " do alvo " << i << "\n";
                    numTargetsHit++;
                    targets.erase( targets.begin()+ i ); // remove this target
                    bullets[bulletIndex].isActive = false;
                    return j; // stop the bullet in mid-flight

                }

            }

        }
    }

    return -1;

}

int checkExtraCollisions(float x, float y, float z, float dx, float dy, float dz){

    for(int i=0; i<(int)extras.size(); i++){

        //if there's a collision inside this target's outer bounding box check the ones inside
        if( extras[i].checkCollision(x, y, z, dx, dy, dz) != -1 ){

            std::cout << " Acertei na OUTER BB do extra " << i << "\n";

            int jMax = extras[i].numBoundingBoxes;
            float distance;

            for(int j=0; j<jMax; j++){

               distance = extras[i].boundingBoxes[j].checkCollision(x, y, z, dx, dy, dz);

               if( distance != -1 ){
                   std::cout << " Acertei na BB " << j << " do extra " << i << "\n";
                   numExtrasHit++;
                   extras.erase( extras.begin()+ i ); // remove this target
                   return 1; // stop the bullet in mid-flight

               }

            }
        }
    }

    return -1;
}

void shootGun(){

    if(bulletsInGun){

        bulletsInGun--;

        float x, y, z;
        float dx, dy, dz;
        camera.GetDirectionVector(dx, dy, dz); // bullet direction
        camera.GetPos(x, y, z); // initial position

        bullets[bulletIndex].Init(x, y, z, dx, dy, dz, bulletSpeed, 0, 0, 0, true);

        bulletIndex++;

        int targetBBIndex = checkTargetCollisions(x, y, z, dx, dy, dz);

        if( targetBBIndex != -1){
            score += targetValues[targetBBIndex];
        }
        else{
            if( checkExtraCollisions(x, y, z, dx, dy, dz) != -1){
                score += extraValue;
            }
        }

        sounds.playGunFiringSound();

    }
}

void updateGameTimer(){

    miliseconds += msecCallback;

    if(miliseconds > 999){
        miliseconds = 0;
        secs++;
    }
    if(secs > 59){
        secs = 0;
        minutes++;
    }

}

void Timer(int value){


    camera.GetPos(xCamera, yCamera, zCamera);

    updateGameTimer();
    updateBullets();

    // update sound

    if(miliseconds%msecDisplayCallback == 0){ // só chama de dez em dez ciclos do physics timer
        //std::cout << "chamei o glutpostredisplay no timer\n";
        glutPostRedisplay(); // flag que chama a função de display na próxima iteração
    }

    glutTimerFunc(msecCallback, Timer, ++value);
}

//======================================================= MAIN
int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize (wScreen, hScreen);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("CG_FPS_PROJECT : (A, W, S, D) - (R, Left Mouse)");

    init();

    glutReshapeFunc(resize);

    glutDisplayFunc(display);

    glutTimerFunc(msecCallback, Timer, 0);

    mainMenu = glutCreateMenu(mainMenuEvents);

    createMainMenu();

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    glutMouseFunc(mouseClicks);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}

// =========================================== EVENTOS

void createMainMenu(){

    for(int i=0; i<numGameModes; i++){
        glutAddMenuEntry(gameModes[i], i);
    }

    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void mainMenuEvents(int value){

    switch(value){


        //"Time Attack"
        case 0:

            break;

        //"No Bullet Left Behind"
        case 1:

            break;

        //"Zen"
        case 2:

            break;

        //"Highscores"
        case 3:

            break;

        //"Quit Game"
        case 4:

            glutDestroyMenu(mainMenu);
            exit(0);

            break;

    }


}

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
        camera.RotateYaw(g_rotation_speed*dx);
    }

    if(dy) {
        camera.RotatePitch(g_rotation_speed*dy);
    }

    if( !isMenuActive ) glutWarpPointer(wCenterScreen, hCenterScreen);

    just_warped = true;

    glutPostRedisplay();

}

void mouseClicks(int button, int state, int x, int y) {

    if(button || state || x || y){}

    //if(DEBUG) std::cout << button << " " << state << " :::: " << x << " - " << y << "\n";

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        shootGun();
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        isMenuActive = !isMenuActive;
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
            camera.Move(g_translation_speed);
            break;

        //--------------------------- back
        case 'S':
        case 's':
            camera.Move(-g_translation_speed);
            break;

        //--------------------------- left
        case 'A':
        case 'a':
            camera.Strafe(g_translation_speed);
            break;

        //--------------------------- left
        case 'D':
        case 'd':
            camera.Strafe(-g_translation_speed);
            break;

        //--------------------------- reload
        case 'R':
        case 'r':
            reloadGun();
            break;


        //--------------------------- main menu
        case 'P':
        case 'p':
            createMainMenu();
            break;


        // ------------------------------ move vertically for DEBUG
        //--------------------------- up
        case 'U':
        case 'u':
            camera.Fly(g_translation_speed);
            break;
        //--------------------------- down
        case 'J':
        case 'j':
            camera.Fly(-g_translation_speed);
            break;



        //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();

}

