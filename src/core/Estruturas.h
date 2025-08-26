#pragma once

#include "interception.h"

struct point
{
    double x;
    double y;
    point(double x, double y) : x(x), y(y) {}
};

struct ChampPosOffset
{
    int offsetX = 0;
    int offsetY = 0;
};

struct EnemyChampsPos
{
    int pos[5][2] = { 0 };
};

struct ClosestEnemyChampPos
{
    int pos[2] = { 0 };
};

struct AllyChampPos
{
    int pos[2] = { 0 };
};

enum ScanCode
{
    SCANCODE_SPACE = 0x39,
    SCANCODE_ESC = 0x01
};

struct KBD_Context_STRUCT
{
    InterceptionContext   Contexto_Teclado;
    InterceptionDevice	  DeviceID_Teclado;
    InterceptionKeyStroke Keystrok_Teclado;
};

struct MSE_Context_STRUCT
{
    InterceptionContext   Contexto_Mouse;
    InterceptionDevice	  DeviceID_Mouse;
    InterceptionKeyStroke Keystrok_Mouse;
    InterceptionStroke    Stroke_Mo_Mouse;
};
