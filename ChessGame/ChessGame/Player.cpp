#include "Player.h"

Player::Player()
{
}

void Player::SetPlayer(int Player)
{
	POINT tmpPoint = {0, 600};
	int AddY = 100;
	m_iPlayer = Player;
	if (m_iPlayer == WHITE)
	{
		tmpPoint = { 0, 100 };
		AddY = -100;
	}
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (i < 8)
			m_parrPiece[i] = new Pawn;
		else if (i == 8 || i == PIECE_MAX - 1)
			m_parrPiece[i] = new Rock;
		else if (i == 9 || i == PIECE_MAX - 2)
			m_parrPiece[i] = new Bishop;
		else if (i == 10 || i == PIECE_MAX - 3)
			m_parrPiece[i] = new Knight;
		else
		{
			if (i == 11)
			{
				if (m_iPlayer == BLACK)
					m_parrPiece[i] = new Queen;
				else
					m_parrPiece[i] = new King;
			}
			else
			{
				if (m_iPlayer == BLACK)
					m_parrPiece[i] = new King;
				else
					m_parrPiece[i] = new Queen;
			}
		}
		m_parrPiece[i]->SetPiece(m_iPlayer, tmpPoint);
		tmpPoint.x += IMAGE_SIZE;
		if (tmpPoint.x >= 800)
		{
			tmpPoint.x = 0;
			tmpPoint.y += AddY;
		}
	}
	UpdatePiece();
}

void Player::DrawPiece(HDC hdc)
{
	for (int i = 0; i < PIECE_MAX; i++)
		m_parrPiece[i]->Draw(hdc);
}

void Player::UpdatePiece()
{
	POINT tmpPoint;
	for (int i = 0; i < PIECE_MAX; i++)
	{
		tmpPoint = m_parrPiece[i]->GetPoint();
		tmpPoint.x /= 100;
		tmpPoint.y /= 100;
		Board::GetInstance()->UpdateBoard(m_iPlayer, tmpPoint);
	}
	for (int i = 0; i < PIECE_MAX; i++)
		m_parrPiece[i]->SetRange();
}

void Player::Click(POINT pt)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (m_parrPiece[i]->ClickCheck(pt))
		{
			m_iSaveIndex = i;
			break;
		}
	}
}

Player::~Player()
{
}