#pragma once
#include"Character.h"
#include"Map.h"

class GameManager
{
private:
	Character m_Char;
	Map m_Map;
public:
	void SetGame(HDC hdc);
	void Draw(HDC hdc);
	GameManager();
	~GameManager();
};

