//
//  Text.cpp
//  Project
//
//  Created by Richard on 2023/11/22.
//

#include "Text.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
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
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        //setBlendMode( );
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        if( mTexture == NULL )
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
    return mTexture != NULL;
}

void Text::render() const 
{
	int _x = posx, _y = posy, _h = mHeight, _w = mWidth;
	SDL_Rect Viewport;
	Viewport.w = _w;
	Viewport.h = _h;
	Viewport.x = visible ? _x : -300;
	Viewport.y = visible ? _y : -300;
	SDL_RenderCopy(gRenderer, mTexture, NULL, &Viewport);
}

void Text::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
        
void Text::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Text::minusTrans5()
{
    trans -= 5;
}

void Text::ResetTrans()
{
    trans = 255;
}
