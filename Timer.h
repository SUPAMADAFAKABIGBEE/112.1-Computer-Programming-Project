//
//  Timer.h
//  Project
//
//  Created by Richard on 2023/11/24.
//

#ifndef Timer_h
#define Timer_h

#define Uint32 uint32_t
#include <stdint.h>

class Timer
{
    public:
        Timer()
        {
            mStartTicks = 0;
            mPausedTicks = 0;
            mPaused = false;
            mStarted = false;
        }

        void start();
        void stop();
        void pause();
        void unpause();

        Uint32 getTicks();

        bool isStarted();
        bool isPaused();

    private:
        Uint32 mStartTicks;

        Uint32 mPausedTicks;

        bool mPaused;
        bool mStarted;
};

#endif /* Timer_h */
