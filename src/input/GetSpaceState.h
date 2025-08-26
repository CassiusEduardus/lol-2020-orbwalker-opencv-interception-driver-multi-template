#pragma once

#include <thread>

class GetSpaceState
{
private:
    std::thread getSpaceStateThread;

    void GetSpaceST();

public:
    GetSpaceState();
    ~GetSpaceState();
};
