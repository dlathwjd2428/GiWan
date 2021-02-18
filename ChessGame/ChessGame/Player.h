#pragma once
#include"Piece.h"

class Player
{
private:
	int m_iPlayer;
	int m_iSaveIndex;
	Piece* m_parrPiece[PIECE_MAX];
public:
	void SetPlayer(int Player);
	void DrawPiece(HDC hdc);
	void UpdatePiece();
	void Click(POINT pt);
	Player();
	~Player();
};

