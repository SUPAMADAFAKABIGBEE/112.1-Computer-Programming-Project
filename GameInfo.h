//
//  GameInfo.h
//  Project
//
//  Created by Richard on 2023/11/21.
//

#ifndef GameInfo_h
#define GameInfo_h
#include "Beatmap.h"

class GameInfo
{
    public:
        GameInfo(int index, int diff)
        {
            BPM = BPMlist[index];
            duration = durationlist[index];
            basicscore = 1000000.0/maxcombo[index][diff];
        }
        
        int score = 0;
        double basicscore;
        int perfect = 0;
        int great = 0;
        int good = 0;
        int fair = 0;
        int miss = 0;
        int currentCombo = 0;
        int maxCombo = 0;
    
        void calculate();
    
    private:
        int BPM;
        int duration;
};

#endif /* GameInfo_h */
