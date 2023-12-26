//
//  Bar.h
//  Project
//
//  Created by Richard on 2023/12/24.
//

#ifndef Bar_h
#define Bar_h
#include "Image.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;


class Bar : public Image
{
    private:
    	bool initialized = 0;
    	int order;
        
    public:
    	Bar(){}
		Bar(int hittime) : Image(5, 240.0 + (hittime / 240.0) * 50.0, 5, 1)
		{
			mTexture = load("./Element/bar.png");
			setAlpha(255);
			order = totalBar;
			totalBar++;
			initialized = 1;
		}
		~Bar()
		{
			if(initialized == 1)
			{
				totalBar--;
			}
		}
		
		void changeAlpha();
		
		static int totalBar;
		static void resetTotal(){totalBar = 0;}
		
};

#endif /* Bar_h */
