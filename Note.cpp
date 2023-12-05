//
//  Note.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "Note.h"
//#include "SoundEffect.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#define PI 3.1415926
using namespace std;

extern SDL_Renderer* gRenderer;
//extern SoundEffect mSoundEffect[SOUNDEFFECT_TOTAL];

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
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
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

void Note::render(int& posx, int& posy, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, int goalx, int goaly, int speed, int time, long double Mi)
{
    double portion = (time - stime * Mi) / (dtime * Mi - stime * Mi);
    double nowdegree = sdegree + portion * (ddegree - sdegree);
    if(result == -1)
    {
        if(portion >= 1) SDL_SetTextureColorMod(mTexture, 255 - 150 * portion, 255 - 150 * portion, 255 - 150 * portion);
        posx = goalx + sin(ddegree * PI / 180.0) * 80.0 * speed * (dtime * Mi - time) / 1000.0;
        posy = goaly - cos(ddegree * PI / 180.0) * 80.0 * speed * (dtime * Mi - time) / 1000.0;
        nowdegree = sdegree + portion * (ddegree - sdegree);
    }
    else
    {
        SDL_SetTextureColorMod(mTexture, 255, 255, 255);
        posx = goalx + sin(ddegree * PI / 180.0) * 75.0;
        posy = goaly - cos(ddegree * PI / 180.0) * 75.0 - 75.0;
        nowdegree = ddegree;
    }
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
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, nowdegree, center, flip);
    //cout << "Rendered with (x, y) = (" << x << ", " << y << ")" << endl;
}

bool Note::judge(int judgeGoal, int time, GameInfo* mGameinfo, long double Mi)
{
    hittime = time;
    int timedif = dtime * Mi - time;
    //mNote[i].getdtime() * Mi - (int)SDL_GetTicks() + (int)startTime
    if(result == -1 && judgeGoal == goal)
    {
        if(-40 <= timedif && timedif <= 40)
        {
            mGameinfo->perfect++;
            mGameinfo->passNote++;
            mGameinfo->currentCombo++;
            mHeight = 160;
            mTexture = loadNote("./Element/perfect.png");
            trans = 120;
            result = 4;
        }
        else if(-80 <= timedif && timedif <= 80)
        {
            mGameinfo->great++;
            mGameinfo->passNote++;
            mGameinfo->currentCombo++;
            mHeight = 160;
            mTexture = loadNote("./Element/great.png");
            trans = 120;
            result = 3;
        }
        else if(-160 <= timedif && timedif <= 160)
        {
            mGameinfo->good++;
            mGameinfo->passNote++;
            mGameinfo->currentCombo++;
            mHeight = 160;
            mTexture = loadNote("./Element/good.png");
            trans = 120;
            result = 2;
        }
        else if(-240 <= timedif && timedif <= 240)
        {
            mGameinfo->fair++;
            mGameinfo->passNote++;
            mGameinfo->cutCombo();
            mHeight = 160;
            mTexture = loadNote("./Element/fair.png");
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
    if(result != -1)
    {
        trans = 120 * (1 - (time - hittime) / 240.0);
        if(trans < 0) trans = 0;
    }
    return trans;
}

/*
 void Note::playsfx()
 {
 Mix_PlayChannel(-1, mSoundEffect[HITSOUND].gSoundEffect, 0);
 }
 */
