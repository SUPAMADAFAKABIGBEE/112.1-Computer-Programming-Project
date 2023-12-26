//
//  GameInfo.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef GameInfo_h
#define GameInfo_h
#include "Judgeline.h"
#include "MaingameMusic.h"
#include "Text.h"
#include <string>
using namespace std;

extern int BPMlist[1];
extern int durationlist[1];
extern int maxcombo[1][3];


class GameInfo
{
    //friend class Note;
    friend void adjust(int index, GameInfo& g);
    friend ostream& operator<<(ostream&, const GameInfo&);

    public:
    	
        GameInfo(int index, int diff) : mMaingameMusic(index)
        {
			currentCombo = 0;
            score = 0;
            getBeatmap(index, diff);
            basicscore = 1000000.0/maxCombo;
            Mi = 60000.0/(BPM * 16);
            //printMusicdatas();
            //printBeatmap();
        }
        
        GameInfo() :mMaingameMusic(0)
        {
        	beatmap = NULL;
		}
        
        
        ~GameInfo()
        {
            for(int i = 0; i < maxObject; i++)
			{
				if(beatmap[i] != NULL) delete [] beatmap[i];
			}
            if(beatmap != NULL) delete [] beatmap;
        }
    
        void calculate();
        void cutCombo();
        void addmiss(){miss++;};
        void addPassNote(){passNote++;};
        
        int **beatmap;
        
        int getScore() const {return score;};
        int getPerfect() const {return perfect;};
        int getGreat() const {return great;};
        int getGood() const {return good;};
        int getFair() const {return fair;};
        int getMiss() const {return miss;};
        int getCurrentCombo() const {return currentCombo;};
        int getBestCombo() const {return bestCombo;};
        int getMaxCombo() const {return maxCombo;};
        int getMaxObject() const {return maxObject;};
        int getPassNote() const {return passNote;};
        long double getMi(){return Mi;};
        string getMusicName() const {return MusicName;};
        string getMusicSubName(){return MusicSubName;};
        string getMusicDifficultyName() const {return MusicDifficultyName;};
        int getMusicDifficultyParam(){return MusicDifficultyParam;};
        void getBeatmap(int index, int difficulty);
        string getString(int temp) const {return to_string(temp);};
        string getString(char temp) const {string s(1, temp); return s;};
        int getJudgelineInit(int index, int pos){return JudgelineInit[index][pos];};
        MaingameMusic& getmMaingameMusic(){return mMaingameMusic;};
        
        void printMusicdatas();
        void printBeatmap();
        
    
    private:
        //歌曲資訊
        MaingameMusic mMaingameMusic;
        int BPM;
        int duration;
        double basicscore;
        long double Mi;
        int maxObject;
        string MusicSubName;
        string MusicDifficultyName;
        int MusicDifficultyParam;
        int JudgelineInit[4][3] = {};
        
        int currentCombo = 0;
        int passNote = 0;
        
    protected:
        //玩家表現
        string MusicName;
        int score = 0;
        int perfect = 0;
        int great = 0;
        int good = 0;
        int fair = 0;
        int miss = 0;
        int maxCombo;
        int bestCombo = 0;
        
};

#endif /* GameInfo_h */
