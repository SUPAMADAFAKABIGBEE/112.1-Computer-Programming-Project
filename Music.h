//
//  Music.h
//  Project
//
//  Created by Richard on 2023/12/6.
//

#ifndef Music_h
#define Music_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Music
{
    protected:
        int type;
        char* address;
        Mix_Music* gMusic = NULL;
        virtual bool loadMusic(int index);
};

#endif /* Music_h */
