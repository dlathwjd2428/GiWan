#pragma once
#include<windows.h>

class Font_Back_MG
{
private:
	static Font_Back_MG* m_hThis;
	HFONT m_hFont, m_hOldFont;
public:
	static Font_Back_MG* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new Font_Back_MG;
		return m_hThis;
	}
	void FontBackSet(HDC hdc, int R, int G, int B);
	void FontSizeSet(HDC hdc, int Size);
	void FontColorSet(HDC hdc, int R, int G, int B);
	void Reset(HDC hdc);
	Font_Back_MG();
	~Font_Back_MG();
};
