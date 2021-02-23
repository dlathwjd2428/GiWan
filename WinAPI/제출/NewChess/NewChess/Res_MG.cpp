#include "Res_MG.h"

Res_MG* Res_MG::m_hThis = NULL;
Res_MG::Res_MG()
{
}

void Res_MG::Init(HDC hdc)
{
	char buf[256];
	for (int i = IMAGE_START; i < IMAGE_MAX; i++)
	{
		wsprintf(buf, "Chess/%d.bmp", i);
		m_arrRES[i].Init(hdc, buf);
	}
}

void Res_MG::Draw(HDC hdc, int Index, POINT pt)
{
	m_arrRES[Index].Draw(hdc, pt);
}

Res_MG::~Res_MG()
{
}