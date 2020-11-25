#pragma once
#include"Map.h"
#include"Character.h"

class GameManager
{
private:
	Map m_Map;
	Character m_Char;
public:
	void LoadingGame(HDC hdc);
	void Draw(HDC hdc);
	void Move();
	GameManager();
	~GameManager();
};

