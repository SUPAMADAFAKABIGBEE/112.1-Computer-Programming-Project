//
//  Button.h
//  Project
//
//  Created by Richard on 2023/11/24.
//

#ifndef Button_h
#define Button_h
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

enum PauseButtonName
{
    continuE,
    closE,
    PAUSEBUTTON_TOTAL
};

class Button
{
    public:
        //Initializes variables
        Button(int x, int y)
        {
            posx = x;
            posy = y;
        }

        //Deallocates memory
        ~Button()
        {
            /*
            for(int i = 0; i < maxCombo; i++) delete [] beatmap[i];
            delete [] beatmap;
             */
        }

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        //Set blending
        void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        void setAlpha(Uint8 alpha);
        
        SDL_Texture* loadButton(string path);
        bool loadByIndex(int index);
    
        //Renders texture at given point
        void render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
        
        void unpressed();
        void pressed();
        //void detect(SDL_Event e, int index);
        
        //Gets image dimensions
        int getWidth(){return mWidth;};
        int getHeight(){return mHeight;};
        
        int getPosx(){return posx;};
        int getPosy(){return posy;};
        void setPosx(int x){posx = x;};
        void setPosy(int y){posy = y;};
        void setType(int t)
        {
            type = t;
            loadByIndex(type);
        }
    
        //The actual hardware texture
        SDL_Texture* mTexture;

    private:
        //Image dimensions
        int mWidth = 50;
        int mHeight = 50;
        int posx = -100;
        int posy = -100;
        int type;
};

#endif /* Button_h */
