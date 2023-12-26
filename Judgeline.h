//
//  Judgeline.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef Judgeline_h
#define Judgeline_h
#include "Button.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

enum JudgelineName
{
    SDLK_D,
    SDLK_F,
    SDLK_J,
    SDLK_K,
    JUDGELINE_TOTAL
};

class Judgeline : public Button
{
    public:
        //Initializes variables
        //Judgeline(): Image(100, 10) {};
        Judgeline(int a, int b, int c, int d, int e) : Button(a, b, e, c, d)
		{
			mTexture = load("./Element/judgeline.png");
		}

        //Deallocates memory
        ~Judgeline()
        {
            for(int i = 0; i < movementAmount; i++)
			{
				if(movementMap[i] != NULL) delete [] movementMap[i];
			}
            if(movementMap != NULL) delete [] movementMap;
        }
    
        //Renders texture at given time
        void render(int time, long double Mi);
        
        int getMovementAmount(){return movementAmount;};
        void setInitx(int x){initx = x;};
        void setInity(int y){inity = y;};
        void setInitDegree(int d){initDegree = d/10.0;};
        void setType(int index){type = index;};
        
        void setMovementMap(int **data, int total);
        void resetMovementAmount(){movementAmount = 0;};
        void resetCurrentMovement(){currentMovement = 0;};
        void printMovementMap();
    
    private:
        //Image dimensions
        int initx;
        int inity;
        double initDegree;
        double degree = 0.0;
        bool inited = 0;
        int movementAmount = 0;
        int currentMovement = 0;
        int **movementMap;
};

#endif /* Judgeline_h */
