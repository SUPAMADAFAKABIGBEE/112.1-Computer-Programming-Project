//
//  PreviewMusic.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef PreviewMusic_h
#define PreviewMusic_h

#include "Music.h"
#include "SDL.h"
#include "SDL_mixer.h"

extern const char* PreviewMusicAddr[3];

class PreviewMusic : public Music
{
    public:
    	PreviewMusic(int index) : Music(index, PreviewMusicAddr[index])
    	{
			loadMusic(index);
		}
		~PreviewMusic()
		{
			Mix_FreeMusic(gMusic);
        	gMusic = NULL;
		}
        bool loadMusic(int index);
};

#endif /* PreviewMusic_h */
