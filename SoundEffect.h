//
//  SoundEffect.h
//  Project
//
//  Created by Richard on 2023/11/22.
//

#ifndef SoundEffect_h
#define SoundEffect_h

#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"

enum SoundEffectName
{
    HITSOUND,
    SOUNDEFFECT_TOTAL
};

class SoundEffect
{
    public:
        int type;
        char* address;
        Mix_Chunk* gSoundEffect = NULL;
        bool loadSoundEffect(int index);
};

#endif /* SoundEffect_h */
