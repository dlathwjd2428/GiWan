#pragma once
#include"Player.h"

class GameFrame
{
private:
	HDC m_hGameFrame;
	HBITMAP m_hFrame, m_hOldFrame;
	Player m_arrPlayer[PLAYER];
	int m_iClock;
	int m_iTurn;
public:
	void SetGame(HDC hdc);
	void UpdateGame(HWND hWnd, HDC hdc, POINT pt);
	void Draw(HDC hdc);
	void Click(HWND hWnd, POINT pt);
	void EndGame();
	GameFrame();
	~GameFrame();
};

