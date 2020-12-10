#pragma once
#include"ResManager.h"

//부모
class Obstacles
{
protected:
public:
	virtual void SetObstacle() = 0;
	virtual void Draw(HDC hdc) = 0;
	Obstacles();
	~Obstacles();
};

//불링
class FireRing : public Obstacles
{
private:
	MyIMG m_arrFRing[RING_MAX];
public:
	void SetObstacle();
	void Draw(HDC hdc);
	FireRing();
	~FireRing();
};
//불링

//불화분
class FirePot : public Obstacles
{
private:
public:
	void SetObstacle();
	void Draw(HDC hdc);
	FirePot();
	~FirePot();
};
//불화분

//골인지점
class Goal : public Obstacles
{
private:
	MyIMG m_Goal;
public:
	void SetObstacle();
	void Draw(HDC hdc);
	Goal();
	~Goal();
};
//골인지점