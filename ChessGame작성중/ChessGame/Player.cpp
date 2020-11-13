#include "Player.h"

Player::Player()
{
}

void Player::SetPlayer(int Type)
{
	//플레이어타입설정(흑/백)
	m_iType = Type;
	//플레이어가 가지고있는 말들 설정
	SetPieceArr();
	//클릭상태설정
	m_bClickState = false;
	//말 선택인덱스 설정
	m_iSelectIndex = NONE;
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

std::vector<RECT> Player::DrawRange(HDC hdc)
{
	return m_parrPiece[m_iSelectIndex]->DrawRange(hdc);
}

void Player::DrawAtkPiece(HDC hdc, std::vector<RECT> rect)
{
	if (rect.size() != NULL)
	{
		for (int i = 0; i < PIECE_MAX; i++)
			m_parrPiece[i]->RectCheck(rect, hdc);
	}
}

void Player::UpdatePlayer(RECT* Enemy)
{
	//말들 Rect값 가져오기
	for (int i = 0; i < PIECE_MAX; i++)
		m_arrPieceRect[i] = m_parrPiece[i]->GetRect();
	//말들 범위설정
	for (int i = 0; i < PIECE_MAX; i++)
		m_parrPiece[i]->SetRange(m_arrPieceRect, Enemy);
}

bool Player::Click(POINT pt)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		m_bClickState = m_parrPiece[i]->ClickCheck(pt);
		if (m_bClickState == true)	//해당 좌표가 해당이미지에 존재하면 true
		{
			m_iSelectIndex = i;
			break;
		}
	}
	return m_bClickState;
}

int Player::MovePiece(POINT pt)
{
	if (m_parrPiece[m_iSelectIndex]->Move(pt) == true)
	{
		m_bClickState = false;
		return m_iSelectIndex;
	}
	return NONE;
}

bool Player::KingCheck(RECT KingRect)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (m_parrPiece[i]->KingCheck(KingRect) == true)
			return true;
	}
	return false;
}

void Player::DeletePiece(RECT rect)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (m_parrPiece[i]->Delete(rect) == true)
			break;
	}
}

Player::~Player()
{
	for (int i = 0; i < PIECE_MAX; i++)
		delete m_parrPiece[i];
}
