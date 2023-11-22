//
//  MaingameMusic.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef MaingameMusic_h
#define MaingameMusic_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

enum MaingameMusicName
{
    UmUsic,
    MAINGAMEMUSIC_TOTAL
};

class MaingameMusic
{
    public:
        int type;
        char* address;
        Mix_Music* gMaingameMusic = NULL;
        bool loadMaingameMusic(int index);
};

#endif /* MaingameMusic_h */
