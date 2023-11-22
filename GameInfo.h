//
//  GameInfo.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef GameInfo_h
#define GameInfo_h
//#include "Beatmap.h"
#include "Note.h"
#include <string>
using namespace std;

extern int BPMlist[1];
extern int durationlist[1];
extern int maxcombo[1][3];

class GameInfo
{
    friend class Note;

    public:
        GameInfo(int index, int diff)
        {
            currentCombo = 0;
            score = 0;
            getBeatmap(index, diff);
            basicscore = 1000000.0/maxCombo;
            Mi = 60000.0/(BPM * 16);
            printMusicdatas();
        }
    
        int **beatmap;
    
        void calculate();
        void cutCombo();
        void addmiss(){miss++;};
        int getCurrentCombo(){return currentCombo;};
        int getScore(){return score;};
        int getMaxCombo(){return maxCombo;};
        long double getMi(){return Mi;};
        string getMusicName(){return MusicName;};
        string getMusicSubName(){return MusicSubName;};
        string getMusicDifficultyName(){return MusicDifficultyName;};
        int getMusicDifficultyParam(){return MusicDifficultyParam;};
        void getBeatmap(int index, int difficulty);
        string getString(int temp){return to_string(temp);};
    
        void printMusicdatas();
    
    private:
        //歌曲資訊
        int BPM;
        int duration;
        double basicscore;
        long double Mi;
        int maxCombo;
        string MusicName;
        string MusicSubName;
        string MusicDifficultyName;
        int MusicDifficultyParam;
        
        //玩家表現
        int score = 0;
        int perfect = 0;
        int great = 0;
        int good = 0;
        int fair = 0;
        int miss = 0;
        int currentCombo = 0;
        int bestCombo = 0;
};

#endif /* GameInfo_h */
