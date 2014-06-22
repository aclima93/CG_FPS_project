// =========================================== EVENTOS

#include <GL/glut.h>

#define bounceFactor 3

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

    if(!gameOver){

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

    if(!gameOver){

        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            shootGun();
        }

        glutPostRedisplay();

    }

}

void keyboard(unsigned char key, int x, int y){

    if(key||x||y){}

    if(!gameOver){
        switch (key){
    
            //--------------------------- forward
            case 'W':
            case 'w':
                camera.Move(g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Move(-g_translation_speed*bounceFactor); // undo
                }
                break;
    
            //--------------------------- back
            case 'S':
            case 's':
                camera.Move(-g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Move(g_translation_speed*bounceFactor); // undo
                }
                break;
    
            //--------------------------- right
            case 'A':
            case 'a':
                camera.Strafe(g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Strafe(-g_translation_speed*bounceFactor); // undo
                }
                break;
    
            //--------------------------- left
            case 'D':
            case 'd':
                camera.Strafe(-g_translation_speed);
                if( checkPlayerWallCollisions() ){
                    camera.Strafe(g_translation_speed*bounceFactor); // undo
                }
                break;
    
            //--------------------------- reload
            case 'R':
            case 'r':
                reloadGun();
                break;
    
    
            //--------------------------- Pause
            case 'P':
            case 'p':
                break;
    
            //--------------------------- main menu
            case 'M':
            case 'm':
                isMenuActive = !isMenuActive;
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
        }
    }


    switch(key) {

        // restart game
        case ' ':
            //Restart();
            exit(0);
            break;

        //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();

}
