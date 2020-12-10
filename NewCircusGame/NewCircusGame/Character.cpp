#include "Character.h"

Character::Character()
{
}

void Character::SetChar()
{
	m_iCount = 0;
	m_bMoveState = false;
	m_Char.m_iIndex = IMAGE_CHAR1;
	m_Char.m_Point = { 100, WIN_SIZE - 150 };
	m_Char.m_Rect1 = { m_Char.m_Point.x, m_Char.m_Point.y, m_Char.m_Point.x + 100, m_Char.m_Point.y + 100 };
	m_Char.m_Size = { 100, 100 };
}

void Character::Draw(HDC hdc)
{
	if(m_bMoveState == false)
		m_Char.m_iIndex = IMAGE_CHAR1;
	ResManager::GetInstance()->DrawBitMap(hdc, m_Char.m_iIndex, m_Char.m_Point, m_Char.m_Size);
}

void Character::Move(int Direction)
{	
	if (Direction != JUMP && m_iCount >= 5)
	{
		m_Char.m_iIndex++;
		if (m_Char.m_iIndex > IMAGE_CHAR3)
			m_Char.m_iIndex = IMAGE_CHAR1;
		m_iCount = 0;
	}
	m_iCount++;
}

Character::~Character()
{
}
