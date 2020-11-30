#pragma once
#include"BitManager.h"

class Obstacle
{
private:
	int m_iRingSpeed;
	MyIMG m_arrFire[FIRE_MAX];
	MyIMG m_RightRing;
	MyIMG m_Goal;
	std::vector<MyIMG> m_vRing;
public:
	void SetObstacle();
	void CreateRing();
	void Update(int Option = DEFAULT_SPEED);
	void Draw(HDC hdc);
	void RightDraw(HDC hdc);
	void Move(int Direction);
	int CollideCheck(RECT CharRect);
	void DeleteRing();
	inline void SetRingSpeed() { m_iRingSpeed = DEFAULT_SPEED; }
	Obstacle();
	~Obstacle();
};

