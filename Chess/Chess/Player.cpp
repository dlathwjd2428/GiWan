#include "Player.h"

Player::Player()
{
}

void Player::SetPlayer(int Type)
{
	//플레이어타입설정
	m_iType = Type;
	//말들설정
	SetPiece();
}

void Player::SetPiece()
{
	int Add = 0, ImageIndex;
	POINT pt = { 0, IMAGE_SIZE * 6 };
	if (m_iType == PLAYER_WHITE)
	{
		Add = 6;
		pt = { 0, IMAGE_SIZE };
	}
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (i < 8)
			ImageIndex = IMAGE_BLACK_PAWN + Add;
		else if(i == 8 || i == 15)
			ImageIndex = IMAGE_BLACK_ROCK + Add;
		else if(i == 9 || i == 14)
			ImageIndex = IMAGE_BLACK_KNIGHT + Add;
		else if(i == 10 || i == 13)
			ImageIndex = IMAGE_BLACK_BISHOP + Add;
		else if (i == 11)
		{
			if(m_iType == PLAYER_BLACK)
				ImageIndex = IMAGE_BLACK_QUEEN + Add;
			else
				ImageIndex = IMAGE_BLACK_KING + Add;
		}
		else
		{
			if (m_iType == PLAYER_BLACK)
				ImageIndex = IMAGE_BLACK_KING + Add;
			else
				ImageIndex = IMAGE_BLACK_QUEEN + Add;
		}
		m_arrPiece[i].SetPiece(ImageIndex, pt);
		pt.x += IMAGE_SIZE;
		if ((i + 1) % 8 == 0)
		{
			pt.x = 0;
			pt.y += IMAGE_SIZE;
			if (m_iType == PLAYER_WHITE)
				pt.y -= 2 *IMAGE_SIZE;
		}
	}
}

void Player::DrawPiece(HDC hdc)
{
	for (int i = 0; i < PIECE_MAX; i++)
		m_arrPiece[i].DrawPiece(hdc);
}
Player::~Player()
{
}