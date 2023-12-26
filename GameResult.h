//
//  GameResult.h
//  Project
//
//  Created by T on 2023/12/19.
//

#ifndef GameResult_h
#define GameResult_h
#include "GameInfo.h"
#include "Text.h"
#include <string>
using namespace std;

extern Text ResultData[];

class GameResult : public GameInfo
{
	
    friend ostream& operator<<(ostream&, const GameResult&);
    
    public:
        GameResult(const GameInfo &g) : GameInfo()
		{
        	MusicName = g.getMusicName();
        	score = g.getScore();
        	perfect = g.getPerfect();
        	great = g.getGreat();
        	good = g.getGood();
        	fair = g.getFair();
        	miss = g.getMiss();
        	bestCombo = g.getBestCombo();
        	maxCombo = g.getMaxCombo();
			calculateRank();
			updateHistoryRankString();
        }
        
        ~GameResult()
        {	
        
        }
    
        void calculateRank();
        void updateHistoryRankString();
        char getRank() const {return rank;}
        static Text ResultList[];
        static Text HistoryRank;
        static string HistoryRankString;
        const GameResult& printResultList() const;
        const GameResult& printResultData() const;
        const GameResult& printHistoryRank() const;
    
    private:
        char rank;
        
};

#endif /* GameResult_h */
