//
//  Note.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "Note.h"
#include <iostream>
#include "SDL.h"
#include <cmath>
#include "SDL_image.h"
#include "SDL_mixer.h"
#define PI 3.1415926
using namespace std;

extern SDL_Renderer* gRenderer;

void Note::render(int time, long double Mi)
{
    double portion = (time - stime * Mi) / (dtime * Mi - stime * Mi);
    double nowdegree = sdegree + portion * (ddegree - sdegree);
    if(result == -1)
    {
        if(portion >= 1) SDL_SetTextureColorMod(mTexture, 0 < 255 - 150 * portion ? 255 - 150 * portion : 0, 0 < 255 - 150 * portion ? 255 - 150 * portion : 0, 0 < 255 - 150 * portion ? 255 - 150 * portion : 0);
        setPosx(endx + sin(ddegree * PI / 180.0) * 80.0 * speed * (dtime * Mi - time) / 1000.0);
        setPosy(endy - cos(ddegree * PI / 180.0) * 80.0 * speed * (dtime * Mi - time) / 1000.0);
        nowdegree = sdegree + portion * (ddegree - sdegree);
    }
    else if(1 <= result && result <= 4)
    {
        SDL_SetTextureColorMod(mTexture, 255, 255, 255);
        setPosx(endx + sin(ddegree * PI / 180.0) * 75.0);
        setPosy(endy - cos(ddegree * PI / 180.0) * 75.0 - 75.0);
        nowdegree = ddegree;
    }
    else
    {
    	setPosx(-400);
    	setPosy(-400);
	}
    SDL_Rect renderQuad = {posx, posy, mWidth, mHeight};

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, NULL, &renderQuad, nowdegree, NULL, SDL_FLIP_NONE);
}

bool Note::judge(int judgeGoal, int time, GameInfo* mGameinfo, long double Mi)
{
    //mNote[i].getdtime() * Mi - (int)SDL_GetTicks() + (int)startTime
    if(result == -1 && judgeGoal == goal)
    {
        hittime = time;
        timedif = dtime * Mi - time;
		if(-40 <= timedif && timedif <= 40)
        {
			adjust(4, *mGameinfo);
            mHeight = 160;
            mTexture = load("./Element/perfect.png");
            trans = 120;
            result = 4;
        }
        else if(-80 <= timedif && timedif <= 80)
        {
            adjust(3, *mGameinfo);
            mHeight = 160;
            mTexture = load("./Element/great.png");
            trans = 120;
            result = 3;
        }
        else if(-160 <= timedif && timedif <= 160)
        {
            adjust(2, *mGameinfo);
            mHeight = 160;
            mTexture = load("./Element/good.png");
            trans = 120;
            result = 2;
        }
        else if(-240 <= timedif && timedif <= 240)
        {
            adjust(1, *mGameinfo);
            mHeight = 160;
            mTexture = load("./Element/fair.png");
            trans = 120;
            result = 1;
        }
        else return 0;
        mGameinfo->calculate();
        return 1;
    }
    else return 0;
}

void Note::printNoteInfo()
{
    cout << stime << " " << dtime << " " << type << " " << goal << " " << endx << " " << endy << " " << speed << endl;
}

/*
void Note::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
*/

/*
void Note::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}
*/
 
Uint8 Note::setTrans(int time)
{
    if(result != -1 && result != 5 && result != 0)
    {
        if(time - hittime <= 240)
		{
			trans = 120 * (1 - (time - hittime) / 240.0);
		}
		else trans = 0;
    }
    return trans;
}
