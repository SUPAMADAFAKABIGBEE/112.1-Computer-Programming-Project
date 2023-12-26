//
//  Judgeline.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "Judgeline.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

extern SDL_Renderer* gRenderer;
extern const char* JudgelineAddr[JUDGELINE_TOTAL];
extern int BEATMAPPARAMS_TOTAL;

void Judgeline::render(int time, long double Mi)
{
    double portion;
    
    if(inited)
    {
        while(currentMovement < movementAmount)
        {
            if(time >= movementMap[currentMovement][1] * Mi) currentMovement++;
            else break;
        }
        
        if(currentMovement == 0)
        {
            portion = (time - (-3000.0)) / (movementMap[0][1] * Mi - (-3000.0));
            posx = initx + portion * (double)(movementMap[0][4] - initx);
            posy = inity + portion * (double)(movementMap[0][5] - inity);
            degree = initDegree + portion * (double)(movementMap[0][8]/10.0 - initDegree);
        }
        else if(currentMovement < movementAmount)
        {
            portion = (time - movementMap[currentMovement - 1][1] * Mi) / (movementMap[currentMovement][1] * Mi - movementMap[currentMovement - 1][1] * Mi);
            posx = movementMap[currentMovement - 1][4] + portion * (movementMap[currentMovement][4] - movementMap[currentMovement - 1][4]);
            posy = movementMap[currentMovement - 1][5] + portion * (movementMap[currentMovement][5] - movementMap[currentMovement - 1][5]);
            degree = movementMap[currentMovement - 1][8]/10.0 + portion * (double)(movementMap[currentMovement][8]/10.0 - movementMap[currentMovement - 1][8]/10.0);
        }
    }
    
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {posx, posy, mWidth, mHeight};

    //Render to screen
    SDL_RenderCopyEx(gRenderer, mTexture, NULL, &renderQuad, degree, NULL, SDL_FLIP_NONE);
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
