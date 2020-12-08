#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, LPCWSTR FileName, int Option, int x, int y)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	if (Option == BACK)
		m_Image = CreateCompatibleBitmap(hdc, x, y);
	else
		m_Image = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldImage = (HBITMAP)SelectObject(m_hMemDC, m_Image);

	BITMAP BitMap;
	GetObject(m_Image, sizeof(BitMap), &BitMap);
	m_Size.cx = BitMap.bmWidth;
	m_Size.cy = BitMap.bmHeight;
}

void BitMap::Draw(HDC hdc, POINT pt, SIZE Size)
{
	TransparentBlt(hdc, pt.x, pt.y, Size.cx, Size.cy, m_hMemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
	DeleteObject(m_Image);
	SelectObject(m_hMemDC, m_OldImage);
	DeleteDC(m_hMemDC);
}
