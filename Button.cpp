//
//  Button.cpp
//  Project
//
//  Created by Richard on 2023/11/24.
//

#include "Button.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

extern SDL_Renderer* gRenderer;
extern const char* ButtonAddr[];

SDL_Texture* Button::loadButton(string path)
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

bool Button::loadByIndex(int index)
{
    bool success = true;
    mTexture = loadButton(ButtonAddr[index]);
    if(mTexture == NULL)
    {
        printf( "Failed to load button!\n" );
        success = false;
    }
    return success;
}

void Button::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    
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
}

void Button::pressed()
{
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_SetTextureColorMod(mTexture, 255, 255, 255);
}

void Button::unpressed()
{
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_SetTextureColorMod(mTexture, 100, 100, 100);
}

