#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::LoadingGame(HWND hWnd)
{
	m_Map.SetMapInfo();
	m_Char.SetChar();
	BitMapManager::GetInstance()->Init(hWnd);
}

void GameManager::Draw(HDC hdc)
{
	m_Map.DrawMap(hdc);
	m_Char.Draw(hdc);
}

void GameManager::Move()
{
	if (GetKeyState(VK_LEFT) & 0x8000)
		m_Char.Move(LEFT);
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_Char.Move(RIGHT);
		m_Map.Move();
	}
	if (GetKeyState(VK_RETURN) & 0x8000)
		m_Char.Move(JUMP);
}

void GameManager::Update()
{
	//m_Map.MoveBack();
}
GameManager::~GameManager()
{
}
