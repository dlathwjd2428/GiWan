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
		
		for (int j = 0; j < i; j++)
		{
			if ((Rpoint >= m_arrFire[i].m_Point.x - 300) && (Rpoint <= m_arrFire[i].m_Point.x + 500))
			{
				Check = false;
				i--;
				break;
			}
		}
		if (Check == true)
		{
			m_arrFire[i].m_iIndex = IMAGE_FIRE1;
			m_arrFire[i].m_Point = { Rpoint, WIN_Y - 180 };
			m_arrFire[i].m_Size = { 80, 80 };
			m_arrFire[i].m_Rect = { m_arrFire[i].m_Point.x + 10, m_arrFire[i].m_Point.y + 20, m_arrFire[i].m_Point.x + m_arrFire[i].m_Size.cx - 10, m_arrFire[i].m_Point.y + m_arrFire[i].m_Size.cy };
		}
	}
	//골인지점설정
	m_Goal.m_iIndex = IMAGE_GOAL;
	m_Goal.m_Point = { WIN_X * 20, POINT_Y };
	m_Goal.m_Size = { 200, 100 };
	m_Goal.m_Rect = { m_Goal.m_Point.x, m_Goal.m_Point.y, m_Goal.m_Point.x + m_Goal.m_Size.cx, m_Goal.m_Point.y + m_Goal.m_Size.cy };
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
		tmp.m_Size = { 80, 200 };
		tmp.m_Rect = { tmp.m_Point.x + 10, tmp.m_Point.y, tmp.m_Point.x + 70, tmp.m_Point.y + 20 };
		tmp.m_Rect2 = { tmp.m_Point.x + 30, tmp.m_Point.y + 180, tmp.m_Point.x + 50, tmp.m_Point.y + 200 };
		m_vRing.push_back(tmp);
	}
}

void Obstacle::Update(int Option)
{
	for (auto iter = m_vRing.begin(); iter != m_vRing.end(); iter++)
	{
		iter->m_Point.x -= Option;
		iter->m_Rect = { iter->m_Point.x, iter->m_Point.y, iter->m_Point.x + 80, iter->m_Point.y + 20 };
		iter->m_Rect2 = { iter->m_Point.x + 30, iter->m_Point.y + 180, iter->m_Point.x + 50, iter->m_Point.y + 200 };
		if (iter->m_Point.x < -80)
		{
			iter = m_vRing.erase(iter);
			break;
		}			
	}
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
	//골인지점그리기
	BitManager::GetInstance()->Draw(hdc, m_Goal.m_iIndex, m_Goal.m_Point, m_Goal.m_Size);
}

void Obstacle::RightDraw(HDC hdc)
{
	for (int i = 0; i < m_vRing.size(); i++)
	{
		m_RightRing.m_iIndex = m_vRing[i].m_iIndex + 2;
		m_RightRing.m_Point = { m_vRing[i].m_Point.x + 40, WIN_Y / 2 };
		m_RightRing.m_Size = { 40, 200 };
		BitManager::GetInstance()->Draw(hdc, m_RightRing.m_iIndex, m_RightRing.m_Point, m_RightRing.m_Size);
	}
}

void Obstacle::Move(int Direction)
{
	//불화분움직이기
	int Add;
	if (Direction == LEFT)
	{
		Add = 10;
		m_iRingSpeed = BACK_SPEED;
	}
	else
	{
		Add = -20;
		m_iRingSpeed = FRONT_SPEED;
	}
	for (int i = 0; i < FIRE_MAX; i++)
	{
		m_arrFire[i].m_Point.x += Add;
		m_arrFire[i].m_Rect = { m_arrFire[i].m_Point.x + 10, m_arrFire[i].m_Point.y + 20, m_arrFire[i].m_Point.x + m_arrFire[i].m_Size.cx - 10, m_arrFire[i].m_Point.y + m_arrFire[i].m_Size.cy };
	}
	//골인지점움직이기
	m_Goal.m_Point.x += Add;
	m_Goal.m_Rect = { m_Goal.m_Point.x, m_Goal.m_Point.y, m_Goal.m_Point.x + m_Goal.m_Size.cx, m_Goal.m_Point.y + m_Goal.m_Size.cy };
	//링생성 및 제어
	CreateRing();
	Update(m_iRingSpeed);
}

int Obstacle::CollideCheck(RECT CharRect)
{
	RECT tmpRect;
	//불화분충돌체크
	for (int i = 0; i < MITER_MAX; i++)
	{
		if (IntersectRect(&tmpRect, &m_arrFire[i].m_Rect, &CharRect) == true)
			return DIE;
	}
	//링충돌체크
	for (int i = 0; i < m_vRing.size(); i++)
	{
		if (IntersectRect(&tmpRect, &m_vRing[i].m_Rect, &CharRect) == true || IntersectRect(&tmpRect, &m_vRing[i].m_Rect2, &CharRect) == true)
			return DIE;
	}
	//골인지점충돌체크
	if (IntersectRect(&tmpRect, &m_Goal.m_Rect, &CharRect) == true)
		return WIN;
	return NONE;
}

void Obstacle::DeleteRing()
{
	while (!m_vRing.empty())
	{
		m_vRing.pop_back();
	}
}

Obstacle::~Obstacle()
{
}