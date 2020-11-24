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
	void Init(HDC hdc, LPCWSTR FileName, int Option = NORMAL);
	void Draw(HDC hdc, POINT pt, SIZE Size);
	inline HDC GetMemDC() { return m_hMemDC; }
	BitMap();
	~BitMap();
};

