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
            //printBeatmap();
        }
        ~GameInfo()
        {
            /*
            for(int i = 0; i < maxCombo; i++) delete [] beatmap[i];
            delete [] beatmap;
             */
            //cout << "IM DESTRUCTOR" << endl;
        }
    
        int **beatmap;
    
        void calculate();
        void getRank()
        {
            if(0 <= score && score <= 599999) grade = 'F';
            else if(600000 <= score && score <= 699999) grade = 'D';
            else if(700000 <= score && score <= 799999) grade = 'C';
            else if(800000 <= score && score <= 899999) grade = 'B';
            else if(900000 <= score && score <= 949999) grade = 'A';
            else grade = 'S';
        }
        void cutCombo();
        void addmiss(){miss++;};
        void addPassNote(){passNote++;};
        
        int getScore(){return score;};
        int getPerfect(){return perfect;};
        int getGreat(){return great;};
        int getGood(){return good;};
        int getFair(){return fair;};
        int getMiss(){return miss;};
        int getCurrentCombo(){return currentCombo;};
        int getBestCombo(){return bestCombo;};
        int getMaxCombo(){return maxCombo;};
        int getMaxObject(){return maxObject;};
        int getPassNote(){return passNote;};
        char getGrade(){return grade;};
        long double getMi(){return Mi;};
        string getMusicName(){return MusicName;};
        string getMusicSubName(){return MusicSubName;};
        string getMusicDifficultyName(){return MusicDifficultyName;};
        int getMusicDifficultyParam(){return MusicDifficultyParam;};
        void getBeatmap(int index, int difficulty);
        string getString(int temp){return to_string(temp);};
        string getString(char temp){string s(1, temp); return s;};
        int getJudgelineInit(int index, int pos){return JudgelineInit[index][pos];};
        
        void printMusicdatas();
        void printBeatmap();
    
    private:
        //歌曲資訊
        int BPM;
        int duration;
        double basicscore;
        long double Mi;
        int maxCombo;
        int maxObject;
        string MusicName;
        string MusicSubName;
        string MusicDifficultyName;
        int MusicDifficultyParam;
        int JudgelineInit[JUDGELINE_TOTAL][3] = {};
        
        //玩家表現
        int score = 0;
        int perfect = 0;
        int great = 0;
        int good = 0;
        int fair = 0;
        int miss = 0;
        int currentCombo = 0;
        int bestCombo = 0;
        int passNote = 0;
    
        char grade = 'A';
};

#endif /* GameInfo_h */
