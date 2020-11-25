#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;
BitMapManager::BitMapManager()
{
}

void BitMapManager::Init(HDC hdc)
{
	WCHAR buf[256];
	for (int i = IMAGE_START; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, L"Circus/%d.bmp", i);
		m_arrBitMap[i].Init(hdc, buf);
	}
}

void BitMapManager::Draw(HDC hdc, int Index, POINT pt, SIZE Size)
{
	m_arrBitMap[Index].Draw(hdc, pt, Size);
}

BitMapManager::~BitMapManager()
{
}
