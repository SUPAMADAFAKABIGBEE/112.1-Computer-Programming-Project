/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "Background.cpp"
#include "State.cpp"
#include "MaingameMusic.cpp"
#include "Judgeline.cpp"

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

//The Judgeline
Judgeline *mJudgeline = new class Judgeline [JUDGELINE_TOTAL];

//The state
State NowState;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "巨大蜜蜂那三小的", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
    for(int i = 0; i < JUDGELINE_TOTAL; i++)
    {
        //Judgeline[i].type = i;
        //mJudgeline[i] = Judgeline(gRenderer);
        mJudgeline[i].initx = JudgelineInit[i][0];
        mJudgeline[i].inity = JudgelineInit[i][1];
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
    
    SDL_DestroyRenderer(gRenderer);
    
    //Quit SDL subsystems
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
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

            //Set default current surface
            gCurrentBackground = mBackground[NowState.BackgroundType].gBackground;

            //While application is running
            while(!quit)
            {
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
                        //Select surfaces based on key press
                        NowState.changeBackground(e);
                        gCurrentBackground = mBackground[NowState.BackgroundType].gBackground;
                        NowState.changeMaingameMusic();
                        if(NowState.detect(e) >= 0)
                        {
                            mJudgeline[NowState.detect(e)].pressed();
                        }
                    }
                }
                
                if(0 <= NowState.MaingameMusicType && NowState.MaingameMusicType < MAINGAMEMUSIC_TOTAL && NowState.MaingameMusicEnable != 0)
                {
                    if(Mix_PlayingMusic() == 0)
                    {
                        Mix_PlayMusic(MaingameMusic[NowState.MaingameMusicType].gMaingameMusic, 0);
                        NowState.MaingameMusicEnable = 0;
                    }
                }
                
                double degrees = 0;
                SDL_RendererFlip flipType = SDL_FLIP_NONE;
                
                //Clear screen
                SDL_RenderClear( gRenderer );
                
                SDL_RenderCopy( gRenderer, gCurrentBackground, NULL, NULL );

                //Render texture to screen
                
                for(int i = 0; i < JUDGELINE_TOTAL; i++)
                {
                    mJudgeline[i].render(NowState.BackgroundType, mJudgeline[i].initx, mJudgeline[i].inity, NULL, degrees, NULL, flipType );
                    //SDL_RenderCopy( gRenderer, mJudgeline[i].mTexture, NULL, NULL );
                }
            
                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
