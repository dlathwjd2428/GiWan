#pragma once
#include"Piece.h"

class Player
{
private:
	Piece* m_parrPiece[PIECE_MAX];
	int m_iType;
	int m_iSelectIndex;
	bool m_bClickState;
	RECT m_arrPieceRect[PIECE_MAX];
public:
	void SetPlayer(int Type);
	void SetPieceArr();
	void DrawPieceArr(HDC hdc);
	void DrawAtkPiece(HDC hdc, std::vector<RECT> rect);
	std::vector<RECT> DrawRange(HDC hdc);
	void UpdatePlayer(RECT* Enemy);
	bool Click(POINT pt);
	int MovePiece(POINT pt);
	bool KingCheck(RECT KingRect);
	void DeletePiece(RECT rect);
	//인라인함수
	inline RECT* GetRectArr() { return m_arrPieceRect; }
	Player();
	~Player();
};

