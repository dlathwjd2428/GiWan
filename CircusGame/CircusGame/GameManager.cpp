#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::SetGame(HDC hdc)
{
	BitManager::GetInstance()->Init(hdc);
	m_Map.SetMap(hdc);
	m_Character.SetCharacter();
	m_Obstacle.SetObstacle();
}

void GameManager::Draw(HDC hdc)
{
	m_Map.Draw(hdc);
	m_Character.Draw(hdc);
	m_Obstacle.Draw(hdc);
}

void GameManager::Move()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_Map.Move(LEFT);
		m_Character.Move();
		m_Obstacle.Move(LEFT);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_Map.Move(RIGHT);
		m_Character.Move();
		m_Obstacle.Move(RIGHT);
	}
	
}
GameManager::~GameManager()
{
}