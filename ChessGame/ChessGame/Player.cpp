#include "Player.h"

Player::Player()
{
}

void Player::SetPlayer(int Type)
{
	//�÷��̾�Ÿ�Լ���(��/��)
	m_iType = Type;
	//�÷��̾ �������ִ� ���� ����
	SetPieceArr();
	//Ŭ�����¼���
	m_bClickState = false;
}

void Player::SetPieceArr()
{
	int Add = 0;
	POINT pt = { 0, IMAGE_SIZE * 6 };
	int tmpImage;
	if (m_iType == TYPE_WHITE)
	{
		Add = 6;
		pt = { 0, IMAGE_SIZE };
	}
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (i < 8)
		{
			m_parrPiece[i] = new Pawn;
			tmpImage = IMAGE_BLACK_PAWN + Add;
		}
		else if (i == 8 || i == 15)
		{
			m_parrPiece[i] = new Rock;
			tmpImage = IMAGE_BLACK_ROCK + Add;
		}
		else if (i == 9 || i == 14)
		{
			m_parrPiece[i] = new Knight;
			tmpImage = IMAGE_BLACK_KNIGHT + Add;
		}
		else if (i == 10 || i == 13)
		{
			m_parrPiece[i] = new Bishop;
			tmpImage = IMAGE_BLACK_BISHOP + Add;
		}
		else if ((i == 11 && m_iType == TYPE_BLACK) || (i == 12 && m_iType == TYPE_WHITE))
		{
			m_parrPiece[i] = new Queen;
			tmpImage = IMAGE_BLACK_QUEEN + Add;
		}
		else
		{
			m_parrPiece[i] = new King;
			tmpImage = IMAGE_BLACK_KING+ Add;
		}
		m_parrPiece[i]->SetInfo(tmpImage, pt);
		pt.x += IMAGE_SIZE;
		if ((i + 1) % 8 == 0)
		{
			pt.x = 0;
			pt.y += IMAGE_SIZE;
			if (m_iType == TYPE_WHITE)
				pt.y -= 2 * IMAGE_SIZE;
		}
	} 
}

void Player::DrawPieceArr(HDC hdc)
{
	for (int i = 0; i < PIECE_MAX; i++)
		m_parrPiece[i]->DrawPiece(hdc);
}

void Player::UpdatePlayer(RECT* Enemy)
{
	//���� Rect�� ��������
	for (int i = 0; i < PIECE_MAX; i++)
		m_arrPieceRect[i] = m_parrPiece[i]->GetRect();
	//���� ��������
	for (int i = 0; i < PIECE_MAX; i++)
		m_parrPiece[i]->SetRange(m_arrPieceRect, Enemy);
}

void Player::Click(POINT pt)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		m_parrPiece[i]->
	}
}

Player::~Player()
{
}
