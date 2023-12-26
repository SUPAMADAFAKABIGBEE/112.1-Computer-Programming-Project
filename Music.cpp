//
//  Music.cpp
//  Project
//
//  Created by Richard on 2023/12/6.
//

#include "Music.h"
#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"
using namespace std;

Music::Music(int i, const char* a) : type(i), address(a){}
