#include "Player.h"

Player::Player()
{
	m_iSelectIndex = NONE;
}

void Player::SetPlayer(int Type)
{
	//플레이어타입설정
	m_iType = Type;
	//말들설정
	SetPiece();
	//말선택상태 초기값설정
	m_bClickState = false;
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
		{
			ImageIndex = IMAGE_BLACK_PAWN + Add;
			m_arrPiece[i] = new Pawn;
		}
		else if (i == 8 || i == 15)
		{
			ImageIndex = IMAGE_BLACK_ROCK + Add;
			m_arrPiece[i] = new Rock;
		}
		else if (i == 9 || i == 14)
		{
			ImageIndex = IMAGE_BLACK_KNIGHT + Add;
			m_arrPiece[i] = new Knight;
		}
		else if (i == 10 || i == 13)
		{
			ImageIndex = IMAGE_BLACK_BISHOP + Add;
			m_arrPiece[i] = new Bishop;
		}
		else if (i == 11)
		{
			if (m_iType == PLAYER_BLACK)
			{
				ImageIndex = IMAGE_BLACK_QUEEN + Add;
				m_arrPiece[i] = new Queen;
			}
			else
			{
				ImageIndex = IMAGE_BLACK_KING + Add;
				m_arrPiece[i] = new King;
			}
		}
		else
		{
			if (m_iType == PLAYER_BLACK)
			{
				ImageIndex = IMAGE_BLACK_KING + Add;
				m_arrPiece[i] = new King;
			}
			else
			{
				ImageIndex = IMAGE_BLACK_QUEEN + Add;
				m_arrPiece[i] = new Queen;
			}
		}
		m_arrPiece[i]->SetPiece(ImageIndex, pt);
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
		m_arrPiece[i]->DrawPiece(hdc);
}

void Player::DrawRange(HDC hdc)
{

	for (int i = 0; i < PIECE_MAX; i++)
		m_arrPiece[i]->DrawRange(hdc);
}

bool Player::Click(POINT pt)
{
	
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (m_bClickState == true && m_arrPiece[i]->GetClickState() == true && m_arrPiece[i]->ClickCheck(pt) == true)
		{
			m_bClickState = false;
			m_arrPiece[i]->SetClickState(false);
			break;
		}		
		else if (m_bClickState == false && m_arrPiece[i]->MoveSizeCheck() == true)
		{
			m_bClickState = m_arrPiece[i]->ClickCheck(pt);
			if (m_bClickState == true)
			{
				m_arrPiece[i]->SetClickState(true);
				m_iSelectIndex = i;
				break;
			}
		}
	}
	
	return m_bClickState;
}

int Player::Move(POINT pt)
{
	int MoveCheck = FALSE;
	MoveCheck = m_arrPiece[m_iSelectIndex]->Move(pt);
	if (MoveCheck != FALSE)
		m_bClickState = false;
	//for (int i = 0; i < PIECE_MAX; i++)
	//{
		//MoveCheck = m_arrPiece[i]->Move(pt);
		//if (MoveCheck != FALSE)
		//{
			//m_bClickState = false;
			//break;			
		//}
	//}
	return MoveCheck;
}
void Player::UpdatePlayer(RECT* Enemy)
{
	//말들rect값 성정
	for (int i = 0; i < PIECE_MAX; i++)
		m_arrPieceRect[i] = m_arrPiece[i]->GetRect();
	//말들범위설정
	RECT tmp[PIECE_MAX];
	for (int i = 0; i < PIECE_MAX; i++)
		tmp[i] = Enemy[i];
	for (int i = 0; i < PIECE_MAX; i++)
		m_arrPiece[i]->SetRange(m_arrPieceRect, tmp);
}

void Player::DeletePiece(RECT rect)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (m_arrPiece[i]->Delete(rect) == true)
			break;
	}
}

Player::~Player()
{
}