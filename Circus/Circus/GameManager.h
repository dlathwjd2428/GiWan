#pragma once
#include"Map.h"
#include"Character.h"
#include"Obstacle.h"

class GameManager
{
private:
	Map m_Map;
	Character m_Char;
	Obstacle m_Obstacle;
	int m_iClock;
public:
	void LoadingGame(HDC hdc);
	void UpdateGame(HWND hWnd);
	void Draw(HDC hdc);
	void Move(bool &Timer);
	void Jump(bool& Timer);
	GameManager();
	~GameManager();
};

