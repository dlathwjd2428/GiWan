#include "Obstacles.h"

//�θ�
Obstacles::Obstacles()
{
}

Obstacles::~Obstacles()
{
}
//�θ�

//�ڽ�
//�Ҹ�
FireRing::FireRing()
{
}

void FireRing::SetObstacle()
{
	int RNum;
	for (int i = 0; i < RING_MAX; i++)
	{
		RNum = rand() % 100 + 1;
	}
}

void FireRing::Draw(HDC hdc)
{

}

FireRing::~FireRing()
{
}
//�Ҹ�

//��ȭ��
FirePot::FirePot()
{
}

void FirePot::SetObstacle()
{
	int RNum;
	for (int i = 0; i < RING_MAX; i++)
	{
		RNum = rand() % 100 + 1;
	}
}

void FirePot::Draw(HDC hdc)
{

}

FirePot::~FirePot()
{
}
//��ȭ��

//����
Goal::Goal()
{
}

void Goal::SetObstacle()
{
	m_Goal.m_iIndex = IMAGE_GOAL;
	m_Goal.m_Point = { WIN_SIZE * 1, WIN_SIZE - 200 };
	m_Goal.m_Size = { 200, 100 };
	m_Goal.m_Rect1 = { m_Goal.m_Point.x, m_Goal.m_Point.y, m_Goal.m_Point.x + 200, m_Goal.m_Point.y + 100 };
}

void Goal::Draw(HDC hdc)
{
	if (m_Goal.m_Point.x <= WIN_SIZE)
		ResManager::GetInstance()->DrawBitMap(hdc, m_Goal.m_iIndex, m_Goal.m_Point, m_Goal.m_Size);
}

Goal::~Goal()
{
}
//����
//�ڽ�