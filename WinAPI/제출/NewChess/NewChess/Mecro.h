#pragma once
#pragma comment(lib, "msimg32.lib")
#include<windows.h>
#include<time.h>
#include<vector>

#define IMAGE_SIZE 100
#define WIN_SIZE 800
#define ROOM 8
#define PIECE_MAX 16
#define PLAYER 2
#define DIE -100
#define MOVE 0
#define ATTACK 1

using namespace std;

enum IMAGE
{
	IMAGE_START,
	IMAGE_BACK1 = 0,
	IMAGE_BACK2,
	IMAGE_BACK3,
	IMAGE_B_PAWN,
	IMAGE_B_KNIGHT,
	IMAGE_B_BISHOP,
	IMAGE_B_ROCK,
	IMAGE_B_QUEEN,
	IMAGE_B_KING,
	IMAGE_W_PAWN,
	IMAGE_W_KNIGHT,
	IMAGE_W_BISHOP,
	IMAGE_W_ROCK,
	IMAGE_W_QUEEN,
	IMAGE_W_KING,
	IMAGE_MAX
};

enum EXIST
{
	EXIST_EMPTY = -1,
	EXIST_WHITE,
	EXIST_BLACK,
	EXIST_WHITE_KING,
	EXIST_BLACK_KING
};

typedef struct MyIMG
{
	int m_iIndex;
	int m_iExist;
	POINT m_Point;
	SIZE m_Size;
	RECT m_Rect;
}BOARD, PIECE;

struct Range
{
	POINT m_Point;
	RECT m_Rect;
};