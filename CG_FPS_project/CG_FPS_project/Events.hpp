// =========================================== EVENTOS

#include <GL/glut.h>

#define bounceFactor 3

void initGame(void);

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

    switch(key){

        case GLUT_KEY_F4:
            if( glutGetModifiers() == GLUT_ACTIVE_ALT){
                exit(0);
            }
            break;

    }

    glutPostRedisplay();

}

void mouseMotion(int x, int y){

    if(!gameOver && !paused){

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

}

void mouseClicks(int button, int state, int x, int y) {

    if(button || state || x || y){}

    if(!gameOver && !paused){

        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            shootGun();
        }

        glutPostRedisplay();

    }

}


void keyboardUp(unsigned char key, int x, int y) {
    if(x||y){}
    keyStates[key] = false;
}
void keyboard(unsigned char key, int x, int y){
    if(x||y){}
    keyStates[key] = true;
}

void keyboardOperations(){

    if(!gameOver){


        //--------------------------- (Un)Pause
        if(keyStates['P'] || keyStates['p']){
            paused = !paused;
        }

        if(!paused){

            //--------------------------- forward
            if(keyStates['W'] || keyStates['w']){
                camera.Move(g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Move(-g_translation_speed*bounceFactor); // undo
                }
                sounds.playWalkingSound();
            }

            //--------------------------- back
            if(keyStates['S'] || keyStates['s']){
                camera.Move(-g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Move(g_translation_speed*bounceFactor); // undo
                }
                sounds.playWalkingSound();
            }

            //--------------------------- right
            if(keyStates['A'] || keyStates['a']){
                camera.Strafe(g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Strafe(-g_translation_speed*bounceFactor); // undo
                }
                sounds.playWalkingSound();
            }

            //--------------------------- left
            if(keyStates['D'] || keyStates['d']){
                camera.Strafe(-g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Strafe(g_translation_speed*bounceFactor); // undo
                }
                sounds.playWalkingSound();
            }


            //--------------------------- reload
            if(keyStates['R'] || keyStates['r']){
                reloadGun();
            }

            //--------------------------- main menu
            if(keyStates['M'] || keyStates['m']){
                isMenuActive = !isMenuActive;
            }


            // ------------------------------ move vertically for DEBUG
            //--------------------------- up
            if(keyStates['U'] || keyStates['u']){
                if(DEBUG_MODE) camera.Fly(g_translation_speed);
            }
            //--------------------------- down
            if(keyStates['J'] || keyStates['j']){
                if(DEBUG_MODE) camera.Fly(-g_translation_speed);
            }

        }
    }


    // restart game
    if(keyStates[' ']){
        gameOver = false;
        initGame();
    }

    //--------------------------- Escape
    if(keyStates[27]){
        exit(0);
    }

    glutPostRedisplay();

}
