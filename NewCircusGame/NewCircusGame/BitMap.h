#pragma once
#include"DefineMecro.h"

class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_BitMap, m_OldBitMap;
	SIZE m_Size;
public:
	void Init(HDC hdc, LPCWSTR FileName);
	void Draw(HDC hdc, POINT pt, SIZE Size);
	BitMap();
	~BitMap();
};

