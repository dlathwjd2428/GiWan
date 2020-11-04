#pragma once
#include"BitMap.h"

#define ALIVE 0
#define DIE 1

class ChessPiece
{
private:
	BitMap m_ChessPiece;
	bool m_bPieceState;
public:
	void SetChessPiece();
	ChessPiece();
	~ChessPiece();
};

