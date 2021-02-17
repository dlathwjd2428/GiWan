#pragma once
#include"Res_MG.h"

class Character
{
private:
	int m_iCharState;
	int m_iMotionCount;
	int m_iJumpPower;
	MyIMG m_Char;
	POINT m_Save;
public:
	void SetChar();
	void DrawChar(HDC hdc);
	void Jump();
	inline void SetState(int State) { m_iCharState = State; }
	inline int GetState() { return m_iCharState; }
	inline RECT GetRect() { return m_Char.m_Rect1; }
	Character();
	~Character();
};

