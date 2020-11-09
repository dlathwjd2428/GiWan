#pragma once
#include"BitMapManager.h"

class Piece
{
protected:
	RESOURCE m_Image;
public:
	void SetPiece(int Index, POINT pt);
	void DrawPiece(HDC hdc);
	Piece();
	~Piece();
};

//Pawn
class Pawn : public Piece
{
private:
public:
	Pawn();
	~Pawn();
};
//Pawn

//Knight
class Knight : public Piece
{
private:
public:
	Knight();
	~Knight();
};
//Knight

//Bishop
class Bishop : public Piece
{
private:
public:
	Bishop();
	~Bishop();
};
//Bishop

//Rock
class Rock : public Piece
{
private:
public:
	Rock();
	~Rock();
};
//Rock

//Queen
class Queen : public Piece
{
private:
public:
	Queen();
	~Queen();
};
//Queen

//King
class King : public Piece
{
private:
public:
	King();
	~King();
};
//King