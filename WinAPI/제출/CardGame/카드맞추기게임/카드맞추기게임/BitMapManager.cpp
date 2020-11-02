#include "BitMapManager.h"

BitMapManager* BitMapManager::m_sBitMapManager = NULL;
BitMapManager::BitMapManager()
{
}

void BitMapManager::Set_BitMap(HWND hWnd, HINSTANCE hInst)
{
	BitMap tmpImage;
	HDC hdc = GetDC(hWnd);
	char buf[256];
	for (int i = IMAGE_START; i < IMAGE_END; i++)
	{
		sprintf(buf, "RES/0%d.bmp", i);
		if (i == IMAGE_BACKGROUND)
			sprintf(buf, "RES/bb.bmp");
		tmpImage.Init(hdc, hInst, buf);
		m_Image.push_back(tmpImage);
	}
	ReleaseDC(hWnd, hdc);
}

void BitMapManager::DrawBackGround(HDC hdc)
{
	m_Image[IMAGE_BACKGROUND].Draw(hdc);
}

BitMap* BitMapManager::Get_Image(int Index) { return &m_Image[Index]; }
BitMapManager::~BitMapManager()
{
}