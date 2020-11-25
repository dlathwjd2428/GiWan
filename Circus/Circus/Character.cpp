#include "Character.h"

Character::Character()
{
}

void Character::SetChar(HDC hdc)
{
	m_Char.m_iIndex = IMAGE_PLAYER;
	m_Char.m_iPoint = { 0, WIN_Y - 150 };
	m_Char.m_iSize = { 100, 100 };
}

void Character::Draw(HDC hdc)
{
	BitMapManager::GetInstance()->Draw(hdc, m_Char.m_iIndex, m_Char.m_iPoint, m_Char.m_iSize);
}

void Character::CharMove(int Direction)
{
	if (m_Char.m_iIndex >= IMAGE_PLAYER2)
		m_Char.m_iIndex = IMAGE_PLAYER;
	else
		m_Char.m_iIndex++;
	switch (Direction)
	{
	case LEFT:
		if (m_Char.m_iPoint.x >= 0)
			m_Char.m_iPoint.x--;
		break;
	case RIGHT:
		if (m_Char.m_iPoint.x <= WIN_X / 2)
			m_Char.m_iPoint.x++;
		break;
	default:
		break;
	}
}

Character::~Character()
{
}
