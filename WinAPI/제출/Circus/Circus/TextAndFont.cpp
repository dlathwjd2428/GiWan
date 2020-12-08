#include "TextAndFont.h"

TextAndFont* TextAndFont::m_Font = NULL;
TextAndFont::TextAndFont()
{
}

void TextAndFont::Reset(HDC hdc)
{
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, m_OldFont);
	DeleteObject(m_MyFont);
	SelectObject(hdc, m_OldBrush);
	DeleteObject(m_Brush);
}

void TextAndFont::FontSize(HDC hdc, int Size)
{
	m_MyFont = CreateFont(Size, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"tmp");
	m_OldFont = (HFONT)SelectObject(hdc, m_MyFont);
}

void TextAndFont::ColorSet(HDC hdc, int Option, int R, int G, int B)
{
	if (Option == TEXT_COLOR)
		SetTextColor(hdc, RGB(R, G, B));
	else if(Option == BACK_COLOR)
		SetBkColor(hdc, RGB(R, G, B));
	else
	{
		m_Brush = (HBRUSH)CreateSolidBrush(RGB(R, G, B));
		m_OldBrush = (HBRUSH)SelectObject(hdc, m_Brush);
	}
}

TextAndFont::~TextAndFont()
{
}