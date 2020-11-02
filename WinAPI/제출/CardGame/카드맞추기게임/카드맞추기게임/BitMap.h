#pragma once
#include<Windows.h>
#include<string>

class BitMap
{
private:
	HDC m_MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	SIZE m_Size;
public:
	void Init(HDC hdc, HINSTANCE hInst, char* FileName);
	void Draw(HDC hdc, int x = 0, int y = 0);
	inline SIZE GetSize() { return m_Size; }
	BitMap();
	~BitMap();
};