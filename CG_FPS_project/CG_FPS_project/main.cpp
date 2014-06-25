
#include "main.hpp"


#include "ModelsTargetsExtras.hpp"
#include "Physics.hpp"
#include "Lights.hpp"
#include "Events.hpp"
#include "Particles.hpp"




void initGame(void){

    //redefine constants and stuffs

    minutes = 0;
    secs = 0;
    miliseconds = 0;

    time(&timer);  // get current time

    numTargetsHit = 0;
    numExtrasHit = 0;
    score = 0;

    bulletsInGun = CLIPSIZE;
    bulletsLeft = CLIPSIZE * NUMCLIPS;
    bulletIndex = 0;

    memset(map.isGlassActive, 1, sizeof(map.isGlassActive));



    //……………………………………………………………………………………………………………………………Lighting set up
    initLights();

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    initParticles();

    map.createTexture();
    hud.createTextures();

    glutWarpPointer(wCenterScreen, hCenterScreen);

    //camera starting position and orientation
    camera.SetYaw(-M_PI/2);
    camera.SetPitch(0.0);
    camera.SetPos( xStart, yStart, zStart);


    player.Init(ROBOT_OBJ, ROBOT_TEXTURE);
    map.Init();
    createTargetsAndExtras();

    /* Sky Box */
    skybox.createTexture();


}


//================================================================================
//======================================================================== DISPLAY

void drawScene(){

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );


    glEnable(GL_BLEND); //Activar as funcoes de BLEND
    glEnable(GL_DEPTH_TEST); //Activar o "teste de profundidade", z-buffer


    skybox.drawSkyBox();
    drawFog();
    drawRain();

    drawTargets();
    drawExtras();
    drawBullets();
    map.drawMap();
    camera.Refresh(); // não me tires daqui senão o minimapa fica diferente!
    drawPlayer(); // desenha o robot



}


GLvoid resize(GLsizei width, GLsizei height){

    wScreen=width;
    hScreen=height;
}




void display(void){


    //================================================================= Viewport1 (minimap)
    glDisable(GL_LIGHTING);
    hud.drawMiniMap(xCamera, yCamera, zCamera, dxCamera, dzCamera );
    drawScene(); //--------------------- desenha objectos no viewport1


    //================================================================= Viewport2 (game)
    glEnable(GL_LIGHTING);
    glViewport (0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, wScreen/hScreen, 0.1, 2000.0);
    glMatrixMode(GL_MODELVIEW);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(wCenterScreen, hCenterScreen);

    drawScene();//--------------------- desenha objectos no viewport2
    drawFlashlightLight();

    //================================================================= Viewport3 (HUD)
    hud.drawHUD();


    //don't delete this!
    glutSwapBuffers();

}



void updateGameTimer(){

    if( bulletsLeft+bulletsInGun > 0 && numTargetsHit+numExtrasHit < NUMTARGETS+NUMEXTRAS ){


        miliseconds = difftime(timer, time(NULL));
        //secs = (int) (miliseconds / 1000) % 60 ;
        //minutes = (int) ((miliseconds / (1000*60)) % 60);

        miliseconds = -(miliseconds - ( (((miliseconds / 1000) % 60)*1000) + (((miliseconds / (1000*60)) % 60)*1000*60) ));


        if(miliseconds > 59){
            miliseconds = 0;
            secs++;
        }
        if(secs > 59){
            secs = 0;
            minutes++;
        }
        if(minutes > 9){
            gameOver = true; // i'd stay away from FPSs if I were you...
        }

        /*
        //miliseconds += msecCallback;

        if(miliseconds > 999){
            miliseconds = 0 + (miliseconds - 1000);
            secs++;
        }
        if(secs > 59){
            secs = 0;
            minutes++;
        }
        if(minutes > 9){
            gameOver = true; // i'd stay away from FPSs if I were you...
        }
        */


    }
    else{
        gameOver = true;
    }

}

void Timer(int value){

    if(!paused){
        camera.GetPos(xCamera, yCamera, zCamera);
        camera.GetDirectionVector(dxCamera, dyCamera, dzCamera);

        updateGameTimer();
        updateBullets();

        if(miliseconds%msecDisplayCallback == 0){ // só chama de dez em dez ciclos do physics timer
            glutPostRedisplay(); // flag que chama a função de display na próxima iteração
        }
    }

    glutTimerFunc(msecCallback, Timer, ++value);
}

//======================================================= MAIN
int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("|| CG_FPS_PROJECT : (A, W, S, D) - (R, Left Mouse) - (P, Spacebar) ||");

    initGame();

    glutReshapeFunc(resize);

    glutDisplayFunc(display);

    glutTimerFunc(msecCallback, Timer, 0);

    //mainMenu = glutCreateMenu(mainMenuEvents);

    //createMainMenu();

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(teclasNotAscii);
    glutMouseFunc(mouseClicks);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}

