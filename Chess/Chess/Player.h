#pragma once
#include"Piece.h"

class Player
{
private:
	int m_iType;
	int m_iSelectIndex;
	bool m_bClickState;
	RECT m_arrPieceRect[PIECE_MAX];
	Piece* m_arrPiece[PIECE_MAX];
public:
	void SetPlayer(int Type);
	void SetPiece();
	void DrawPiece(HDC hdc);
	void DrawRange(HDC hdc);
	void UpdatePlayer(RECT* Enemy);
	bool PieceCheck();
	bool KingCheck(RECT KingRect);
	bool Click(POINT pt);
	int Move(POINT pt);
	void DeletePiece(RECT rect);
	void PawnTest();
	inline RECT* GetRectArr() { return m_arrPieceRect; }
	Player();
	~Player();
};

