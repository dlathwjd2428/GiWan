#include "Character.h"

Character::Character()
{
}

void Character::SetCharacter()
{
	//캐릭터설정
	m_Char.m_iIndex = IMAGE_CHARACTER1;
	m_Char.m_Point = { POINT_X, POINT_Y };
	m_Char.m_Size = { DEFAULT_SIZE , DEFAULT_SIZE };
	m_Char.m_Rect = { m_Char.m_Point.x + 20, m_Char.m_Point.y + 10, m_Char.m_Point.x + m_Char.m_Size.cx - 20, m_Char.m_Point.y + m_Char.m_Size.cy - 10 };
	m_iSpeed = 0;
	m_iJumpPower = JUMP;
	m_bJumpState = false;
}

void Character::Draw(HDC hdc, int Option)
{
	if (Option == WIN)
		m_Char.m_iIndex = IMAGE_WIN1;
	else if (Option == DIE)
		m_Char.m_iIndex = IMAGE_DIE;
	BitManager::GetInstance()->Draw(hdc, m_Char.m_iIndex, m_Char.m_Point, m_Char.m_Size);
}

void Character::Move()
{
	if (m_bJumpState == true)
		m_Char.m_iIndex = IMAGE_CHARACTER_JUMP;
	else if (m_Char.m_iIndex >= IMAGE_CHARACTER_JUMP)
		m_Char.m_iIndex = IMAGE_CHARACTER1;
	else
		m_Char.m_iIndex++;
}

void Character::Jump()
{
	if (m_bJumpState == false)
	{
		m_bJumpState = true;
		m_SavePt = m_Char.m_Point;
	}
	else
	{
		m_Char.m_Point.y -= m_iJumpPower;
		m_Char.m_Rect = { m_Char.m_Point.x, m_Char.m_Point.y, m_Char.m_Point.x + m_Char.m_Size.cx, m_Char.m_Point.y + m_Char.m_Size.cy };
		m_iJumpPower += GRAVITY;
		if (m_Char.m_Point.y >= m_SavePt.y)
		{
			m_bJumpState = false;
			m_iJumpPower = JUMP;
		}
	}
}

Character::~Character()
{
}