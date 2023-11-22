//
//  Text.cpp
//  Project
//
//  Created by Richard on 2023/11/22.
//

#include "Text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

extern TTF_Font* gFont[FONT_TOTAL][10];
extern SDL_Renderer* gRenderer;

bool Text::loadFromRenderedText(string textureText, SDL_Color textColor, int index, int size)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont[index][size], textureText.c_str(), textColor);
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mText = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if( mText == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return mText != NULL;
}

void Text::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {posx, posy, visible ? mWidth : 0, visible ? mHeight : 0};

    //Set clip rendering dimensions
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mText, clip, &renderQuad, angle, center, flip);
    //cout << "Rendered with (x, y) = (" << x << ", " << y << ")" << endl;
}
