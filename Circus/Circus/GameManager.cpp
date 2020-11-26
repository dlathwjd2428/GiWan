#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::LoadingGame(HDC hdc)
{	
	BitMapManager::GetInstance()->Init(hdc);
	m_Map.SetMap(hdc);
	m_Char.SetChar();
	m_Obstacle.SetObstacle();
	m_iClock = clock();
}

void GameManager::UpdateGame(HWND hWnd)
{
	if (clock() > m_iClock)
	{
		m_Obstacle.MoveRing(NULL);
		SendMessage(hWnd, WM_PAINT, 0, 0);
		m_iClock = clock() + 50;
	}
}

void GameManager::Draw(HDC hdc)
{
	m_Map.DrawMap(hdc);
	m_Char.Draw(hdc);
	m_Obstacle.DrawRing(hdc);
}

void GameManager::Move(bool &Timer)
{
	if (GetKeyState(VK_RETURN) & 0x8000)
		Timer = true;
	m_Obstacle.Move(NULL);
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_Char.CharMove(LEFT);
		m_Map.MapMove(LEFT);
		m_Obstacle.Move(LEFT);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_Char.CharMove(RIGHT);
		m_Map.MapMove(RIGHT);
		m_Obstacle.Move(RIGHT);
	}
}

void GameManager::Jump(bool& Timer)
{
	if (m_Char.CharJump() == false)
		Timer = false;
}

GameManager::~GameManager()
{
}
