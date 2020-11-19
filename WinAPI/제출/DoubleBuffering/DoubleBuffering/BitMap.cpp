#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::SetImage(HDC hdc, LPCWSTR FileName, int Option)
{
	m_hMemDC = CreateCompatibleDC(hdc);
	if (Option == BACK)
		m_Image = CreateCompatibleBitmap(hdc, 1024, 768);
	else
		m_Image = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldImage = (HBITMAP)SelectObject(m_hMemDC, m_Image);
}

void BitMap::Draw(HDC hdc, POINT CharPt, POINT ImagePt)
{
	TransparentBlt(hdc, CharPt.x, CharPt.y, IMAGE_X, IMAGE_Y, m_hMemDC, ImagePt.x * IMAGE_X, ImagePt.y * IMAGE_Y, IMAGE_X, IMAGE_Y, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
}