//
//  MaingameMusic.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "MaingameMusic.h"
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
using namespace std;

extern const char* MaingameMusicAddr[MAINGAMEMUSIC_TOTAL];

bool MaingameMusic::loadMusic(int index)
{
    bool success = true;
    gMusic = Mix_LoadMUS(MaingameMusicAddr[index]);
    if(gMusic == NULL )
    {
        printf( "Failed to load music!\n" );
        success = false;
    }
    return success;
}
