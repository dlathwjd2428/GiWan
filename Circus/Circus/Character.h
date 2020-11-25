#pragma once
#include"BitMapManager.h"

class Character
{
private:
	MyIMG m_Char;
public:
	void SetChar(HDC hdc);
	void Draw(HDC hdc);
	void CharMove(int Direction);
	Character();
	~Character();
};

