#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <windows.h>
#include <conio.h>
#include <math.h>


#include <FMOD/fmod.h>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_codec.h>
#include <FMOD/fmod_dsp.h>
#include <FMOD/fmod_errors.h>
#include <FMOD/fmod_memoryinfo.h>
#include <FMOD/fmod_output.h>

#include <SFML/Audio.hpp>

using namespace std;
using namespace FMOD;
using namespace sf;

#define SOUND_SHELL_FALLING "sounds/Shells_falls-Marcel-829263474.wav"
#define SONG_BACKGROUND "sounds/Robbie Williams - Let Me Entertain You.wav"


class Sounds{


    public:
    /*
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

        */

    void playSound()
    {
        // Load a sound buffer from a wav file
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(SOUND_SHELL_FALLING)){
            cout << "fail sound...\n";
            return;
        }

        // Create a sound instance and play it
        sf::Sound sound(buffer);
        sound.play();


        // Loop while the sound is playing
        while (sound.getStatus() == sf::Sound::Playing)
        {
            // Leave some CPU time for other processes
            //sf::sleep(sf::milliseconds(100));

        }

    }


    void playMusic()
    {
        // Load an ogg music file
        sf::Music music;
        if (!music.openFromFile(SONG_BACKGROUND)){
            cout << "fail song...\n";
            return;
        }

        // Play it
        //music.play();


        // Loop while the music is playing
        while (music.getStatus() == sf::Music::Playing)
        {
            // Leave some CPU time for other processes
            //sf::sleep(sf::milliseconds(100));

        }

    }



        void playGunFiringSound(){
            playSound();
            playMusic();
        }


};


#endif
