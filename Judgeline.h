//
//  Judgeline.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef Judgeline_h
#define Judgeline_h
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

class Judgeline
{
    public:
        //Initializes variables
        Judgeline(){};

        //Deallocates memory
        //~Judgeline();

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        //Set blending
        void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        void setAlpha(Uint8 alpha);
        
        SDL_Texture* loadJudgeline(string path);
        bool loadByIndex(int index);
    
        //Renders texture at given point
        void render(int BackgroundType, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        void unpressed();
        void pressed();
        //void detect(SDL_Event e, int index);
        
        //Gets image dimensions
        int getWidth(){return mWidth;};
        int getHeight(){return mHeight;};
    
        int posx;
        int posy;
    
        //The actual hardware texture
        SDL_Texture* mTexture;

    private:
        //Image dimensions
        int mWidth = 100;
        int mHeight = 10;
};

#endif /* Judgeline_h */
