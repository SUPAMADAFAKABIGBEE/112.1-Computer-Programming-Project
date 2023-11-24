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
#include "Timer.cpp"
#include "Button.cpp"
#include "GameData.h"

enum BeatmapParams
{
    stime,
    dtime,
    type,
    goal,
    endx,
    endy,
    speed,
    //BEATMAPPARAMS_TOTAL
};

extern const char* FontAddr[];
extern const char* SoundEffectAddr[];
extern const char* NoteAddr[];
extern const char* JudgelineAddr[];
extern const char* MaingameMusicAddr[];
extern const char* BackgroundAddr[];
extern const char* BeatmapAddr[][3];

extern int JudgelineInit[][2];

/*
extern int BPMlist[]; //Unit: beats per minute
extern int durationlist[]; //Unit: s (不含開頭準備3秒)
extern int maxcombo[][3];
extern long double Mi[];//Unit: ms
*/

extern int notedata[][3][1500][7];

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
TTF_Font* gFont[FONT_TOTAL][10] = {};

//The surface contained by the window
Background *mBackground = new class Background[BACKGROUND_TOTAL];
SDL_Texture* gCurrentBackground = NULL;

//The combo and score (in the maingame)
Text MainCombo(SCREEN_WIDTH - 210, 0, 210, 30);
Text MainScore(0, 0, 210, 30);
Text MainMusicData[] = {Text(100, SCREEN_HEIGHT/2 - 30, 200, 30), Text(100, SCREEN_HEIGHT/2, 200, 20), Text(100, SCREEN_HEIGHT/2 + 20, 200, 20)};//0: Name, 1:SubName, 2:Difficulty
//Text StoryDialogue()

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

//The Gameclock
Timer mTimer;

//The Buttons
Button PauseButton[PAUSEBUTTON_TOTAL] = {Button(260, 215), Button(330, 215)};
//Button SelectButton[1] = {Button(320, 320)};

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
        mJudgeline[i].setPosx(-100);
        mJudgeline[i].setPosy(-100);
        mJudgeline[i].setType(i);
        success = success && mJudgeline[i].loadByIndex(i);
    }
    for(int i = 0; i < FONT_TOTAL; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            gFont[i][j] = TTF_OpenFont(FontAddr[i], 5 + 5 * j);
            if(gFont[i][j] == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
            }
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
        for(int j = 0; j < 10; j++)
        {
            TTF_CloseFont(gFont[i][j]);
            gFont[i][j] = NULL;
        }
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

Uint32 maingameBackgroundDim(Uint32 interval, void* param)
{
    SDL_SetTextureColorMod(gCurrentBackground, NowState.getr(), NowState.getg(), NowState.getb());
    NowState.GettingDim5();
    return 0;
}

Uint32 maingameNameTrans(Uint32 interval, void* param)
{
    for(int i = 0; i < 3; i++)
    {
        MainMusicData[i].minusTrans5();
    }
    return 0;
}

Uint32 maingameMusicNameCallback(Uint32 interval, void* param)
{
    for(int i = 0; i < 3; i++)
    {
        MainMusicData[i].changeVisible(0);
    }
    return 0;
}

bool MaingameCon = 0; //決定Maingame初始化
Uint32 maingameMusicCallback(Uint32 interval, void* param)
{
    if(0 <= NowState.MaingameMusicType && NowState.MaingameMusicType < MAINGAMEMUSIC_TOTAL && NowState.MaingameMusicEnable != 0 && MaingameCon == 1)
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
            
            SDL_TimerID MaingameMusicNameTimerID;
            SDL_TimerID MaingameMusicTimerID;
            SDL_TimerID ButtonTimerID;
            SDL_TimerID MaingameBackgroundDimID;
            SDL_TimerID MaingameMusicNameTransID;
            
            int furtherNote = 0; //螢幕上會顯示的最後面的note
            long double Mi = 0; //Maingame的最小分析時間單位，先讀取以免延遲
            
            double degrees = 0;
            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            //Set default current surface
            gCurrentBackground = mBackground[NowState.BackgroundType].gBackground;
            
            //While application is running
            while(!quit)
            {
                /*
                if(NowState.BackgroundType == 1)
                {
                    for(int i = 0; i < 1; i++) SelectButton[i].setType(i);
                }
                 */
                if(NowState.MaingameStart)
                {
                    if(NowState.MaingamePause)
                    {
                        if(Mix_PausedMusic() == 0)  Mix_PauseMusic();
                        mTimer.pause();
                    }
                    else
                    {
                        if(Mix_PausedMusic() == 1)  Mix_ResumeMusic();
                        mTimer.unpause();
                    }
                    if(!MaingameCon)
                    {
                        //cout << "Hello once!!" << endl;
                        NowState.ResetRGB();
                        SDL_SetTextureColorMod(gCurrentBackground, NowState.getr(), NowState.getg(), NowState.getb());
                        for(int i = 0; i < PAUSEBUTTON_TOTAL; i++) PauseButton[i].setType(i);
                        mTimer.start();
                        mGameInfo = new class GameInfo(NowState.MaingameMusicType, NowState.MaingameDifficulty);
                        Mi = mGameInfo->getMi();
                        for(int i = 0; i < JUDGELINE_TOTAL; i++)
                        {
                            //Judgeline[i].type = i;
                            //mJudgeline[i] = Judgeline(gRenderer);
                            mJudgeline[i].setInitx(mGameInfo->getJudgelineInit(i, 0));
                            mJudgeline[i].setInity(mGameInfo->getJudgelineInit(i, 1));
                            mJudgeline[i].setPosx(mGameInfo->getJudgelineInit(i, 0));
                            mJudgeline[i].setPosy(mGameInfo->getJudgelineInit(i, 1));
                            mJudgeline[i].setInitDegree(mGameInfo->getJudgelineInit(i, 2));
                            mJudgeline[i].setMovementMap(mGameInfo->beatmap, mGameInfo->getMaxObject());
                        }
                        MaingameCon = 1;
                        furtherNote = 0;
                        MainCombo.changeVisible(1);
                        MainScore.changeVisible(1);
                        //cout << MainCombo.getTrans() << " " << MainScore.getTrans() << endl;
                        if(NowState.MaingameMusicType >= 0)
                        {
                            MaingameMusicTimerID = SDL_AddTimer(3000, maingameMusicCallback, const_cast<char*>( "3 seconds waited!" ) );
                            //NowState.changeMaingameMusic();
                        }
                        for(int i = 0; i < 3; i++) MainMusicData[i].changeVisible(1);
                        MaingameMusicNameTimerID = SDL_AddTimer(3000, maingameMusicNameCallback, const_cast<char*>( "." ));
                        for(int i = 0; i < 31; i++)
                        {
                            MaingameBackgroundDimID = SDL_AddTimer(1500 + i * 50, maingameBackgroundDim, const_cast<char*>( "." ));
                            MaingameMusicNameTransID = SDL_AddTimer(1500 + i * 30, maingameNameTrans, const_cast<char*>( "." ));
                        }
                        for(int i = 31; i < 51; i++)
                        {
                            MaingameMusicNameTransID = SDL_AddTimer(1500 + i * 30, maingameNameTrans, const_cast<char*>( "." ));
                        }
                        startTime = mTimer.getTicks() + 3000;
                        if(furtherNote < mGameInfo->getMaxObject())
                        {
                            for(; furtherNote < mGameInfo->getMaxObject(); furtherNote++)
                            {
                                //cout << mGameInfo->beatmap[furtherNote][0] * Mi << " " << (int)mTimer.getTicks() - (int)startTime << endl; //mGameInfo->getMi()
                                if(mGameInfo->beatmap[furtherNote][2] != -1)
                                {
                                    if(mGameInfo->beatmap[furtherNote][0] * Mi - (int)mTimer.getTicks() + (int)startTime < 1000)
                                    {
                                        tempNote = new class Note(mGameInfo->beatmap[furtherNote]);
                                        mNote.push_back(*tempNote);
                                        //cout << "Now we have: " << mNote.size() << " Notes" << endl;
                                        delete tempNote;
                                    }
                                    else break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(furtherNote < mGameInfo->getMaxObject())
                        {
                            for(; furtherNote < mGameInfo->getMaxObject(); furtherNote++)
                            {
                                //cout << mGameInfo->beatmap[furtherNote][0] * Mi << " " << (int)mTimer.getTicks() - (int)startTime << endl;
                                if(mGameInfo->beatmap[furtherNote][2] != -1)
                                {
                                    if(mGameInfo->beatmap[furtherNote][0] * Mi - (int)mTimer.getTicks() + (int)startTime < 1000)
                                    {
                                        tempNote = new class Note(mGameInfo->beatmap[furtherNote]);
                                        mNote.push_back(*tempNote);
                                        //cout << "Now we have: " << mNote.size() << " Notes" << endl;
                                        delete tempNote;
                                    }
                                    else break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(MaingameCon)
                    {
                        for(int i = 0; i < 3; i++)
                        {
                            MainMusicData[i].changeVisible(0);
                            MainMusicData[i].ResetTrans();
                        }
                        MaingameCon = 0;
                        Mix_HaltMusic();
                        mTimer.stop();
                        mNote.clear();
                        delete mGameInfo;
                        SDL_SetTextureColorMod(gCurrentBackground, 255, 255, 255);
                        NowState.ResetRGB();
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
                        NowState.changeMaingameMusic();
                        if(NowState.MaingameStart && !NowState.MaingamePause)
                        {
                            if(NowState.detect(e) >= 0)
                            {
                                for(int i = 0; i < mNote.size(); i++)
                                {
                                    if(mNote[i].judge(NowState.detect(e), (int)mTimer.getTicks() - (int)startTime, mGameInfo, Mi))
                                    {
                                        break;
                                    }
                                }
                                mJudgeline[NowState.detect(e)].pressed();
                                ButtonTimerID = SDL_AddTimer(100, buttonCallback, const_cast<char*>( "0.1 seconds waited!" ) );
                            }
                        }
                        else if(NowState.MaingameStart && NowState.MaingamePause)
                        {
                            NowState.changeMaingamePauseState(e);
                        }
                        /*
                        if(NowState.BackgroundType == 1)
                        {
                            NowState.changeSelectState(e);
                        }
                         */
                    }
                }
                
                //Clear screen
                SDL_RenderClear( gRenderer );
                
                gCurrentBackground = mBackground[NowState.BackgroundType].gBackground;
                SDL_RenderCopy( gRenderer, gCurrentBackground, NULL, NULL );
                
                
                //Render texture to screen
                /*
                if(NowState.BackgroundType == 1)
                {
                    StoryDialogue.render(NULL, 0, NULL, flipType);
                }
                 */
                if(mGameInfo != NULL)
                {
                    MainCombo.loadFromRenderedText(mGameInfo->getString(mGameInfo->getCurrentCombo()), MainCombo.textColor = { 255, 255, 255 }, 2, 4);
                    MainScore.loadFromRenderedText(mGameInfo->getString(mGameInfo->getScore()), MainScore.textColor = { 255, 255, 255 }, 2, 4);
                    MainCombo.render(MainCombo.getPosx(), MainCombo.getPosy());
                    MainScore.render(MainScore.getPosx(), MainScore.getPosy());
                }
                if(NowState.MaingameStart && !NowState.MaingamePause)
                {
                    for(int i = 0; i < JUDGELINE_TOTAL; i++)
                    {
                        mJudgeline[i].render(NowState.BackgroundType, NULL, degrees, NULL, flipType, (int)mTimer.getTicks() - (int)startTime, Mi);
                        //int BackgroundType, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, int time
                        //SDL_RenderCopy( gRenderer, mJudgeline[i].mTexture, NULL, NULL );
                    }
                    for(int i = 0; i < mNote.size(); i++)
                    {
                        if(mNote[i].getdtime() * Mi - (int)mTimer.getTicks() + (int)startTime < -240)
                        {
                            if(mNote[i].getResult() == -1)
                            {
                                mGameInfo->addmiss();
                                mGameInfo->calculate();
                                mGameInfo->cutCombo();
                            }
                            mNote.erase(mNote.begin() + i);
                            //cout << "mNote size: " << mNote.size() << endl;
                            //cout << "Oops: " << i << endl;
                        }
                        if(i >= mNote.size()) break;
                        //cout << "Now rendering: " << i << endl;
                        mNote[i].setAlpha(mNote[i].setTrans((int)mTimer.getTicks() - (int)startTime));
                        mNote[i].render(mNote[i].posx, mNote[i].posy, NULL, degrees, NULL, flipType, mNote[i].getEndx(), mNote[i].getEndy(), mNote[i].getspeed(), (int)mTimer.getTicks() - (int)startTime, Mi);
                    }
                    if(mGameInfo != NULL)
                    {
                        MainMusicData[0].loadFromRenderedText(mGameInfo->getMusicName(), MainCombo.textColor = { 255, 255, 255 }, 4, 5);
                        MainMusicData[1].loadFromRenderedText(mGameInfo->getMusicSubName(), MainScore.textColor = { 255, 255, 255 }, 1, 3);
                        MainMusicData[2].loadFromRenderedText(mGameInfo->getMusicDifficultyName() + " " + mGameInfo->getString(mGameInfo->getMusicDifficultyParam()), MainScore.textColor = { 255, 255, 255 }, 1, 3);
                        for(int i = 0; i < 3; i++)
                        {
                            MainMusicData[i].setAlpha(MainMusicData[i].getTrans());
                            MainMusicData[i].render(MainMusicData[i].getPosx(), MainMusicData[i].getPosy());
                        }
                    }
                }
                else if(NowState.MaingameStart && NowState.MaingamePause)
                {
                    for(int i = 0; i < PAUSEBUTTON_TOTAL; i++)
                    {
                        if(i == NowState.MaingamePauseState) PauseButton[i].pressed();
                        else PauseButton[i].unpressed();
                        PauseButton[i].render(NULL, 0, NULL, flipType);
                    }
                }
                /*
                if(NowState.BackgroundType == 1)
                {
                    for(int i = 0; i < 1; i++)
                    {
                        if(i == NowState.MaingamePauseState) SelectButton[i].pressed();
                        else SelectButton[i].unpressed();
                        SelectButton[i].render(NULL, 0, NULL, flipType);
                    }
                }
                 */
                
                //Update screen
                SDL_RenderPresent(gRenderer);
            }
            
            SDL_RemoveTimer(MaingameMusicNameTimerID);
            SDL_RemoveTimer(MaingameMusicTimerID);
            SDL_RemoveTimer(ButtonTimerID);
            SDL_RemoveTimer(MaingameBackgroundDimID);
            SDL_RemoveTimer(MaingameMusicNameTransID);
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
