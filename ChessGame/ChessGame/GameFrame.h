#pragma once
#include"Player.h"

class GameFrame
{
private:
	int m_iClock;
	int m_iTurn;
	HDC m_hFrameDC;
	HBITMAP m_hFrame, m_hOldFrame;
	Player m_arrPlayer[PLAYER_MAX];
public:
	void SetGame(HDC hdc);
	void UpdateGame(HDC hdc, POINT pt);
	void Draw(HDC hdc);
	void Click(POINT pt);
	void EndGame();
	GameFrame();
	~GameFrame();
};

