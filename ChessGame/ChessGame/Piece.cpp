#include "Piece.h"

Piece::Piece()
{
}

void Piece::SetInfo(int Index, POINT pt)
{
	//말 이미지주소, rect설정
	m_Image.m_iImageIndex = Index;
	m_Image.m_ImageRect = { pt.x, pt.y, pt.x + IMAGE_SIZE, pt.y + IMAGE_SIZE };
	//Y축 + 값설정
	AddY = IMAGE_SIZE;
	if (m_Image.m_iImageIndex < IMAGE_WHITE_PAWN)
		AddY = -IMAGE_SIZE;
}

void Piece::SetDefault()
{
	while (!m_vAtkRange.empty())
		m_vAtkRange.pop_back();
	while (!m_vMoveRange.empty())
		m_vMoveRange.pop_back();
}

void Piece::DrawPiece(HDC hdc) { BitMapManager::GetBManager()->DrawBitMap(hdc, m_Image.m_iImageIndex, m_Image.m_ImageRect); }

int Piece::CheckRectForRange(RECT* player, RECT* enemy, RECT Move, RECT Atk)
{
	RECT null;
	int Check = 0;
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (IntersectRect(&null, &Move, &player[i]) == true || IntersectRect(&null, &Move, &enemy[i]) == true)
			Check++;
		if (IntersectRect(&null, &Atk, &player[i]) == false && IntersectRect(&null, &Atk, &enemy[i]) == true)
			m_vAtkRange.push_back(Atk);
	}
	return Check;
}

bool Piece::ClickCheck(POINT pt)
{
	if (PtInRect(&m_Image.m_ImageRect, pt))
		return true;
	return false;
}

Piece::~Piece()
{
}

//Pawn
Pawn::Pawn()
{
	m_iMoveCount = 0;
}

void Pawn::SetRange(RECT* player, RECT* enemy)
{
	RECT tmpMove, tmpAtk;
	SetDefault();
	tmpMove = m_Image.m_ImageRect;
	for (int i = 0; i < 2; i++)
	{
		tmpAtk = m_Image.m_ImageRect;
		if (i == 0)
		{
			tmpAtk.left -= IMAGE_SIZE;
			tmpAtk.top += AddY;
		}
		else
		{
			tmpAtk.left += IMAGE_SIZE;
			tmpAtk.top += AddY;
		}
		tmpMove.top += AddY;
		tmpMove.bottom = tmpMove.top - IMAGE_SIZE;
		tmpAtk.right = tmpAtk.left + IMAGE_SIZE;
		tmpAtk.bottom = tmpAtk.top - IMAGE_SIZE;
		if (CheckRectForRange(player, enemy, tmpMove, tmpAtk) == 0)
			m_vMoveRange.push_back(tmpMove);
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

void Knight::SetRange(RECT* player, RECT* enemy)
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

void Bishop::SetRange(RECT* player, RECT* enemy)
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

void Rock::SetRange(RECT* player, RECT* enemy)
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

void Queen::SetRange(RECT* player, RECT* enemy)
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

void King::SetRange(RECT* player, RECT* enemy)
{

}

King::~King()
{
}
//King