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
        void changeBackground(SDL_Event e);
};

#endif /* State_h */
