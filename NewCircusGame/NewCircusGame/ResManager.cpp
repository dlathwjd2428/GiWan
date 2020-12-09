#include "ResManager.h"

ResManager* ResManager::m_hThis = NULL;
ResManager::ResManager()
{
}

void ResManager::InitBitMap(HDC hdc)
{
	WCHAR buf[256];
	for (int i = IMAGE_START; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, L"Circus/%d.bmp", i);
		m_arrBit[i].Init(hdc, buf);
	}
}

void ResManager::DrawBitMap(HDC hdc, int Index, POINT pt, SIZE Size)
{
	m_arrBit[Index].Draw(hdc, pt, Size);
}

ResManager::~ResManager()
{
}
