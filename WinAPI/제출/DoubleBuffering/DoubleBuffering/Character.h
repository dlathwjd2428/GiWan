#pragma once
#include"BitMap.h"
#define LEFT 2
#define RIGHT 3
#define UP 1
#define DOWN 0
#define NONE -1
#define GRAVITY 10
class Character
{
private:
	int m_iDirection;
	bool m_bJumpState;
	int m_iJumpY;
	BitMap m_Image;
	POINT m_SavePt;
	POINT m_CharPt;
	POINT m_IMG_Pt;
public:
	void SetDefault(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	bool Jump();
	inline bool GetJumpState() { return m_bJumpState; }
	inline void SetJumpState(bool State) { m_bJumpState = State; }
	Character();
	~Character(); 
};

