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
	m_iClock = clock();
}

void GameManager::UpdateGame(HWND hWnd)
{
	if (clock() - m_iClock > CREATE_SPEED)
	{
		m_Obstacle.CreateRing();
		m_Obstacle.Update();
		m_iClock = clock() + CREATE_SPEED;
	}
}

void GameManager::Draw(HDC hdc)
{
	m_Map.Draw(hdc);
	m_Obstacle.Draw(hdc);
	m_Character.Draw(hdc);
	if(m_Character.GetJumpState() == true)
		//우측편 그리기
}

void GameManager::Move()
{
	m_Obstacle.SetRingSpeed();
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
	if ((GetKeyState(VK_RETURN) & 0x8000) && m_Character.GetJumpState() == false)
		m_Character.Jump();
	if (m_Character.GetJumpState() == true)
		m_Character.Jump();
}
GameManager::~GameManager()
{
}