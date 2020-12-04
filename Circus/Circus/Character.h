#pragma once
#include"BitManager.h"

class Character
{
private:
	MyIMG m_Char;
public:
	void SetChar();
	void Draw(HDC hdc);
	Character();
	~Character();
};

