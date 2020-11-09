#pragma once
#include"Piece.h"

class Player
{
private:
	int m_iType;
	Piece m_arrPiece[PIECE_MAX];
public:
	void SetPlayer(int Type);
	void SetPiece();
	void DrawPiece(HDC hdc);
	Player();
	~Player();
};

