//
//  Background.cpp
//  Project
//
//  Created by Richard on 2023/11/20.
//

#include "Background.h"
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

SDL_Surface* Background::loadBackgroundSurface(string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}

bool Background::loadBackground(int index)
{
    bool success = true;
    gBackground = loadBackgroundSurface(BackgroundAddr[index]);
    if(gBackground == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }
    return success;
}

