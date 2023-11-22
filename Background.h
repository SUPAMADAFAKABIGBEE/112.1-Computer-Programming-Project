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

enum BackgroundName
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
        Background(){};
    
        int type; //0: title, 1: select, 2: maingame, 3: result
        char* address;
        SDL_Texture* gBackground = NULL;
        SDL_Texture* loadBackground(string path);
        bool loadByIndex(int index);
};

#endif /* background_h */
