#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::SetBitMap(HDC hdc, LPWSTR FileName)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	m_Image = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldImage = (HBITMAP)SelectObject(m_hMemDC, m_Image);
}

void BitMap::DrawBitMap(HDC hdc, RECT rect, int Option)
{
	TransparentBlt(hdc, rect.left, rect.top, IMAGE_SIZE, IMAGE_SIZE, m_hMemDC, 0, 0, IMAGE_SIZE, IMAGE_SIZE, RGB(255, Option, 255));
}

BitMap::~BitMap()
{
}