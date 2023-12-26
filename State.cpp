//
//  State.cpp
//  Project
//
//  Created by Richard on 2023/11/20.
//

#include "State.h"
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
using namespace std;

//Background
//0: title, 1: select, 2: maingame, 3: result

void State::changeMaingameMusic(SDL_Event e)
{
    if(BackgroundType == 1)
	{
		if(MaingameMusicType == -1) MaingameMusicType = 0;
		MaingameMusicEnable = 1;
	}
	if(e.key.keysym.sym == SDLK_s && !ChooseDifficult)
    {
    	MaingameMusicType++;
    	MaingameMusicType %= 3;
	}
	else if(e.key.keysym.sym == SDLK_w && !ChooseDifficult)
	{
		MaingameMusicType--;
		if(MaingameMusicType < 0)
		{
			MaingameMusicType += 3;
		}
	}
	
	if(BackgroundType == 2)
    {
        MaingameMusicType = 0;
    }
}

void State::changeMaingameDifficulty(SDL_Event e)
{
    if(BackgroundType == 1)
	{
		if(MaingameDifficulty == -1)MaingameDifficulty = 0;
		MaingameMusicEnable = 1;
		if(e.key.keysym.sym == SDLK_d && ChooseDifficult)
	    {
	    	MaingameDifficulty++;
	    	MaingameDifficulty %= 3;
		}
		else if(e.key.keysym.sym == SDLK_a && ChooseDifficult)
		{
			MaingameDifficulty--;
			if(MaingameDifficulty < 0)
			{
				MaingameDifficulty += 3;
			}
		}
	}
}

void State::changeMaingamePauseState(SDL_Event e)
{
    if(MaingamePause)
    {
        if(e.key.keysym.sym == SDLK_a)
        {
            if(MaingamePauseState != 0) MaingamePauseState--;
        }
        else if(e.key.keysym.sym == SDLK_d)
        {
            if(MaingamePauseState < 1) MaingamePauseState++;
        }
        else if(e.key.keysym.sym == SDLK_RETURN)
        {
            changeByPauseState();
        }
    }
}

void State::changeByPauseState()
{
    switch(MaingamePauseState)
    {
        case 0:
            MaingamePause = 0;
            break;
        case 1:
            MaingameStart = 0;
            MaingamePause = 0;
            BackgroundType = 1;
            MaingameMusicEnable = 1;
            MaingamePauseState = 0;
            break;
    }
}

void State::changeBackground(SDL_Event e)
{
	if(e.key.keysym.sym == SDLK_ESCAPE)
    {
        if(BackgroundType == 1)
        {
        	if(ChooseDifficult == 1){
 				ChooseDifficult = 0;
 				MaingameDifficulty = -1;
 				//等等加上去
			}
			else if(ChooseDifficult == 0){
				 BackgroundType = 0;
			}
		}
        else if(BackgroundType == 2)
        {
            MaingamePause = !MaingamePause;
        }
    }
    else if(e.key.keysym.sym == SDLK_RETURN)
    {
        if(BackgroundType == 0) BackgroundType = 1;
        else if(BackgroundType == 1 )
        {
        	if(ChooseDifficult == 1){
        		MaingameStart = 1;
            	BackgroundType = 2;
			}
			else if(ChooseDifficult == 0){
				ChooseDifficult = 1;
			}
        }
        else if(BackgroundType == 3)
        {
        	BackgroundType = 1;
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
