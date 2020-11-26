#pragma once
#include"BitMapManager.h"

class Character
{
private:
	bool m_bJumpState;
	int m_iJumpPower;
	int m_iDirection;
	int m_iMoveCount;
	POINT m_SavePt;
	MyIMG m_Char;
public:
	void SetChar();
	void Draw(HDC hdc);
	void CharMove(int Direction);
	bool CharJump();
	inline bool GetJumpState() { return m_bJumpState; }
	Character();
	~Character();
};

