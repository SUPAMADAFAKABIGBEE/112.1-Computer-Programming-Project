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
        int MaingameMusicType = -1;
        bool MaingameMusicEnable = 0; //Determine whether to play or not
        void changeMaingameMusic();
        void changeBackground(SDL_Event e);
        int detect(SDL_Event e);
};

#endif /* State_h */
