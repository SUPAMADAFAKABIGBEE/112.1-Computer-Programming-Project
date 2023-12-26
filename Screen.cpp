#include <iostream>
#include <cmath>
#include "Screen.h"

extern const char* ScreenButton[];
extern SDL_Renderer* gRenderer; 

void Screen::projecting(int music, int difficulty, Songfile* s,bool SelectDiff){
	cout<<s[(music) % 3];
	if(SelectDiff){
		for(int i=0;i<3;i++){
			if(i == difficulty) buttoms[i].pass_file_location(ScreenButton[i+3]);
			else buttoms[i].pass_file_location(ScreenButton[i]);
			buttoms[i].setAll( 40+100*i, 250, 150, 150);
			gRenderer << *(Object*)(&buttoms[i]);
		}
	}
}

