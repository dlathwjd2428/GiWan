#include "Res_MG.h"

Res_MG* Res_MG::m_hThis = NULL;
Res_MG::Res_MG()
{
}

void Res_MG::Init(HDC hdc)
{
	WCHAR buf[256];
	for (int i = IMAGE_START; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, L"Circus/%d.bmp", i);
		m_arrImage[i].Init(hdc, buf);
	}
}

void Res_MG::Draw(HDC hdc, int Index, POINT pt, SIZE Size)
{
	m_arrImage[Index].Draw(hdc, pt, Size);
}

Res_MG::~Res_MG()
{
}