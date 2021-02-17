#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

//Lane
Lane::Lane()
{
}

void Lane::SetObject(HDC hdc)
{
	m_Lane.m_iIndex = IMAGE_LANE;
	m_Lane.m_Point = { 0, WIN_SIZE / 2 };
	m_Lane.m_Size = { WIN_SIZE, WIN_SIZE / 2 };
}

void Lane::Draw(HDC hdc)
{
	Res_MG::GetInstance()->Draw(hdc, m_Lane.m_iIndex, m_Lane.m_Point, m_Lane.m_Size);
}

void Lane::Move(int Direction)
{

}

int Lane::CollideCheck(RECT CharRect)
{
	return 0;
}

Lane::~Lane()
{
}
//Lane

//People
People::People()
{
}

void People::SetObject(HDC hdc)
{
	//그림합치기
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBit = CreateCompatibleBitmap(hdc, WIN_SIZE * 2 + 100, 100);
	m_hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBit);
	int tmpIndex;
	POINT tmpPoint = { 0, 0 };
	SIZE tmpSize = { 100, 100 };
	for (int i = 0; i < 21; i++)
	{
		if (i == 10)
			tmpIndex = IMAGE_DECO;
		else
			tmpIndex = IMAGE_PEOPLE1;
		tmpPoint = { 100 * i, 0 };
		Res_MG::GetInstance()->Draw(m_hMemDC, tmpIndex, tmpPoint, tmpSize);
	}
	//그림정보들설정
	m_arrInfo.m_Point = { -100, WIN_SIZE / 2 - 100 };
	m_arrInfo.m_Size = { WIN_SIZE * 2 + 100, 100 };
}

void People::Draw(HDC hdc)
{
	BitBlt(hdc, m_arrInfo.m_Point.x, m_arrInfo.m_Point.y, m_arrInfo.m_Size.cx, m_arrInfo.m_Size.cy, m_hMemDC, 0, 0, SRCCOPY);
}

void People::Move(int Direction)
{
	m_arrInfo.m_Point.x += Direction;
	if (m_arrInfo.m_Point.x == 0)
		m_arrInfo.m_Point.x = -1100;
	else if (m_arrInfo.m_Point.x < -1110)
		m_arrInfo.m_Point.x = -10;
}

int People::CollideCheck(RECT CharRect)
{
	return 0;
}

People::~People()
{
}
//People

//Miter
Miter::Miter()
{
}

void Miter::SetObject(HDC hdc)
{
	POINT tmpPoint;
	SIZE tmpSize = { 80, 50 };
	for (int i = 0; i < MAX; i++)
	{
		tmpPoint = { 100 + WIN_SIZE * i, WIN_SIZE - 50 };
		m_arrMiter[i].m_iIndex = IMAGE_MITER;
		m_arrMiter[i].m_Point = tmpPoint;
		m_arrMiter[i].m_Size = tmpSize;
		m_arrMiter[i].m_Rect1 = { m_arrMiter[i].m_Point.x, m_arrMiter[i].m_Point.y,
		m_arrMiter[i].m_Point.x + m_arrMiter[i].m_Size.cx, m_arrMiter[i].m_Point.y + m_arrMiter[i].m_Size.cy };
		m_arrMiter[i].m_Rect2 = { m_arrMiter[i].m_Point.x, m_arrMiter[i].m_Point.y - 200,
		m_arrMiter[i].m_Point.x + m_arrMiter[i].m_Size.cx, m_arrMiter[i].m_Point.y };
	}
}

void Miter::Draw(HDC hdc)
{
	WCHAR buf[256];
	for (int i = 0; i < MAX; i++)
	{
		if (m_arrMiter[i].m_Point.x >= -100 && m_arrMiter[i].m_Point.x <= WIN_SIZE)
		{
			wsprintf(buf, L"%d", (i + 1) * 100);
			Res_MG::GetInstance()->Draw(hdc, m_arrMiter[i].m_iIndex, m_arrMiter[i].m_Point, m_arrMiter[i].m_Size);
			Font_Back_MG::GetInstance()->FontColorSet(hdc, 204, 166, 61);
			Font_Back_MG::GetInstance()->FontSizeSet(hdc, 20);
			TextOut(hdc, m_arrMiter[i].m_Point.x + 15, m_arrMiter[i].m_Point.y + 15, buf, lstrlen(buf));
			Font_Back_MG::GetInstance()->Reset(hdc);
		}
	}
}

void Miter::Move(int Direction)
{
	for (int i = 0; i < MAX; i++)
		m_arrMiter[i].m_Point.x += Direction;
}

int Miter::CollideCheck(RECT CharRect)
{

	return 0;
}

Miter::~Miter()
{
}
//Miter

//Goal
Goal::Goal()
{
}

void Goal::SetObject(HDC hdc)
{
	m_Goal.m_iIndex = IMAGE_GOAL;
	m_Goal.m_Point = { WIN_SIZE * 10, WIN_SIZE - 130 };
	m_Goal.m_Size = { 100, 80 };
	m_Goal.m_Rect1 = { m_Goal.m_Point.x, m_Goal.m_Point.y,
	m_Goal.m_Point.x + m_Goal.m_Size.cx, m_Goal.m_Point.y + m_Goal.m_Size.cy };
}

void Goal::Draw(HDC hdc)
{
	if (m_Goal.m_Point.x >= 100 && m_Goal.m_Point.x <= WIN_SIZE)
		Res_MG::GetInstance()->Draw(hdc, m_Goal.m_iIndex, m_Goal.m_Point, m_Goal.m_Size);
}

void Goal::Move(int Direction)
{
	m_Goal.m_Point.x += Direction;
	m_Goal.m_Rect1 = { m_Goal.m_Point.x, m_Goal.m_Point.y,
	m_Goal.m_Point.x + m_Goal.m_Size.cx, m_Goal.m_Point.y + m_Goal.m_Size.cy };
}

int Goal::CollideCheck(RECT CharRect)
{
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &m_Goal.m_Rect1, &CharRect))
		return WIN;
}

Goal::~Goal()
{
}
//Goal

//FirePot
FirePot::FirePot()
{
}

void FirePot::SetObject(HDC hdc)
{
	int RPoint = NULL;;
	bool Check = true;
	for (int i = 0; i < MAX;)
	{
		Check = true;
		RPoint = rand() % (WIN_SIZE * 10 - 200) + 200;
		for (int j = 0; j < i; j++)
		{		
			if (RPoint >= m_arrFirePot[j].m_Point.x - 300 && RPoint <= m_arrFirePot[j].m_Point.x + 500)
			{
				Check = false;
				break;
			}
		}
		if (Check == true)
		{
			m_arrFirePot[i].m_iIndex = IMAGE_FIREPOT1;
			m_arrFirePot[i].m_Point = { RPoint, WIN_SIZE - 130 };
			m_arrFirePot[i].m_Size = { 80, 80 };
			m_arrFirePot[i].m_Rect1 = { m_arrFirePot[i].m_Point.x + 20, m_arrFirePot[i].m_Point.y + 10,
			m_arrFirePot[i].m_Point.x + m_arrFirePot[i].m_Size.cx - 20, m_arrFirePot[i].m_Point.y + m_arrFirePot[i].m_Size.cy };
			m_arrFirePot[i].m_Rect2 = { m_arrFirePot[i].m_Point.x, m_arrFirePot[i].m_Point.y - 200,
			m_arrFirePot[i].m_Point.x + m_arrFirePot[i].m_Size.cx, m_arrFirePot[i].m_Point.y };
			i++;
		}
	}
}

void FirePot::Draw(HDC hdc)
{
	for (int i = 0; i < MAX; i++)
	{
		if (m_arrFirePot[i].m_Point.x >= -100 && m_arrFirePot[i].m_Point.x <= WIN_SIZE)
			Res_MG::GetInstance()->Draw(hdc, m_arrFirePot[i].m_iIndex, m_arrFirePot[i].m_Point, m_arrFirePot[i].m_Size);
	}
}

void FirePot::Move(int Direction)
{
	for (int i = 0; i < MAX; i++)
	{
		m_arrFirePot[i].m_Point.x += Direction;
		m_arrFirePot[i].m_Rect1 = { m_arrFirePot[i].m_Point.x + 20, m_arrFirePot[i].m_Point.y + 10,
			m_arrFirePot[i].m_Point.x + m_arrFirePot[i].m_Size.cx - 20, m_arrFirePot[i].m_Point.y + m_arrFirePot[i].m_Size.cy };
		if (m_arrFirePot[i].m_Rect2.left != 0)
		{
			m_arrFirePot[i].m_Rect2 = { m_arrFirePot[i].m_Point.x, m_arrFirePot[i].m_Point.y - 200,
			m_arrFirePot[i].m_Point.x + m_arrFirePot[i].m_Size.cx, m_arrFirePot[i].m_Point.y };
		}
	}
}

int FirePot::CollideCheck(RECT CharRect)
{
	RECT tmpRect;
	for (int i = 0; i < MAX; i++)
	{
		if (IntersectRect(&tmpRect, &m_arrFirePot[i].m_Rect1, &CharRect))
			return DIE;
		if (IntersectRect(&tmpRect, &m_arrFirePot[i].m_Rect2, &CharRect))
		{
			m_arrFirePot[i].m_Rect2 = { 0, 0, 100, 100 };
			return 1000;
		}
	}
	return 0;
}

FirePot::~FirePot()
{
}
//FirePot

//Ring
Ring::Ring()
{
}

void Ring::SetObject(HDC hdc)
{
	int RPoint = NULL;;
	bool Check = true;
	for (int i = 0; i < MAX;)
	{
		Check = true;
		RPoint = rand() % (WIN_SIZE * 10) + WIN_SIZE;
		for (int j = 0; j < i; j++)
		{
			if (RPoint >= m_arrRing[j].m_Point.x - 300 && RPoint <= m_arrRing[j].m_Point.x + 500)
			{
				Check = false;
				break;
			}
		}
		if (Check == true)
		{
			m_arrRing[i].m_iIndex = IMAGE_RING1;
			m_arrRing[i].m_Point = { RPoint, WIN_SIZE / 2 };
			m_arrRing[i].m_Size = { 100, 300 };
			m_arrRing[i].m_Rect1 = { m_arrRing[i].m_Point.x + 20, m_arrRing[i].m_Point.y + m_arrRing[i].m_Size.cy - 50,
			m_arrRing[i].m_Point.x + m_arrRing[i].m_Size.cx - 20, m_arrRing[i].m_Point.y + m_arrRing[i].m_Size.cy };
			m_arrRing[i].m_Rect2 = { m_arrRing[i].m_Point.x, m_arrRing[i].m_Point.y,
			m_arrRing[i].m_Point.x + m_arrRing[i].m_Size.cx, m_arrRing[i].m_Point.y + m_arrRing[i].m_Size.cy - 50 };
			i++;
		}
	}
}

void Ring::Draw(HDC hdc)
{
	for (int i = 0; i < MAX; i++)
	{
		if (m_arrRing[i].m_Point.x >= -100 && m_arrRing[i].m_Point.x <= WIN_SIZE)
			Res_MG::GetInstance()->Draw(hdc, m_arrRing[i].m_iIndex, m_arrRing[i].m_Point, m_arrRing[i].m_Size);
	}
}

void Ring::Move(int Direction)
{
	int Speed;
	int RPoint;
	bool Check = true;
	if (Direction == LEFT)
		Speed = -5;
	else if (Direction == RIGHT)
		Speed = -20;
	else
		Speed = -10;
	for (int i = 0; i < MAX; i++)
	{
		m_arrRing[i].m_Point.x += Speed;
		if (m_arrRing[i].m_Point.x <= -200)
		{
			while (true)
			{
				Check = true;
				RPoint = rand() % (WIN_SIZE * 10) + WIN_SIZE;
				for (int j = 0; j < MAX; j++)
				{	
					if (j != i)
					{
						if (RPoint >= m_arrRing[j].m_Point.x - 300 && RPoint <= m_arrRing[j].m_Point.x + 500)
						{
							Check = false;
							break;
						}
					}
				}
				if (Check == true)
				{
					m_arrRing[i].m_Point = { RPoint, WIN_SIZE / 2 };
					break;
				}
			}
		}
		m_arrRing[i].m_Rect1 = { m_arrRing[i].m_Point.x + 20, m_arrRing[i].m_Point.y + m_arrRing[i].m_Size.cy - 50,
		   m_arrRing[i].m_Point.x + m_arrRing[i].m_Size.cx - 20, m_arrRing[i].m_Point.y + m_arrRing[i].m_Size.cy };
		if (m_arrRing[i].m_Rect2.left != 0)
		{
			m_arrRing[i].m_Rect2 = { m_arrRing[i].m_Point.x, m_arrRing[i].m_Point.y,
			m_arrRing[i].m_Point.x + m_arrRing[i].m_Size.cx, m_arrRing[i].m_Point.y + m_arrRing[i].m_Size.cy - 50 };
		}
	}
}

int Ring::CollideCheck(RECT CharRect)
{
	RECT tmpRect;
	for (int i = 0; i < MAX; i++)
	{
		if (IntersectRect(&tmpRect, &m_arrRing[i].m_Rect1, &CharRect))
			return DIE;
		if (IntersectRect(&tmpRect, &m_arrRing[i].m_Rect2, &CharRect))
		{
			m_arrRing[i].m_Rect2 = { 0, 0, 100, 100 };
			return 1000;
		}
	}
	return 0;
}

Ring::~Ring()
{
}
//Ring