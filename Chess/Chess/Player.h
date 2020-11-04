#pragma once
#include"ChessPiece.h"

#define CHESS_MAX 16

class Player
{
private:
	ChessPiece m_ChessPiece[CHESS_MAX];
public:
	void SetChessPiece();
	Player();
	~Player();
};

