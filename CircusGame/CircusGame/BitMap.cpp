#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, LPCWSTR FileName, int Option)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	if (Option == BACK)
		m_Image = CreateCompatibleBitmap(hdc, 1024, 768);
	else
		m_Image = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldImage = (HBITMAP)SelectObject(m_hMemDC, m_Image);

	BITMAP BitMap;
	GetObject(m_Image, sizeof(BitMap), &BitMap);
	m_ImageSize.cx = BitMap.bmWidth;
	m_ImageSize.cy = BitMap.bmHeight;
}

void BitMap::Draw(HDC hdc, POINT pt, SIZE Size)
{
	TransparentBlt(hdc, pt.x, pt.y, Size.cx, Size.cy, m_hMemDC, 0, 0, m_ImageSize.cx, m_ImageSize.cy, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
}
