#pragma once
#include"BitMap.h"

class BitMapManager
{
private:
	BitMap m_arrImage[IMAGE_MAX];
public:
	void Init(HWND hWnd);
	void DrawImage(HDC hdc, int Index, POINT pt);
	BitMapManager();
	~BitMapManager();
};

