#pragma once
#include<windows.h>
#define BACK 0
#define FRONT 1
#define IMAGE_X 60
#define IMAGE_Y 100

class BitMap
{
private:
	HDC m_hMemDC;
	HBITMAP m_Image, m_OldImage;
public:
	void SetImage(HDC hdc, LPCWSTR FileName, int Option);
	void Draw(HDC hdc, POINT CharPt, POINT ImagePt);
	inline HDC GetMemDC() { return m_hMemDC; }
	BitMap();
	~BitMap();
};

