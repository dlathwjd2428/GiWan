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
	Character m_Char;
	Map m_Map;
	Obstacle m_Obstacle;
public:
	void SetGame(HDC hdc);
	void UpdateGame();
	void Draw(HDC hdc);
	void Move();
	inline void SetMessageState(bool State) { m_bMessageState = State; }
	inline bool GetMessageState() { return m_bMessageState; }
	GameManager();
	~GameManager();
};

