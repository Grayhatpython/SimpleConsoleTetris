#pragma once

using timeTick = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Time
{
    enum
    {
        KEY_INPUT_TICK = 50,
        MOVE_TICK = 200,
    };

public:
    
    static void CurrentTickCheck()
    {
        //moveCurrentTick = std::chrono::high_resolution_clock::now();
        keyInputCurrentTick = std::chrono::high_resolution_clock::now();
    }

    static bool DeltaTickCheck()
    {
        timeTick endTick = std::chrono::high_resolution_clock::now();

        deltaTick = endTick - moveCurrentTick;

        if (std::chrono::duration_cast<std::chrono::milliseconds>(deltaTick).count() <= MOVE_TICK)
            return false;

        moveCurrentTick = std::chrono::high_resolution_clock::now();

        return true;
    }

    static bool KeyInputTickCheck()
    {
        timeTick endTick = std::chrono::high_resolution_clock::now();

        keyInputTick = endTick - keyInputCurrentTick;

        if (std::chrono::duration_cast<std::chrono::milliseconds>(keyInputTick).count() <= KEY_INPUT_TICK)
            return false;

        keyInputCurrentTick = std::chrono::high_resolution_clock::now();

        return true;
    }

public:
    static timeTick moveCurrentTick;
    static timeTick keyInputCurrentTick;
    static std::chrono::nanoseconds deltaTick;
    static std::chrono::nanoseconds keyInputTick;
};

