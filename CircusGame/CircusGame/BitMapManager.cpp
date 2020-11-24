#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
}

void BitMapManager::Init(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	WCHAR buf[256];
	for (int i = 0; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, L"Circus/%d.bmp", i);
		m_arrImage[i].Init(hdc, buf);
	}
	ReleaseDC(hWnd, hdc);
}

void BitMapManager::DrawImage(HDC hdc, int Index, POINT pt, SIZE Size)
{
	m_arrImage[Index].Draw(hdc, pt, Size);
}

BitMapManager::~BitMapManager()
{
}
