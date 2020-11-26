#include "Obstacle.h"

Obstacle::Obstacle()
{
}

void Obstacle::SetObstacle()
{
	int RNum;
	for (int i = 0; i < FIRE_MAX; i++)
	{
		m_arrFire[i].m_iIndex = IMAGE_FIRE1;
		RNum = rand() % WIN_X * 10 + 1;
		m_arrFire[i].m_iPoint = { RNum, WIN_Y - 180 };
		m_arrFire[i].m_iSize = { 80, 80 };
		for (int j = 0; j < i - 1; j++)
		{
			if (RNum == m_arrFire[j].m_iPoint.x || RNum > WIN_X * 10)
			{
				i--;
				break;
			}
		}
	}
	for (int i = 0; i < RING_MAX; i++)
	{
		m_arrRing[i].m_iIndex = IMAGE_ENEMY;
		m_arrRing->m_iPoint = { WIN_X - 300, WIN_Y / 2 };
		m_arrRing[i].m_iSize = { 60, 200 };
	}
	m_iRingMoveSpeed = 10;
}

void Obstacle::DrawRing(HDC hdc)
{
	BitMapManager::GetInstance()->Draw(hdc, m_arrRing[0].m_iIndex, m_arrRing[0].m_iPoint, m_arrRing[0].m_iSize);
	if (m_arrRing[0].m_iIndex == IMAGE_ENEMY)
		m_arrRing[0].m_iIndex = IMAGE_ENEMY1;
	else
		m_arrRing[0].m_iIndex = IMAGE_ENEMY;
	for (int i = 0; i < FIRE_MAX; i++)
	{
		BitMapManager::GetInstance()->Draw(hdc, m_arrFire[i].m_iIndex, m_arrFire[i].m_iPoint, m_arrFire[i].m_iSize);
		if (m_arrFire[i].m_iIndex == IMAGE_FIRE1)
			m_arrFire[i].m_iIndex++;
		else
			m_arrFire[i].m_iIndex--;
	}
}

void Obstacle::Move(int Direction)
{
	if (m_arrRing[0].m_iPoint.x <= 0)
		m_arrRing[0].m_iPoint.x = WIN_X;
	if (Direction == RIGHT)
	{
		m_iRingMoveSpeed = 20;
		for (int i = 0; i < FIRE_MAX; i++)
			m_arrFire[i].m_iPoint.x -= 10;
	}
	else if (Direction == LEFT)
	{
		m_iRingMoveSpeed = -5;
		for (int i = 0; i < FIRE_MAX; i++)
			m_arrFire[i].m_iPoint.x += 10;
	}
	else
		m_iRingMoveSpeed = 10;
}

void Obstacle::MoveRing(int Direction)
{
	m_arrRing[0].m_iPoint.x -= m_iRingMoveSpeed;
	
}

Obstacle::~Obstacle()
{
}