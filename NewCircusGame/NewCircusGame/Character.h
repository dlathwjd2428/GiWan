#pragma once
#include"ResManager.h"

class Character
{
private:
	int m_iCount;
	bool m_bMoveState;
	MyIMG m_Char;
public:
	void SetChar();
	void Draw(HDC hdc);
	void Move(int Direction);
	Character();
	~Character();
};

