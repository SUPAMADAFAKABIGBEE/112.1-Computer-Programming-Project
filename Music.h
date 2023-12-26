//
//  Music.h
//  Project
//
//  Created by Richard on 2023/12/6.
//

#ifndef Music_h
#define Music_h

#include "SDL.h"
#include "SDL_mixer.h"

class Music
{
    protected:
        int type;
        const char* address;
        Mix_Music* gMusic = NULL;
        
    public:
    	Music(int i, const char* a);
    	virtual bool loadMusic(int index) = 0;
    	Mix_Music*& getGMusic(){return gMusic;} 
};

#endif /* Music_h */
