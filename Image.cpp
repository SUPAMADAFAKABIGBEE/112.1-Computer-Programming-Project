//
//  Image.cpp
//  Project
//
//  Created by Richard on 2023/12/5.
//

#include "Image.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

extern SDL_Renderer* gRenderer;

void Image::render() const
{
	int _x = posx, _y = posy, _h = mHeight, _w = mWidth;
	SDL_Rect Viewport;
	Viewport.w = _w;
	Viewport.h = _h;
	Viewport.x = _x;
	Viewport.y = _y;
	SDL_RenderCopy(gRenderer, mTexture, NULL, &Viewport);
}

void Image::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
        
void Image::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

