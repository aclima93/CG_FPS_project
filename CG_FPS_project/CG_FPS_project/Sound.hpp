#ifndef SOUND_HPP
#define SOUND_HPP

#include <stdlib.h>
#include <stdio.h>
#include "fmod/inc/fmod.h"
#include "fmod/lib/fmod.a"


class Sound{

    public:

        FSOUND_SAMPLE* handle;
        int volume;

        Sound(){
            volume = 255;
            FSOUND_Init( 44100, 32, 0); // Hz, num channels, flags
        }
        ~Sound(){
            cleanup();
        }

        void playSound(char* fileName, int num){

            handle = FSOUND_Sample_Load( 0, fileName,0,0,0 );

            for(int i=0; i<num; i++){
                FSOUND_PlaySound( 0, handle);
            }

            FSOUND_Sample_Free( handle);

        }

        void setSoundVolume(char v){ // 0 ... 255
            volume = v;
            FSOUND_SetVolume( handle, volume);
        }

        void setSoundPaused(bool state){
            FSOUND_SetPaused( handle, state);
        }

        void stopSound(){
            FSOUND_StopSound( handle);
        }
        void cleanup(){
            FSOUND_Close();
        }


};

#endif
