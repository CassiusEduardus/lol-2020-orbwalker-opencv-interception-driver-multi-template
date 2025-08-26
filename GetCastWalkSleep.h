#pragma once

#include <thread>

class GetCastWalkSleep
{
private:
    std::thread getCastWalkSleepThread;

    void GetCastWalkSleepTimes();
public:
    GetCastWalkSleep();
    ~GetCastWalkSleep();
};