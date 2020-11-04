#pragma once
#include<windows.h>

class BitMap
{
private:
	HBITMAP m_Image;
	HBITMAP m_OldImage;
	HDC m_hMemDC;
	int m_iSizeX, m_iSizeY;
public:
	void SetBitMap(HDC hdc, HINSTANCE hInst, char* FileName);
	void ShowBitMap(HDC hdc, int x, int y);
	BitMap();
	~BitMap();
};

