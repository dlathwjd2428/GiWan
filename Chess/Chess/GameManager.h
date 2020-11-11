#pragma once
#include"Player.h"

class GameManager
{
private:
	int m_iTurn;
	int m_iPlayer;
	int m_iEnemy;
	int m_iKingIndex;
	bool m_bSelectState;
	RESOURCE m_arrMap[Y][X]; 
	Player m_arrPlayer[PLAYER_MAX];
public:
	void LoadingGame(HWND hWnd);
	void UpdateGame();
	void GameDraw(HDC hdc);
	void ClicK(POINT pt);
	bool GameCheck(HWND hWnd);
	GameManager();
	~GameManager();
};

