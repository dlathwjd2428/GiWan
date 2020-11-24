#include "Character.h"

Character::Character()
{
}

void Character::SetChar()
{
	m_ImgIndex = IMAGE_PLAYER;
	m_CharPt = { 66, WIN_SIZE_Y - 150 };
	m_Size = { 100, 100 };
}

void Character::Draw(HDC hdc)
{
	BitMapManager::GetInstance()->DrawImage(hdc, m_ImgIndex, m_CharPt, m_Size);
}

void Character::Move(int Direction)
{
	switch (Direction)
	{
	case LEFT:
		if (m_CharPt.x > 0)
		{
			m_CharPt.x -= 10;
			m_ImgIndex++;
			if (m_ImgIndex >= IMAGE_STAR)
				m_ImgIndex = IMAGE_PLAYER;
		}
		break;
	case RIGHT:
		if (m_CharPt.x < WIN_SIZE_X / 3)
		{
			m_CharPt.x += 10;
			m_ImgIndex++;
			if (m_ImgIndex >= IMAGE_STAR)
				m_ImgIndex = IMAGE_PLAYER;
		}
		break;
	case JUMP:
		break;
	}
}

Character::~Character()
{
}
