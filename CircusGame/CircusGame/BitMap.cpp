#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, LPCWSTR FileName)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_Image = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldImage = (HBITMAP)SelectObject(m_hMemDC, m_Image);

	BITMAP BitMap;
	GetObject(m_Image, sizeof(BitMap), &BitMap);
	m_ImageSize.cx = BitMap.bmWidth;
	m_ImageSize.cy = BitMap.bmHeight;
}

void BitMap::Draw(HDC hdc, POINT pt)
{
	StretchBlt(hdc, pt.x, pt.y, m_ImageSize.cx * 16, m_ImageSize.cy * 3, m_hMemDC, 0, 0, m_ImageSize.cx, m_ImageSize.cy, SRCCOPY);
	//TransparentBlt(hdc, pt.x, pt.y, m_ImageSize.cx, m_ImageSize.cy, m_hMemDC, 0, 0, m_ImageSize.cx, m_ImageSize.cy, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
}
