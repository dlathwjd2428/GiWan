#pragma once
#include"ResManager.h"

//�θ�
class Obstacles
{
protected:
public:
	virtual void SetObstacle() = 0;
	virtual void Draw(HDC hdc) = 0;
	Obstacles();
	~Obstacles();
};

//�Ҹ�
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
//�Ҹ�

//��ȭ��
class FirePot : public Obstacles
{
private:
public:
	void SetObstacle();
	void Draw(HDC hdc);
	FirePot();
	~FirePot();
};
//��ȭ��

//��������
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
//��������