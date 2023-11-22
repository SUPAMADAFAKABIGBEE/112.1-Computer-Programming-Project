//
//  State.h
//  Project
//
//  Created by Richard on 2023/11/20.
//

#ifndef State_h
#define State_h

#include <SDL2/SDL.h>

class State
{
    public:
        int BackgroundType = 0;
        int MaingameDifficulty = 0; //0: Easy, 1: Hard, 2: Insane
        int MaingameMusicType = -1;
        bool MaingameMusicEnable = 0; //Determine whether to play or not
        bool MaingameStart = 0;
        void changeMaingameMusic();
        void changeBackground(SDL_Event e);
        int detect(SDL_Event e);
};

#endif /* State_h */
