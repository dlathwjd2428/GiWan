#include "Character.h"

Character::Character()
{
	
}

void Character::SetDefaultChar(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	m_Image.SetBitMap(hdc, TEXT("image.bmp"));
	m_CharPt = { 150, 150 };
	m_ImagePt = { 0, 0 };
	m_iDirection = DOWN;
	m_bMoveState = false;
	m_bJumpState = false;
}

void Character::Draw(HDC hdc)
{
	m_Image.DrawBitMap(hdc, m_CharPt, m_ImagePt);
}

void Character::Move(int Direction)
{
	if (m_ImagePt.x >= 3)
		m_ImagePt.x = 0;
	else
		m_ImagePt.x++;
	switch (Direction)
	{
	case LEFT:
		if (m_CharPt.x - 10 >= 0)
		{
			m_CharPt.x -= 10;
			m_ImagePt.y = LEFT;
			m_iDirection = LEFT;
		}
		break;
	case RIGHT:
		if (m_CharPt.x + 10 <= 1000)
		{
			m_CharPt.x += 10;
			m_ImagePt.y = RIGHT;
			m_iDirection = RIGHT;
		}
		break;
	case UP:
		if (m_CharPt.y - 10 >= 0)
		{
			m_CharPt.y -= 10;
			m_ImagePt.y = UP;
			m_iDirection = UP;
		}
		break;
	case DOWN:
		if (m_CharPt.y + 10 <= 1000)
		{
			m_CharPt.y += 10;
			m_ImagePt.y = DOWN;
			m_iDirection = DOWN;
		}
		break;
	case JUMP:
		if (m_bJumpState == false)
			m_bJumpState = true;
		break;
	default:
		break;
	}	
}

void Character::Jump(int Count)
{
	if (m_bJumpState == true)
	{
		if (m_iDirection == RIGHT)
		{
			m_CharPt.x += 5;
			if (Count < 10)
				m_CharPt.y -= 5;
			else
				m_CharPt.y += 5;
		}
		else if (m_iDirection == LEFT)
		{
			m_CharPt.x -= 5;
			if (Count < 10)
				m_CharPt.y -= 5;
			else
				m_CharPt.y += 5;
		}
		else if (m_iDirection == UP)
			m_CharPt.y -= 5;
		else
			m_CharPt.y += 5;
	}
}
RECT Character::GetRect()
{
	RECT tmp;
	tmp = { m_CharPt.x, m_CharPt.y, m_CharPt.x + IMAGE_X, m_CharPt.y + IMAGE_Y };
	return tmp;
}
Character::~Character()
{
}