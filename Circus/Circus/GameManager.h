#pragma once
#include"Character.h"
#include"Map.h"
#include"Obstacle.h"

class GameManager
{
private:
	int m_iScore;
	int m_iClock;
	bool m_bMessageState;
	int m_iGameState;
	Character m_Char;
	Map m_Map;
	Obstacle m_Obstacle;
public:
	void SetGame(HWND hWnd);
	void UpdateGame();
	void Draw(HDC hdc);
	void Move();
	void CollideCheck(HWND hWnd);
	inline int GetGameState() { return m_iGameState; }
	inline void SetMessageState(bool State) { m_bMessageState = State; }
	inline bool GetMessageState() { return m_bMessageState; }
	GameManager();
	~GameManager();
};

