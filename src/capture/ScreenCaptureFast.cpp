#include "ScreenCaptureFast.h"

extern unsigned int screenWidth;
extern unsigned int screenHeight;

ScreenCaptureFast::ScreenCaptureFast()
{
    if (!InitScreenCaptureFastDirectX())
    {
        std::cout << "[!!!] Erro ao iniciar directX..." << std::endl;
        exit(5);
    }

    divisorColunas = 8;
    divisorLinhas  = 8;

    blockWidth  = screenWidth / divisorColunas;
    blockHeigth = screenHeight / divisorLinhas;
}

bool ScreenCaptureFast::InitScreenCaptureFastDirectX()
{
    D3D_FEATURE_LEVEL gFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0,
                                           D3D_FEATURE_LEVEL_10_1,
                                           D3D_FEATURE_LEVEL_10_0,
                                           D3D_FEATURE_LEVEL_9_1 };

    UINT gNumFeatureLevels = ARRAYSIZE(gFeatureLevels);
    D3D_FEATURE_LEVEL lFeatureLevel;

    HRESULT resultHandle(E_FAIL);

    resultHandle = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_SINGLETHREADED, gFeatureLevels,
        gNumFeatureLevels, D3D11_SDK_VERSION, &deviceD3D11, &lFeatureLevel,
        &immediateContextD3D11);

    if (FAILED(resultHandle))
        return false;

    if (!deviceD3D11)
        return false;

    IDXGIDevice* lDxgiDevice;
    resultHandle = deviceD3D11->QueryInterface(__uuidof(IDXGIDevice),
        reinterpret_cast<void**>(&lDxgiDevice));
    if (FAILED(resultHandle))
        return false;

    IDXGIAdapter* lDxgiAdapter;
    resultHandle = lDxgiDevice->GetParent(__uuidof(IDXGIAdapter),
        reinterpret_cast<void**>(&lDxgiAdapter));
    lDxgiDevice->Release();
    lDxgiDevice = nullptr;

    if (FAILED(resultHandle))
        return false;

    UINT Output = 0;

    IDXGIOutput* lDxgiOutput;
    resultHandle = lDxgiAdapter->EnumOutputs(Output, &lDxgiOutput);

    if (FAILED(resultHandle))
        return false;

    lDxgiAdapter->Release();
    lDxgiAdapter = nullptr;

    resultHandle = lDxgiOutput->GetDesc(&outputDescD3D11);

    if (FAILED(resultHandle))
        return false;

    IDXGIOutput1* lDxgiOutput1;
    resultHandle = lDxgiOutput->QueryInterface(__uuidof(lDxgiOutput1),
        reinterpret_cast<void**>(&lDxgiOutput1));
    lDxgiOutput->Release();
    lDxgiOutput = nullptr;
    if (FAILED(resultHandle))
        return false;

    resultHandle = lDxgiOutput1->DuplicateOutput(deviceD3D11, &desktopDuplicationD3D11);

    if (FAILED(resultHandle))
        return false;

    lDxgiOutput1->Release();
    lDxgiOutput1 = nullptr;

    desktopDuplicationD3D11->GetDesc(&outputDuplDescD3D11);

    D3D11_TEXTURE2D_DESC desc;
    desc.Width = outputDuplDescD3D11.ModeDesc.Width;
    desc.Height = outputDuplDescD3D11.ModeDesc.Height;
    desc.Format = outputDuplDescD3D11.ModeDesc.Format;
    desc.ArraySize = 1;
    desc.BindFlags = 0;
    desc.MiscFlags = 0;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.MipLevels = 1;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
    desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;

    resultHandle = deviceD3D11->CreateTexture2D(&desc, NULL, &currentTextureD3D11);
    if (!currentTextureD3D11) {
        resultHandle = desktopDuplicationD3D11->ReleaseFrame();
        return false;
    }

    return true;
}

bool ScreenCaptureFast::GetScreenShot()
{
    HRESULT resultHandle(E_FAIL);

    IDXGIResource* lDesktopResource = nullptr;
    DXGI_OUTDUPL_FRAME_INFO lFrameInfo;

    resultHandle = desktopDuplicationD3D11->AcquireNextFrame(999, &lFrameInfo, &lDesktopResource);

    if (FAILED(resultHandle))
        return false;

    if (lFrameInfo.LastPresentTime.HighPart == 0) // not interested in just mouse updates, which can happen much faster than 60fps if you really shake the mouse
    {
        resultHandle = desktopDuplicationD3D11->ReleaseFrame();
        return false;
    }

    // QI for ID3D11Texture2D
    resultHandle = lDesktopResource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&acquiredDesktopImageD3D11));
    lDesktopResource->Release();
    lDesktopResource = nullptr;
    if (FAILED(resultHandle))
    {
        resultHandle = desktopDuplicationD3D11->ReleaseFrame();
        return false;
    }

    immediateContextD3D11->CopyResource(currentTextureD3D11, acquiredDesktopImageD3D11);
    UINT subresource = D3D11CalcSubresource(0, 0, 0);
    immediateContextD3D11->Map(currentTextureD3D11, subresource, D3D11_MAP_READ, 0, &resourceD3D11);
    immediateContextD3D11->Unmap(currentTextureD3D11, 0);
    resultHandle = desktopDuplicationD3D11->ReleaseFrame();

    if (!matScreenShot.empty())
        matScreenShot.release();

    matScreenShot = cv::Mat(screenHeight, screenWidth, CV_8UC4, resourceD3D11.pData);

    return true;
}

void ScreenCaptureFast::GetCurrentFrame(cv::Mat& outputFrame)
{
    if (!outputFrame.empty())
        outputFrame.release();

    while (!GetScreenShot())
        ;

    outputFrame = matScreenShot.clone();
}

bool ScreenCaptureFast::ResizeFrame(ChampPosOffset& posOffset, cv::Mat& inputFrame, cv::Mat& outputFrame)
{
    posOffset.offsetX = 0;
    posOffset.offsetY = 0;

    std::vector<cv::Mat> Blocos_Imagem;

    cv::Mat Imagem_Array[8][8];

    int LINESUM = 324;

    int  x[8][8] = { 0 };

    int START_LINHAS = (-1);
    int STOP_LINHAS = (-1);

    int START_COLUNAS = (-1);
    int STOP_COLUNAS = (-1);

    int ELEMENTOS_LINHAS = 0;
    int ELEMENTOS_COLUNAS = 0;

    for (int y = 0; y < inputFrame.cols; y += inputFrame.cols / divisorColunas)
    {
        for (int x = 0; x < inputFrame.rows; x += inputFrame.rows / divisorLinhas)
            Blocos_Imagem.push_back(inputFrame(cv::Rect(y, x, (inputFrame.cols / divisorColunas), (inputFrame.rows / divisorLinhas))).clone());
    }

    for (int i = 0, countUm = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j == 0 && i == 0 || j == 7 && i == 2 || j == 7 && i == 3 || j == 7 && i == 7)
                Imagem_Array[j][i] = cv::Mat::zeros(blockHeigth, blockWidth, 0);
            else
                Imagem_Array[j][i] = Blocos_Imagem[countUm];

            countUm++;
        }
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            x[i][j] = cv::countNonZero(Imagem_Array[i][j]);

    for (int i = 0, soma_l = 0, soma_c = 0, y = 0, z = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            soma_l = soma_l + x[i][j];
            soma_c = soma_c + x[j][i];
        }

        if (soma_l > LINESUM && y == 0)
        {
            START_LINHAS = i;
            y++;
        }

        if (soma_c > LINESUM && z == 0)
        {
            START_COLUNAS = i;
            z++;
        }

        if (soma_l > LINESUM)
            STOP_LINHAS = i;

        if (soma_c > LINESUM)
            STOP_COLUNAS = i;

        soma_l = 0;
        soma_c = 0;
    }

    if (START_LINHAS < 0 || STOP_LINHAS < 0 || START_COLUNAS < 0 || STOP_COLUNAS < 0)
        return false;

    if (START_LINHAS > 1)
        START_LINHAS--;

    if (STOP_LINHAS < 7)
        STOP_LINHAS += 2;
    else
        if (STOP_LINHAS < 8)
            STOP_LINHAS++;

    ELEMENTOS_LINHAS = ((STOP_LINHAS - START_LINHAS));

    if (START_COLUNAS > 1)
        START_COLUNAS--;

    if (STOP_COLUNAS < 7)
        STOP_COLUNAS += 2;
    else
        if (STOP_COLUNAS < 8)
            STOP_COLUNAS++;

    ELEMENTOS_COLUNAS = ((STOP_COLUNAS - START_COLUNAS));

    if (!outputFrame.empty())
        outputFrame.release();

    outputFrame = inputFrame(cv::Rect(START_COLUNAS * blockWidth, START_LINHAS * blockHeigth, ELEMENTOS_COLUNAS * blockWidth, ELEMENTOS_LINHAS * blockHeigth)).clone();

    if (START_COLUNAS == 0)
        posOffset.offsetX = 0;
    else
        posOffset.offsetX = ((START_COLUNAS)*blockWidth);

    if (START_LINHAS == 0)
        posOffset.offsetY = 0;
    else
        posOffset.offsetY = ((START_LINHAS)*blockHeigth);

    Blocos_Imagem.clear();

    return true;
}

ScreenCaptureFast::~ScreenCaptureFast()
{
    ;
}

ScreenCaptureSlow::ScreenCaptureSlow()
{
    ;
}

void ScreenCaptureSlow::GetCurrentFrameSlow(cv::Mat& outputFrame)
{
    HDC HDCScreen;
    HDC HDCMemory;
    HBITMAP HBitmap;
    HBITMAP HOldBitmap;
    BITMAPINFOHEADER bi;

    HDCScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);

    HDCMemory = CreateCompatibleDC(HDCScreen);

    HBitmap = CreateCompatibleBitmap(HDCScreen, screenWidth, screenHeight);

    HOldBitmap = (HBITMAP)SelectObject(HDCMemory, HBitmap);

    BitBlt(HDCMemory, 0, 0, screenWidth, screenHeight, HDCScreen, 0, 0, SRCCOPY);

    HBitmap = (HBITMAP)SelectObject(HDCMemory, HOldBitmap);

    if (!outputFrame.empty())
        outputFrame.release();

    if (!matScreenShot.empty())
        matScreenShot.release();

    matScreenShot.create(screenHeight, screenWidth, CV_8UC4);

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = -(int)screenHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 32; //Intensidade
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    GetDIBits(HDCScreen, HBitmap, 0, screenHeight, matScreenShot.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    outputFrame = matScreenShot.clone();

    DeleteDC(HDCScreen);
    DeleteDC(HDCMemory);
    DeleteObject(HOldBitmap);
    DeleteObject(HBitmap);
}

ScreenCaptureSlow::~ScreenCaptureSlow()
{
    ;
}
