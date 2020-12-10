#include "GameManager.h"

GameManager::GameManager()
{
	srand((unsigned)time(NULL));
}

void GameManager::LoadingGame(HDC hdc)
{
	ResManager::GetInstance()->InitBitMap(hdc);
	m_arrObstacle = new Goal;
	m_arrObstacle->SetObstacle();
	m_iDirection = NULL;
	m_Char.SetChar();
	m_Map.SetMap();
	m_iClock = clock();
}

void GameManager::UpdateGame(HDC hdc)
{
	if (clock() - m_iClock >= 50)
	{
		m_Char.Move(m_iDirection);
		m_Map.Move(m_iDirection);
		m_arrObstacle->Draw(hdc);
		m_Map.Draw(hdc);
		m_Char.Draw(hdc);
		m_iClock = clock();
	}
}

void GameManager::Move()
{
	m_iDirection = NULL;
	if (GetKeyState(VK_LEFT) & 0x8000)
		m_iDirection = LEFT;
	if (GetKeyState(VK_RIGHT) & 0x8000)
		m_iDirection = RIGHT;
	if (GetKeyState(VK_SPACE) & 0x8000)
		m_iDirection = JUMP;

}

GameManager::~GameManager()
{
}
