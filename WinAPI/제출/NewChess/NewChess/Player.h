#pragma once
#include"Piece.h"

class Player
{
private:
	int m_iColor;
	int m_iSaveIndex;
	int m_iEnemy;
	int m_iAdd;
	Piece* m_parrPiece[PIECE_MAX];
public:
	void SetPlayer(int Color);
	void Draw(HDC hdc);
	bool Click(HWND hWnd, POINT pt, int& Turn);
	void RangeUpdate();
	void Die(POINT pt);
	void PawnChange();
	void KingCheck(HWND hWnd);
	Player();
	~Player();
};

