#pragma once
#include"Res_MG.h"

class GameFrame
{
private:
	HDC m_hFrameDC;
	HBITMAP m_hFrame, m_hOldFrame;
	bool m_bGameState;
	int m_iClock;
public:
	void SetGame(HDC hdc);
	void UpdateGame(HDC hdc);
	void Draw(HDC hdc);
	void EndGame();
	GameFrame();
	~GameFrame();
};

