
#include "main.hpp"


#include "ModelsTargetsExtras.hpp"
#include "Physics.hpp"
#include "Lights.hpp"
#include "Events.hpp"




void init(void)
{

    //……………………………………………………………………………………………………………………………Lighting set up
    initLights();

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    map.createTexture();
    hud.createTextures();

    glutWarpPointer(wCenterScreen, hCenterScreen);

    //camera starting position and orientation
    camera.SetYaw(-M_PI/2);
    camera.SetPitch(0.0);
    camera.SetPos( xStart, yStart, zStart);


    createTargetsAndExtras();

    /* Sky Box */
    skybox.createTexture();


}


//================================================================================
//======================================================================== DISPLAY

void drawGrid(){


    glPushMatrix();

        for(float i = -300; i <= 300; i += 5)
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

        glColor4f(AZUL);
        glBegin(GL_LINES);
            glVertex3i(0,0,-zC);
            glVertex3i(0,0, zC);
        glEnd();
        glBegin(GL_LINES);
            glVertex3i(0,-yC,0);
            glVertex3i(0,yC,0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3i(-xC,0,0);
            glVertex3i( xC,0,0);
        glEnd();

    glPopMatrix();


}


void drawScene(){

    draw_local_lights(); // fuck, que atraso tão grande x]

    //grelha no chão
    //drawGrid();


    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );


    glEnable(GL_BLEND); //Activar as funcoes de BLEND
    glEnable(GL_DEPTH_TEST); //Activar o "teste de profundidade", z-buffer


    /*
    glBlendFunc(GL_ONE, GL_ZERO);
    draw_esfera1();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    draw_esfera2();
    */

    /* Draw SkyBox */
    skybox.drawSkyBox();

    //drawFog();
    map.drawMap();
    drawTargets();
    drawExtras();
    drawBullets();

    /* Transparency Glass */
    //glass.drawGlass();

    camera.Refresh(); // não me tires daqui senão o minimapa fica diferente!



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
    gluPerspective(100.0, wScreen/hScreen, 0.1, 1000.0);
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

        miliseconds += msecCallback;

        if(miliseconds > 999){
            miliseconds = 0 + (miliseconds - 1000);
            secs++;
        }
        if(secs > 59){
            secs = 0;
            minutes++;
        }
    }
    else{
        gameOver = true;
    }

}

void Timer(int value){


    camera.GetPos(xCamera, yCamera, zCamera);
    camera.GetDirectionVector(dxCamera, dyCamera, dzCamera);

    updateGameTimer();
    updateBullets();

    if(miliseconds%msecDisplayCallback == 0){ // só chama de dez em dez ciclos do physics timer
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

