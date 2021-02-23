#pragma once
#include"Res_MG.h"

class Board
{
private:
	static Board* m_hThis;
	BOARD m_arrBoard[ROOM][ROOM];
	POINT m_KillPoint;
public:
	static Board* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new Board;
		return m_hThis;
	}
	void SetBoard();
	void UpdateBoard(int Exist, POINT PrevPt, POINT CurPt);
	void DrawBoard(HDC hdc);
	bool KingCheck(HWND hWnd);
	bool FindExist(int Exist);
	inline int GetExist(int x, int y) { return m_arrBoard[y / 100][x / 100].m_iExist; }
	inline void SetKillPoint(POINT pt) { m_KillPoint = pt; }
	inline POINT GetKillPoint() { return m_KillPoint; }
	Board();
	~Board();
};

