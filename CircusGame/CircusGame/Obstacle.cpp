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
	//링스피드설정
	m_iRingSpeed = DEFAULT_SPEED;
}

void Obstacle::CreateRing()
{
	int RNum;
	MyIMG tmp;
	RNum = rand() % 100 + 1;
	if (RNum < 5 && m_vRing.size() <= 3)
	{
		tmp.m_iIndex = IMAGE_ENEMY1;
		tmp.m_Point = { WIN_X + 200, WIN_Y / 2 };
		tmp.m_Size = { 100, 200 };
		m_vRing.push_back(tmp);
	}
}

void Obstacle::Update()
{
	for (int i = 0; i < m_vRing.size(); i++)
		m_vRing[i].m_Point.x -= m_iRingSpeed;
}

void Obstacle::Draw(HDC hdc)
{
	//불화분그리기
	for (int i = 0; i < FIRE_MAX; i++)
	{
		BitManager::GetInstance()->Draw(hdc, m_arrFire[i].m_iIndex, m_arrFire[i].m_Point, m_arrFire[i].m_Size);
		if (m_arrFire[i].m_iIndex == IMAGE_FIRE1)
			m_arrFire[i].m_iIndex++;
		else
			m_arrFire[i].m_iIndex--;
	}
	//링그리기
	for (int i = 0; i < m_vRing.size(); i++)
	{
		BitManager::GetInstance()->Draw(hdc, m_vRing[i].m_iIndex, m_vRing[i].m_Point, m_vRing[i].m_Size);
	}
}

void Obstacle::Move(int Direction)
{
	//불화분움직이기
	switch (Direction)
	{
	case LEFT:
		for (int i = 0; i < FIRE_MAX; i++)
			m_arrFire[i].m_Point.x += 10;
		m_iRingSpeed = BACK_SPEED;
		break;
	case RIGHT:
		for (int i = 0; i < FIRE_MAX; i++)
			m_arrFire[i].m_Point.x -= 10;
		m_iRingSpeed = FRONT_SPEED;
		break;
	}
}

Obstacle::~Obstacle()
{
}