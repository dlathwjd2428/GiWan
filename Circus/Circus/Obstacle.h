#pragma once
#include"BitMapManager.h"

class Obstacle
{
private:
	int m_iRingMoveSpeed;
	MyIMG m_arrRing[RING_MAX];
public:
	void SetObstacle();
	void DrawRing(HDC hdc);
	void SetRingSpeed(int Direction);
	void Move(int Direction);
	Obstacle();
	~Obstacle();
};

