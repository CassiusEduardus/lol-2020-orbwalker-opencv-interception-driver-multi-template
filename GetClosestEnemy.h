#pragma once

#include "ScreenCaptureFast.h"

class GetClosestEnemy : public ScreenCaptureFast, ScreenCaptureSlow
{
private:
    std::thread getClosestEnemyPosThread;

    cv::Mat screenShotFrame;

    cv::Mat allyOutputFrame;
    cv::Mat enemyOutputFrame;

    cv::Mat allyOutputFrameResized;
    cv::Mat enemyOutputFrameResized;

    cv::Mat enemyTemplate;
    cv::Mat allyTemplate;

    ChampPosOffset allyPosOffset;
    ChampPosOffset enemyPosOffset;

    AllyChampPos allyChampPos;

    ClosestEnemyChampPos closestEnemyChampPosG;

    int resolutionID = 0;

    void GetClosestEnemyPos1920();
    void GetClosestEnemyPos1366();

    bool ProcessFrame();

    void FindEnemyMatch();
    bool FindAllyMatch();

public:
    GetClosestEnemy(int resolutionID);
    ~GetClosestEnemy();

};