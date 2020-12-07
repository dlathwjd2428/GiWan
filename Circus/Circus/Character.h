#pragma once
#include"BitManager.h"
class Character
{
private:
	bool m_bMoveState;
	bool m_bJumpState;
	MyIMG m_Char;
	POINT m_Save;
	int m_iAngle;
	int m_iJumpPower;
public:
	void SetChar();
	void Draw(HDC hdc);
	void MoveChar(int Direction);
	bool Jump();
	inline bool GetMoveState() { return m_bMoveState; }
	inline bool GetJumpState() { return m_bJumpState; }
	Character();
	~Character();
};

