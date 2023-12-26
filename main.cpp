#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "Background.h"
#include "State.h"
#include "MaingameMusic.h"
#include "Judgeline.h"
#include "Note.h"
#include "GameInfo.h"
#include "SoundEffect.h"
#include "Text.h"
#include "Timer.h"
#include "Button.h"
#include "Image.h"
#include "Songfile.h"
#include "Screen.h"
#include "GameData.h"
#include "Object.h"
#include "PreviewMusic.h"
#include "GameResult.h"
#include "Bar.h"

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

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font form 5pt to 50pt
TTF_Font* gFont[FONT_TOTAL][10] = {};

//The surface contained by the window
Background *mBackground = NULL;
SDL_Texture* gCurrentBackground = NULL;

//The combo and score (in the maingame)
Text MainCombo(SCREEN_WIDTH - 210, 0, 210, 30);
Text MainScore(0, 0, 210, 30);
Text MainMusicData[] = {Text(100, SCREEN_HEIGHT/2 - 30, 200, 30),	//0: Name
						Text(100, SCREEN_HEIGHT/2, 200, 20), 		//1: SubName
						Text(100, SCREEN_HEIGHT/2 + 20, 200, 20)};	//2: Difficulty
Text ResultData[] = {	Text(120, 80, 200, 30),  //0: MusicName
						Text(250, 140, 200, 30), //1: Score
						Text(280, 200, 200, 30), //2: Perfect
						Text(280, 230, 200, 30), //3: Great
						Text(280, 260, 200, 30), //4: Good
						Text(280, 290, 200, 30), //5: Fair
						Text(280, 320, 200, 30), //6: Miss
						Text(280, 350, 200, 30), //7: BestCombo
						Text(450, 230, 200, 30)  //8: Rank
					};

//The sound effect
SoundEffect mSoundEffect[SOUNDEFFECT_TOTAL];

//The Notes
Note *mNote = NULL;

//The GameInfo
GameInfo *mGameInfo = NULL;

//The GameResult
GameResult *mGameResult = NULL;

//The Gameclock
Timer mTimer;

//The Judgelines
Judgeline *mJudgeline = NULL;

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
        gWindow = SDL_CreateWindow("Reincarnation of the BIG BEE in ISEKAI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
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
    for(int i = 0; i < SOUNDEFFECT_TOTAL; i++)
    {
        mSoundEffect[i].type = i;
        success = success && mSoundEffect[i].loadSoundEffect(i);
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
    if(NowState.getMaingameStart())
    {
		SDL_SetTextureColorMod(gCurrentBackground, NowState.getr(), NowState.getg(), NowState.getb());
	    NowState.GettingDim5();
	}
	else
	{
		SDL_SetTextureColorMod(gCurrentBackground, 255, 255, 255);
	    NowState.ResetRGB();
	}
    return 0;
}

Uint32 maingameNameTrans(Uint32 interval, void* param)
{
    if(NowState.getMaingameStart())
    {
    	for(int i = 0; i < 3; i++)
	    {
	        MainMusicData[i].minusTrans5();
	    }
	}
	else
	{
		for(int i = 0; i < 3; i++)
	    {
	        MainMusicData[i].changeVisible(0);
	    }
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

bool MaingameCon = 0; // M wMaingame  l  
bool MaingameEnd = 0;
Uint32 maingameMusicCallback(Uint32 interval, void* param)
{
    if(0 <= NowState.getMaingameMusicType() && NowState.getMaingameMusicType() < MAINGAMEMUSIC_TOTAL && NowState.getMaingameMusicEnable() != 0 && MaingameCon == 1)
    {
        if(Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(mGameInfo->getmMaingameMusic().getGMusic(), 0);
            NowState.setMaingameMusicEnable(0);
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


Uint32 MaingameEndCallback(Uint32 interval, void* param)
{
    //fcn
    if(NowState.getMaingameStart())
    {
    	for(int i = 0; i < 3; i++)
	    {
	        MainMusicData[i].changeVisible(0);
	        MainMusicData[i].ResetTrans();
	    }
	    SDL_SetTextureColorMod(gCurrentBackground, 255, 255, 255);
	    NowState.ResetRGB();
	    NowState.setBackgroundType(3);
	    NowState.setMaingamePause(0);
	    MaingameCon = 0;
	    MaingameEnd = 1;
	    NowState.setMaingameStart(0);
	    Mix_HaltMusic();
	    mTimer.stop();
	    if(mGameResult != NULL){
	    	delete mGameResult;
	    	mGameResult = NULL;
		}
	    mGameResult = new GameResult(*mGameInfo);
	    if(mGameInfo!=NULL){
	    	delete mGameInfo;
	    	mGameInfo = NULL;
		}
	}
    return 0;
}

SDL_TimerID MaingameMusicNameTimerID;
SDL_TimerID MaingameMusicTimerID;
SDL_TimerID ButtonTimerID;
SDL_TimerID MaingameBackgroundDimID;
SDL_TimerID MaingameMusicNameTransID;
SDL_TimerID MaingameEndCallbackID;

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
        //stc
		Songfile* Song = new Songfile[3]{Songfile(0), Songfile(1), Songfile(2)};
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
            
            int furtherNote = 0; // ù  W |  ܪ  ̫᭱  note
            long double Mi = 0; //Maingame   ̤p   R ɶ    A  Ū   H K    
            
            //SDL_RendererFlip flipType = SDL_FLIP_NONE;
            
            mBackground = new Background[BACKGROUND_TOTAL]{Background(0), Background(1), Background(2), Background(3)};

            //Set default current surface
            gCurrentBackground = mBackground[NowState.getBackgroundType()].mTexture;
            
            Note *tempNote = NULL;
            Screen screen = Screen(340, 10, 300, 400);
            PreviewMusic gPreviewMusic[3] = {PreviewMusic(0), PreviewMusic(1), PreviewMusic(2)};
            
            Image PreciseBar = Image(5, 190, 5, 101);
            PreciseBar.pass_file_location("./Element/precisebar.png");
            Bar **mBar = NULL;
            Bar *tempBar = NULL;
            int currentMusic = 0;    
            
			//The Judgeline
			mJudgeline = new Judgeline [JUDGELINE_TOTAL]{Judgeline(-100, -100, 100, 10, 0), Judgeline(-100, -100, 100, 10, 1), Judgeline(-100, -100, 100, 10, 2), Judgeline(-100, -100, 100, 10, 3)};
            
			//The Buttons
			const Button PauseButton[PAUSEBUTTON_TOTAL] = {Button(260, 215, 0), Button(330, 215, 1)};
            
            //While application is running
            while(!quit)
            {
//Added by stc Start
				if(NowState.getBackgroundType() == 1)
				{
                	if(mBar != NULL)
					{
						for(int i = Bar::totalBar - 1; i >= 0; i--)
	                	{
							if(mBar[i] != NULL)
							{
								delete mBar[i];
								mBar[i] = NULL;
							}
						}
						delete [] mBar;
						mBar = NULL;
					}
                	if(mGameResult != NULL)
					{
						delete mGameResult;
						mGameResult = NULL;
					}
					if(mGameInfo != NULL)
					{
						delete mGameInfo;
						mGameInfo = NULL;
					}
                    if(mNote != NULL)
                    {
                    	delete [] mNote;
                    	mNote = NULL;
					}
					if(Mix_PlayingMusic() == 0 && NowState.getMaingameDifficulty() != -1)
			        {
			            Mix_PlayMusic(gPreviewMusic[NowState.getMaingameMusicType()].getGMusic(), 0);
			        }
				}
//Added by stc End  
                if(NowState.getMaingameStart())
                {
					if(NowState.getMaingamePause())
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
                        Mix_HaltMusic(); 
						MaingameEnd = 0;
                        NowState.ResetRGB();
                        SDL_SetTextureColorMod(gCurrentBackground, NowState.getr(), NowState.getg(), NowState.getb());
                        mTimer.start();
                        mGameInfo = new class GameInfo(NowState.getMaingameMusicType(), NowState.getMaingameDifficulty());
                        Mi = mGameInfo->getMi();
                        for(int i = 0; i < JUDGELINE_TOTAL; i++)
                        {
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
                        if(NowState.getMaingameMusicType() >= 0)
                        {
                            MaingameMusicTimerID = SDL_AddTimer(3000, maingameMusicCallback, const_cast<char*>( "3 seconds waited!" ) );
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
                        mNote = new Note [mGameInfo->getMaxCombo()];
                        mBar = new Bar* [mGameInfo->getMaxCombo()];
                        for(; furtherNote < mGameInfo->getMaxObject(); furtherNote++)
                        {
                            if(mGameInfo->beatmap[furtherNote][2] != -1)
                            {
								tempNote = new Note(mGameInfo->beatmap[furtherNote]);
								mNote[furtherNote] =  *tempNote;
                            }
                        }
                    }
                    else
                    {
                        if(mGameInfo->getPassNote() == mGameInfo->getMaxCombo())
                        {
                            //      result
                            if(MaingameEnd == 0)
							{
								MaingameEnd = 1;
								MaingameEndCallbackID = SDL_AddTimer(5000, MaingameEndCallback, const_cast<char*>( "." ) );
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
                        MaingameEnd = 1;
                        Mix_HaltMusic();
                        mTimer.stop();
                        SDL_SetTextureColorMod(gCurrentBackground, 255, 255, 255);
                        NowState.ResetRGB();
                    }
                }
                if(NowState.getBackgroundType() == 3)
                {
					if(mBar != NULL)
					{
						for(int i = Bar::totalBar - 1; i >= 0; i--)
	                	{
							if(mBar[i] != NULL)
							{
								delete mBar[i];
								mBar[i] = NULL;
							}
						}
						delete [] mBar;
						mBar = NULL;
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
                        NowState.changeMaingameMusic(e);
                        NowState.changeMaingameDifficulty(e);
                        if(currentMusic != NowState.getMaingameMusicType())
				        {
				            currentMusic = NowState.getMaingameMusicType();
							Mix_PlayMusic(gPreviewMusic[NowState.getMaingameMusicType()].getGMusic(), 0);
				        }
                        if(NowState.getMaingameStart() && !NowState.getMaingamePause())
                        {
                            if(NowState.detect(e) >= 0)
                            {
                                for(int i = 0; i < mGameInfo->getMaxCombo(); i++)
                                {
                                    if(mNote[i].judge(NowState.detect(e), (int)mTimer.getTicks() - (int)startTime, mGameInfo, Mi))
                                    {
                                        tempBar = new Bar(mNote[i].getTimedif());
                                        mBar[Bar::totalBar - 1] = tempBar;
										break;
                                    }
                                }
                                mJudgeline[NowState.detect(e)].pressed();
                                ButtonTimerID = SDL_AddTimer(100, buttonCallback, const_cast<char*>( "0.1 seconds waited!" ) );
                            }
                        }
                        else if(NowState.getMaingameStart() && NowState.getMaingamePause())
                        {
                            NowState.changeMaingamePauseState(e);
                        }
                    }
                }
                
                //Clear screen
                SDL_RenderClear( gRenderer );
                
                gCurrentBackground = mBackground[NowState.getBackgroundType()].mTexture;
                SDL_RenderCopy( gRenderer, gCurrentBackground, NULL, NULL );
                
                //Render texture to screen
                if(NowState.getBackgroundType() == 1)
                {
					Songfile::MusicType = NowState.getMaingameMusicType();
					screen.render();
                    if(Song != NULL) SongSelecting(Song, NowState.getChooseDifficult());
                    screen.projecting(NowState.getMaingameMusicType(), NowState.getMaingameDifficulty(), Song, NowState.getChooseDifficult());
                    if(NowState.getMaingameMusicType()!=0)  //other song file not ready yet
					{
						NowState.setChooseDifficult(0);	
						Text SongNotReady(80, 340, 100, 40);
						SongNotReady.loadFromRenderedText("COMING SOON", SongNotReady.textColor = {255, 255, 255}, 3, 6);
						SongNotReady.changeVisible(1);
						SongNotReady.setAlpha(SongNotReady.getTrans());
						gRenderer << *(Object*)(&SongNotReady);
					}
                }
                if(mGameInfo != NULL && NowState.getMaingameStart())
                {
					MainCombo.loadFromRenderedText(mGameInfo->getString(mGameInfo->getCurrentCombo()), MainCombo.textColor = { 255, 255, 255 }, 2, 4);
                    MainScore.loadFromRenderedText(mGameInfo->getString(mGameInfo->getScore()), MainScore.textColor = { 255, 255, 255 }, 2, 4);
                    gRenderer << *(Object*)(&MainCombo);
                    gRenderer << *(Object*)(&MainScore);
                }
                if(NowState.getBackgroundType() == 3)
                {
                	if( mGameResult != NULL ){
						cout << *mGameResult;		
					}
                }
                if(NowState.getMaingameStart() && !NowState.getMaingamePause())
                {
                    for(int i = 0; i < JUDGELINE_TOTAL; i++)
                    {
                        mJudgeline[i].render((int)mTimer.getTicks() - (int)startTime, Mi);
                    }
                    if(mNote != NULL)
                    {
                    	for(int i = 0; i < mGameInfo->getMaxCombo(); i++)
	                    {
	                        if(mNote[i].getdtime() * Mi - (int)mTimer.getTicks() + (int)startTime < -240)
	                        {
	                            if(mNote[i].getResult() == -1)
	                            {
	                                mGameInfo->addmiss();
	                                mGameInfo->addPassNote();
	                                mGameInfo->calculate();
	                                mGameInfo->cutCombo();
	                                mNote[i].setResult(0);
	                            }
	                            else if(mNote[i].getResult() != 0)
	                            {
	                            	mNote[i].setResult(5);
								}
	                        }
	                        if(mNote[i].getResult() != 5 && mNote[i].getstime() * Mi - (int)mTimer.getTicks() + (int)startTime < 1000)
	                        {
	                        	mNote[i].setAlpha(mNote[i].setTrans((int)mTimer.getTicks() - (int)startTime));
	                        	mNote[i].render((int)mTimer.getTicks() - (int)startTime, Mi);
							}
	                    }
					}
                    if(mGameInfo != NULL && NowState.getMaingameStart())
                    {
                        MainMusicData[0].loadFromRenderedText(mGameInfo->getMusicName(), MainCombo.textColor = { 255, 255, 255 }, 4, 5);
                        MainMusicData[1].loadFromRenderedText(mGameInfo->getMusicSubName(), MainScore.textColor = { 255, 255, 255 }, 1, 3);
                        MainMusicData[2].loadFromRenderedText(mGameInfo->getMusicDifficultyName() + " " + mGameInfo->getString(mGameInfo->getMusicDifficultyParam()), MainScore.textColor = { 255, 255, 255 }, 1, 3);
                        for(int i = 0; i < 3; i++)
                        {
                            MainMusicData[i].setAlpha(MainMusicData[i].getTrans());
                            gRenderer << *(Object*)(&MainMusicData[i]);
                        }
                    }
                }
                else if(NowState.getMaingameStart() && NowState.getMaingamePause())
                {
                    for(int i = 0; i < PAUSEBUTTON_TOTAL; i++)
                    {
                        if(i == NowState.getMaingamePauseState()) PauseButton[i].pressed();
                        else PauseButton[i].unpressed();
                        gRenderer << *(Object*)(&PauseButton[i]);
                    }
                }
                if(NowState.getBackgroundType() == 2)
                {
					PreciseBar.render();
					gRenderer << *(Object*)(&PreciseBar);
					for(int i = 0; i < Bar::totalBar; i++)
					{
						gRenderer << *(Object*)mBar[i];
						mBar[i]->changeAlpha();
					}
				}
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
        
