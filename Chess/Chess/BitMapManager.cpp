#include "BitMapManager.h"

BitMapManager* BitMapManager::m_BitManager = NULL;
BitMapManager::BitMapManager()
{
}

void BitMapManager::SetBitMaps(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc;
	hdc = GetDC(hWnd);
	char buf[256];
	for (int i = 0; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, "Chess//block0%d.bmp", i);
		if(i > 2)
			wsprintf(buf, "Chess//block_w_0%d.bmp", i - 3);
		if (i > 8)
			wsprintf(buf, "Chess//block_b_0%d.bmp", i - 9);
		m_Images[i].SetBitMap(hdc, hInst, buf);
	}
}

void BitMapManager::ShowBitMaps(HDC hdc)
{
	int x = 0, y = 0;
	for (int i = 0; i < IMAGE_MAX; i++)
	{
		m_Images[i].ShowBitMap(hdc, x, y);
		x += 50;
		if (i % 5 == 0)
			y += 50;
	}
}
BitMapManager::~BitMapManager()
{
}
