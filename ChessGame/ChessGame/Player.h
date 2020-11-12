#pragma once
#include"Piece.h"

class Player
{
private:
	Piece* m_parrPiece[PIECE_MAX];
	int m_iType;
	bool m_bClickState;
	RECT m_arrPieceRect[PIECE_MAX];
public:
	void SetPlayer(int Type);
	void SetPieceArr();
	void DrawPieceArr(HDC hdc);
	void UpdatePlayer(RECT* Enemy);
	void Click(POINT pt);
	//인라인함수
	inline RECT* GetRectArr() { return m_arrPieceRect; }
	Player();
	~Player();
};

