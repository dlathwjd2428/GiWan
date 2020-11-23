#include "Character.h"

Character::Character()
{
}

void Character::SetDefault(HDC hdc)
{
	m_CharPt = { 150, 150 };
	m_IMG_Pt = { 0, 0 };
	m_Image.SetImage(hdc, TEXT("image.bmp"), FRONT);
	m_iDirection = NONE;
	m_bJumpState = false;
	m_iJumpY = JUMP;
}

void Character::Draw(HDC hdc)
{
	m_Image.Draw(hdc, m_CharPt, m_IMG_Pt);
}

void Character::Move(int Direction)
{
	if (m_IMG_Pt.x >= 3)
		m_IMG_Pt.x = 0;
	m_IMG_Pt.x++;
	switch (Direction)
	{
	case LEFT:
		m_CharPt.x -= 10;
		m_IMG_Pt.y = LEFT;
		m_iDirection = LEFT;
		break;
	case RIGHT:
		m_CharPt.x += 10;
		m_IMG_Pt.y = RIGHT;
		m_iDirection = RIGHT;
		break;
	case UP:
		m_CharPt.y -= 10;
		m_IMG_Pt.y = UP;
		m_iDirection = UP;
		break;
	case DOWN:
		m_CharPt.y += 10;
		m_IMG_Pt.y = DOWN;
		m_iDirection = DOWN;
		break;
	}
}

bool Character::Jump()
{
	if (m_bJumpState == false)
	{
		m_SavePt = m_CharPt;
		m_bJumpState = true;
	}
	else
	{
		m_CharPt.y -= m_iJumpY;
		m_iJumpY -= GRAVITY;
		if (m_SavePt.y <= m_CharPt.y)
		{
			m_bJumpState = false;
			m_iJumpY = JUMP;
			return false;
		}
	}
	return true;
}

Character::~Character()
{
}