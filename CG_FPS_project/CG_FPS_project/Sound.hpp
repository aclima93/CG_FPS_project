#ifndef SOUND_HPP
#define SOUND_HPP

#include <stdlib.h>
#include <stdio.h>

#include "fmod.h"
///
///#include "fmod.hpp"
///#include "fmod_codec.h"
///#include "fmod_dsp.h"
///#include "fmod_errors.h"
///#include "fmod_memoryinfo.h"
///#include "fmod_output.h"
///

#define SOUND_SHELL_FALLING "sounds/Shells_falls-Marcel-829263474.mp3"


class Sound{

    /*

    public:

        bool on; //is sound on?
        bool possible; //is it possible to play sound?
        char *currentSound; //currently played sound
        //FMOD-specific stuff
        FMOD_RESULT result;
        FMOD_SYSTEM *fmodsystem;
        FMOD_SOUND *sound;
        FMOD_CHANNEL *channel;

        Sound(){
            on = true;
            possible = true;
        }
        ~Sound(){
            unload();
        }

        //initialises sound
        void initialise (void) {

            //create the sound system. If fails, sound is set to impossible
            result = FMOD_System_Create(&fmodsystem);
            if (result != FMOD_OK) possible = false;

            //if initialise the sound system. If fails, sound is set to impossible
            if (possible) result = FMOD_System_Init(fmodsystem,32, FMOD_INIT_NORMAL, 0);
            if (result != FMOD_OK) possible = false;

            //sets initial sound volume (mute)
            if (possible) FMOD_Channel_SetVolume(channel,0.0f);
        }

        //sets the actual playing sound's volume
        void setVolume (float v) {
            if (possible && on && v >= 0.0f && v <= 1.0f) {
                FMOD_Channel_SetVolume(channel,v);
            }
        }

        //loads a soundfile
        void load (const char * filename) {
            currentSound = (char *)filename;
            if (possible && on) {
                result = FMOD_Sound_Release(sound);
                result = FMOD_System_CreateStream(fmodsystem,currentSound, FMOD_SOFTWARE, 0, &sound);
                if (result != FMOD_OK) possible = false;
            }
        }

        //frees the sound object
        void unload (void) {
            if (possible) {
                result = FMOD_Sound_Release(sound);
            }
        }

        //plays a sound (no argument to leave pause as dafault)
        void play (bool pause) {
            if (possible && on) {
                result = FMOD_System_PlaySound(fmodsystem,FMOD_CHANNEL_FREE, sound, pause, &channel);
                FMOD_Channel_SetMode(channel,FMOD_LOOP_NORMAL);
            }
        }

        //toggles sound on and off
        void toggleSound (void) {
            on = !on;
            if (on == true) { load(currentSound); play( false); }
            if (on == false) { unload(); }
        }

        //pause or unpause the sound
        void setPause (bool pause) {
            FMOD_Channel_SetPaused (channel, pause);
        }

        //turn sound on or off
        void setSound (bool s) {
            on = s;
        }

        //toggle pause on and off
        void togglePause (void) {
            FMOD_BOOL p;
            FMOD_Channel_GetPaused( channel,&p);
            FMOD_Channel_SetPaused( channel,!p);
        }

        void playSound( char* filename){
            //initialise();
            //load(filename);
            //play(true);
            //unload();
        }

    */
};

#endif
