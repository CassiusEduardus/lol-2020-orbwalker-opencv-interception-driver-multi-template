#pragma once

class GetScreenSize
{
public:
	GetScreenSize();
	~GetScreenSize();

	int GetScreenResolutionID();

private:
	inline void GetScreenX();
	inline void GetScreenY();
};
