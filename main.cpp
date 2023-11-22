/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Background.cpp"
#include "State.cpp"
#include "MaingameMusic.cpp"
#include "Judgeline.cpp"
#include "Note.cpp"
#include "GameInfo.cpp"
#include "SoundEffect.cpp"

enum KeyPressSurface
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
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

//The surface contained by the window
Background *mBackground = new class Background[BACKGROUND_TOTAL];
SDL_Texture* gCurrentBackground = NULL;

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
        success = success && mBackground[i].loadBackground(i);
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
        success = success && mJudgeline[i].loadJudgeline(i);
    }
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Free
    for(int i = 0; i < BACKGROUND_TOTAL; i++)
    {
        SDL_DestroyTexture(mBackground[i].gBackground);
        mBackground[i].gBackground = NULL;
    }
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
                        mGameInfo->miss++;
                        mGameInfo->calculate();
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
