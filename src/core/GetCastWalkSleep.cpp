#include "GetCastWalkSleep.h"

extern int SLEEP_CAST_G;
extern int SLEEP_WALK_G;

extern float ATSP_G;

extern int myChampID;

struct CHAMPS
{
    //0 TWITCH
    //1 ASHE
    //2 VAYNE
    //3 TRISTANA
    //4 KOG'MAW
    //5 SIVIR
    //6 XAYAH
    //7 JINX
    //8 KALISTA
    //9 KINDRED
    float RATIO_CDOFFSET[10][2] = {
        {0.679 , (-0.08)},
        {0.658 , (-0.05)},
        {0.658 , (-0.05)},
        {0.656 , (-0.0473)},
        {0.665 , (-0.06)},
        {0.625 , (0)},
        {0.625 , (0)},
        {0.625 , (0)},
        {0.644 , (-0.03)},
        {0.625 , (0)}
    };
};

GetCastWalkSleep::GetCastWalkSleep()
{
    this->getCastWalkSleepThread = std::thread(&GetCastWalkSleep::GetCastWalkSleepTimes, this);
    this->getCastWalkSleepThread.detach();
}

void GetCastWalkSleep::GetCastWalkSleepTimes()
{
    CHAMPS champ;

    float GlobalBaseAttackCooldown = (1.6);
    float GlobalBaseAttackCastPer = (0.333);
    float GlobalBaseWindupTime = (0.53);

    float BaseAttackCooldown = 0;
    float TotalAttackSpeed = 0;
    float TotalAttackCooldown = 0;
    float TotalBonusAttackSpeed = 0;
    float AttackWindupPercent = 0;
    float BaseAttackWindupTime = 0;
    float TotalAttackWindupTime = 0;

    BaseAttackCooldown = (GlobalBaseAttackCooldown * (1 + champ.RATIO_CDOFFSET[myChampID][1]));
    AttackWindupPercent = (GlobalBaseAttackCastPer + champ.RATIO_CDOFFSET[myChampID][1]);

    while (1)
    {
        TotalAttackSpeed = ATSP_G;

        TotalAttackCooldown = (1 / TotalAttackSpeed);

        TotalBonusAttackSpeed = ((TotalAttackSpeed - champ.RATIO_CDOFFSET[myChampID][0]) / champ.RATIO_CDOFFSET[myChampID][0]);

        BaseAttackWindupTime = (BaseAttackCooldown * AttackWindupPercent);

        TotalAttackWindupTime = (BaseAttackWindupTime / (1 + (TotalBonusAttackSpeed * 1)));

        if (ATSP_G > 2.50)
        {
            SLEEP_CAST_G = static_cast<int>((TotalAttackWindupTime * 1000));
            SLEEP_WALK_G = static_cast<int>((TotalAttackCooldown * 1000) - SLEEP_CAST_G);
        }
        else
        {
            SLEEP_CAST_G = static_cast<int>((TotalAttackWindupTime * 1000) + 15);
            SLEEP_WALK_G = static_cast<int>((TotalAttackCooldown * 1000) - SLEEP_CAST_G + 15);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds((50)));
    }
}

GetCastWalkSleep::~GetCastWalkSleep()
{
    ;
}
