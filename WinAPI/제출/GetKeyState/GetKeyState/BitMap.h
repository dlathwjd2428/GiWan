#pragma once
#include<windows.h>
#define IMAGE_X 60
#define IMAGE_Y 100

class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_Image, m_OldImage;
public:
	void SetBitMap(HDC hdc, LPCWSTR FileName);
	void DrawBitMap(HDC hdc, POINT CharPt, POINT DrawPt);
	BitMap();
	~BitMap();
};

