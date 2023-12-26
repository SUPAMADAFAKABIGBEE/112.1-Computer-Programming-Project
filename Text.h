//
//  Text.h
//  Project
//
//  Created by Richard on 2023/11/22.
//

#ifndef Text_h
#define Text_h
#include "Object.h"
#include "SDL.h"
#include "SDL_ttf.h"
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

class Text : public Object
{
    public:
    	Text(){}
        Text(int a, int b, int c, int d) : mWidth(c), mHeight(d), Object(a, b){}
		
        ~Text(){}

        bool loadFromRenderedText(string textureText, SDL_Color textColor, int index, int size);

        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        void setBlendMode( SDL_BlendMode blending );
        void setAlpha( Uint8 alpha );
        
        void render() const;

        //Gets image dimensions
        void setWidth(int w){mWidth = w;}
        void setHeight(int h){mHeight = h;}
        void setAll(int x, int y, int w, int h)
        {
        	setPosx(x);
	        setPosy(y);
	        setWidth(w);
	        setHeight(h);
		}
        int getWidth();
        int getHeight();
        int getPosx(){return posx;};
        int getPosy(){return posy;};
        int getWidth() const {return mWidth;}
		int getHeight() const {return mHeight;}
        int getTrans(){return trans;};
        void changeVisible(bool set){visible = set;};
        
        void minusTrans5();
        void ResetTrans();
        
        SDL_Color textColor = { 0, 0, 0 };
	
	private:
		int mWidth=100;
        int mHeight=10;
        bool visible = 0;
        int trans = 255;
};

#endif /* Text_h */
