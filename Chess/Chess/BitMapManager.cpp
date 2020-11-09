#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;
BitMapManager::BitMapManager()
{
}

void BitMapManager::SetBitMapArr(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	TCHAR buf[256];
	for (int i = IMAGE_START; i < IMAGE_MAX; i++)
	{
		if (i < IMAGE_BLACK_PAWN)
			wsprintf(buf, L"chess/block0%d.bmp", i);
		else if(i >= IMAGE_BLACK_PAWN && i < IMAGE_WHITE_PAWN)
			wsprintf(buf, L"chess/block_b_0%d.bmp", i - IMAGE_BLACK_PAWN);
		else
			wsprintf(buf, L"chess/block_w_0%d.bmp", i - IMAGE_WHITE_PAWN);
		m_arrBitMap[i].SetBitMap(hdc, buf);
	}
	ReleaseDC(hWnd, hdc);
}

void BitMapManager::DrawBitMap(HDC hdc, int Index, RECT rect, int Option)
{
	m_arrBitMap[Index].DrawBitMap(hdc, rect, Option);
}

BitMapManager::~BitMapManager()
{
}