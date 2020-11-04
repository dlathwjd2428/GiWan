#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::SetBitMap(HDC hdc, HINSTANCE hInst, char* FileName)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_Image = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldImage = (HBITMAP)SelectObject(m_hMemDC, m_Image);

	BITMAP BitMap;
	GetObject(m_Image, sizeof(BitMap), &BitMap);
	m_iSizeX = BitMap.bmWidth;
	m_iSizeY = BitMap.bmHeight;
}

void BitMap::ShowBitMap(HDC hdc, int x, int y)
{
	TransparentBlt(hdc, x, y, m_iSizeX, m_iSizeY, m_hMemDC, 0, 0, m_iSizeX, m_iSizeY, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
}
