#pragma once
#include<windows.h>
#include"DefineMecro.h"
class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_Image;
	HBITMAP m_OldImage;
	SIZE m_ImageSize;
public:
	void Init(HDC hdc, LPCWSTR FileName);
	void Draw(HDC hdc, POINT pt);
	BitMap();
	~BitMap();
};

