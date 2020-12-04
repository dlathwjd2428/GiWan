#include "Character.h"

Character::Character()
{
}

void Character::SetChar()
{
	m_Char.m_iIndex = IMAGE_CHAR1;
	m_Char.m_Point = { CHAR_PT_X, CHAR_PT_Y };
	m_Char.m_Size = { IMAGE_SIZE, IMAGE_SIZE };
	m_Char.m_Rect1 = { m_Char.m_Point.x, m_Char.m_Point.y, m_Char.m_Point.x + IMAGE_SIZE, m_Char.m_Point.y + IMAGE_SIZE };
}

void Character::Draw(HDC hdc)
{
	BitManager::GetInstance()->Draw(hdc, m_Char.m_iIndex, m_Char.m_Point, m_Char.m_Size);
}

Character::~Character()
{
}
