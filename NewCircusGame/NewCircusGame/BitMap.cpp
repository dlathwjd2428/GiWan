#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, LPCWSTR FileName)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_BitMap);

	BITMAP BitMap;
	GetObject(m_BitMap, sizeof(BitMap), &BitMap);
	m_Size.cx = BitMap.bmWidth;
	m_Size.cy = BitMap.bmHeight;
}

void BitMap::Draw(HDC hdc, POINT pt, SIZE Size)
{
	TransparentBlt(hdc, pt.x, pt.y, Size.cx, Size.cy, m_hMemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	SelectObject(m_hMemDC, m_OldBitMap);
	DeleteDC(m_hMemDC);
}
