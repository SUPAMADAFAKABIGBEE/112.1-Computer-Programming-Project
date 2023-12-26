//
//  State.h
//  Project
//
//  Created by Richard on 2023/11/20.
//

#ifndef State_h
#define State_h

#include "SDL.h"

class State
{
    public:
        void changeByPauseState();
        void changeMaingameMusic(SDL_Event e);
        void changeMaingameDifficulty (SDL_Event e);
        void changeMaingamePauseState(SDL_Event e);
        void changeBackground(SDL_Event e);
        
        int detect(SDL_Event e);
        
        int getBackgroundType(){return BackgroundType;}
        int getMaingameDifficulty(){return MaingameDifficulty;}
        int getMaingameMusicType(){return MaingameMusicType;}
        bool getMaingameMusicEnable(){return MaingameMusicEnable;}
        bool getMaingameStart(){return MaingameStart;}
        bool getMaingamePause(){return MaingamePause;}
        bool getChooseDifficult(){return ChooseDifficult;}
        int getMaingamePauseState(){return MaingamePauseState;}
        
        void setBackgroundType(int b){BackgroundType = b;}
        void setMaingameDifficulty(int m){MaingameDifficulty = m;}
        void setMaingameMusicType(int m){MaingameMusicType = m;}
		void setMaingameMusicEnable(bool m){MaingameMusicEnable = m;}
		void setMaingameStart(bool m){MaingameStart = m;}
        void setMaingamePause(bool m){MaingamePause = m;}
        void setChooseDifficult(bool m){ChooseDifficult = m;}
        void setMaingamePauseState(int m){MaingamePauseState = m;}
        
        int getr(){return r;};
        int getg(){return g;};
        int getb(){return b;};
    
        void GettingDim5();
        void ResetRGB();
    
    private:
    	int BackgroundType = 0; //0: Title, 1: Select, 2: Maingame, 3: Result
    	int MaingameDifficulty = -1; //0: Easy, 1: Hard, 2: Insane ** 選難度機制還沒進來，目前只能在這手動改(诶黑我做了)
        int MaingameMusicType = -1;
        bool MaingameMusicEnable = 0; //Determine whether to play or not
        bool MaingameStart = 0;
        bool MaingamePause = 0;
        bool ChooseDifficult = 0;
        int MaingamePauseState = 0; //0: continue, 1: close
    	
        int r = 255;
        int g = 255;
        int b = 255;
};

#endif /* State_h */
