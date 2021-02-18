#pragma once
#pragma comment(lib, "msimg32.lib")
#include<windows.h>
#include<time.h>
#include<vector>

#define IMAGE_SIZE 100
#define WIN_SIZE 800
#define MAX 8
#define NONE -1
#define WHITE 0
#define BLACK 1
#define PLAYER_MAX 2
#define PIECE_MAX 16
#define DIE -200

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
	IMAGE_W_PANW,
	IMAGE_W_KNIGHT,
	IMAGE_W_BISHOP,
	IMAGE_W_ROCK,
	IMAGE_W_QUEEN,
	IMAGE_W_KING,
	IMAGE_MAX
};

struct MyBoard
{
	int m_iIndex;
	int m_iExist;
	POINT m_Point;
};

struct Range
{
	POINT m_Point;
	RECT m_Rect;
};