//
//  Songfile.cpp
//  Project
//
//  Created by Richard on 2023/11/29.
//

#include <iostream>
#include <cmath>
#include "Songfile.h"

extern SDL_Renderer* gRenderer;
extern const char* ButtonAddr[];
//extern const char* SongfileAddr[];
extern const char* JudgelineAddr[];

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

const int Num_Of_Songs = 3;
enum song{
	song1 = 0, song2
};
const char* picture_file_location[Num_Of_Songs] = {"./Song/songselection1.png", "./Song/songselection2.png", "./Song/songselection3.png"};
const char* songcover_location[Num_Of_Songs] = {"./Song/UmUsic.png", "./Song/biri-biri.png", "./Song/LastStardust.png"};

int Songfile::MusicType = 0;

ostream& operator<<(ostream &output,Songfile &s){
	s.getInfo().render();
	return output;
}

void SongSelecting(Songfile* s, bool SelectDiff){
	if(SelectDiff){
		s[Songfile::MusicType].getTag().setAll(100 , 120, 150.0*1.5, 100.0*1.5 );
		s[Songfile::MusicType].getTag().render();
	}
	else if(!SelectDiff){
		for(int i = 2; i >= 0; i--)
		{		
			s[(Songfile::MusicType + i) % 3].getTag().setAll(100 - 20 * i, 160 - 30 * i, 150.0 * pow(1.2, 2 - i), 100.0 * pow(1.2, 2 - i));
			s[(Songfile::MusicType + i) % 3].getTag().render();
		}
	}

}
