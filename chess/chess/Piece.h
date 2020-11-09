#pragma once
#include"BitMapManager.h"
#include<vector>

class Piece
{
protected:
	RESOURCE m_Image;
	std::vector<RECT> m_vMoveRange;
	int m_iType;
	bool m_bClickState;
public:
	void SetPiece(int Index, POINT pt);
	void DrawPiece(HDC hdc);
	void DrawRange(HDC hdc);
	bool ClickCheck(POINT pt);
	inline RECT GetRect() { return m_Image.m_Rect; }
	inline bool GetClickState() { return m_bClickState; }
	virtual void SetRange(RECT* Player, RECT* Enemy) = 0;
	Piece();
	~Piece();
};

//Pawn
class Pawn : public Piece
{
private:
public:
	void SetRange(RECT* Player, RECT* Enemy);
	Pawn();
	~Pawn();
};
//Pawn

//Knight
class Knight : public Piece
{
private:
public:
	void SetRange(RECT* Player, RECT* Enemy);
	Knight();
	~Knight();
};
//Knight

//Bishop
class Bishop : public Piece
{
private:
public:
	void SetRange(RECT* Player, RECT* Enemy);
	Bishop();
	~Bishop();
};
//Bishop

//Rock
class Rock : public Piece
{
private:
public:
	void SetRange(RECT* Player, RECT* Enemy);
	Rock();
	~Rock();
};
//Rock

//Queen
class Queen : public Piece
{
private:
public:
	void SetRange(RECT* Player, RECT* Enemy);
	Queen();
	~Queen();
};
//Queen

//King
class King : public Piece
{
private:
public:
	void SetRange(RECT* Player, RECT* Enemy);
	King();
	~King();
};
//King