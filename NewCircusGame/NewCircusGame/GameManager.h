#pragma once
#include"Character.h"
#include"Map.h"
#include"Obstacles.h"

class GameManager
{
private:
	int m_iClock;
	int m_iDirection;
	Character m_Char;
	Map m_Map;
	Obstacles* m_arrObstacle;
public:
	void LoadingGame(HDC hdc);
	void UpdateGame(HDC hdc);
	void Move();
	GameManager();
	~GameManager();
};

