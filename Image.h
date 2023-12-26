//
//  Image.h
//  Project
//
//  Created by Richard on 2023/12/5.
//

#ifndef Image_h
#define Image_h
#include "Object.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;


class Image : public Object
{
	protected:
		int mWidth=100;
        int mHeight=10;
        
    public:
    
    	Image(){} 
		Image(int a, int b, int c, int d) : mWidth(c), mHeight(d), Object(a, b){}
        Image(string path)
        {
        	mTexture = load(path);
		}
		~Image(){}

        void pass_file_location(string path)
        {
        	//added
			if(mTexture!=NULL){
				SDL_DestroyTexture(mTexture);
			} 
        	//added
        	mTexture = load(path);
        	if(mTexture==NULL)cout<<"fail"<<endl;
		}        
    
        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
    
        //Set blending
        void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        void setAlpha(Uint8 alpha);
    
    	void render() const; 
		
		void setWidth(int w){mWidth = w;}
        void setHeight(int h){mHeight = h;}
        void setAll(int x, int y, int w, int h)
        {
        	setPosx(x);
	        setPosy(y);
	        setWidth(w);
	        setHeight(h);
		}
		int getWidth() const {return mWidth;}
		int getHeight() const {return mHeight;}
		
};

#endif /* Image_h */
