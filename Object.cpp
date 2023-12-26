//
//  Object.cpp
//  Project
//
//  Created by Richard on 2023/12/5.
//

#include "Object.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

extern SDL_Renderer* gRenderer;

SDL_Texture* Object::load(string path)
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

void Object::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
        
void Object::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

SDL_Renderer*& operator<<(SDL_Renderer*& r, const Object& t)
{
	t.render();
	return r;
}

