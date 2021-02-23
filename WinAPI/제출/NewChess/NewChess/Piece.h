#pragma once
#include"Board.h"

class Piece
{
protected:
	PIECE m_Piece;
	POINT m_SavePt;
	int m_iEnemyColor;
	int m_iAdd;
	int m_iMoveCount;
	bool m_bClick;
	vector<Range> m_vMove;
	vector<Range> m_vAtk;
public:
	void SetPiece(int Exist, int Enemy, int Index, int Add, POINT pt);
	void Draw(HDC hdc);
	bool Click(POINT pt);
	bool Move(POINT pt);
	bool Fix();
	bool MoveRangeFix();
	void ResetRange();
	bool CheckRange(Range range, int Option);
	bool KingCheck();
	bool Die(POINT pt);
	inline int GetIndex() { return m_Piece.m_iIndex; }
	inline POINT GetPoint() { return m_Piece.m_Point; }
	virtual void SetRange() = 0;
	Piece();
	~Piece();
};

//Pawn
class Pawn : public Piece
{
private:
public:
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
	void SetRange();
	King();
	~King();
};
//King