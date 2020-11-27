#pragma once
#include"BitManager.h"

class Obstacle
{
private:
	MyIMG m_arrFire[FIRE_MAX];
public:
	void SetObstacle();
	void Draw(HDC hdc);
	void Move(int Direction);
	Obstacle();
	~Obstacle();
};

