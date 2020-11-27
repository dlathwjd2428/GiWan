#include "Obstacle.h"

Obstacle::Obstacle()
{
	srand((unsigned)time(NULL));
}

void Obstacle::SetObstacle()
{
	//불화분설정
	int Rpoint;
	bool Check;
	for (int i = 0; i < FIRE_MAX; i++)
	{
		Check = true;
		Rpoint = rand() % (WIN_X * 10 - POINT_X) + POINT_X;
		if (i != 0)
		{
			for (int j = 0; j < i; j++)
			{
				if ((Rpoint >= m_arrFire[j].m_Point.x - 200) && (Rpoint <= m_arrFire[i].m_Point.x + 200))
				{
					Check = false;
					i--;
					break;
				}
			}
		}
		if (Check == true)
		{
			m_arrFire[i].m_iIndex = IMAGE_FIRE1;
			m_arrFire[i].m_Point = { Rpoint, WIN_Y - 200 };
			m_arrFire[i].m_Size = { 100, 100 };
		}
	}
}

void Obstacle::Draw(HDC hdc)
{
	for (int i = 0; i < FIRE_MAX; i++)
	{
		BitManager::GetInstance()->Draw(hdc, m_arrFire[i].m_iIndex, m_arrFire[i].m_Point, m_arrFire[i].m_Size);
		if (m_arrFire[i].m_iIndex == IMAGE_FIRE1)
			m_arrFire[i].m_iIndex++;
		else
			m_arrFire[i].m_iIndex--;
	}
}

void Obstacle::Move(int Direction)
{
	for (int i = 0; i < FIRE_MAX; i++)
	{
		if (Direction == RIGHT)
			m_arrFire[i].m_Point.x -= 10;
		else
			m_arrFire[i].m_Point.x += 10;
	}
}

Obstacle::~Obstacle()
{
}