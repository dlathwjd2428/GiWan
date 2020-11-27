#pragma once
#include"BitManager.h"

class Obstacle
{
private:
	int m_iRingSpeed;
	MyIMG m_arrFire[FIRE_MAX];
	std::vector<MyIMG> m_vRing;
public:
	void SetObstacle();
	void CreateRing();
	void Update();
	void Draw(HDC hdc);
	void Move(int Direction);
	inline void SetRingSpeed() { m_iRingSpeed = DEFAULT_SPEED; }
	Obstacle();
	~Obstacle();
};

