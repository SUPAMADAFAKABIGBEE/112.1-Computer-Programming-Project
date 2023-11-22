//
//  GameInfo.cpp
//  Project
//
//  Created by Richard on 2023/11/21.
//

#include "GameInfo.h"
#include <iostream>
using namespace std;

void GameInfo::calculate()
{
    score = perfect * basicscore + great * (2 * basicscore / 3) + good * (basicscore / 3) + fair * (basicscore / 6);
    maxCombo = (maxCombo <= currentCombo) ? currentCombo : maxCombo;
    /*
    cout << "perfect: " << perfect << endl;
    cout << "great: " << great << endl;
    cout << "good: " << good << endl;
    cout << "fair: " << fair << endl;
    cout << "miss: " << miss << endl;
    cout << "combo: " << currentCombo << endl;
    cout << "maxcombo: " << maxCombo << endl;
    cout << "score: " << score << endl;
    */
}

void GameInfo::cutCombo()
{
    currentCombo = 0;
}
