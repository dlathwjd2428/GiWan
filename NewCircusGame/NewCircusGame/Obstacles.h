#pragma once
#include"ResManager.h"

//부모
class Obstacles
{
public:
	Obstacles();
	~Obstacles();
};

//불링
class FireRing : public Obstacles
{
private:
public:
	FireRing();
	~FireRing();
};
//불링

//불화분
class FirePot : public Obstacles
{
private:
public:
	FirePot();
	~FirePot();
};
//불화분

//골인지점
class Goal : public Obstacles
{
private:
public:
	Goal();
	~Goal();
};
//골인지점