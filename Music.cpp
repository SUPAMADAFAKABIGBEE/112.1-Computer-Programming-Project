//
//  Music.cpp
//  Project
//
//  Created by Richard on 2023/12/6.
//

#include "Music.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

bool mMusic::loadMusic(int index)
{
    bool success = true;
    gMaingameMusic = Mix_LoadMUS(MaingameMusicAddr[index]);
    if(gMusic == NULL )
    {
        printf( "Failed to load music!\n" );
        success = false;
    }
    return success;
}
