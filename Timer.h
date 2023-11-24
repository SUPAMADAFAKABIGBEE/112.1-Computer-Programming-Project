//
//  Timer.h
//  Project
//
//  Created by Richard on 2023/11/24.
//

#ifndef Timer_h
#define Timer_h

class Timer
{
    public:
        //Initializes variables
        Timer()
        {
            mStartTicks = 0;
            mPausedTicks = 0;
            mPaused = false;
            mStarted = false;
        }

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        Uint32 getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        //The clock time when the timer started
        Uint32 mStartTicks;

        //The ticks stored when the timer was paused
        Uint32 mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
};

#endif /* Timer_h */
