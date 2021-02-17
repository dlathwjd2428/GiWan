#include"Res_MG.h"

class Object
{
public:
	virtual void SetObject(HDC hdc) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Move(int Direction) = 0;
	virtual int CollideCheck(RECT CharRect) = 0;
	Object();
	~Object();
};

//Lane
class Lane : public Object
{
private:
	MyIMG m_Lane;
public:
	void SetObject(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	int CollideCheck(RECT CharRect);
	Lane();
	~Lane();
};
//Lane

//People
class People : public Object
{
private:
	HDC m_hMemDC;
	HBITMAP m_hBit, m_hOld;
	MyIMG m_arrInfo;
public:
	void SetObject(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	int CollideCheck(RECT CharRect);
	People();
	~People();
};
//People

//Miter
class Miter : public Object
{
private:
	MyIMG m_arrMiter[MAX];
public:
	void SetObject(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	int CollideCheck(RECT CharRect);
	Miter();
	~Miter();
};
//Miter

//Goal
class Goal : public Object
{
private:
	MyIMG m_Goal;
public:
	void SetObject(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	int CollideCheck(RECT CharRect);
	Goal();
	~Goal();
};
//Goal

//FirePot
class FirePot : public Object
{
private:
	MyIMG m_arrFirePot[MAX];
public:
	void SetObject(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	int CollideCheck(RECT CharRect);
	FirePot();
	~FirePot();
};
//FirePot

//Ring
class Ring : public Object
{
private:
	MyIMG m_arrRing[MAX];
public:
	void SetObject(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	int CollideCheck(RECT CharRect);
	Ring();
	~Ring();
};
//Ring