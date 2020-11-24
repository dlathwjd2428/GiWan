#pragma once
#include"Map.h"
#include"Character.h"

class GameManager
{
private:
	Map m_Map;
	Character m_Char;
public:
	void LoadingGame(HWND hWnd);
	void Draw(HDC hdc);
	void Update();
	void Move();
	GameManager();
	~GameManager();
};

