//
//  Judgeline.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef Judgeline_h
#define Judgeline_h
#include "Image.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

enum JudgelineName
{
    SDLK_D,
    SDLK_F,
    SDLK_J,
    SDLK_K,
    JUDGELINE_TOTAL
};

class Judgeline : public Image
{
    public:
        //Initializes variables
        //Judgeline(): Image(100, 10) {};
        Judgeline(){};

        //Deallocates memory
        ~Judgeline()
        {
            /*
            for(int i = 0; i < maxCombo; i++) delete [] beatmap[i];
            delete [] beatmap;
             */
        }

        //Deallocates texture
        //void free();

        //Set color modulation
        //void setColor(Uint8 red, Uint8 green, Uint8 blue);

        //Set blending
        //void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        //void setAlpha(Uint8 alpha);
        
        SDL_Texture* loadJudgeline(string path);
        bool loadByIndex(int index);
    
        //Renders texture at given point
        void render(int BackgroundType, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, int time, long double Mi);
        
        void unpressed();
        void pressed();
        //void detect(SDL_Event e, int index);
        
        //Gets image dimensions
        //int getWidth(){return mWidth;};
        //int getHeight(){return mHeight;};
        
        //int getPosx(){return posx;};
        //int getPosy(){return posy;};
        int getMovementAmount(){return movementAmount;};
        void setPosx(int x){posx = x;};
        void setPosy(int y){posy = y;};
        void setInitx(int x){initx = x;};
        void setInity(int y){inity = y;};
        void setInitDegree(int d){initDegree = d/10.0;};
        void setType(int index){type = index;};
    
        int **movementMap;
        
        void setMovementMap(int **data, int total);
        void resetMovementAmount(){movementAmount = 0;};
        void resetCurrentMovement(){currentMovement = 0;};
        void printMovementMap();
    
        //The actual hardware texture
        //SDL_Texture* mTexture;

    
    private:
        //Image dimensions
        //int mWidth = 100;
        //int mHeight = 10;
        int initx;
        int inity;
        double initDegree;
        //int posx = -100;
        //int posy = -100;
        double degree = 0.0;
        int type;
        bool inited = 0;
        //int maxCombo;
        int movementAmount = 0;
        int currentMovement = 0;
};

#endif /* Judgeline_h */
