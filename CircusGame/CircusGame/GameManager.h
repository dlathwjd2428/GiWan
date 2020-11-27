#pragma once
#include"Map.h"
#include"Character.h"
#include"Obstacle.h"

class GameManager
{
private:
	int m_iClock;
	Map m_Map;
	Character m_Character;
	Obstacle m_Obstacle;
public:
	void SetGame(HDC hdc);
	void UpdateGame(HWND hWnd);
	void Draw(HDC hdc);
	void Move();
	GameManager();
	~GameManager();
};

