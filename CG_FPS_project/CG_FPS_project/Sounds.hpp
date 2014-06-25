#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <unistd.h>

#include <SFML/Audio.hpp>

using namespace std;

#define NUMSONGS 1

#define SONG_BACKGROUND "sounds/musica_ambiente.wav"

#define NUMSOUNDS 8

#define SOUND_SHELL_FALLING "sounds/Shells_falls-Marcel-829263474.wav"
#define SOUND_DRY_FIRE_GUN "sounds/Dry Fire Gun-SoundBible.com-2053652037.wav"
#define SOUND_GUN_COCKING_SLOW "sounds/Gun_Cocking_Slow-Mike_Koenig-1019236976.wav"
#define SOUND_GUN_SHOT "sounds/Gun_Shot-Marvin-1140816320.wav"
#define SOUND_POP_CLIP_IN "sounds/Pop Clip In-SoundBible.com-583746573.wav"
#define SOUND_POWERUP_RAY "sounds/Power_Up_Ray-Mike_Koenig-800933783.wav"
#define SOUND_SNIPER_RIFLE "sounds/Sniper_Rifle-Kibblesbob-2053709564.wav"

#define SOUND_GLASS_BREAKING "sounds/vidro.wav"
#define SOUND_METAL_SHOT "sounds/metal.wav"
#define SOUND_WALKING "sounds/andar.wav"
#define SOUND_WALL_SHOT "sounds/parede.wav"

const char *soundFile[] = { SOUND_SHELL_FALLING, SOUND_SNIPER_RIFLE,
                             SOUND_POP_CLIP_IN, SOUND_GUN_COCKING_SLOW,
                             SOUND_GLASS_BREAKING, SOUND_METAL_SHOT,
                            SOUND_WALKING, SOUND_WALL_SHOT};
const char *songFile[] = { SONG_BACKGROUND  };

sf::SoundBuffer soundBuffer[NUMSOUNDS];
sf::Sound sound[NUMSOUNDS];

sf::Music song[NUMSONGS];

class Sounds{


    public:

    Sounds(){

        for(int i=0; i<NUMSOUNDS; i++){
            // Load a sound buffer
            if( !soundBuffer[i].loadFromFile(soundFile[i]) ){
                cout << "Failed loading sound to buffer: " << soundFile[i] << "\n";
                exit(0);
            }
            sound[i].setBuffer(soundBuffer[i]);
        }

        for(int i=0; i<NUMSONGS; i++){
            // Load a music file
            if( !song[i].openFromFile(songFile[i]) ){
                cout << "Failed loading sound to buffer: " << songFile[i] << "\n";
                exit(0);
            }
            song[i].setLoop(-1);
        }

    }

    void playSound( int i ){
        sound[i].play();
    }


    void playMusic(int i){
        song[i].play();
    }

    void playGunFiringSound(){
        playSound(1); //shoot
        playSound(0); //shell falls
    }

    void playReloadSound(){
        playSound(2);
        playSound(3);
    }

    void playCannotReloadSound(){
        playSound(2);
    }

    void playMetalSound(){
        playSound(5);
    }

    void playGlassBreakingSound(){
        playSound(4);
    }

    void playShotWallSound(){
        playSound(7);
    }

    void playWalkingSound(){
        //playSound(6); // é demasiado rápido xD
    }


};


#endif
