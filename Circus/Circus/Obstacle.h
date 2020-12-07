#pragma once
#include"BitManager.h"

class Obstacle
{
private:
	int m_iRingSpeed;
	MyIMG m_arrRing[OB_MAX];
	MyIMG m_arrFire[OB_MAX];
	MyIMG m_Goal;
public:
	void SetObstacle();
	void UpdateRing();
	void Draw(HDC hdc);
	void RightDraw(HDC hdc);
	void Move(int Direction);
	void MoveFire(int Add);
	void JumpMove(bool MoveState);
	inline void SetRingSpeed(int Speed) { m_iRingSpeed = Speed; }
	Obstacle();
	~Obstacle();
};

