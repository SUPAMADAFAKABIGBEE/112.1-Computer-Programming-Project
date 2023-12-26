//
//  PreviewMusic.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "PreviewMusic.h"
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
using namespace std;

extern const char* PreviewMusicAddr[3];

bool PreviewMusic::loadMusic(int index)
{
    bool success = true;
    gMusic = Mix_LoadMUS(PreviewMusicAddr[index]);
    if(gMusic == NULL)
    {
        printf( "Failed to load music!\n" );
        success = false;
    }
    return success;
}
