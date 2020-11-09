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
}

void Piece::DrawPiece(HDC hdc) { BitMapManager::GetInstance()->DrawBitMap(hdc, m_Image.m_iIndex, m_Image.m_Rect); }

void Piece::DrawRange(HDC hdc)
{
	if (m_bClickState == true)
	{
		for (int i = 0; i < m_vMoveRange.size(); i++)
			BitMapManager::GetInstance()->DrawBitMap(hdc, IMAGE_BLOCK_PINK, m_vMoveRange[i]);
	}
}

bool Piece::ClickCheck(POINT pt)
{
	if (PtInRect(&m_Image.m_Rect, pt))
	{
		if (m_bClickState == true)
			m_bClickState = false;
		else
			m_bClickState = true;
		return true;
	}
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
	RECT tmpRect, nullRect;
	int Check = 0;
	int Add = IMAGE_SIZE;
	if (m_Image.m_iIndex < IMAGE_WHITE_PAWN)
		Add = -IMAGE_SIZE;
	tmpRect = m_Image.m_Rect;
	for (int i = 0; i < 2; i++)
	{
		tmpRect.top += Add;
		tmpRect.bottom = tmpRect.top - Add;
		for (int i = 0; i < PIECE_MAX; i++)
		{
			if (IntersectRect(&nullRect, &tmpRect, &Player[i]) == true || IntersectRect(&nullRect, &tmpRect, &Enemy[i]) == true)
			{
				Check++;
				break;
			}
		}
		if (Check == 0)
			m_vMoveRange.push_back(tmpRect);
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