#pragma once
#include"Map.h"
#include"Character.h"
#include"Obstacle.h"

class GameManager
{
private:
	int m_iClock;
	bool m_bGameState;
	Map m_Map;
	Character m_Character;
	Obstacle m_Obstacle;
	bool m_bMessageState;
public:
	void SetGame(HWND hWnd);
	void UpdateGame(HWND hWnd);
	void Draw(HDC hdc);
	void Move();
	void SetMessageState();
	void CollideCheck(HWND hWnd);
	inline bool GetJump() { return m_Character.GetJumpState(); }	
	inline bool GetGameState() { return m_bGameState; }
	GameManager();
	~GameManager();
};

