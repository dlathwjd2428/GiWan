#include "Piece.h"

Piece::Piece()
{
}

void Piece::SetPiece(int Index, POINT pt)
{
	//리소스이미지인덱스,rect설정
	m_Image.m_iIndex = Index;
	m_Image.m_Rect = { pt.x, pt.y, pt.x + IMAGE_SIZE, pt.y + IMAGE_SIZE };
}

void Piece::DrawPiece(HDC hdc) { BitMapManager::GetInstance()->DrawBitMap(hdc, m_Image.m_iIndex, m_Image.m_Rect); }

Piece::~Piece()
{
}

//Pawn
Pawn::Pawn()
{
}

Pawn::~Pawn()
{
}
//Pawn

//Knight
Knight::Knight()
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

Bishop::~Bishop()
{
}
//Bishop

//Rock
Rock::Rock()
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

Queen::~Queen()
{
}
//Queen

//King
King::King()
{
}

King::~King()
{
}
//King