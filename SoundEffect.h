//
//  SoundEffect.h
//  Project
//
//  Created by Richard on 2023/11/22.
//

#ifndef SoundEffect_h
#define SoundEffect_h

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

const char* SoundEffectAddr[] = {"./SoundEffect/hitsound.mp3"};

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
