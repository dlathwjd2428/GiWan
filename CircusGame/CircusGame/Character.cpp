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
	m_iSpeed = 0;
}

void Character::Draw(HDC hdc)
{
	BitManager::GetInstance()->Draw(hdc, m_Char.m_iIndex, m_Char.m_Point, m_Char.m_Size);
}

void Character::Move()
{
	if (m_iSpeed > 1)
	{
		if (m_Char.m_iIndex >= IMAGE_CHARACTER_JUMP)
			m_Char.m_iIndex = IMAGE_CHARACTER1;
		else
			m_Char.m_iIndex++;
		m_iSpeed = 0;
	}
	m_iSpeed++;
}

Character::~Character()
{
}