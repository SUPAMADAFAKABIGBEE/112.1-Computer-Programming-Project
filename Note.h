//
//  Note.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef Note_h
#define Note_h
#include "GameInfo.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

const char* NoteAddr[] = {"./Element/hit.png", "./Element/hold.png"};

//JudgelineInit[][2] = {{75, 360}, {205, 360}, {335, 360}, {465, 360}};

enum NoteName
{
    HIT,
    HOLD,
    NOTE_TOTAL
};

class Note
{
    public:
        //Initializes variables
        Note(int data[7])
        {
            stime = data[0];
            dtime = data[1];
            type = data[2];
            goal = data[3];
            endx = data[4];
            endy = data[5];
            speed = data[6];
            //loadNote(NoteAddr[data[2]]);
            mTexture = loadNote("./Element/hit.png");
        }

        //Deallocates memory
        //~Judgeline();
        bool hited = 0;
        int posx = 100;
        int posy = 100;
        //Deallocates texture
        void free();

        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        //Set blending
        void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        void setAlpha(Uint8 alpha);
        
        SDL_Texture* loadNote(string path);
        //bool loadNote(int index);
    
        //Renders texture at given point
        void render(int& posx, int& posy, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, int goalx, int goaly, int speed, int time);
    
        bool judge(int goal, int time, GameInfo* mGameinfo);
        void playsfx();
        
        //Gets image dimensions
        int getWidth(){return mWidth;};
        int getHeight(){return mHeight;};
        int getdtime(){return dtime;};
        int getgoal(){return goal;};
        int getspeed(){return speed;};
    
        //The actual hardware texture
        SDL_Texture* mTexture;

    private:
        //Image dimensions
        int mWidth = 100;
        int mHeight = 10;
        int stime;
        int dtime;
        int type;
        int goal;
        int endx;
        int endy;
        int speed;
};

#endif /* Note_h */
