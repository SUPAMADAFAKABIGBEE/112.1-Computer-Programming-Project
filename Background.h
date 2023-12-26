//
//  Background.h
//  Project
//
//  Created by Richard on 2023/11/20.
//

#ifndef Background_h
#define Background_h

#include "Image.h"
#include <cstring>
#include "SDL.h"
#include <iostream>
using namespace std;

enum BackgroundName
{
    TITLE,
    SELECT,
    MINIGAME,
    RESULT,
    BACKGROUND_TOTAL
};

extern const char* BackgroundAddr[BACKGROUND_TOTAL];

class Background : public Image
{
    public:
        Background(int index) : Image(0, 0, 640, 480)
		{
			type = index;
			mTexture = loadBackground(BackgroundAddr[index]);
		}

        SDL_Texture* loadBackground(string path);
        
    private:
    	int type; //0: title, 1: select, 2: maingame, 3: result
};

#endif /* background_h */
