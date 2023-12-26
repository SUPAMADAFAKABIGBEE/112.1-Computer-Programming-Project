
#define Screen_h

#include "Image.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Songfile.h"

using namespace std;


class Screen : public Image{
	
	public :
		Screen(int a, int b, int c, int d){
			posx = a;
            posy = b;
            mWidth = c;
            mHeight = d;
			mTexture = load("./Song/screen_image2.png");
			buttoms = new Image [3] ;
			for(int i = 0 ; i < 3; i++){
				buttoms[i].pass_file_location("./Song/test1.png");
			} 
		}
		~Screen(){
			delete [] buttoms;
		}
		void projecting(int nows, int difficulty, Songfile* s,bool SelectDiff);
		
	private : 
		int index ;
		Image* buttoms;
};
