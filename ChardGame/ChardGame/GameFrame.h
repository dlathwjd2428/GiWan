#pragma once
#include"Board.h"

class GameFrame
{
private:
	int m_iClock;
	int m_iStopClock;
	int m_iClick;
	HDC m_hFrameDC;
	HBITMAP m_hFrame, m_hOldFrame;
	Board m_Board;
public:
	void SetGame(HDC hdc);
	void UpdateGame(HWND hWnd, HDC hdc, POINT& pt);
	void Draw(HDC hdc);
	void Click(POINT pt);
	void EndGame();
	GameFrame();
	~GameFrame();
};

