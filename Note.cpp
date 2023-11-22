//
//  Note.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "Note.h"
#include "SoundEffect.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

extern SDL_Renderer* gRenderer;
extern SoundEffect mSoundEffect[SOUNDEFFECT_TOTAL];

SDL_Texture* Note::loadNote(string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
        //cout << "load Success!!" << endl;
    }

    return newTexture;
}

void Note::render(int& posx, int& posy, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, int goalx, int goaly, int speed, int time)
{
    posx = goalx;
    posy = goaly - 80 * speed * time / 1000;
    //cout << "rendered at (" << posx << ", " << posy << ")" << endl;
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {posx, posy, mWidth, mHeight};

    //Set clip rendering dimensions
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
    //cout << "Rendered with (x, y) = (" << x << ", " << y << ")" << endl;
}

bool Note::judge(int judgeGoal, int time, GameInfo* mGameinfo)
{
    if(judgeGoal == goal)
    {
        if(-40 <= time && time <= 40)
        {
            mGameinfo->perfect++;
        }
        else if(-80 <= time && time <= 80)
        {
            mGameinfo->great++;
        }
        else if(-160 <= time && time <= 160)
        {
            mGameinfo->good++;
        }
        else if(-240 <= time && time <= 240)
        {
            mGameinfo->fair++;
        }
        else return 0;
        mGameinfo->calculate();
        return 1;
    }
    else return 0;
}

void Note::playsfx()
{
    Mix_PlayChannel(-1, mSoundEffect[HITSOUND].gSoundEffect, 0);
}
