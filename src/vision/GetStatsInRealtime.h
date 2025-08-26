#pragma once

#include <thread>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

struct boxSizes
{
    unsigned int mil920life[6][4] = {
        {505, 99, 90,  30},
        {495, 97, 100, 34},
        {490, 95, 105, 32},
        {480, 90, 110, 38},
        {469, 87, 130, 39},
        {471, 87, 124, 39}
    };

    unsigned int mil920stats[6][2] = {
            {50,20},
            {50,20},
            {55,25},
            {60,25},
            {65,30},
            {70,30}
    };

    unsigned int mil366life[6][4] = {
            {369, 74, 52, 23},
            {363, 72, 56, 25},
            {357, 69, 61, 28},
            {352, 68, 66, 29},
            {345, 65, 73, 29},
            {340, 63, 80, 31}
    };

    unsigned int mil366stats[6][2] = {
            {29, 15},
            {30, 15},
            {34, 17},
            {37, 18},
            {38, 19},
            {43, 21}
    };
};

class GetStatsInRealtime
{
private:
    std::thread getMyChampStatsThread;
    std::thread getMyChampIdThread;

    cv::Mat templatesStatsLadoAd[6];
    cv::Mat templateRngChampions[5];
    cv::Mat interfaceFullFrame;
    cv::Mat interfaceFullFrameChamp;
    cv::Mat interfaceStatAdFrame;
    cv::Mat interfaceLifeFrame;

    cv::Point templateAdMatchLocalization;

    unsigned int templateMatchLocalizationArrayPos = 0;
    unsigned int ladoAdTemplateOffset[6][2] = { 0 };
    unsigned int startBoxFullInterfaceX = 0;
    unsigned int startBoxFullInterfaceY = 0;
    unsigned int widthBoxFullInterface  = 0;
    unsigned int heighBoxFullInterface  = 0;

    double minConfidence = 0.00;
    double maxConfidence = 0.00;

    int vidaAtual = 0;
    float velocidadeDeAtaque = 0.0;

    unsigned int lifemanaBoxSize[6][4] = { 0 };
    unsigned int ladoAdBoxSize[6][2] = { 0 };

    void GetCurrentFrame(int boxBeginX, int boxBeginY, int boxWidth, int boxHeight);

    void GetMyChampStats();

    void GetMyChampId();

    void ResizeAttackSpeedFrame();
    void ResizeLifeFrame();

    void ExtractAttackSpeed();
    void ExtractLife();

    bool FindTemplateMatches();

    int FindSmallest(int arr[], int n) {
        int temp = arr[0];
        int chosen = 0;
        for (int i = 0; i < n; i++) {
            if (temp > arr[i])
            {
                temp = arr[i];
                chosen = i;
            }
        }
        return chosen;
    }

    int FindSmallest(double arr[], int n) {
        int temp = arr[0];
        int chosen = 0;
        for (int i = 0; i < n; i++) {
            if (temp > arr[i])
            {
                temp = arr[i];
                chosen = i;
            }
        }
        return chosen;
    }

public:
    GetStatsInRealtime(int resolutionID);
    ~GetStatsInRealtime();
};
