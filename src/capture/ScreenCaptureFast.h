#pragma once

#include <Windows.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <DXGI1_2.h>
#include <D3D11.h>
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "Dxgi.lib")

#include "Estruturas.h"

class ScreenCaptureFast
{
private:
    cv::Mat matScreenShot;
    cv::Mat matScreenShotFilterAuxA;
    cv::Mat matScreenShotFilterAuxB;

    ID3D11Device*            deviceD3D11;
    ID3D11DeviceContext*     immediateContextD3D11;
    IDXGIOutputDuplication*  desktopDuplicationD3D11;
    ID3D11Texture2D*         acquiredDesktopImageD3D11;
    DXGI_OUTPUT_DESC         outputDescD3D11;
    DXGI_OUTDUPL_DESC        outputDuplDescD3D11;
    D3D11_MAPPED_SUBRESOURCE resourceD3D11;
    ID3D11Texture2D*         currentTextureD3D11;

    unsigned int divisorColunas = 0;
    unsigned int divisorLinhas  = 0;
    unsigned int blockWidth     = 0;
    unsigned int blockHeigth    = 0;

    bool GetScreenShot();
    bool InitScreenCaptureFastDirectX();
public:
    ScreenCaptureFast();
    ~ScreenCaptureFast();

    void GetCurrentFrame(cv::Mat& outputFrame);

    bool ResizeFrame(ChampPosOffset& posOffset, cv::Mat& inputFrame, cv::Mat& outputFrame);
};

class ScreenCaptureSlow
{
private:
    cv::Mat matScreenShot;
public:
    ScreenCaptureSlow();
    ~ScreenCaptureSlow();

    void GetCurrentFrameSlow(cv::Mat& outputFrame);
};
