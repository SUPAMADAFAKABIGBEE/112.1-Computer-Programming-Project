//
//  Judgeline.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "Judgeline.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

extern SDL_Renderer* gRenderer;
extern const char* JudgelineAddr[JUDGELINE_TOTAL];
extern int BEATMAPPARAMS_TOTAL;

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

bool Judgeline::loadByIndex(int index)
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

void Judgeline::render(int BackgroundType, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, int time, long double Mi)
{
    //currentMovement = 0
    double portion;
    
    if(inited)
    {
        //cout << "Type " << type << " time = " << time << ", dtime = " << movementMap[currentMovement][1] * Mi << endl;
        while(currentMovement < movementAmount)
        {
            if(time >= movementMap[currentMovement][1] * Mi) currentMovement++;
            else break;
        }
        //if(type == 0) cout << "Type " << type << " current = " << currentMovement << endl;
        
        if(currentMovement == 0)
        {
            portion = (time - (-3000.0)) / (movementMap[0][1] * Mi - (-3000.0));
            //if(type == 0) cout << "Type " << type << " at " << portion << endl;
            //cout << "Type " << type << " with " << initx << " and " << inity << endl;
            posx = initx + portion * (double)(movementMap[0][4] - initx);
            posy = inity + portion * (double)(movementMap[0][5] - inity);
            degree = initDegree + portion * (double)(movementMap[0][8]/10.0 - initDegree);
            //if(type == 0) cout << "Type " << type << " at (" << posx << ", " << posy << ")" << endl;
        }
        else if(currentMovement < movementAmount)
        {
            portion = (time - movementMap[currentMovement - 1][1] * Mi) / (movementMap[currentMovement][1] * Mi - movementMap[currentMovement - 1][1] * Mi);
            //if(type == 0) cout << "Type " << type << " at " << portion << endl;
            posx = movementMap[currentMovement - 1][4] + portion * (movementMap[currentMovement][4] - movementMap[currentMovement - 1][4]);
            posy = movementMap[currentMovement - 1][5] + portion * (movementMap[currentMovement][5] - movementMap[currentMovement - 1][5]);
            degree = movementMap[currentMovement - 1][8]/10.0 + portion * (double)(movementMap[currentMovement][8]/10.0 - movementMap[currentMovement - 1][8]/10.0);
            //if(type == 0) cout << "Type " << type << " at (" << posx << ", " << posy << ")" << endl;
        }
    }
    
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {posx, posy, BackgroundType == 2 ? mWidth : 0, BackgroundType == 2 ? mHeight : 0};

    //Set clip rendering dimensions
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, degree, center, flip);
}

void Judgeline::unpressed()
{
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_SetTextureColorMod(mTexture, 255, 255, 255);
}

void Judgeline::pressed()
{
    //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_SetTextureColorMod(mTexture, 100, 100, 100);
}

void Judgeline::setMovementMap(int **data, int total)
{
    resetMovementAmount();
    resetCurrentMovement();
    movementMap = new int* [total];
    for(int i = 0; i < total; i++)
    {
        movementMap[i] = new int [BEATMAPPARAMS_TOTAL];
    }
    int index = 0;
    while(index < total)
    {
        if(data[index][3] == type)
        {
            for(int i = 0; i < BEATMAPPARAMS_TOTAL; i++)
            {
                movementMap[movementAmount][i] = data[index][i];
            }
            movementAmount++;
        }
        index++;
    }
    inited = 1;
    //printMovementMap();
}

void Judgeline::printMovementMap()
{
    cout << "MovementMap Order: " << type << endl;
    for(int i = 0; i < movementAmount; i++)
    {
        for(int j = 0; j < BEATMAPPARAMS_TOTAL; j++)
        {
            cout << movementMap[i][j] << " ";
        }
        cout << endl;
    }
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
