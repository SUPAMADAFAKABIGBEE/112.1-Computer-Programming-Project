//
//  Object.h
//  Project
//
//  Created by Richard on 2023/12/5.
//

#ifndef Object_h
#define Object_h
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;


class Object
{    
	protected:
		int posx;
		int posy;
    public:
    	Object(){}
    	Object(int a, int b) : posx(a), posy(b){};
		~Object()
		{
			free();
		}
    
        // Deallocates texture
        void free()
		{
			if(mTexture != NULL)
			{
				SDL_DestroyTexture(mTexture);
    			mTexture = NULL;
			}
		}
    
        virtual SDL_Texture* load(string path);
        virtual void pass_file_location(string path){}; 
    
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
    
    	virtual void render() const = 0;
        
    	void setPosx(int x){posx = x;}
        void setPosy(int y){posy = y;}
        
        int getPosx() const {return posx;}
        int getPosy() const {return posy;}
    
        //The actual hardware texture
        SDL_Texture* mTexture = NULL;
        
		friend SDL_Renderer*& operator<<(SDL_Renderer*& r, const Object& t);
};

#endif /* Object_h */
