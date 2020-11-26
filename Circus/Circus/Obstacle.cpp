#include "Obstacle.h"

Obstacle::Obstacle()
{
}

void Obstacle::SetObstacle()
{
	for (int i = 0; i < RING_MAX; i++)
	{
		m_arrRing[i].m_iIndex = IMAGE_ENEMY;
		m_arrRing->m_iPoint = { WIN_X - 300, WIN_Y / 2 };
		m_arrRing[i].m_iSize = { 60, 250 };
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
}

void Obstacle::SetRingSpeed(int Direction)
{
	if (m_arrRing[0].m_iPoint.x <= 0)
		m_arrRing[0].m_iPoint.x = WIN_X;
	if (Direction == RIGHT)
		m_iRingMoveSpeed = 20;
	else if (Direction == LEFT)
		m_iRingMoveSpeed = -5;
	else
		m_iRingMoveSpeed = 10;
}

void Obstacle::Move(int Direction)
{
	m_arrRing[0].m_iPoint.x -= m_iRingMoveSpeed;
}

Obstacle::~Obstacle()
{
}