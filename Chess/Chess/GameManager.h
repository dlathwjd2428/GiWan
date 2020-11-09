#pragma once
#include"Player.h"

class GameManager
{
private:
	RESOURCE m_arrMap[Y][X]; 
	Player m_arrPlayer[PLAYER_MAX];
public:
	void LoadingGame(HWND hWnd);
	void DrawMap(HDC hdc);
	void DrawPiece(HDC hdc);
	GameManager();
	~GameManager();
};

