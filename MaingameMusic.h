//
//  MaingameMusic.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef MaingameMusic_h
#define MaingameMusic_h

#include "Music.h"
#include "SDL.h"
#include "SDL_mixer.h"

enum MaingameMusicName
{
    UmUsic,
    MAINGAMEMUSIC_TOTAL
};

extern const char* MaingameMusicAddr[MAINGAMEMUSIC_TOTAL];

class MaingameMusic : public Music
{
    public:
    	MaingameMusic(int index) : Music(index, MaingameMusicAddr[index])
    	{
			loadMusic(index);
		}
		~MaingameMusic()
		{
			Mix_FreeMusic(gMusic);
        	gMusic = NULL;
		}
        bool loadMusic(int index);
};

#endif /* MaingameMusic_h */
