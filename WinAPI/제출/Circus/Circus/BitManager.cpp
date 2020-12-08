#include "BitManager.h"

BitManager* BitManager::m_hThis = NULL;
BitManager::BitManager()
{
}

void BitManager::Init(HDC hdc)
{
	WCHAR buf[256];
	for (int i = IMAGE_START; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, L"Circus/%d.bmp", i);
		m_arrBit[i].Init(hdc, buf);
	}
}

void BitManager::Draw(HDC hdc, int Index, POINT pt, SIZE Size)
{
	m_arrBit[Index].Draw(hdc, pt, Size);
}

BitManager::~BitManager()
{
}
