//
//  GameResult.cpp
//  Project
//
//  Created by T on 2023/12/19.
//

#include "GameResult.h"
#include <iostream>
#include <fstream>
using namespace std;

extern Text ResultData[];
extern SDL_Renderer* gRenderer;

string ResultListString[] = {"SCORE", "Perfect", "Great", "Good", "Fair", "Miss", "Best Combo"};


Text GameResult::ResultList[] = {   Text(120, 150, 80, 30),	//Score
									Text(120, 200, 50, 30), //Perfect
									Text(120, 230, 50, 30), //Great
									Text(120, 260, 50, 30), //Good
									Text(120, 290, 50, 30), //Fair
									Text(120, 320, 50, 30), //Miss
									Text(120, 350, 50, 30)  //BestCombo
								};
								
Text GameResult::HistoryRank = Text(40, 440, 200, 30);
string GameResult::HistoryRankString = "HISTORY ";

void GameResult::calculateRank()
{
	if(0 <= score && score <= 599999) rank = 'F';
    else if(600000 <= score && score <= 699999) rank = 'D';
    else if(700000 <= score && score <= 799999) rank = 'C';
    else if(800000 <= score && score <= 899999) rank = 'B';
    else if(900000 <= score && score <= 949999) rank = 'A';
    else rank = 'S';
}

void GameResult::updateHistoryRankString()
{
	HistoryRankString = HistoryRankString + " ";
	HistoryRankString = HistoryRankString + getString(rank);
}

const GameResult& GameResult::printResultList() const
{
	ResultList[0].loadFromRenderedText(ResultListString[0], ResultList[0].textColor = {255, 255, 255}, 1, 4);
    for(int i=1; i<7; i++){
		ResultList[i].loadFromRenderedText(ResultListString[i], ResultList[i].textColor = {255, 255, 255}, 1, 4);
	}
	
	for(int i = 0; i < 7; ++i)
    {
    	ResultList[i].changeVisible(1);
    	ResultList[i].setAlpha(ResultList[i].getTrans());
    	gRenderer << *(Object*)(&ResultList[i]);
	}
	
	return *this;
}

const GameResult& GameResult::printResultData() const
{
 	ResultData[0].loadFromRenderedText(MusicName, ResultData[0].textColor = { 255, 255, 255 }, 1, 9);
    ResultData[1].loadFromRenderedText(getString(score), ResultData[1].textColor = { 255, 255, 255 }, 1, 6);
    ResultData[2].loadFromRenderedText(getString(perfect), ResultData[2].textColor = { 255, 255, 255 }, 1, 4);
    ResultData[3].loadFromRenderedText(getString(great), ResultData[3].textColor = { 255, 255, 255 }, 1, 4);
    ResultData[4].loadFromRenderedText(getString(good), ResultData[4].textColor = { 255, 255, 255 }, 1, 4);
    ResultData[5].loadFromRenderedText(getString(fair), ResultData[5].textColor = { 255, 255, 255 }, 1, 4);
    ResultData[6].loadFromRenderedText(getString(miss), ResultData[6].textColor = { 255, 255, 255 }, 1, 4);
    ResultData[7].loadFromRenderedText(getString(bestCombo), ResultData[7].textColor = { 255, 255, 255 }, 1, 4);
    ResultData[8].loadFromRenderedText(getString(rank), ResultData[8].textColor = { 255, 255, 255 }, 1, 9);
    
    for(int i = 0; i < 9; ++i)
    {
        ResultData[i].changeVisible(1);
        ResultData[i].setAlpha(ResultData[i].getTrans());
        gRenderer << *(Object*)(&ResultData[i]);
    }
   
    return *this;
}

const GameResult& GameResult::printHistoryRank() const
{
	
	HistoryRank.loadFromRenderedText(HistoryRankString, HistoryRank.textColor = {255, 255, 255}, 1, 3);
	HistoryRank.changeVisible(1);
	HistoryRank.setAlpha(HistoryRank.getTrans());
	gRenderer << *(Object*)(&HistoryRank);
}

ostream& operator<<(ostream& output, const GameResult& g)
{
	g.printResultList().printResultData().printHistoryRank();
    return output;
}


