#include "GetScreenSize.h"

extern unsigned int screenWidth;
extern unsigned int screenHeight;

#include <Windows.h>

GetScreenSize::GetScreenSize()
{
	GetScreenX();
	GetScreenY();
}

GetScreenSize::~GetScreenSize()
{
	;
}

int GetScreenSize::GetScreenResolutionID()
{
	if (screenWidth == 1920 && screenHeight == 1080)
		return 1920;

	if (screenWidth == 1366 && screenHeight == 768)
		return 1366;

	return -1;
}

inline void GetScreenSize::GetScreenX()
{
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

inline void GetScreenSize::GetScreenY()
{
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
}
