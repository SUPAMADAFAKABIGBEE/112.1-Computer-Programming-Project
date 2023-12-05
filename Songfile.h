//
//  Songfile.h
//  Project
//
//  Created by Richard on 2023/11/29.
//

#ifndef Songfile_h
#define Songfile_h

#include "Button.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;


enum songselected{
    Song1,
    Song2,
    Songtotal
};

class Songfile {
    
    public:
    Songfile(int x, int y){
        posx = x;
        posy = y;
    }
    
    private:
    int posx,posy;
    
};

#endif /* Songfile_h */
