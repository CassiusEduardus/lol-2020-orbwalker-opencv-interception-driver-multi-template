#include "GetClosestEnemy.h"

extern InterceptionMouseStroke MOUSE_STROKE_ENPOS;

extern int SPACE_STATE_G;

extern unsigned int screenWidth;
extern unsigned int screenHeight;

GetClosestEnemy::GetClosestEnemy(int resolutionID)
{
    this->resolutionID = resolutionID;

    enemyTemplate = cv::imread("Interface Templates\\CHAMPS\\ENEMY TEMPLATE.png", CV_8U);
    allyTemplate = cv::imread("Interface Templates\\CHAMPS\\ALLY TEMPLATE.png", CV_8U);

    switch (resolutionID)
    {
    case 1920:
        this->getClosestEnemyPosThread = std::thread(&GetClosestEnemy::GetClosestEnemyPos1920, this);
        this->getClosestEnemyPosThread.detach();
        break;

    case 1366:
        this->getClosestEnemyPosThread = std::thread(&GetClosestEnemy::GetClosestEnemyPos1366, this);
        this->getClosestEnemyPosThread.detach();
        break;

    default:
        std::cout << "[!!!] Sua resolucao nao e suportada..." << std::endl;
        exit(-1);
        break;
    }
}

bool GetClosestEnemy::ProcessFrame()
{
    switch (resolutionID)
    {
    case 1920:

        if (!allyOutputFrame.empty())
            allyOutputFrame.release();

        if (!enemyOutputFrame.empty())
            enemyOutputFrame.release();

        if (!allyOutputFrameResized.empty())
            allyOutputFrameResized.release();

        if (!enemyOutputFrameResized.empty())
            enemyOutputFrameResized.release();

        cv::cvtColor(screenShotFrame, allyOutputFrame, cv::COLOR_BGR2HSV);
        cv::inRange(allyOutputFrame, cv::Scalar(22, 140, 40), cv::Scalar(28, 255, 255), allyOutputFrame);

        cv::cvtColor(screenShotFrame, enemyOutputFrame, cv::COLOR_BGR2HSV);
        cv::inRange(enemyOutputFrame, cv::Scalar(2, 100, 50), cv::Scalar(4, 255, 255), enemyOutputFrame);

        if (ResizeFrame(allyPosOffset, allyOutputFrame, allyOutputFrameResized))
        {
            if (ResizeFrame(enemyPosOffset, enemyOutputFrame, enemyOutputFrameResized))
            {
                return true;
            }
        }

        return false;
        break;
    
    case 1366:

        if (!allyOutputFrame.empty())
            allyOutputFrame.release();

        if (!enemyOutputFrame.empty())
            enemyOutputFrame.release();

        cv::cvtColor(screenShotFrame, allyOutputFrame, cv::COLOR_BGR2HSV);
        cv::inRange(allyOutputFrame, cv::Scalar(22, 140, 40), cv::Scalar(28, 255, 255), allyOutputFrame);

        cv::cvtColor(screenShotFrame, enemyOutputFrame, cv::COLOR_BGR2HSV);
        cv::inRange(enemyOutputFrame, cv::Scalar(2, 100, 50), cv::Scalar(4, 255, 255), enemyOutputFrame);

        return true;
        break;

    default:

        std::cout << "[!!!] Sua resolucao nao e suportada..." << std::endl;
        exit(-1);
        break;
    }

    return false;
}

bool GetClosestEnemy::FindAllyMatch()
{
    cv::Mat resultTemplate;

    cv::Point allyMatchLoc;

    double minConfidence = 0;
    double maxConfidence = 0.35;

    switch (resolutionID)
    {
    case 1920:
        cv::matchTemplate(allyOutputFrameResized, allyTemplate, resultTemplate, cv::TM_SQDIFF_NORMED);
        break;
    case 1366:
        cv::matchTemplate(allyOutputFrame, allyTemplate, resultTemplate, cv::TM_SQDIFF_NORMED);
        break;
    }
    
    cv::minMaxLoc(resultTemplate, &minConfidence, NULL, &allyMatchLoc, NULL);

    if (minConfidence < maxConfidence)
    {
        switch (resolutionID)
        {
        case 1920:
            allyChampPos.pos[0] = allyMatchLoc.x + allyPosOffset.offsetX;
            allyChampPos.pos[1] = allyMatchLoc.y + allyPosOffset.offsetY;
            break;
        case 1366:
            allyChampPos.pos[0] = allyMatchLoc.x;
            allyChampPos.pos[1] = allyMatchLoc.y;
            break;
        }

        return true;
    }

    closestEnemyChampPosG.pos[0] = 0;
    closestEnemyChampPosG.pos[1] = 0;

    allyChampPos.pos[0] = 0;
    allyChampPos.pos[1] = 0;

    return false;
}

void GetClosestEnemy::FindEnemyMatch()
{
    cv::Mat resultTemplate;

    cv::Point enemyMatchLoc;

    EnemyChampsPos enemyChampsPos;

    int detectedEnemys  = 0;
    int closestArrayPos = 0;

    double distanciaMaxima = 1000000;
    double distanciaMatchi = 0;

    double maxRange = 0;

    double minConfidence = 0;
    double maxConfidence = 0.48;

    switch (resolutionID)
    {
    case 1920:
        maxRange = 550;
        cv::matchTemplate(enemyOutputFrameResized, enemyTemplate, resultTemplate, cv::TM_SQDIFF_NORMED);
        break;
    case 1366:
        maxRange = 380;
        cv::matchTemplate(enemyOutputFrame, enemyTemplate, resultTemplate, cv::TM_SQDIFF_NORMED);
        break;
    }

    for (int i = 0; i < 5; i++)
    {
        cv::minMaxLoc(resultTemplate, &minConfidence, NULL, &enemyMatchLoc, NULL);

        if (minConfidence < maxConfidence)
        {
            cv::rectangle(resultTemplate, cv::Point(enemyMatchLoc.x - 16, enemyMatchLoc.y - 16), cv::Point(enemyMatchLoc.x + enemyTemplate.cols, enemyMatchLoc.y + enemyTemplate.rows), cv::Scalar::all(255), -1);

            switch (resolutionID)
            {
            case 1920:
                enemyChampsPos.pos[detectedEnemys][0] = enemyMatchLoc.x + enemyPosOffset.offsetX;
                enemyChampsPos.pos[detectedEnemys][1] = enemyMatchLoc.y + enemyPosOffset.offsetY;
                break;
            case 1366:
                enemyChampsPos.pos[detectedEnemys][0] = enemyMatchLoc.x;
                enemyChampsPos.pos[detectedEnemys][1] = enemyMatchLoc.y;
                break;
            }

            distanciaMatchi = sqrt((pow((allyChampPos.pos[0] - enemyChampsPos.pos[detectedEnemys][0]), 2) + pow(allyChampPos.pos[1] - enemyChampsPos.pos[detectedEnemys][1], 2)));
            
            if (distanciaMatchi < distanciaMaxima && distanciaMatchi > 0 && distanciaMatchi <= maxRange)
            {
                distanciaMaxima = distanciaMatchi;
                closestArrayPos = detectedEnemys;
                detectedEnemys++;
            }
        }
        else
        {
            break;
        }
    }

    if (detectedEnemys > 0)
    {   
        switch (resolutionID)
        {
        case 1920:
            MOUSE_STROKE_ENPOS.x = static_cast<int>((0xFFFF * (enemyChampsPos.pos[closestArrayPos][0] + 80)) / screenWidth);
            MOUSE_STROKE_ENPOS.y = static_cast<int>((0xFFFF * (enemyChampsPos.pos[closestArrayPos][1] + 150)) / screenHeight);
            break;
        case 1366:
            MOUSE_STROKE_ENPOS.x = static_cast<int>((0xFFFF * (enemyChampsPos.pos[closestArrayPos][0] + 70)) / screenWidth);
            MOUSE_STROKE_ENPOS.y = static_cast<int>((0xFFFF * (enemyChampsPos.pos[closestArrayPos][1] + 100)) / screenHeight);
            break;
        }
    }
    else
    {
        MOUSE_STROKE_ENPOS.x = 0;
        MOUSE_STROKE_ENPOS.y = 0;
    }
}

void GetClosestEnemy::GetClosestEnemyPos1920()
{
    while (TRUE)
    {
        GetCurrentFrame(screenShotFrame);

        if (ProcessFrame())
        {
            if (FindAllyMatch())
                FindEnemyMatch();
        }

        if (SPACE_STATE_G)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((50)));
        }
        else
            std::this_thread::sleep_for(std::chrono::milliseconds((250)));
    }
}

void GetClosestEnemy::GetClosestEnemyPos1366()
{
    while (TRUE)
    {
        GetCurrentFrameSlow(screenShotFrame);

        if (ProcessFrame())
        {
            if (FindAllyMatch())
                FindEnemyMatch();
        }

        if (SPACE_STATE_G)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((50)));
        }
        else
            std::this_thread::sleep_for(std::chrono::milliseconds((250)));
    }
}

GetClosestEnemy::~GetClosestEnemy()
{
    ;
}