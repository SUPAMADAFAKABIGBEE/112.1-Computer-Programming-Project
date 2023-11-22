//
//  SoundEffect.cpp
//  Project
//
//  Created by Richard on 2023/11/22.
//

#include "SoundEffect.h"
#include <iostream>

extern const char* SoundEffectAddr[SOUNDEFFECT_TOTAL];

bool SoundEffect::loadSoundEffect(int index)
{
    bool success = true;
    gSoundEffect = Mix_LoadWAV(SoundEffectAddr[index]);
    if(gSoundEffect == NULL )
    {
        printf( "Failed to SFX!\n" );
        success = false;
    }
    return success;
}
