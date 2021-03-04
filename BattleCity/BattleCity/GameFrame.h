#pragma once
#include"MapTool.h"

class GameFrame
{
private:
	HDC m_hFrameDC;
	HBITMAP m_hFrame, m_hOldFrame;
	Map m_arrMap[MAP_MAX];
public:
	void SetGame(HDC hdc);
	void UpdateGame(HDC hdc);
	void Draw(HDC hdc);
	void EndGame();
	GameFrame();
	~GameFrame();
};