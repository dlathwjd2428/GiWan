#pragma once
#include"Character.h"
#include"Object.h"

class GameFrame
{
private:
	HDC m_hFrameDC;
	HBITMAP m_hFrame, m_hOldFrame;
	Character m_Char;
	Object* m_arrObject[OBJECT_MAX];
	int m_iClock;
	int m_iDirection;
	int m_iScore;
	bool m_bGameState;
public:
	void SetGame(HDC hdc);
	void UpdateGame(HDC hdc, HWND hWnd);
	void Draw(HDC hdc);
	void Move();
	void CollideCheck(HWND hWnd, HDC hdc);
	GameFrame();
	~GameFrame();
};

