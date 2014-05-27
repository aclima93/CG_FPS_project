#ifndef FMOD_HPP
#define FMOD_HPP

#include <stdlib.h>
#include <stdio.h>

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_errors.h"
#include "fmod_memoryinfo.h"
#include "fmod_output.h"


#define SOUND_SHELL_FALLING "sounds/Shells_falls-Marcel-829263474.mp3"
#define BACKGROUND_SONG "sounds/Robbie Williams - Let Me Entertain You.mp3"


class FMOD{

    public:

        System *fmodSystem;	// the global variable for talking to FMOD
        Sound *music;
        Channel *musicChannel;

        void FmodErrorCheck(FMOD_RESULT result)	// this is an error handling function
        {						// for FMOD errors
            if (result != FMOD_OK)
            {
                printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
                exit(-1);
            }
        }

        void Init(){

            FMOD_RESULT result;
            result = System_Create(&fmodSystem);
            FmodErrorCheck(result);

            result = fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
            FmodErrorCheck(result);


            result = fmodSystem->createStream(BACKGROUND_SONG, FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &music);
            FmodErrorCheck(result);

            result = fmodSystem->playSound(FMOD_CHANNEL_FREE, music, false, &musicChannel);
            FmodErrorCheck(result);

            result = fmodSystem->createSound(SOUND_SHELL_FALLING, FMOD_SOFTWARE, 0,
                                    &actionSound);
            FmodErrorCheck(result);


        }

        void setVolume(float v){ // value between 0 and 1
            musicChannel->setVolume( v );
        }

};

#endif
