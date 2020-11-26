#include "Character.h"

Character::Character()
{
}

void Character::SetChar()
{
	m_Char.m_iIndex = IMAGE_PLAYER;
	m_Char.m_iPoint = { 150, WIN_Y - 200 };
	m_Char.m_iSize = { 100, 100 };
	m_iJumpPower = JUMP;
	m_bJumpState = false;
	m_iMoveCount = 0;
}

void Character::Draw(HDC hdc)
{
	if (m_Char.m_iPoint.y < m_SavePt.y)
		m_Char.m_iIndex = IMAGE_PLAYER2;

	BitMapManager::GetInstance()->Draw(hdc, m_Char.m_iIndex, m_Char.m_iPoint, m_Char.m_iSize);
}

void Character::CharMove(int Direction)
{
	if (m_iMoveCount == 3)
	{
		if (m_Char.m_iIndex >= IMAGE_PLAYER2)
			m_Char.m_iIndex = IMAGE_PLAYER;
		else
			m_Char.m_iIndex++;
		m_iMoveCount = 0;
	}
	m_iMoveCount++;
}

bool Character::CharJump()
{
	m_Char.m_iIndex = IMAGE_PLAYER2;
	if (m_bJumpState == false)
	{
		m_bJumpState = true;
		m_SavePt = m_Char.m_iPoint;
	}
	if(m_bJumpState == true)
	{	
		m_Char.m_iPoint.y -= m_iJumpPower;
		m_iJumpPower += GRAVITY;
		if (m_Char.m_iPoint.y >= m_SavePt.y)
		{
			m_iJumpPower = JUMP;
			m_bJumpState = false;
			m_iDirection = NULL;
		}
	}
	return m_bJumpState;
}

Character::~Character()
{
}
