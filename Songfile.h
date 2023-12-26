//
//  Songfile.h
//  Project
//
//  Created by Richard on 2023/11/29.
//

#ifndef Songfile_h
#define Songfile_h

#include "Button.h"
#include "Image.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

extern const char* SongfileAddr[];
extern const char* picture_file_location[];
extern const char* songcover_location[];

enum songselected{
    Song1,
    Song2,
    Songtotal
};

class Songfile{
    
	friend ostream& operator<<(ostream &output,Songfile &s);
    public:
    	Songfile(int index):tag(),Info(385, 90, 215, 195)
    	{
    		tag.pass_file_location(picture_file_location[index]);
    		Info.pass_file_location(songcover_location[index]);
		}
		Songfile():tag(),Info(){}
    
    SDL_Texture* loadSongFile(string path);
    Image& getTag(){return tag;}
	Image& getInfo(){return Info;}
	
	static int MusicType;
	
    private:
		Image tag;
	    Image Info;
};
void SongSelecting(Songfile* s, bool SelectDiff);
void End_Selection();
#endif /* Songfile_h */
