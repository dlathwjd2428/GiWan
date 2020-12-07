#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::SetGame(HDC hdc)
{
	m_iScore = 0;
	BitManager::GetInstance()->Init(hdc);
	m_Char.SetChar();
	m_Map.SetMap(hdc);
	m_Obstacle.SetObstacle();
	m_iClock = clock();
	m_bMessageState = true;
}

void GameManager::UpdateGame()
{
	if (m_bMessageState == true)
	{
		if (clock() - m_iClock >= 50)
		{
			m_Obstacle.UpdateRing();
			m_iClock = clock();
		}
	}
}

void GameManager::Draw(HDC hdc)
{
	m_Map.DrawMap(hdc);
	m_Obstacle.Draw(hdc);
	m_Char.Draw(hdc);
	if (m_Char.GetJumpState() == true)
		m_Obstacle.RightDraw(hdc);
	//점수판표기
	WCHAR buf[256];
	TextAndFont::GetInstance()->ColorSet(hdc, BACK_COLOR, 255, 193, 158);
	TextAndFont::GetInstance()->FontSize(hdc, 60);
	wsprintf(buf, L"Score : %d", m_iScore);
	TextOut(hdc, 350, 170, buf, lstrlen(buf));
	TextAndFont::GetInstance()->Reset(hdc);
}

void GameManager::Move()
{
	int Direction = NULL;
	if (m_Char.GetJumpState() == false)
	{
		
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			m_Obstacle.SetRingSpeed(LOW_SPEED);
			Direction = LEFT;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			Direction = RIGHT;
			m_Obstacle.SetRingSpeed(HIGH_SPEED);
		}
		if (GetKeyState(VK_RETURN) & 0x8000)
			Direction = JUMP;
		m_Map.Move(Direction);
		m_Obstacle.Move(Direction);	
		m_Char.MoveChar(Direction);	
	}
	else
	{
		if (m_Char.Jump() == false)
			m_Map.SetCheer();
		m_Map.JumpMove(m_Char.GetMoveState());
		m_Obstacle.JumpMove(m_Char.GetMoveState());
	}

	if (Direction == NULL)
	{
		m_Obstacle.SetRingSpeed(NORMAL_SPEED);
		m_bMessageState = true;
	}
	else
	{
		m_bMessageState = false;
		//m_Obstacle.SetRingSpeed(HIGH_SPEED);
		m_Obstacle.UpdateRing();
	}
	
}

GameManager::~GameManager()
{
}
