//
//  Image.h
//  Project
//
//  Created by Richard on 2023/12/5.
//

#ifndef Image_h
#define Image_h
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;


class Image
{
    
    protected:
        
        int mWidth=100;
        int mHeight=10;
        int posx;
        int posy;
    
    public:
    
        //Image(int , int );
        
        //virtual ~Image(){};
    
        // Deallocates texture
        void free();
    
        // ???
        SDL_Texture* loadImage(string path);
    
        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
    
        //Set blending
        void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        void setAlpha(Uint8 alpha);
    
    
        int getWidth(){return mWidth;};
        int getHeight(){return mHeight;};
        
    
        void setPosx(int x){posx = x;};
        void setPosy(int y){posy = y;};
        int getPosx(){return posx;};
        int getPosy(){return posy;};
    
    
        //The actual hardware texture
        SDL_Texture* mTexture;
    
    
    
};

#endif /* Image_h */
