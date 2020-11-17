#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::SetBitMap(HDC hdc, LPCWSTR FileName)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_Image = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldImage = (HBITMAP)SelectObject(m_hMemDC, m_Image);
}

void BitMap::DrawBitMap(HDC hdc, POINT CharPt, POINT DrawPt)
{
	TransparentBlt(hdc, CharPt.x, CharPt.y, IMAGE_X, IMAGE_Y, m_hMemDC, DrawPt.x * IMAGE_X, DrawPt.y * IMAGE_Y, IMAGE_X, IMAGE_Y, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
	DeleteObject(m_Image);
	SelectObject(m_hMemDC, m_OldImage);
	DeleteDC(m_hMemDC);
}