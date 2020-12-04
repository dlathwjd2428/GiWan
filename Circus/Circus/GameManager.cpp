#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::SetGame(HDC hdc)
{
	BitManager::GetInstance()->Init(hdc);
	m_Char.SetChar();
	m_Map.SetMap(hdc);
}

void GameManager::Draw(HDC hdc)
{
	m_Map.DrawMap(hdc);
	m_Char.Draw(hdc);
}

GameManager::~GameManager()
{
}
