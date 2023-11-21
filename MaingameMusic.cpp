//
//  MaingameMusic.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "MaingameMusic.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

bool MaingameMusic::loadMaingameMusic(int index)
{
    bool success = true;
    gMaingameMusic = Mix_LoadMUS(MaingameMusicAddr[index]);
    if(gMaingameMusic == NULL )
    {
        printf( "Failed to load music!\n" );
        success = false;
    }
    return success;
}
