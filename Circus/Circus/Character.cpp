#include "Character.h"

Character::Character()
{
}

void Character::SetChar()
{
	m_Char.m_iIndex = IMAGE_CHAR1;
	m_Char.m_Point = { CHAR_PT_X, CHAR_PT_Y };
	m_Char.m_Size = { IMAGE_SIZE + 20, IMAGE_SIZE + 20};
	m_Char.m_Rect1 = { m_Char.m_Point.x, m_Char.m_Point.y, m_Char.m_Point.x + IMAGE_SIZE, m_Char.m_Point.y + IMAGE_SIZE };
	m_bMoveState = false;
	m_bJumpState = false;
	m_iJumpPower = JUMP;
}

void Character::Draw(HDC hdc)
{
	if (m_bJumpState == true)
		m_Char.m_iIndex = IMAGE_CHAR3;
	else if (m_bMoveState == false)
		m_Char.m_iIndex = IMAGE_CHAR1;
	else
	{
		if (m_Char.m_iIndex == IMAGE_CHAR3)
			m_Char.m_iIndex = IMAGE_CHAR1;
		else
			m_Char.m_iIndex++;
	}
	BitManager::GetInstance()->Draw(hdc, m_Char.m_iIndex, m_Char.m_Point, m_Char.m_Size);
}

void Character::MoveChar(int Direction)
{
	switch (Direction)
	{
	case LEFT:
	case RIGHT:
		m_bMoveState = true;
		break;
	case JUMP:
		if (m_bJumpState == false)
		{
			m_bJumpState = true;
			m_Save = m_Char.m_Point;
		}
		break;
	case NULL:
		m_bMoveState = false;
		break;
	}
}

bool Character::Jump()
{
	m_Char.m_Point.y -= m_iJumpPower;
	m_iJumpPower += GRAVITY;
	if (m_Save.y <= m_Char.m_Point.y)
	{
		m_bJumpState = false;
		m_iJumpPower = JUMP;
		return false;
	}
	return true;
}

Character::~Character()
{
}
