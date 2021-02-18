#pragma once
#include"Board.h"

class Piece
{
protected:
	bool m_bClick;
	int m_iIndex;
	int m_iAdd;	 
	int m_iEnemyColor;
	POINT m_Point;
	POINT m_SavePoint;
	RECT m_Rect;
	vector<Range> m_vMove;
	vector<Range> m_vAtk;
public:
	void Draw(HDC hdc);
	bool ClickCheck(POINT pt);
	virtual void SetPiece(int Player, POINT pt) = 0;
	virtual void SetRange() = 0;
	inline POINT GetPoint() { return m_Point; }
	Piece();
	~Piece();
};

//Pawn
class Pawn : public Piece
{
private:
	int m_iMoveCount;
public:
	void SetPiece(int Player, POINT pt);
	void SetRange();
	Pawn();
	~Pawn();
};
//Pawn

//Knight
class Knight : public Piece
{
private:
public:
	void SetPiece(int Player, POINT pt);
	void SetRange();
	Knight();
	~Knight();
};
//Knight

//Bishop
class Bishop : public Piece
{
private:
public:
	void SetPiece(int Player, POINT pt);
	void SetRange();
	Bishop();
	~Bishop();
};
//Bishop

//Rock
class Rock : public Piece
{
private:
public:
	void SetPiece(int Player, POINT pt);
	void SetRange();
	Rock();
	~Rock();
};
//Rock

//Queen
class Queen : public Piece
{
private:
public:
	void SetPiece(int Player, POINT pt);
	void SetRange();
	Queen();
	~Queen();
};
//Queen

//King
class King : public Piece
{
private:
public:
	void SetPiece(int Player, POINT pt);
	void SetRange();
	King();
	~King();
};
//King