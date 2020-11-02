#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, HINSTANCE hInst, char* FileName)
{
	m_MemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitMap = (HBITMAP)SelectObject(m_MemDC, m_BitMap);
	BITMAP BitMap_Info;
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
}

void BitMap::Draw(HDC hdc, int x, int y)
{
	SIZE tmpSize;
	if (x == 0 && y == 0)
	{
		tmpSize.cx = m_Size.cx;
		tmpSize.cy = m_Size.cy * 1.5f;
	}
	else
	{
		tmpSize.cx = m_Size.cx * 0.5f;
		tmpSize.cy = m_Size.cy * 0.5f;
	}
	StretchBlt(hdc, x, y, tmpSize.cx, tmpSize.cy, m_MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
}

BitMap::~BitMap()
{
	//SelectObject(m_MemDC, m_OldBitMap);
	//DeleteObject(m_BitMap);
	//DeleteDC(m_MemDC);
}