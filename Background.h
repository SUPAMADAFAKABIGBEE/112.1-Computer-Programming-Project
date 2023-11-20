//
//  Background.h
//  Project
//
//  Created by Richard on 2023/11/20.
//

#ifndef Background_h
#define Background_h

#include <cstring>
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

const char* addr[] = {"./Background/title.bmp", "./Background/select.bmp", "./Background/maingame.bmp", "./Background/result.bmp"};

enum BackgroundNames
{
    TITLE,
    SELECT,
    MINIGAME,
    RESULT,
    BACKGROUND_TOTAL
};

class Background
{
    public:
        
        int type; //0: title, 1: select, 2: maingame, 3: result
        char* address;
        SDL_Surface* gBackground = NULL;
        SDL_Surface* loadBackgroundSurface( std::string path );
        bool loadBackground(int index);
};

#endif /* background_h */