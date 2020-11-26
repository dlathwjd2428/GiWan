#pragma once
#include"BitMapManager.h"

class Obstacle
{
private:
	int m_iRingMoveSpeed;
	MyIMG m_arrRing[RING_MAX];
	MyIMG m_arrFire[FIRE_MAX];
public:
	void SetObstacle();
	void DrawRing(HDC hdc);
	void Move(int Direction);
	void MoveRing(int Direction);
	Obstacle();
	~Obstacle();
};

