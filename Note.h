//
//  Note.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef Note_h
#define Note_h
#include "Image.h"
#include "GameInfo.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

//JudgelineInit[][2] = {{75, 360}, {205, 360}, {335, 360}, {465, 360}};

enum NoteName
{
    HIT,
    HOLD,
    NOTE_TOTAL
};

static int notecount = 0;

class Note : public Image
{
	
	public:
        //Initializes variables
        Note(){}
        Note(int data[9])
        {
			result = -1;
			stime = data[0];
            dtime = data[1];
            type = data[2];
            goal = data[3];
            endx = data[4];
            endy = data[5];
            speed = data[6];
            sdegree = data[7] / 10.0;
            ddegree = data[8] / 10.0;
            
            mTexture = load("./Element/hit.png");
            SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
            
            //printNoteInfo();
        }
        
        ~Note(){}
        bool hited = 0;
    
        //Renders texture at given time
        void render(int time, long double Mi);
    
        bool judge(int goal, int time, GameInfo* mGameinfo, long double Mi);
        void playsfx();
        
        //Gets image dimensions
        int getstime() const {return stime;}
        int getdtime() const {return dtime;}
        int getgoal() const {return goal;}
        int getEndx() const {return endx;}
        int getEndy() const {return endy;}
        int getspeed() const {return speed;}
        int getResult() const {return result;}
        int getTrans() const {return trans;}
        int getHittime() const {return hittime;}
        int getTimedif() const {return timedif;}
    
        Uint8 setTrans(int time);
        int setResult(int r){result = r;}
        void setInitx(int x){initx = x;}
        void setInity(int y){inity = y;}
        
        void printNoteInfo();  
                
    private:
        int initx;
        int inity;
        int stime;
        int dtime;
        int type;
        int goal;
        int endx;
        int endy;
        int speed;
        double sdegree;
        double ddegree;
        
        int result = -1;//0: miss, 1: fair, 2: good, 3: great, 4: perfect, 5: disappeared
        int trans = 255;
        int hittime = 0;
        int timedif;
};

#endif /* Note_h */
