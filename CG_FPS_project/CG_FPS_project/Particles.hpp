#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>


#define MAX_PARTICLES 250 // water drops
#define PARTICLE_FACTOR 4 // resulting in 10000

float slowdown = 2.0;
float velocity = 0.0;
float zoom = -40.0;
float pan = 0.0;
float tilt = 0.0;

int fall;
int pi;

float offsetRain = 10;

//floor colors
float r = 0.0;
float g = 1.0;
float b = 0.0;
float ground_points[21][21][3];
float ground_colors[21][21][4];
float accum = -10.0;

typedef struct {
    // Life
    bool alive;	// is the particle alive?
    float life;	// particle lifespan
    float fade; // decay
    // color
    float red;
    float green;
    float blue;
    // Position/direction
    float xpos;
    float ypos;
    float zpos;
    // Velocity/Direction, only goes down in y dir
    float vel;
    // Gravity
    float gravity;
}particles;


// Paticle System
particles par_sys[MAX_PARTICLES];


void updateRain(){

    par_sys[pi].alive = true;
    par_sys[pi].life = 2;
    par_sys[pi].fade = float(rand()%100)/1000.0f+0.003f;


    par_sys[pi].xpos = (float) (rand() % mapWidth/PARTICLE_FACTOR);
    par_sys[pi].ypos = mapHeight*2;
    par_sys[pi].zpos = (float) (rand() % mapLength/(PARTICLE_FACTOR*2)*(-1));


    par_sys[pi].red = 0.5;
    par_sys[pi].green = 0.5;
    par_sys[pi].blue = 1.0;

    par_sys[pi].vel = velocity;
    par_sys[pi].gravity = -200;//9.8;

}


void initParticles(){
    int x, z;

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);



    // Ground Verticies
    // Ground Colors
    for (z = 0; z < 21; z++) {
        for (x = 0; x < 21; x++) {
            ground_points[x][z][0] = x - 10.0;
            ground_points[x][z][1] = accum;
            ground_points[x][z][2] = z - 10.0;

            ground_colors[z][x][0] = r; // red value
            ground_colors[z][x][1] = g; // green value
            ground_colors[z][x][2] = b; // blue value
            ground_colors[z][x][3] = 0.0; // acummulation factor
        }
    }



    // Initialize particles
    for(pi = 0; pi < MAX_PARTICLES; pi++) {
        updateRain();
    }
}

// For Rain
void drawRain() {



    float x, y, z;
    float wx=0, wz=0;

    for(pi = 0; pi < MAX_PARTICLES; pi=pi+2) {

        if(par_sys[pi].alive == true && !paused) {

            x = par_sys[pi].xpos;
            y = par_sys[pi].ypos;
            z = par_sys[pi].zpos + zoom;

            // Update values
            //Move
            if (par_sys[pi].ypos <= -1) {
                par_sys[pi].vel = par_sys[pi].vel * -1.0;
            }
            // Adjust slowdown for speed!
            par_sys[pi].ypos += par_sys[pi].vel / (slowdown*1000);
            par_sys[pi].vel += par_sys[pi].gravity;
            // Decay
            par_sys[pi].life -= par_sys[pi].fade;

            if(par_sys[pi].ypos <= -1) {
                par_sys[pi].life = -1.0;
            }
            //Revive
            if(par_sys[pi].life < 0.0) {
                updateRain();
            }


            for(wx = -3; wx <4; wx +=2 ){
                for(wz = 1 ; wz <5 ; wz ++){

                    // Draw particles
                    glColor3f(0.5, 0.5, 1.0);
                    glBegin(GL_LINES);
                        glVertex3f(wx*x, y, wz*z);
                        glVertex3f(wx*x, y+0.5, wz*z);
                    glEnd();

                    /*
                    // Draw particles
                    glColor3f(0.5, 0.5, 1.0);
                    glBegin(GL_LINES);
                        glVertex3f(wx*(x+offsetRain), y, wz*(z+offsetRain));
                        glVertex3f(wx*(x+offsetRain), y+0.5, wz*(z+offsetRain));
                    glEnd();

                    // Draw particles
                    glColor3f(0.5, 0.5, 1.0);
                    glBegin(GL_LINES);
                        glVertex3f(wx*(x+offsetRain), y, wz*(z-offsetRain));
                        glVertex3f(wx*(x+offsetRain), y+0.5, wz*(z-offsetRain));
                    glEnd();
                    */

                    // Draw particles
                    glColor3f(0.5, 0.5, 1.0);
                    glBegin(GL_LINES);
                        glVertex3f(wx*(x-offsetRain), y, wz*(z+offsetRain));
                        glVertex3f(wx*(x-offsetRain), y+0.5, wz*(z+offsetRain));
                    glEnd();

                    // Draw particles
                    glColor3f(0.5, 0.5, 1.0);
                    glBegin(GL_LINES);
                        glVertex3f(wx*(x-offsetRain), y, wz*(z-offsetRain));
                        glVertex3f(wx*(x-offsetRain), y+0.5, wz*(z-offsetRain));
                    glEnd();



                }
            }

        }
    }

}


#endif
