/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "Background.cpp"
#include "State.cpp"
#include "MaingameMusic.cpp"
#include "Judgeline.cpp"
#include "Note.cpp"
#include "GameInfo.cpp"
#include "SoundEffect.cpp"
#include "Text.cpp"

const char* FontAddr[] = {"./Font/lazy.ttf", "./Font/CaviarDreams.ttf", "./Font/CaviarDreams_Italic.ttf", "./Font/CaviarDreams_BoldItalic.ttf", "./Font/Caviar_Dreams_Bold.ttf"};
const char* SoundEffectAddr[] = {"./SoundEffect/hitsound.mp3"};
const char* NoteAddr[] = {"./Element/hit.png", "./Element/hold.png"};
const char* JudgelineAddr[] = {"./Element/judgeline.png", "./Element/judgeline.png", "./Element/judgeline.png", "./Element/judgeline.png"};
const char* MaingameMusicAddr[] = {"./Music/M000.mp3"};
const char* BackgroundAddr[] = {"./Background/title.bmp", "./Background/select.bmp", "./Background/maingame.bmp", "./Background/result.bmp"};

int JudgelineInit[][2] = {{75, 360}, {205, 360}, {335, 360}, {465, 360}};

int BPMlist[] = {175}; //Unit: beats per minute
int durationlist[] = {123}; //Unit: s (不含開頭準備3秒)
int maxcombo[][3] = {{300}};
long double Mi[] = {60000.0/(175*16)};//Unit: ms

int notedata[][3][1500][7] =
{
    {//000.mp3 從-140Mi開始
        {//Easy
            {-50, 0, 0, 0, 75, 360, 5},
            {2*Q-50, 2*Q, 0, 1, 205, 360, 5},
            {4*Q-50, 4*Q, 0, 3, 465, 360, 5},
            {6*Q-50, 6*Q, 0, 2, 335, 360, 5},
            {6*Q-50, 6*Q, 0, 0, 335, 360, 5},
            {8*Q-50, 8*Q, 0, 3, 465, 360, 5},
            {10*Q-50, 10*Q, 0, 0, 75, 360, 5},
            {10*Q-50, 10*Q, 0, 2, 335, 360, 5},
            {11*Q-50, 11*Q, 0, 1, 205, 360, 5},
            {11*Q-50, 11*Q, 0, 3, 465, 360, 5},
            {12*Q-50, 12*Q, 0, 0, 75, 360, 5},
            {12*Q-50, 12*Q, 0, 2, 335, 360, 5},
            {16*Q-50, 16*Q, 0, 0, 75, 360, 5},
            {18*Q-50, 18*Q, 0, 1, 205, 360, 5},
            {20*Q-50, 20*Q, 0, 3, 465, 360, 5},
            {22*Q-50, 22*Q, 0, 2, 335, 360, 5},
            {24*Q-50, 24*Q, 0, 1, 205, 360, 5},
            {24*Q-50, 24*Q, 0, 3, 465, 360, 5},
            {26*Q-50, 26*Q, 0, 0, 75, 360, 5},
            {26*Q-50, 26*Q, 0, 2, 335, 360, 5},
            {28*Q-50, 28*Q, 0, 1, 205, 360, 5},
            {28*Q-50, 28*Q, 0, 3, 465, 360, 5},
            {36*Q-50, 36*Q, 0, 0, 75, 360, 5},
            {36*Q-50, 36*Q, 0, 3, 465, 360, 5},
            {40*Q-50, 40*Q, 0, 1, 205, 360, 5},
            {40*Q-50, 40*Q, 0, 2, 335, 360, 5},
            {44*Q-50, 44*Q, 0, 0, 75, 360, 5},
            {44*Q-50, 44*Q, 0, 2, 335, 360, 5},
            {48*Q-50, 48*Q, 0, 1, 205, 360, 5},
            {48*Q-50, 48*Q, 0, 3, 465, 360, 5},
            {52*Q-50, 52*Q, 0, 0, 75, 360, 5},
            {52*Q-50, 52*Q, 0, 3, 465, 360, 5},
            {56*Q-50, 56*Q, 0, 1, 205, 360, 5},
            {56*Q-50, 56*Q, 0, 2, 335, 360, 5},
            {59*Q-50, 59*Q, 0, 1, 205, 360, 5},
            {60*Q-50, 60*Q, 0, 0, 75, 360, 5},
            {60*Q-50, 60*Q, 0, 2, 335, 360, 5},
            {63*Q-50, 63*Q, 0, 2, 335, 360, 5},
            {64*Q-50, 64*Q, 0, 1, 205, 360, 5},
            {64*Q-50, 64*Q, 0, 3, 465, 360, 5},
            {68*Q-50, 68*Q, 0, 0, 75, 360, 5},
            {69*Q-50, 69*Q, 0, 0, 75, 360, 5},
            {70*Q-50, 70*Q, 0, 0, 75, 360, 5},
            {72*Q-50, 72*Q, 0, 3, 465, 360, 5},
            {73*Q-50, 73*Q, 0, 3, 465, 360, 5},
            {74*Q-50, 74*Q, 0, 3, 465, 360, 5},
            {76*Q-50, 76*Q, 0, 1, 205, 360, 5},
            {77*Q-50, 77*Q, 0, 1, 205, 360, 5},
            {78*Q-50, 78*Q, 0, 1, 205, 360, 5},
            {80*Q-50, 80*Q, 0, 2, 335, 360, 5},
            {81*Q-50, 81*Q, 0, 2, 335, 360, 5},
            {82*Q-50, 82*Q, 0, 2, 335, 360, 5},
            {84*Q-50, 84*Q, 0, 1, 205, 360, 5},
            {85*Q-50, 85*Q, 0, 1, 205, 360, 5},
            {86*Q-50, 86*Q, 0, 1, 205, 360, 5},
            {88*Q-50, 88*Q, 0, 3, 465, 360, 5},
            {89*Q-50, 89*Q, 0, 3, 465, 360, 5},
            {90*Q-50, 90*Q, 0, 3, 465, 360, 5},
            {92*Q-50, 92*Q, 0, 2, 335, 360, 5},
            {93*Q-50, 93*Q, 0, 2, 335, 360, 5},
            {94*Q-50, 94*Q, 0, 2, 335, 360, 5},
            {96*Q-50, 96*Q, 0, 0, 75, 360, 5},
            {97*Q-50, 97*Q, 0, 0, 75, 360, 5},
            {98*Q-50, 98*Q, 0, 0, 75, 360, 5},
            {99*Q-50, 99*Q, 0, 0, 75, 360, 5},
            {101*Q-50, 101*Q, 0, 0, 75, 360, 5},
            {101*Q-50, 101*Q, 0, 1, 205, 360, 5},
            {101*Q-50, 101*Q, 0, 2, 335, 360, 5},
            {101*Q-50, 101*Q, 0, 3, 465, 360, 5},
            {102*Q-50, 102*Q, 0, 1, 205, 360, 5},
            {103*Q-50, 103*Q, 0, 1, 205, 360, 5},
            {104*Q-50, 104*Q, 0, 1, 205, 360, 5},
            {106*Q-50, 106*Q, 0, 3, 465, 360, 5},
            {108*Q-50, 108*Q, 0, 0, 75, 360, 5},
            {109*Q-50, 109*Q, 0, 0, 75, 360, 5},
            {109*Q+8-50, 109*Q+8, 0, 0, 75, 360, 5},
            {112*Q-50, 112*Q, 0, 2, 335, 360, 5},
            {114*Q-50, 114*Q, 0, 3, 465, 360, 5},
            {115*Q-50, 115*Q, 0, 1, 205, 360, 5},
            {117*Q-50, 117*Q, 0, 0, 75, 360, 5},
            {117*Q-50, 117*Q, 0, 1, 205, 360, 5},
            {117*Q-50, 117*Q, 0, 2, 335, 360, 5},
            {117*Q-50, 117*Q, 0, 3, 465, 360, 5},
            {118*Q-50, 118*Q, 0, 0, 75, 360, 5},
            {119*Q-50, 119*Q, 0, 0, 75, 360, 5},
            {120*Q-50, 120*Q, 0, 0, 75, 360, 5},
            {122*Q-50, 122*Q, 0, 2, 335, 360, 5},
            {124*Q-50, 124*Q, 0, 3, 465, 360, 5},
            {125*Q+8-50, 125*Q+8, 0, 1, 205, 360, 5},
            {126*Q+8-50, 126*Q+8, 0, 1, 205, 360, 5},
            {127*Q+8-50, 127*Q+8, 0, 1, 205, 360, 5},
            {128*Q+8-50, 128*Q+8, 0, 1, 205, 360, 5},
            {130*Q-50, 130*Q, 0, 0, 75, 360, 5},
            {130*Q-50, 130*Q, 0, 2, 335, 360, 5},
            {131*Q-50, 131*Q, 0, 0, 75, 360, 5},
            {131*Q-50, 131*Q, 0, 2, 335, 360, 5},
            {132*Q-50, 132*Q, 0, 0, 75, 360, 5},
            {132*Q-50, 132*Q, 0, 1, 205, 360, 5},
            {132*Q-50, 132*Q, 0, 2, 335, 360, 5},
            {132*Q-50, 132*Q, 0, 3, 465, 360, 5},
            {134*Q-50, 134*Q, 0, 1, 205, 360, 5},
            {135*Q-50, 135*Q, 0, 3, 465, 360, 5},
            {136*Q-50, 136*Q, 0, 0, 75, 360, 5},
            {136*Q-50, 136*Q, 0, 1, 205, 360, 5},
            {136*Q-50, 136*Q, 0, 2, 335, 360, 5},
            {136*Q-50, 136*Q, 0, 3, 465, 360, 5},
            {138*Q-50, 138*Q, 0, 0, 75, 360, 5},
            {139*Q-50, 139*Q, 0, 2, 335, 360, 5},
            {140*Q-50, 140*Q, 0, 0, 75, 360, 5},
            {140*Q-50, 140*Q, 0, 1, 205, 360, 5},
            {140*Q-50, 140*Q, 0, 2, 335, 360, 5},
            {140*Q-50, 140*Q, 0, 3, 465, 360, 5},
            {142*Q-50, 142*Q, 0, 3, 465, 360, 5},
            {143*Q-50, 143*Q, 0, 0, 75, 360, 5},
            {144*Q-50, 144*Q, 0, 0, 75, 360, 5},
            {144*Q-50, 144*Q, 0, 1, 205, 360, 5},
            {144*Q-50, 144*Q, 0, 2, 335, 360, 5},
            {144*Q-50, 144*Q, 0, 3, 465, 360, 5},
            {146*Q-50, 146*Q, 0, 1, 205, 360, 5},
            {147*Q-50, 147*Q, 0, 2, 335, 360, 5},
            {148*Q-50, 148*Q, 0, 0, 75, 360, 5},
            {148*Q-50, 148*Q, 0, 1, 205, 360, 5},
            {150*Q-50, 150*Q, 0, 2, 335, 360, 5},
            {150*Q-50, 150*Q, 0, 3, 465, 360, 5},
            {152*Q-50, 152*Q, 0, 2, 335, 360, 5},
            {152*Q-50, 152*Q, 0, 3, 465, 360, 5},
            {154*Q-50, 154*Q, 0, 0, 75, 360, 5},
            {154*Q-50, 154*Q, 0, 1, 205, 360, 5},
            {156*Q-50, 156*Q, 0, 0, 75, 360, 5},
            {156*Q-50, 156*Q, 0, 1, 205, 360, 5},
            {157*Q-50, 157*Q, 0, 0, 75, 360, 5},
            {157*Q-50, 157*Q, 0, 1, 205, 360, 5},
            {158*Q-50, 158*Q, 0, 2, 335, 360, 5},
            {158*Q-50, 158*Q, 0, 3, 465, 360, 5},
            {159*Q-50, 159*Q, 0, 2, 335, 360, 5},
            {159*Q-50, 159*Q, 0, 3, 465, 360, 5},
            {160*Q-50, 160*Q, 0, 0, 75, 360, 5},
            {160*Q-50, 160*Q, 0, 1, 205, 360, 5},
            {161*Q-50, 161*Q, 0, 0, 75, 360, 5},
            {161*Q-50, 161*Q, 0, 1, 205, 360, 5},
            {162*Q-50, 162*Q, 0, 2, 335, 360, 5},
            {162*Q-50, 162*Q, 0, 3, 465, 360, 5},//transition
            {164*Q-50, 164*Q, 0, 0, 75, 360, 5},
            {164*Q-50, 164*Q, 0, 1, 205, 360, 5},
            {164*Q-50, 164*Q, 0, 2, 335, 360, 5},
            {164*Q-50, 164*Q, 0, 3, 465, 360, 5},
            {166*Q-50, 166*Q, 0, 1, 205, 360, 5},
            {168*Q-50, 168*Q, 0, 3, 465, 360, 5},
            {170*Q-50, 170*Q, 0, 2, 335, 360, 5},
            {172*Q-50, 172*Q, 0, 3, 465, 360, 5},
            {174*Q-50, 174*Q, 0, 0, 75, 360, 5},
            {174*Q-50, 174*Q, 0, 2, 335, 360, 5},
            {176*Q-50, 176*Q, 0, 0, 75, 360, 5},
            {176*Q-50, 176*Q, 0, 2, 335, 360, 5},
            {178*Q-50, 178*Q, 0, 0, 75, 360, 5},
            {178*Q-50, 178*Q, 0, 2, 335, 360, 5},
            {180*Q-50, 180*Q, 0, 0, 75, 360, 5},
            {180*Q-50, 180*Q, 0, 1, 205, 360, 5},
            {180*Q-50, 180*Q, 0, 2, 335, 360, 5},
            {180*Q-50, 180*Q, 0, 3, 465, 360, 5},
            {182*Q-50, 182*Q, 0, 1, 205, 360, 5},
            {184*Q-50, 184*Q, 0, 3, 465, 360, 5},
            {186*Q-50, 186*Q, 0, 2, 335, 360, 5},
            {188*Q-50, 188*Q, 0, 1, 205, 360, 5},
            {188*Q-50, 188*Q, 0, 3, 465, 360, 5},
            {190*Q-50, 190*Q, 0, 0, 75, 360, 5},
            {190*Q-50, 190*Q, 0, 2, 335, 360, 5},
            {192*Q-50, 192*Q, 0, 1, 205, 360, 5},
            {192*Q-50, 192*Q, 0, 3, 465, 360, 5},//196
            {196*Q-50, 196*Q, 0, 1, 205, 360, 5},
            {197*Q-50, 197*Q, 0, 1, 205, 360, 5},
            {198*Q-50, 198*Q, 0, 1, 205, 360, 5},
            {200*Q-50, 200*Q, 0, 2, 335, 360, 5},
            {201*Q-50, 201*Q, 0, 2, 335, 360, 5},
            {202*Q-50, 202*Q, 0, 2, 335, 360, 5},
            {204*Q-50, 204*Q, 0, 0, 75, 360, 5},
            {205*Q-50, 205*Q, 0, 0, 75, 360, 5},
            {206*Q-50, 206*Q, 0, 0, 75, 360, 5},
            {208*Q-50, 208*Q, 0, 1, 205, 360, 5},
            {208*Q-50, 208*Q, 0, 3, 465, 360, 5},
            {210*Q-50, 210*Q, 0, 1, 205, 360, 5},
            {210*Q-50, 210*Q, 0, 3, 465, 360, 5},
            {212*Q-50, 212*Q, 0, 3, 465, 360, 5},
            {213*Q-50, 213*Q, 0, 3, 465, 360, 5},
            {214*Q-50, 214*Q, 0, 3, 465, 360, 5},
            {216*Q-50, 216*Q, 0, 1, 205, 360, 5},
            {217*Q-50, 217*Q, 0, 1, 205, 360, 5},
            {218*Q-50, 218*Q, 0, 1, 205, 360, 5},
            {220*Q-50, 220*Q, 0, 0, 75, 360, 5},
            {220*Q-50, 220*Q, 0, 1, 205, 360, 5},
            {220*Q-50, 220*Q, 0, 2, 335, 360, 5},
            {220*Q-50, 220*Q, 0, 3, 465, 360, 5},
            {222*Q-50, 222*Q, 0, 0, 75, 360, 5},
            {222*Q-50, 222*Q, 0, 1, 205, 360, 5},
            {222*Q-50, 222*Q, 0, 2, 335, 360, 5},
            {222*Q-50, 222*Q, 0, 3, 465, 360, 5},
            {224*Q-50, 224*Q, 0, 0, 75, 360, 5},
            {224*Q-50, 224*Q, 0, 1, 205, 360, 5},
            {224*Q-50, 224*Q, 0, 2, 335, 360, 5},
            {224*Q-50, 224*Q, 0, 3, 465, 360, 5},//228
            {228*Q-50, 228*Q, 0, 1, 205, 360, 5},
            {229*Q-50, 229*Q, 0, 1, 205, 360, 5},
            {230*Q-50, 230*Q, 0, 1, 205, 360, 5},
            {232*Q-50, 232*Q, 0, 2, 335, 360, 5},
            {233*Q-50, 233*Q, 0, 2, 335, 360, 5},
            {234*Q-50, 234*Q, 0, 2, 335, 360, 5},
            {236*Q-50, 236*Q, 0, 0, 75, 360, 5},
            {237*Q-50, 237*Q, 0, 0, 75, 360, 5},
            {238*Q-50, 238*Q, 0, 0, 75, 360, 5},
            {240*Q-50, 240*Q, 0, 1, 205, 360, 5},
            {240*Q-50, 240*Q, 0, 3, 465, 360, 5},
            {242*Q-50, 242*Q, 0, 1, 205, 360, 5},
            {242*Q-50, 242*Q, 0, 3, 465, 360, 5},
            {244*Q-50, 244*Q, 0, 3, 465, 360, 5},
            {245*Q-50, 245*Q, 0, 3, 465, 360, 5},
            {246*Q-50, 246*Q, 0, 3, 465, 360, 5},
            {248*Q-50, 248*Q, 0, 1, 205, 360, 5},
            {249*Q-50, 249*Q, 0, 1, 205, 360, 5},
            {250*Q-50, 250*Q, 0, 1, 205, 360, 5},
            {252*Q-50, 252*Q, 0, 0, 75, 360, 5},
            {252*Q-50, 252*Q, 0, 1, 205, 360, 5},
            {252*Q-50, 252*Q, 0, 2, 335, 360, 5},
            {252*Q-50, 252*Q, 0, 3, 465, 360, 5},
            {254*Q-50, 254*Q, 0, 0, 75, 360, 5},
            {254*Q-50, 254*Q, 0, 1, 205, 360, 5},
            {254*Q-50, 254*Q, 0, 2, 335, 360, 5},
            {254*Q-50, 254*Q, 0, 3, 465, 360, 5},
            {256*Q-50, 256*Q, 0, 0, 75, 360, 5},
            {256*Q-50, 256*Q, 0, 1, 205, 360, 5},
            {256*Q-50, 256*Q, 0, 2, 335, 360, 5},
            {256*Q-50, 256*Q, 0, 3, 465, 360, 5},
            {258*Q-50, 258*Q, 0, 3, 465, 360, 5},
            {259*Q-50, 259*Q, 0, 3, 465, 360, 5},//260
            {260*Q-50, 260*Q, 0, 1, 205, 360, 5},
            {261*Q-50, 261*Q, 0, 1, 205, 360, 5},
            {262*Q-50, 262*Q, 0, 1, 205, 360, 5},
            {264*Q-50, 264*Q, 0, 2, 335, 360, 5},
            {265*Q-50, 265*Q, 0, 2, 335, 360, 5},
            {266*Q-50, 266*Q, 0, 2, 335, 360, 5},
            {268*Q-50, 268*Q, 0, 0, 75, 360, 5},
            {269*Q-50, 269*Q, 0, 0, 75, 360, 5},
            {270*Q-50, 270*Q, 0, 0, 75, 360, 5},
            {272*Q-50, 272*Q, 0, 1, 205, 360, 5},
            {272*Q-50, 272*Q, 0, 3, 465, 360, 5},
            {274*Q-50, 274*Q, 0, 1, 205, 360, 5},
            {274*Q-50, 274*Q, 0, 3, 465, 360, 5},
            {276*Q-50, 276*Q, 0, 3, 465, 360, 5},
            {277*Q-50, 277*Q, 0, 3, 465, 360, 5},
            {278*Q-50, 278*Q, 0, 3, 465, 360, 5},
            {280*Q-50, 280*Q, 0, 1, 205, 360, 5},
            {281*Q-50, 281*Q, 0, 1, 205, 360, 5},
            {282*Q-50, 282*Q, 0, 1, 205, 360, 5},
            {284*Q-50, 284*Q, 0, 0, 75, 360, 5},
            {284*Q-50, 284*Q, 0, 1, 205, 360, 5},
            {284*Q-50, 284*Q, 0, 2, 335, 360, 5},
            {284*Q-50, 284*Q, 0, 3, 465, 360, 5},
            {286*Q-50, 286*Q, 0, 0, 75, 360, 5},
            {286*Q-50, 286*Q, 0, 1, 205, 360, 5},
            {286*Q-50, 286*Q, 0, 2, 335, 360, 5},
            {286*Q-50, 286*Q, 0, 3, 465, 360, 5},
            {288*Q-50, 288*Q, 0, 0, 75, 360, 5},
            {289*Q-50, 289*Q, 0, 1, 205, 360, 5},
            {290*Q-50, 290*Q, 0, 2, 335, 360, 5},
            {291*Q-50, 291*Q, 0, 3, 465, 360, 5},
            {292*Q-50, 292*Q, 0, 3, 465, 360, 5},
            {293*Q-50, 293*Q, 0, 2, 335, 360, 5},
            {294*Q-50, 294*Q, 0, 1, 205, 360, 5},
            {295*Q-50, 295*Q, 0, 0, 75, 360, 5},
            {296*Q-50, 296*Q, 0, 0, 75, 360, 5},
            {296*Q-50, 296*Q, 0, 1, 205, 360, 5},
            {296*Q-50, 296*Q, 0, 2, 335, 360, 5},
            {296*Q-50, 296*Q, 0, 3, 465, 360, 5},//休11拍
            {307*Q-50, 307*Q, 0, 0, 75, 360, 5},
            {309*Q-50, 309*Q, 0, 1, 205, 360, 5},
            {311*Q-50, 311*Q, 0, 3, 465, 360, 5},
            {313*Q-50, 313*Q, 0, 2, 335, 360, 5},
            {313*Q-50, 313*Q, 0, 0, 335, 360, 5},
            {315*Q-50, 315*Q, 0, 3, 465, 360, 5},
            {317*Q-50, 317*Q, 0, 0, 75, 360, 5},
            {317*Q-50, 317*Q, 0, 2, 335, 360, 5},
            {318*Q-50, 318*Q, 0, 1, 205, 360, 5},
            {318*Q-50, 318*Q, 0, 3, 465, 360, 5},
            {319*Q-50, 319*Q, 0, 0, 75, 360, 5},
            {319*Q-50, 319*Q, 0, 2, 335, 360, 5},
            {321*Q-50, 321*Q, 0, 1, 205, 360, 5},
            {321*Q-50, 321*Q, 0, 3, 465, 360, 5},
            {323*Q-50, 323*Q, 0, 0, 75, 360, 5},
            {325*Q-50, 325*Q, 0, 1, 205, 360, 5},
            {327*Q-50, 327*Q, 0, 3, 465, 360, 5},
            {329*Q-50, 329*Q, 0, 2, 335, 360, 5},
            {331*Q-50, 331*Q, 0, 1, 205, 360, 5},
            {331*Q-50, 331*Q, 0, 3, 465, 360, 5},
            {333*Q-50, 333*Q, 0, 0, 75, 360, 5},
            {333*Q-50, 333*Q, 0, 2, 335, 360, 5},
            {335*Q-50, 335*Q, 0, 1, 205, 360, 5},
            {335*Q-50, 335*Q, 0, 3, 465, 360, 5},
            {339*Q-50, 339*Q, 0, 0, 75, 360, 5},
            {339*Q-50, 339*Q, 0, 1, 205, 360, 5},
            {339*Q-50, 339*Q, 0, 2, 335, 360, 5},
            {339*Q-50, 339*Q, 0, 3, 465, 360, 5},
        }
    }
};

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
//SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font form 5pt to 50pt
TTF_Font* gFont[FONT_TOTAL] = {};

//The surface contained by the window
Background *mBackground = new class Background[BACKGROUND_TOTAL];
SDL_Texture* gCurrentBackground = NULL;

//The combo and score (in the maingame)
Text MainCombo(210, 30, SCREEN_WIDTH - 210, 0);
Text MainScore(210, 30, 0, 0);
//Text MainMusicData[] = {Text(320, 30, 30, SCREEN_HEIGHT/2 - 30), Text(320, 30, 30, SCREEN_HEIGHT/2 - 30), Text(320, 30, 30, SCREEN_HEIGHT/2 - 30)};//0: Name, 1:SubName, 2:Difficulty

//The maingame music
MaingameMusic MaingameMusic[MAINGAMEMUSIC_TOTAL];

//The sound effect
SoundEffect mSoundEffect[SOUNDEFFECT_TOTAL];

//The Judgeline
Judgeline *mJudgeline = new class Judgeline [JUDGELINE_TOTAL];

//The Notes
vector<Note> mNote;
Note *tempNote;

//The GameInfo
GameInfo *mGameInfo;

//The state
State NowState;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("巨大蜜蜂那三小的", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            //gScreenSurface = SDL_GetWindowSurface( gWindow );
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    for(int i = 0; i < BACKGROUND_TOTAL; i++)
    {
        //mBackground[i] = Background(gRenderer);
        mBackground[i].type = i;
        success = success && mBackground[i].loadByIndex(i);
    }
    for(int i = 0; i < MAINGAMEMUSIC_TOTAL; i++)
    {
        MaingameMusic[i].type = i;
        success = success && MaingameMusic[i].loadMaingameMusic(i);
    }
    for(int i = 0; i < SOUNDEFFECT_TOTAL; i++)
    {
        mSoundEffect[i].type = i;
        success = success && mSoundEffect[i].loadSoundEffect(i);
    }
    for(int i = 0; i < JUDGELINE_TOTAL; i++)
    {
        //Judgeline[i].type = i;
        //mJudgeline[i] = Judgeline(gRenderer);
        mJudgeline[i].posx = JudgelineInit[i][0];
        mJudgeline[i].posy = JudgelineInit[i][1];
        success = success && mJudgeline[i].loadByIndex(i);
    }
    for(int i = 0; i < FONT_TOTAL; i++)
    {
        gFont[i] = TTF_OpenFont(FontAddr[i], 28);
        if(gFont[i] == NULL)
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
    }
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Free global font
    for(int i = 0; i < FONT_TOTAL; i++)
    {
        TTF_CloseFont(gFont[i]);
        gFont[i] = NULL;
    }
    
    //Free
    for(int i = 0; i < BACKGROUND_TOTAL; i++)
    {
        SDL_DestroyTexture(mBackground[i].gBackground);
        mBackground[i].gBackground = NULL;
    }
    SDL_DestroyTexture(MainCombo.mText);
    MainCombo.mText = NULL;
    SDL_DestroyTexture(MainScore.mText);
    MainScore.mText = NULL;
    for(int i = 0; i < MAINGAMEMUSIC_TOTAL; i++)
    {
        Mix_FreeMusic(MaingameMusic[i].gMaingameMusic);
        MaingameMusic[i].gMaingameMusic = NULL;
    }
    for(int i = 0; i < SOUNDEFFECT_TOTAL; i++)
    {
        Mix_FreeChunk(mSoundEffect[i].gSoundEffect);
        mSoundEffect[i].gSoundEffect = NULL;
    }
    
    SDL_DestroyRenderer(gRenderer);
    
    //Quit SDL subsystems
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

Uint32 maingameMusicCallback(Uint32 interval, void* param)
{
    //Print callback message
    //printf( "Callback called back with message: %s\n", static_cast<char*>(param));
    if(0 <= NowState.MaingameMusicType && NowState.MaingameMusicType < MAINGAMEMUSIC_TOTAL && NowState.MaingameMusicEnable != 0)
    {
        if(Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(MaingameMusic[NowState.MaingameMusicType].gMaingameMusic, 0);
            NowState.MaingameMusicEnable = 0;
        }
    }
    return 0;
}

Uint32 buttonCallback(Uint32 interval, void* param)
{
    //Print callback message
    //printf( "Callback called back with message: %s\n", static_cast<char*>(param));
    for(int i = 0; i < JUDGELINE_TOTAL; i++)
    {
        mJudgeline[i].unpressed();
    }
    return 0;
}

int main(int argc, char* args[])
{
    //trial();
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;
            
            //Current time start time
            Uint32 startTime = 0;
            
            SDL_TimerID MaingameMusicTimerID = SDL_AddTimer(100, maingameMusicCallback, const_cast<char*>( "3 seconds waited!" ) );
            SDL_TimerID ButtonTimerID = SDL_AddTimer(100, buttonCallback, const_cast<char*>( "3 seconds waited!" ) );
            
            bool MaingameCon = 0; //決定Maingame初始化
            int furtherNote = 0; //螢幕上會顯示的最後面的note
            
            double degrees = 0;
            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            //Set default current surface
            gCurrentBackground = mBackground[NowState.BackgroundType].gBackground;
            
            //While application is running
            while(!quit)
            {
                if(NowState.MaingameStart)
                {
                    if(!MaingameCon)
                    {
                        mGameInfo = new class GameInfo(NowState.MaingameMusicType, NowState.MaingameDifficulty);
                        MaingameCon = 1;
                        MainCombo.changeVisible(1);
                        MainScore.changeVisible(1);
                        startTime = SDL_GetTicks() + 3000;
                        for(furtherNote = 0; notedata[NowState.MaingameMusicType][NowState.MaingameDifficulty][furtherNote][0] * Mi[NowState.MaingameMusicType] - (int)SDL_GetTicks() + (int)startTime < 1000 && furtherNote < maxcombo[NowState.MaingameMusicType][NowState.MaingameDifficulty]; furtherNote++)
                        {
                            //cout << notedata[NowState.MaingameMusicType][NowState.MaingameDifficulty][furtherNote][0] * Mi[NowState.MaingameMusicType] << " " << (int)SDL_GetTicks() - (int)startTime << endl;
                            tempNote = new class Note(notedata[NowState.MaingameMusicType][NowState.MaingameDifficulty][furtherNote]);
                            mNote.push_back(*tempNote);
                            //cout << "Now we have: " << mNote.size() << " Notes" << endl;
                            delete tempNote;
                        }
                    }
                    else
                    {
                        for(; notedata[NowState.MaingameMusicType][NowState.MaingameDifficulty][furtherNote][0] * Mi[NowState.MaingameMusicType] - (int)SDL_GetTicks() + (int)startTime < 1000 && furtherNote < maxcombo[NowState.MaingameMusicType][NowState.MaingameDifficulty]; furtherNote++)
                        {
                            //cout << notedata[NowState.MaingameMusicType][NowState.MaingameDifficulty][furtherNote][0] * Mi[NowState.MaingameMusicType] << " " << (int)SDL_GetTicks() - (int)startTime << endl;
                            tempNote = new class Note(notedata[NowState.MaingameMusicType][NowState.MaingameDifficulty][furtherNote]);
                            mNote.push_back(*tempNote);
                            //cout << "Now we have: " << mNote.size() << " Notes" << endl;
                            delete tempNote;
                        }
                    }
                }
                
                //Handle events on queue
                while(SDL_PollEvent( &e ) != 0)
                {
                    //User requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN)
                    {
                        Mix_PlayChannel(-1, mSoundEffect[HITSOUND].gSoundEffect, 0);
                        //Select surfaces based on key press
                        NowState.changeBackground(e);
                        gCurrentBackground = mBackground[NowState.BackgroundType].gBackground;
                        NowState.changeMaingameMusic();
                        if(NowState.MaingameMusicType >= 0)
                        {
                            MaingameMusicTimerID = SDL_AddTimer(3000, maingameMusicCallback, const_cast<char*>( "3 seconds waited!" ) );
                            //NowState.changeMaingameMusic();
                        }
                        if(NowState.detect(e) >= 0)
                        {
                            for(int i = 0; i < mNote.size(); i++)
                            {
                                if(mNote[i].judge(NowState.detect(e), mNote[i].getdtime() * Mi[NowState.MaingameMusicType] - (int)SDL_GetTicks() + (int)startTime, mGameInfo))
                                {
                                    mNote.erase(mNote.begin() + i);
                                    break;
                                }
                            }
                            mJudgeline[NowState.detect(e)].pressed();
                            ButtonTimerID = SDL_AddTimer(100, buttonCallback, const_cast<char*>( "0.1 seconds waited!" ) );
                        }
                    }
                }
                
                //Clear screen
                SDL_RenderClear( gRenderer );
                
                SDL_RenderCopy( gRenderer, gCurrentBackground, NULL, NULL );

                //Render texture to screen
                
                if(mGameInfo != NULL)
                {
                    MainCombo.loadFromRenderedText(mGameInfo->getString(mGameInfo->getCurrentCombo()), MainCombo.textColor = { 0, 0, 0 }, 2);
                    MainScore.loadFromRenderedText(mGameInfo->getString(mGameInfo->getScore()), MainScore.textColor = { 0, 0, 0 }, 2);
                    MainCombo.render(MainCombo.getPosx(), MainCombo.getPosy());
                    MainScore.render(MainScore.getPosx(), MainScore.getPosy());
                }
                
                for(int i = 0; i < JUDGELINE_TOTAL; i++)
                {
                    mJudgeline[i].render(NowState.BackgroundType, mJudgeline[i].posx, mJudgeline[i].posy, NULL, degrees, NULL, flipType );
                    //SDL_RenderCopy( gRenderer, mJudgeline[i].mTexture, NULL, NULL );
                }
                for(int i = 0; i < mNote.size(); i++)
                {
                    if(mNote[i].getdtime() * Mi[NowState.MaingameMusicType] - (int)SDL_GetTicks() + (int)startTime < -240)
                    {
                        mNote.erase(mNote.begin() + i);
                        mGameInfo->addmiss();
                        mGameInfo->calculate();
                        mGameInfo->cutCombo();
                        //cout << "Oops: " << i << endl;
                    }
                    if(i >= mNote.size()) break;
                    //cout << "Now rendering: " << i << endl;
                    mNote[i].render(mNote[i].posx, mNote[i].posy, NULL, degrees, NULL, flipType, mJudgeline[mNote[i].getgoal()].posx, mJudgeline[mNote[i].getgoal()].posy, mNote[i].getspeed(), mNote[i].getdtime() * Mi[NowState.MaingameMusicType] - (int)SDL_GetTicks() + (int)startTime);
                }
            
                //Update screen
                SDL_RenderPresent(gRenderer);
            }
            SDL_RemoveTimer(MaingameMusicTimerID);
            SDL_RemoveTimer(ButtonTimerID);
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
