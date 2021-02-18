#pragma once
#include"Res_MG.h"

class Board
{
private:
	static Board* m_hThis;
	MyBoard m_arrBoard[MAX][MAX];
public:
	static Board* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new Board;
		return m_hThis;
	}
	void SetBoard();
	void DrawBoard(HDC hdc);
	void ResetBoard();
	void UpdateBoard(int Player, POINT pt);
	inline int CheckBoard(POINT pt) { return m_arrBoard[pt.y / 100][pt.x / 100].m_iExist; }
	Board();
	~Board();
};

