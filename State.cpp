//
//  State.cpp
//  Project
//
//  Created by Richard on 2023/11/20.
//

#include "State.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

//Background
//0: title, 1: select, 2: maingame, 3: result

void State::changeMaingameMusic()
{
    if(BackgroundType == 2)
    {
        MaingameMusicType = 0;
    }
    else
    {
        MaingameMusicType = -1;
    }
    
    if(BackgroundType == 1) MaingameMusicEnable = 1;
}

void State::changeBackground(SDL_Event e)
{
    if(e.key.keysym.sym == SDLK_ESCAPE)
    {
        if(BackgroundType == 1) BackgroundType = 0;
        else if(BackgroundType == 2) BackgroundType = 1;
    }
    else if(e.key.keysym.sym == SDLK_RETURN)
    {
        if(BackgroundType == 0) BackgroundType = 1;
        else if(BackgroundType == 1)
        {
            MaingameStart = 1;
            BackgroundType = 2;
        }
    }
}

int State::detect(SDL_Event e)
{
    switch(e.key.keysym.sym)
    {
        case SDLK_d:
            return 0;
            break;
        case SDLK_f:
            return 1;
            break;
        case SDLK_j:
            return 2;
            break;
        case SDLK_k:
            return 3;
            break;
        default:
            return -1;
            break;
    }
}

void State::GettingDim5()
{
    r -= 5;
    g -= 5;
    b -= 5;
}

void State::ResetRGB()
{
    r = 255;
    g = 255;
    b = 255;
}
