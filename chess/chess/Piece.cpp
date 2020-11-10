#include "Piece.h"

Piece::Piece()
{
}

void Piece::SetPiece(int Index, POINT pt)
{
	//리소스이미지인덱스,rect설정
	m_Image.m_iIndex = Index;
	m_Image.m_Rect = { pt.x, pt.y, pt.x + IMAGE_SIZE, pt.y + IMAGE_SIZE };
	//클릭상태초기값설정
	m_bClickState = false;
	//이동횟수초기값설정
	m_iMoveCount = 0;
}

void Piece::DrawPiece(HDC hdc) { BitMapManager::GetInstance()->DrawBitMap(hdc, m_Image.m_iIndex, m_Image.m_Rect); }

void Piece::DrawRange(HDC hdc)
{
	if (m_bClickState == true)
	{
		for (int i = 0; i < m_vMoveRange.size(); i++)
			BitMapManager::GetInstance()->DrawBitMap(hdc, IMAGE_BLOCK_PINK, m_vMoveRange[i]);
		for (int i = 0; i < m_vAtkRange.size(); i++)
			BitMapManager::GetInstance()->DrawBitMap(hdc, IMAGE_BLOCK_PINK, m_vAtkRange[i]);
	}
}

int Piece::Move(POINT pt)
{
	//이동범위확인후 이동
	for (int i = 0; i < m_vMoveRange.size(); i++)
	{
		if (PtInRect(&m_vMoveRange[i], pt) == true)
		{
			m_Image.m_Rect = m_vMoveRange[i];
			m_iMoveCount++;
			m_bClickState = false;
			return NONE;
		}
	}
	//공격범위확인후 이동
	for (int i = 0; i < m_vAtkRange.size(); i++)
	{
		if (PtInRect(&m_vAtkRange[i], pt) == true)
		{
			m_Image.m_Rect = m_vAtkRange[i];
			m_iMoveCount++;
			m_bClickState = false;
			return i;
		}
	}
	return FALSE;
}

bool Piece::ClickCheck(POINT pt)
{
	if (PtInRect(&m_Image.m_Rect, pt))
		return true;
	return false;
}

bool Piece::Delete(RECT rect)
{
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &rect, &m_Image.m_Rect) == true)
	{
		m_Image.m_Rect = { -1000, -1000, -1000, -1000 };
		m_Image.m_iIndex = IMAGE_BLOCK_PINK;
		m_bClickState = false;
		m_iMoveCount = 0;
		while (!m_vAtkRange.empty())
			m_vAtkRange.pop_back();
		while (!m_vMoveRange.empty())
			m_vMoveRange.pop_back();
		return true;
	}
}
bool Piece::MoveSizeCheck()
{
	if (m_vAtkRange.size() != 0 || m_vMoveRange.size() != 0)
		return true;
	return false;
}

Piece::~Piece()
{
}

//Pawn
Pawn::Pawn()
{
}

void Pawn::SetRange(RECT* Player, RECT* Enemy)
{
	RECT moveRect, atkRect, nullRect;
	int Check = 0;
	int Add = IMAGE_SIZE;
	if (m_Image.m_iIndex < IMAGE_WHITE_PAWN)
		Add = -IMAGE_SIZE;
	//이동, 공격범위 초기화
	while (!m_vMoveRange.empty())
		m_vMoveRange.pop_back();
	while (!m_vAtkRange.empty())
		m_vAtkRange.pop_back();
	moveRect = m_Image.m_Rect;
	//이동, 공격범위 설정
	for (int i = 0; i < 2; i++)
	{
		moveRect.left = m_Image.m_Rect.left;
		moveRect.right = moveRect.left + IMAGE_SIZE;
		moveRect.top += Add;
		moveRect.bottom = moveRect.top + IMAGE_SIZE;
		if (i == 0)
		{
			atkRect.left = m_Image.m_Rect.left - IMAGE_SIZE;
			atkRect.right = atkRect.left + IMAGE_SIZE;
			atkRect.top = m_Image.m_Rect.top + Add;
			atkRect.bottom = atkRect.top + IMAGE_SIZE;
		}
		else
		{
			atkRect.left = m_Image.m_Rect.left + IMAGE_SIZE;
			atkRect.right = atkRect.left + IMAGE_SIZE;
			atkRect.top = m_Image.m_Rect.top + Add;
			atkRect.bottom = atkRect.top + IMAGE_SIZE;
		}
		for (int i = 0; i < PIECE_MAX; i++)
		{
			//공격범위설정
			if (IntersectRect(&nullRect, &Player[i], &atkRect) == false && IntersectRect(&nullRect, &Enemy[i], &atkRect) == true)
				m_vAtkRange.push_back(atkRect);
			//이동범위설정
			if (IntersectRect(&nullRect, &moveRect, &Player[i]) == true || IntersectRect(&nullRect, &moveRect, &Enemy[i]) == true)
				Check++;
		}
		if (Check == 0)
		{
			if (i == 0)
				m_vMoveRange.push_back(moveRect);
			else if(i != 0 && m_iMoveCount == 0)
				m_vMoveRange.push_back(moveRect);
		}
	}
}

Pawn::~Pawn()
{
}
//Pawn

//Knight
Knight::Knight()
{
}

void Knight::SetRange(RECT* Player, RECT* Enemy)
{

}

Knight::~Knight()
{
}
//Knight

//Bishop
Bishop::Bishop()
{
}

void Bishop::SetRange(RECT* Player, RECT* Enemy)
{

}

Bishop::~Bishop()
{
}
//Bishop

//Rock
Rock::Rock()
{
}

void Rock::SetRange(RECT* Player, RECT* Enemy)
{

}

Rock::~Rock()
{
}
//Rock

//Queen
Queen::Queen()
{
}

void Queen::SetRange(RECT* Player, RECT* Enemy)
{

}

Queen::~Queen()
{
}
//Queen

//King
King::King()
{
}

void King::SetRange(RECT* Player, RECT* Enemy)
{

}

King::~King()
{
}
//King