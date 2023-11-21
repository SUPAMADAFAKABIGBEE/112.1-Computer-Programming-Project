//
//  Judgeline.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "Judgeline.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
using namespace std;

extern SDL_Renderer* gRenderer;

SDL_Texture* Judgeline::loadJudgeline(string path)
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
    }

    return newTexture;
}

bool Judgeline::loadJudgeline(int index)
{
    bool success = true;
    mTexture = loadJudgeline(JudgelineAddr[index]);
    if(mTexture == NULL)
    {
        printf( "Failed to load judgelines!\n" );
        success = false;
    }
    return success;
}

void Judgeline::render(int BackgroundType, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, BackgroundType == 2 ? mWidth : 0, BackgroundType == 2 ? mHeight : 0};

    //Set clip rendering dimensions
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void Judgeline::pressed()
{
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_SetTextureColorMod(mTexture, 100, 100, 100);
}

/*
void Judgeline::detect(SDL_Event e, int index)
{
    switch(e.key.keysym.sym)
    {
        case SDLK_D:
            if(index == 0) pressed();
        case SDLK_F:
            if(index == 1) pressed();
        case SDLK_J:
            if(index == 2) pressed();
        case SDLK_K:
            if(index == 3) pressed();
        default:
            break;
    }
}
*/
