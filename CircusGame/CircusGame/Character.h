#pragma once
#include"BitManager.h"

class Character
{
private:
	MyIMG m_Char;
	int m_iSpeed;
public:
	void SetCharacter();
	void Draw(HDC hdc);
	void Move();
	Character();
	~Character();
};