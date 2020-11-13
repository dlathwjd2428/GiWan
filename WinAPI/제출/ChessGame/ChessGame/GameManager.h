#pragma once
#include"Player.h"

class GameManager
{
private:
	int m_iTurn;
	int m_iPlayer, m_iEnemy;
	bool m_bSelectState;   
	int m_iKingIndex;
	ImageInfo m_arrMap[Y][X];
	Player m_arrPlayer[TYPE_MAX];
public:
	void LoadingGame(HWND hWnd);
	void UpdateGame();
	void DrawMap(HDC hdc);
	void DrawPiece(HDC hdc);
	void DrawRange(HDC hdc);
	bool Click(POINT pt);
	bool GameCheck(HWND hWnd);
	GameManager();
	~GameManager();
};

