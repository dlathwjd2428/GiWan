#pragma once
#include"BitManager.h"

class Character
{
private:
	MyIMG m_Char;
	POINT m_SavePt;
	int m_iSpeed;
	int m_iJumpPower;
	bool m_bJumpState;
public:
	void SetCharacter();
	void Draw(HDC hdc);
	void Move();
	void Jump();
	inline void SetJumpState(bool State) { m_bJumpState = State; }
	inline bool GetJumpState() { return m_bJumpState; }
	Character();
	~Character();
};