//
//  Text.h
//  Project
//
//  Created by Richard on 2023/11/22.
//

#ifndef Text_h
#define Text_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

enum FontName
{
    lazy,
    CaviarDreams,
    CaviarDreams_Italic,
    CaviarDreams_BoldItalic,
    CaviarDreams_Bold,
    FONT_TOTAL
};

class Text
{
    public:
        //Initializes variables
        Text(int a, int b, int c, int d)
        {
            mWidth = a;
            mHeight = b;
            posx = c;
            posy = d;
        }

        //Deallocates memory
        //~LTexture();

        //Loads image at specified path
        bool loadFromFile(string path );
        
        //Creates image from font string
        bool loadFromRenderedText(string textureText, SDL_Color textColor, int index);

        //Deallocates texture
        void free()
        {
            SDL_DestroyTexture(mText);
            mText = NULL;
        };

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        //Gets image dimensions
        int getWidth();
        int getHeight();
        int getPosx(){return posx;};
        int getPosy(){return posy;};
        void changeVisible(bool set){visible = set;};
    
        //The actual hardware texture
        SDL_Texture* mText;
        //TTF_Font* mFont = NULL;
        SDL_Color textColor = { 0, 0, 0 };

    private:
        //Image dimensions
        int mWidth;
        int mHeight;
        bool visible = 0;
        int posx;
        int posy;
};

#endif /* Text_h */
