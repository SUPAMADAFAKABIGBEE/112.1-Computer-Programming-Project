//
//  GameInfo.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef GameInfo_h
#define GameInfo_h
#include "Beatmap.h"
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
            BPM = BPMlist[index];
            duration = durationlist[index];
            basicscore = 1000000.0/maxcombo[index][diff];
            currentCombo = 0;
            score = 0;
        }
    
        void calculate();
        void cutCombo();
        void addmiss(){miss++;};
        int getCurrentCombo(){return currentCombo;};
        int getScore(){return score;};
        string getString(int temp){return to_string(temp);};
    
    private:
        int BPM;
        int duration;
    
        int score = 0;
        double basicscore;
        int perfect = 0;
        int great = 0;
        int good = 0;
        int fair = 0;
        int miss = 0;
        int currentCombo = 0;
        int maxCombo = 0;
};

#endif /* GameInfo_h */
