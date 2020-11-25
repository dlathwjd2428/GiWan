#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::LoadingGame(HDC hdc)
{	
	BitMapManager::GetInstance()->Init(hdc);
	m_Map.SetMap(hdc);
	m_Char.SetChar(hdc);
}

void GameManager::Draw(HDC hdc)
{
	m_Map.DrawMap(hdc);
	m_Char.Draw(hdc);
}

void GameManager::Move()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
		m_Char.CharMove(LEFT);
	if (GetKeyState(VK_RIGHT) & 0x8000)
		m_Char.CharMove(RIGHT);
	if (GetKeyState(VK_RETURN) & 0x8000);
}

GameManager::~GameManager()
{
}
