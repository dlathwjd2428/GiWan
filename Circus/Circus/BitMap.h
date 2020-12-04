#pragma once
#include"DefineMecro.h"

class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_Image, m_OldImage;
	SIZE m_Size;
public:
	void Init(HDC hdc, LPCWSTR FileName, int Option = NORMAL, int x = WIN_SIZE, int y = WIN_SIZE);
	void Draw(HDC hdc, POINT pt, SIZE Size);
	inline HDC GetDC() { return m_hMemDC; }
	BitMap();
	~BitMap();
};

