#pragma once
#include"Res_MG.h"

class Board
{
private:
	Card m_arrBoard[Y][X];
	POINT m_Save[2];
public:
	void SetBoard();
	void Draw(HDC hdc);
	int ClickCheck(POINT pt, int& Count);
	bool CorrectCheck();
	void CloseCard();
	bool WinCheck();
	Board();
	~Board();
};

