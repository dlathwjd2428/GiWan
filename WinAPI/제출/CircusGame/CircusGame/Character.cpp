#include "Character.h"

Character::Character()
{
}

void Character::SetChar()
{
	m_Char.m_iIndex = IMAGE_PLAYER1;
	m_Char.m_Point = { 100, WIN_SIZE - 150 };
	m_Char.m_Size = { 100, 100 };
	m_Char.m_Rect1 = { m_Char.m_Point.x + 20, m_Char.m_Point.y - 20,
		m_Char.m_Point.x + m_Char.m_Size.cx - 20, m_Char.m_Point.y + m_Char.m_Size.cy };
	m_iCharState = CHAR_IDLE;
	m_iMotionCount = 0;
	m_iJumpPower = JUMP;
}

void Character::DrawChar(HDC hdc)
{
	if (m_iCharState == CHAR_IDLE)
		m_Char.m_iIndex = IMAGE_PLAYER1;
	else if (m_iCharState == CHAR_JUMP)
		m_Char.m_iIndex = IMAGE_PLAYER3;
	else if (m_iCharState == CHAR_DIE)
		m_Char.m_iIndex = IMAGE_DIE;
	Res_MG::GetInstance()->Draw(hdc, m_Char.m_iIndex, m_Char.m_Point, m_Char.m_Size);
	m_iMotionCount++;
	if (m_iMotionCount > 2)
	{
		m_Char.m_iIndex++;
		if (m_Char.m_iIndex > IMAGE_PLAYER3)
			m_Char.m_iIndex = IMAGE_PLAYER1;	
		m_iMotionCount = 0;
	}
}

void Character::Jump()
{
	if (m_iCharState != CHAR_JUMP)
	{
		m_Save = m_Char.m_Point;
		m_iCharState = CHAR_JUMP;
	}
	else
	{
		m_Char.m_Point.y += m_iJumpPower;
		m_Char.m_Rect1 = { m_Char.m_Point.x + 20, m_Char.m_Point.y - 20,
	m_Char.m_Point.x + m_Char.m_Size.cx - 20, m_Char.m_Point.y + m_Char.m_Size.cy };
		m_iJumpPower += GRAVITY;
		if (m_Save.y == m_Char.m_Point.y)
		{
			m_iJumpPower = JUMP;
			m_iCharState = CHAR_IDLE;
		}
	}
}

Character::~Character()
{
}