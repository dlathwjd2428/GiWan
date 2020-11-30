#pragma once
#include"Map.h"
#include"Character.h"
#include"Obstacle.h"

class GameManager
{
private:
	int m_iClock;
	int m_iGameState;
	Map m_Map;
	Character m_Character;
	Obstacle m_Obstacle;
	bool m_bMessageState;
public:
	void SetGame(HWND hWnd);
	void UpdateGame(HWND hWnd);
	void Draw(HDC hdc, int Option = NORMAL);
	void Move();
	void SetMessageState();
	void CollideCheck(HWND hWnd);
	inline bool GetJump() { return m_Character.GetJumpState(); }
	inline int GetGameState() { return m_iGameState; }
	GameManager();
	~GameManager();
};

