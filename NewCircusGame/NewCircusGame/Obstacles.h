#pragma once
#include"ResManager.h"

//�θ�
class Obstacles
{
public:
	Obstacles();
	~Obstacles();
};

//�Ҹ�
class FireRing : public Obstacles
{
private:
public:
	FireRing();
	~FireRing();
};
//�Ҹ�

//��ȭ��
class FirePot : public Obstacles
{
private:
public:
	FirePot();
	~FirePot();
};
//��ȭ��

//��������
class Goal : public Obstacles
{
private:
public:
	Goal();
	~Goal();
};
//��������