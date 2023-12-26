//
//  Button.h
//  Project
//
//  Created by Richard on 2023/11/24.
//

#ifndef Button_h
#define Button_h
#include "Image.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

extern const char* ButtonAddr[];

enum PauseButtonName
{
    continuE,
    closE,
    PAUSEBUTTON_TOTAL
};

class Button : public Image
{
    public:
        Button(int a, int b, int e, int c = 50, int d = 50) : Image(a, b, c, d), type(e)
		{
			mTexture = load(ButtonAddr[e]);
		}
        ~Button(){}
        
        void unpressed() const;
        void pressed() const;
        void setType(int t);

    protected:
        int type;
};

#endif /* Button_h */
