#pragma once
#include"BitMapManager.h"
#include<vector>

class Piece
{
protected:
	ImageInfo m_Image;
	int AddY;
	std::vector<RECT> m_vMoveRange;
	std::vector<RECT> m_vAtkRange;
public:
	void SetInfo(int Index, POINT pt);
	void SetDefault();
	void DrawPiece(HDC hdc);
	int CheckRectForRange(RECT* player, RECT* enemy, RECT Move, RECT Atk);
	bool ClickCheck(POINT pt);
	//인라인함수
	inline RECT GetRect() { return m_Image.m_ImageRect; }
	//순수가상함수
	virtual void SetRange(RECT* player, RECT* enemy) = 0;
	Piece();
	~Piece();
};

//Pawn
class Pawn : public Piece
{
private:
	int m_iMoveCount;
public:
	void SetRange(RECT* player, RECT* enemy);
	Pawn();
	~Pawn();
};
//Pawn

//Knight
class Knight : public Piece
{
private:
public:
	void SetRange(RECT* player, RECT* enemy);
	Knight();
	~Knight();
};
//Knight

//Bishop
class Bishop : public Piece
{
private:
public:
	void SetRange(RECT* player, RECT* enemy);
	Bishop();
	~Bishop();
};
//Bishop

//Rock
class Rock : public Piece
{
private:
public:
	void SetRange(RECT* player, RECT* enemy);
	Rock();
	~Rock();
};
//Rock

//Queen
class Queen : public Piece
{
private:
public:
	void SetRange(RECT* player, RECT* enemy);
	Queen();
	~Queen();
};
//Queen

//King
class King : public Piece
{
private:
public:
	void SetRange(RECT* player, RECT* enemy);
	King();
	~King();
};
//King