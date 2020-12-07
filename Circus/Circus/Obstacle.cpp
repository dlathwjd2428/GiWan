#include "Obstacle.h"

Obstacle::Obstacle()
{	
}

void Obstacle::SetObstacle()
{
   //불화분 설정
	srand((unsigned)time(NULL));
	m_iRingSpeed = NORMAL_SPEED;
	int RPoint;
	for (int i = 0; i < FIRE_MAX; i++)
	{
		RPoint = rand() % (WIN_SIZE * 10 - (CHAR_PT_X + 100)) + CHAR_PT_X + 100;
		m_arrFire[i].m_iIndex = IMAGE_FIRE1;
		m_arrFire[i].m_Size = { IMAGE_SIZE, IMAGE_SIZE };
		m_arrFire[i].m_Point = { RPoint, CHAR_PT_Y + 50 };
		m_arrFire[i].m_Rect1 = { m_arrFire[i].m_Point.x + 20, m_arrFire[i].m_Point.y + 20, m_arrFire[i].m_Point.x + IMAGE_SIZE - 10, m_arrFire[i].m_Point.y + IMAGE_SIZE  - 10};
		m_arrFire[i].m_Rect2 = { m_arrFire[i].m_Point.x + 10, m_arrFire[i].m_Point.y - IMAGE_SIZE, m_arrFire[i].m_Point.x + IMAGE_SIZE, m_arrFire[i].m_Point.y };
		//중복또는 불가능 위치 생성 제어
		if (i != 0)
		{
			for (int j = 0; j < i; j++)
			{
				if ((RPoint >= m_arrFire[j].m_Point.x - 200) && (RPoint <= m_arrFire[j].m_Point.x + 200))
				{
					i--;
					break;
				}
			}
		}
	}
	//링설정
	for (int i = 0; i < RING_MAX; i++)
	{
		RPoint = rand() % (WIN_SIZE * 9) + WIN_SIZE;
		m_arrRing[i].m_iIndex = IMAGE_ENEMY1;
		m_arrRing[i].m_Size = { IMAGE_SIZE, 270 };
		m_arrRing[i].m_Point = { RPoint, WIN_SIZE / 2 };
		m_arrRing[i].m_Rect1 = { m_arrRing[i].m_Point.x, m_arrRing[i].m_Point.y + 250, m_arrRing[i].m_Point.x + IMAGE_SIZE, m_arrRing[i].m_Point.y + 270 };
		m_arrRing[i].m_Rect2 = { m_arrRing[i].m_Point.x, m_arrRing[i].m_Point.y, m_arrRing[i].m_Point.x + IMAGE_SIZE, m_arrRing[i].m_Point.y + 250 };
		//중복또는 불가능 위치 생성 제어
		if (i != 0)
		{
			for (int j = 0; j < i; j++)
			{
				if ((RPoint >= m_arrRing[j].m_Point.x - 300) && (RPoint <= m_arrRing[j].m_Point.x + 300))
				{
					i--;
					break;
				}
			}
		}
	}
	//골인지점설정
	m_Goal.m_iIndex = IMAGE_GOAL;
	m_Goal.m_Point = { WIN_SIZE * 10, CHAR_PT_Y + 100 };
	m_Goal.m_Rect1 = { m_Goal.m_Point.x, m_Goal.m_Point.y - 50, m_Goal.m_Point.x + m_Goal.m_Point.y };
	m_Goal.m_Size = { IMAGE_SIZE * 2, IMAGE_SIZE / 2 };
}

void Obstacle::UpdateRing()
{
	for (int i = 0; i < RING_MAX; i++)
	{
		m_arrRing[i].m_Point.x -= m_iRingSpeed;
		m_arrRing[i].m_Rect1 = { m_arrRing[i].m_Point.x, m_arrRing[i].m_Point.y + 250, m_arrRing[i].m_Point.x + IMAGE_SIZE, m_arrRing[i].m_Point.y + 270 };
		if (m_arrRing[i].m_Rect2.bottom != 10)
			m_arrRing[i].m_Rect2 = { m_arrRing[i].m_Point.x, m_arrRing[i].m_Point.y, m_arrRing[i].m_Point.x + IMAGE_SIZE, m_arrRing[i].m_Point.y + 250 };
	}
}

void Obstacle::Draw(HDC hdc)
{
	//불화분 그리기
	for (int i = 0; i < FIRE_MAX; i++)
	{
		if (m_arrFire[i].m_iIndex == IMAGE_FIRE1)
			m_arrFire[i].m_iIndex++;
		else
			m_arrFire[i].m_iIndex--;
		BitManager::GetInstance()->Draw(hdc, m_arrFire[i].m_iIndex, m_arrFire[i].m_Point, m_arrFire[i].m_Size);
		
	}
	//링 그리기
	for (int i = 0; i < RING_MAX; i++)
	{
		if(m_arrRing[i].m_iIndex == IMAGE_ENEMY1)
			m_arrRing[i].m_iIndex = IMAGE_ENEMY2;
		else
			m_arrRing[i].m_iIndex = IMAGE_ENEMY1;
		BitManager::GetInstance()->Draw(hdc, m_arrRing[i].m_iIndex, m_arrRing[i].m_Point, m_arrRing[i].m_Size);
	}
	//골인지점그리기
	BitManager::GetInstance()->Draw(hdc, m_Goal.m_iIndex, m_Goal.m_Point, m_Goal.m_Size);
}

void Obstacle::RightDraw(HDC hdc)
{
	int tmpIndex;
	POINT tmpPoint;
	SIZE tmpSize;
	for (int i = 0; i < RING_MAX; i++)
	{
		tmpPoint = { m_arrRing[i].m_Point.x + 50, m_arrRing[i].m_Point.y };
		tmpSize = { m_arrRing[i].m_Size.cx / 2, m_arrRing[i].m_Size.cy };
		if (m_arrRing[i].m_iIndex == IMAGE_ENEMY1)
			tmpIndex = IMAGE_ENEMY1_RIGHT;
		else
			tmpIndex = IMAGE_ENEMY2_RIGHT;
		BitManager::GetInstance()->Draw(hdc, tmpIndex, tmpPoint, tmpSize);
	}
}

void Obstacle::Move(int Direction)
{
	int Add = 0;
	switch (Direction)
	{
	case LEFT:
		Add = 15;
		break;
	case RIGHT:
		Add = -15;		
		break;
	}
	MoveFire(Add);
	m_Goal.m_Point.x += Add;
	m_Goal.m_Rect1 = { m_Goal.m_Point.x, m_Goal.m_Point.y - 50, m_Goal.m_Point.x + m_Goal.m_Point.y };
}

void Obstacle::MoveFire(int Add)
{
	for (int i = 0; i < FIRE_MAX; i++)
	{
		m_arrFire[i].m_Point.x += Add;
		m_arrFire[i].m_Rect1 = { m_arrFire[i].m_Point.x + 20, m_arrFire[i].m_Point.y + 20, m_arrFire[i].m_Point.x + IMAGE_SIZE - 10, m_arrFire[i].m_Point.y + IMAGE_SIZE - 10 };
		if (m_arrFire[i].m_Rect2.bottom != 10)
			m_arrFire[i].m_Rect2 = { m_arrFire[i].m_Point.x, m_arrFire[i].m_Point.y - IMAGE_SIZE, m_arrFire[i].m_Point.x + IMAGE_SIZE, m_arrFire[i].m_Point.y };
	}
}

void Obstacle::JumpMove(bool MoveState)
{
	int Add = 0;
	if (MoveState == true)
	{
		Add = -15;
		m_iRingSpeed = HIGH_SPEED;
	}
	else
		m_iRingSpeed = NORMAL_SPEED;
	m_Goal.m_Point.x += Add;;
	MoveFire(Add);
}

int Obstacle::CollideCheck(RECT CharRect)
{
	RECT tmpRect;
	int Score = 0;
	//죽음확인
	//불화분
	for (int i = 0; i < FIRE_MAX; i++)
	{
		if (IntersectRect(&tmpRect, &m_arrFire[i].m_Rect1, &CharRect) == true)
			return DIE;
	}
	//링
	for (int i = 0; i < RING_MAX; i++)
	{
		if (IntersectRect(&tmpRect, &m_arrRing[i].m_Rect1, &CharRect) == true)
			return DIE;
	}
	//스코어획득확인
	//불화분
	for (int i = 0; i < FIRE_MAX; i++)
	{
		if (IntersectRect(&tmpRect, &m_arrFire[i].m_Rect2, &CharRect) == true)
		{
			Score += FIRE_SCORE;
			m_arrFire[i].m_Rect2 = { 0, 0, 0, 0 };
		}
	}
	//링
	for (int i = 0; i < RING_MAX; i++)
	{
		if (IntersectRect(&tmpRect, &m_arrRing[i].m_Rect2, &CharRect) == true)
		{
			Score += RING_SCORE;
			m_arrRing[i].m_Rect2 = { 0, 0, 10, 10 };
		}
	}
	//승리확인
	if (IntersectRect(&tmpRect, &m_Goal.m_Rect1, &CharRect) == true)
		return WIN;
	return Score;
}

Obstacle::~Obstacle()
{
}