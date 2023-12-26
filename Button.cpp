//
//  Button.cpp
//  Project
//
//  Created by Richard on 2023/11/24.
//

#include "Button.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

extern SDL_Renderer* gRenderer;
extern const char* ButtonAddr[];

void Button::pressed() const
{
    SDL_SetTextureColorMod(mTexture, 100, 100, 100);
}

void Button::unpressed() const
{
    SDL_SetTextureColorMod(mTexture, 255, 255, 255);
}

void Button::setType(int t)
{
    type = t;
    mTexture = load(ButtonAddr[type]);
}

