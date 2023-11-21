/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include "Background.cpp"
#include "State.cpp"
#include "MaingameMusic.cpp"

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
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//The surface contained by the window
Background Background[BACKGROUND_TOTAL];
SDL_Surface* gCurrentBackground = NULL;

//The maingame music
MaingameMusic MaingameMusic[MAINGAMEMUSIC_TOTAL];

//The state
State NowState;

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

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
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }
    
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    for(int i = 0; i < BACKGROUND_TOTAL; i++)
    {
        Background[i].type = i;
        success = success && Background[i].loadBackground(i);
    }
    for(int i = 0; i < MAINGAMEMUSIC_TOTAL; i++)
    {
        MaingameMusic[i].type = i;
        success = success && MaingameMusic[i].loadMaingameMusic(i);
    }
    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gScreenSurface );
    gScreenSurface = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    
    //Free
    for(int i = 0; i < BACKGROUND_TOTAL; i++)
    {
        SDL_FreeSurface(Background[i].gBackground);
        Background[i].gBackground = NULL;
    }
    for(int i = 0; i < MAINGAMEMUSIC_TOTAL; i++)
    {
        Mix_FreeMusic(MaingameMusic[i].gMaingameMusic);
        MaingameMusic[i].gMaingameMusic = NULL;
    }
    
    //Quit SDL subsystems
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
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
            gCurrentBackground = Background[NowState.BackgroundType].gBackground;

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
                        gCurrentBackground = Background[NowState.BackgroundType].gBackground;
                        NowState.changeMaingameMusic();
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
                
                //Apply the current image
                //SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
                SDL_BlitSurface(gCurrentBackground, NULL, gScreenSurface, NULL);
            
                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
