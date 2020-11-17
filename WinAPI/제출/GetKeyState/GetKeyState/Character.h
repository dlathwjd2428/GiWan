#pragma once
#include"BitMap.h"
#define LEFT 2
#define RIGHT 3
#define UP 1
#define DOWN 0
#define JUMP 4
class Character
{
private:
	int m_iDirection;
	bool m_bMoveState;
	bool m_bJumpState;
	BitMap m_Image;
	POINT m_CharPt;
	POINT m_ImagePt;
public:
	void SetDefaultChar(HWND hWnd);
	void Draw(HDC hdc);
	void Move(int Direction);
	void Jump(int Count);
	inline bool GetMoveState() { return m_bMoveState; }
	inline void SetMoveState(bool State) { m_bMoveState = State; }
	inline bool GetJumpState() { return m_bJumpState; }
	RECT GetRect();
	Character();
	~Character();
};

