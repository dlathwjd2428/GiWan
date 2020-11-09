#pragma once
#include<windows.h>
#include"defineMecro.h"

class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_Image, m_OldImage;
public:
	void SetBitMap(HDC hdc, LPWSTR FileName);
	void DrawBitMap(HDC hdc, RECT rect, int Option = NORMAL);
	BitMap();
	~BitMap();
};

