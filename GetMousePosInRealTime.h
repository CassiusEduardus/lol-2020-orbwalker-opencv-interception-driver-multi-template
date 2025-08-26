#pragma once

#include <thread>

#include "Estruturas.h"

class GetMousePosInRealTime
{
private:
    std::thread getMousePosThread;
    
    void GetMousePos();

public:
    GetMousePosInRealTime();
    ~GetMousePosInRealTime();
};