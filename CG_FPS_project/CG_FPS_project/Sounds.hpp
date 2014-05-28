#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

/*
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_errors.h"
#include "fmod_memoryinfo.h"
#include "fmod_output.h"

using namespace std;
using namespace FMOD;

const char* SOUND_SHELL_FALLING = "sounds/Shells_falls-Marcel-829263474.mp3";
const char* SONG_BACKGROUND = "sounds/Robbie Williams - Let Me Entertain You.mp3";


class Sounds{


    private:
        System *fmodSystem;	// the global variable for talking to FMOD
        Sound *music, *actionSound;
        Channel *musicChannel;
        FMOD_RESULT result;


        Sounds(){
            Init();
        }
        ~Sounds(){

        }

        void FmodErrorCheck(FMOD_RESULT result)	// this is an error handling function
        {						// for FMOD errors
            if (result != FMOD_OK)
            {
                printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
                exit(-1);
            }
        }

        void Init(){

            result = System_Create(&fmodSystem);
            FmodErrorCheck(result);

            result = fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
            FmodErrorCheck(result);

            loadSong( SONG_BACKGROUND);

            playSong();

            loadSound( SOUND_SHELL_FALLING);

            playSound();


        }

        void loadSong(const char* filename){
            result = fmodSystem->createStream(filename, FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &music);
            FmodErrorCheck(result);
        }
        void playSong(){
            result = fmodSystem->playSound(FMOD_CHANNEL_FREE, music, false, &musicChannel);
            FmodErrorCheck(result);
        }

        void loadSound(const char* filename){
            result = fmodSystem->createSound(filename, FMOD_SOFTWARE, 0, &actionSound);
            FmodErrorCheck(result);
        }
        void playSound(){
            result = fmodSystem->playSound(FMOD_CHANNEL_FREE, actionSound, false, NULL );
            FmodErrorCheck(result);
        }

        void setVolume(float v){ // value between 0 and 1
            musicChannel->setVolume( v );
        }

        void update(){
            fmodSystem->update();
        }

        void playGunFiringSound(){
            loadSound( SOUND_SHELL_FALLING);
            playSound( );
        }


};

*/

#endif
