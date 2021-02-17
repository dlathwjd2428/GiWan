#include "Font_Back_MG.h"

Font_Back_MG* Font_Back_MG::m_hThis = NULL;
Font_Back_MG::Font_Back_MG()
{
}

void Font_Back_MG::FontBackSet(HDC hdc, int R, int G, int B)
{
	SetBkColor(hdc, RGB(R, G, B));
}

void Font_Back_MG::FontSizeSet(HDC hdc, int Size)
{
	m_hFont = CreateFont(Size, 10, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"tmp");
	m_hOldFont = (HFONT)SelectObject(hdc, m_hFont);
}

void Font_Back_MG::FontColorSet(HDC hdc, int R, int G, int B)
{
	SetTextColor(hdc, RGB(R, G, B));
}

void Font_Back_MG::Reset(HDC hdc)
{
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, m_hOldFont);
	DeleteObject(m_hFont);
}

Font_Back_MG::~Font_Back_MG()
{
}