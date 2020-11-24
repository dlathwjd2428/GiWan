#pragma once
#include"BitMapManager.h"

class Character
{
private:
	int m_ImgIndex;
	POINT m_CharPt;
	SIZE m_Size;
public:
	void SetChar();
	void Draw(HDC hdc);
	void Move(int Direction);
	Character();
	~Character();
};

