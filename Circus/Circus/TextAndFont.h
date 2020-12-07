#pragma once
#include"DefineMecro.h"

class TextAndFont
{
private:
	static TextAndFont* m_Font;
	HFONT m_MyFont, m_OldFont;
	HBRUSH m_Brush, m_OldBrush;
public:
	static TextAndFont* GetInstance()
	{
		if (m_Font == NULL)
			m_Font = new TextAndFont;
		return m_Font;
	}
	void Reset(HDC hdc);
	void FontSize(HDC hdc, int Size);
	void ColorSet(HDC hdc, int Option, int R, int G, int B);
	TextAndFont();
	~TextAndFont();
};

