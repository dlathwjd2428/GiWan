#include "BitMapManager.h"

BitMapManager::BitMapManager()
{
}

void BitMapManager::Init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	WCHAR buf[256];
	for (int i = 0; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, L"Circus/0.bmp", i);
		m_arrImage[i].Init(hdc, buf);
	}
	ReleaseDC(hWnd, hdc);
}

void BitMapManager::DrawImage(HDC hdc, int Index, POINT pt)
{
	m_arrImage[Index].Draw(hdc, pt);
}

BitMapManager::~BitMapManager()
{
}
