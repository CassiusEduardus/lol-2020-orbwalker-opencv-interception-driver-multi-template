#include "GetStatsInRealtime.h"

#include <Windows.h>

#include "avir.h"

extern float ATSP_G;

extern int SPACE_STATE_G;

extern int myChampID;

extern unsigned int screenWidth;
extern unsigned int screenHeight;

GetStatsInRealtime::GetStatsInRealtime(int resolutionID)
{
    boxSizes boxsizes;

    switch (resolutionID)
    {
    case 1920:
        templateRngChampions[0] = cv::imread("Interface Templates\\CHAMPS\\TWITCH 1080p 30.png", CV_8U);
        templateRngChampions[1] = cv::imread("Interface Templates\\CHAMPS\\ASHE 1080p 30.png", CV_8U);

        templatesStatsLadoAd[0] = cv::imread("Interface Templates\\STATS\\1080p - 0% - L1.png", CV_8U);
        templatesStatsLadoAd[1] = cv::imread("Interface Templates\\STATS\\1080p - 20% - L1.png", CV_8U);
        templatesStatsLadoAd[2] = cv::imread("Interface Templates\\STATS\\1080p - 40% - L1.png", CV_8U);
        templatesStatsLadoAd[3] = cv::imread("Interface Templates\\STATS\\1080p - 60% - L1.png", CV_8U);
        templatesStatsLadoAd[4] = cv::imread("Interface Templates\\STATS\\1080p - 80% - L1.png", CV_8U);
        templatesStatsLadoAd[5] = cv::imread("Interface Templates\\STATS\\1080p - 100% - L1.png", CV_8U);

        startBoxFullInterfaceX = 362;
        startBoxFullInterfaceY = 944;
        widthBoxFullInterface = 743;
        heighBoxFullInterface = 136;

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                lifemanaBoxSize[i][j] = boxsizes.mil920life[i][j];
            }
        }

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                ladoAdBoxSize[i][j] = boxsizes.mil920stats[i][j];
            }
        }

        break;
    case 1366:
        templatesStatsLadoAd[0] = cv::imread("Interface Templates\\STATS\\1366p - 0% - L1.png", CV_8U);
        templatesStatsLadoAd[1] = cv::imread("Interface Templates\\STATS\\1366p - 20% - L1.png", CV_8U);
        templatesStatsLadoAd[2] = cv::imread("Interface Templates\\STATS\\1366p - 40% - L1.png", CV_8U);
        templatesStatsLadoAd[3] = cv::imread("Interface Templates\\STATS\\1366p - 60% - L1.png", CV_8U);
        templatesStatsLadoAd[4] = cv::imread("Interface Templates\\STATS\\1366p - 80% - L1.png", CV_8U);
        templatesStatsLadoAd[5] = cv::imread("Interface Templates\\STATS\\1366p - 100% - L1.png", CV_8U);

        startBoxFullInterfaceX = 257;
        startBoxFullInterfaceY = 666;
        widthBoxFullInterface = 533;
        heighBoxFullInterface = 102;

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                lifemanaBoxSize[i][j] = boxsizes.mil366life[i][j];
            }
        }

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                ladoAdBoxSize[i][j] = boxsizes.mil366stats[i][j];
            }
        }

        break;
    default:
        std::cout << "[!!!] Sua resolucao nao e suportada..." << std::endl;
        exit(-1);
        break;
    }

    for (int i = 0; i < 6; i++)
    {
        ladoAdTemplateOffset[i][0] = templatesStatsLadoAd[i].cols;
        ladoAdTemplateOffset[i][1] = templatesStatsLadoAd[i].rows;
    }

    minConfidence = 0.00;
    maxConfidence = 0.30;

    this->getMyChampIdThread = std::thread(&GetStatsInRealtime::GetMyChampId, this);
    this->getMyChampIdThread.detach();

    this->getMyChampStatsThread = std::thread(&GetStatsInRealtime::GetMyChampStats, this);
    this->getMyChampStatsThread.detach();
}

void GetStatsInRealtime::GetMyChampId()
{
    cv::Mat resultTemplate;
    double champIdConfidence[5] = { 0 };
    int closest = 0;

    while (TRUE)
    {
        std::this_thread::sleep_for(std::chrono::seconds((10)));

        for (int i = 0; i < 2; i++)
        {
            cv::matchTemplate(interfaceFullFrameChamp, templateRngChampions[i], resultTemplate, cv::TM_SQDIFF_NORMED);
            cv::minMaxLoc(resultTemplate, &champIdConfidence[i], NULL, &templateAdMatchLocalization, NULL);
        }

        closest = FindSmallest(champIdConfidence, 2);

        if (closest >= 0 && closest <= 5)
            myChampID = closest;
        else
            myChampID = 0;

        std::cout << myChampID << std::endl;

        std::this_thread::sleep_for(std::chrono::minutes((3)));
    }
}

void GetStatsInRealtime::GetMyChampStats()
{
    int sleepTimer = 100;

    while (TRUE)
    {
        GetCurrentFrame(startBoxFullInterfaceX, startBoxFullInterfaceY, widthBoxFullInterface, heighBoxFullInterface);

        if (FindTemplateMatches())
        {
            for (int i = 0; i < 20; i++)
            {
                ExtractAttackSpeed();

                if (SPACE_STATE_G)
                {
                    ExtractLife();

                    sleepTimer = 100;
                }
                else
                {
                    sleepTimer = 250;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds((sleepTimer)));

                GetCurrentFrame(startBoxFullInterfaceX, startBoxFullInterfaceY, widthBoxFullInterface, heighBoxFullInterface);
            }
        }
    }
}

void GetStatsInRealtime::GetCurrentFrame(int boxBeginX, int boxBeginY, int boxWidth, int boxHeight)
{
    if (!interfaceFullFrame.empty())
        interfaceFullFrame.release();

    HDC HDCScreen;
    HDC HDCMemory;
    HBITMAP HBitmap;
    HBITMAP HOldBitmap;
    BITMAPINFOHEADER bi;

    HDCScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);

    HDCMemory = CreateCompatibleDC(HDCScreen);

    HBitmap = CreateCompatibleBitmap(HDCScreen, boxWidth, boxHeight);

    HOldBitmap = (HBITMAP)SelectObject(HDCMemory, HBitmap);

    BitBlt(HDCMemory, 0, 0, boxWidth, boxHeight, HDCScreen, boxBeginX, boxBeginY, SRCCOPY);

    HBitmap = (HBITMAP)SelectObject(HDCMemory, HOldBitmap);

    interfaceFullFrame.create(boxHeight, boxWidth, CV_8UC4);

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = boxWidth;
    bi.biHeight = -boxHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32; //Intensidade
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    GetDIBits(HDCScreen, HBitmap, 0, boxHeight, interfaceFullFrame.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    cv::cvtColor(interfaceFullFrame, interfaceFullFrame, cv::COLOR_BGR2GRAY);

    interfaceFullFrameChamp = interfaceFullFrame.clone();

    DeleteDC(HDCScreen);
    DeleteDC(HDCMemory);
    DeleteObject(HOldBitmap);
    DeleteObject(HBitmap);
}

bool GetStatsInRealtime::FindTemplateMatches()
{
    cv::Mat resultTemplate;

    cv::matchTemplate(interfaceFullFrame, templatesStatsLadoAd[templateMatchLocalizationArrayPos], resultTemplate, cv::TM_SQDIFF_NORMED);
    cv::minMaxLoc(resultTemplate, &minConfidence, NULL, &templateAdMatchLocalization, NULL);

    if (minConfidence < maxConfidence)
    {
        templateMatchLocalizationArrayPos = templateMatchLocalizationArrayPos;

        resultTemplate.release();

        return true;
    }
    else
    {
        resultTemplate.release();

        for (int i = 0; i < 6; i++)
        {
            cv::matchTemplate(interfaceFullFrame, templatesStatsLadoAd[i], resultTemplate, cv::TM_SQDIFF_NORMED);

            cv::minMaxLoc(resultTemplate, &minConfidence, NULL, &templateAdMatchLocalization, NULL);

            if (minConfidence < maxConfidence)
            {
                templateMatchLocalizationArrayPos = i;

                resultTemplate.release();

                return true;
            }

            resultTemplate.release();
        }
    }

    return false;
}

void GetStatsInRealtime::ExtractAttackSpeed()
{
    if (!interfaceStatAdFrame.empty())
        interfaceStatAdFrame.release();

    interfaceStatAdFrame = interfaceFullFrame(cv::Rect((templateAdMatchLocalization.x + ladoAdTemplateOffset[templateMatchLocalizationArrayPos][0]), (templateAdMatchLocalization.y - 5), ladoAdBoxSize[templateMatchLocalizationArrayPos][0], ladoAdBoxSize[templateMatchLocalizationArrayPos][1] + 5));

    cv::bitwise_not(interfaceStatAdFrame, interfaceStatAdFrame);
    interfaceStatAdFrame.convertTo(interfaceStatAdFrame, -1, 1, 30);

    ResizeAttackSpeedFrame();

    char* out = (char*)malloc(23);

    char adstats[5] = { 0 };

    tesseract::TessBaseAPI TesseractAPI;

    TesseractAPI.Init(NULL, "eng");

    TesseractAPI.SetVariable("user_defined_dpi", "70");

    TesseractAPI.SetPageSegMode(tesseract::PSM_SINGLE_LINE);

    TesseractAPI.SetImage((uchar*)interfaceStatAdFrame.data, interfaceStatAdFrame.size().width, interfaceStatAdFrame.size().height, interfaceStatAdFrame.channels(), interfaceStatAdFrame.step1());

    TesseractAPI.Recognize(0);

    out = TesseractAPI.GetUTF8Text();

    for (int i = 0, j = 0; i < 5; i++)
    {
        if (out[i] != '\0')
        {
            if (out[i] != '\n')
            {
                if (out[i] != ' ')
                {
                    adstats[j] = out[i];
                    j++;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    TesseractAPI.End();

    free(out);

    velocidadeDeAtaque = atof(adstats);

    if (velocidadeDeAtaque < 0)
        velocidadeDeAtaque = velocidadeDeAtaque * (-1);

    if (velocidadeDeAtaque >= 0.47 && velocidadeDeAtaque <= 6.00)
        ATSP_G = velocidadeDeAtaque;
}

void GetStatsInRealtime::ExtractLife()
{
    if (!interfaceLifeFrame.empty())
        interfaceLifeFrame.release();

    interfaceLifeFrame = interfaceFullFrame(cv::Rect(lifemanaBoxSize[templateMatchLocalizationArrayPos][0], lifemanaBoxSize[templateMatchLocalizationArrayPos][1] - 5, lifemanaBoxSize[templateMatchLocalizationArrayPos][2], lifemanaBoxSize[templateMatchLocalizationArrayPos][3] + 5));

    cv::bitwise_not(interfaceLifeFrame, interfaceLifeFrame);
    interfaceLifeFrame.convertTo(interfaceLifeFrame, -1, 1, 70);

    ResizeLifeFrame();

    char* out = (char*)malloc(23);

    char lifestats[4][7] = { 0 };

    bool guarda = false;

    tesseract::TessBaseAPI TesseractAPI;

    TesseractAPI.Init(NULL, "eng");

    TesseractAPI.SetVariable("user_defined_dpi", "70");

    TesseractAPI.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

    TesseractAPI.SetImage((uchar*)interfaceLifeFrame.data, interfaceLifeFrame.size().width, interfaceLifeFrame.size().height, interfaceLifeFrame.channels(), interfaceLifeFrame.step1());

    TesseractAPI.Recognize(0);

    out = TesseractAPI.GetUTF8Text();

    TesseractAPI.End();

    for (int i = 0, j = 0, k = 0; i < 22; i++)
    {
        if (out[i] != '\0')
        {
            if (out[i] != ' ')
            {
                if (out[i] == '\n' || out[i] == '/')
                {
                    k = 0;
                    j++;
                }
                else
                {
                    if (j >= 0 && j <= 3)
                    {
                        lifestats[j][k] = out[i];
                        k++;
                    }
                    else
                    {
                        guarda = false;
                        break;
                    }
                }
            }
        }
        else
        {
            guarda = true;
            break;
        }
    }

    free(out);

    if (guarda)
    {
        vidaAtual = atoi(lifestats[0]);
        /*
        if (vidaAtual > 0 && vidaAtual < 5000)
            vidaAtualG = vidaAtual;*/
    }
}

void GetStatsInRealtime::ResizeAttackSpeedFrame()
{
    avir::CImageResizer<> ImageResizer(8);

    cv::Mat InBuffer = interfaceStatAdFrame.clone();
    cv::Mat OutBuffer;

    int width = 0;
    int heigh = 0;
    int channels = 0;
    int type = 0;

    width = interfaceStatAdFrame.cols;
    heigh = interfaceStatAdFrame.rows;
    channels = interfaceStatAdFrame.channels();
    type = InBuffer.type();

    OutBuffer.create(heigh * 2, width * 2, type);

    ImageResizer.resizeImage(InBuffer.data, width, heigh, 0, OutBuffer.data, width * 2, heigh * 2, channels, 0);

    InBuffer.release();

    if (!interfaceStatAdFrame.empty())
        interfaceStatAdFrame.release();

    interfaceStatAdFrame = OutBuffer.clone();

    OutBuffer.release();
}

void GetStatsInRealtime::ResizeLifeFrame()
{
    avir::CImageResizer<> ImageResizer(8);

    cv::Mat InBuffer = interfaceLifeFrame.clone();
    cv::Mat OutBuffer;

    int width = 0;
    int heigh = 0;
    int channels = 0;
    int type = 0;

    width = interfaceLifeFrame.cols;
    heigh = interfaceLifeFrame.rows;
    channels = interfaceLifeFrame.channels();
    type = InBuffer.type();

    OutBuffer.create(heigh * 2, width * 2, type);

    ImageResizer.resizeImage(InBuffer.data, width, heigh, 0, OutBuffer.data, width * 2, heigh * 2, channels, 0);

    InBuffer.release();

    if (!interfaceLifeFrame.empty())
        interfaceLifeFrame.release();

    interfaceLifeFrame = OutBuffer.clone();

    OutBuffer.release();
}

GetStatsInRealtime::~GetStatsInRealtime()
{
    ;
}
