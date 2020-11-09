#pragma once
#include"Piece.h"

class Player
{
private:
	int m_iType;
	bool m_bClickState;
	RECT m_arrPieceRect[PIECE_MAX];
	Piece* m_arrPiece[PIECE_MAX];
public:
	void SetPlayer(int Type);
	void SetPiece();
	void DrawPiece(HDC hdc);
	void DrawRange(HDC hdc);
	bool CheckPieceRect(POINT pt, RECT* Enemy);
	void UpdatePlayer();
	inline RECT* GetRectArr() { return m_arrPieceRect; }
	Player();
	~Player();
};

