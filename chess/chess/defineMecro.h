#pragma once
#define IMAGE_SIZE 125
#define NORMAL 0
#define PINK 255
#define X 8
#define Y 8
#define PIECE_MAX 16
#define NONE -1
#define FALSE -2
struct RESOURCE
{
	int m_iIndex;
	RECT m_Rect;
};
enum PLAYER
{
	PLAYER_WHITE,
	PLAYER_BLACK,
	PLAYER_MAX
};
enum IMAGE
{
	IMAGE_START,
	IMAGE_BLOCK_IVORY = 0,
	IMAGE_BLOCK_BROWN,
	IMAGE_BLOCK_PINK,
	IMAGE_BLACK_PAWN,
	IMAGE_BLACK_KNIGHT,
	IMAGE_BLACK_BISHOP,
	IMAGE_BLACK_ROCK,
	IMAGE_BLACK_QUEEN,
	IMAGE_BLACK_KING,
	IMAGE_WHITE_PAWN,
	IMAGE_WHITE_KNIGHT,
	IMAGE_WHITE_BISHOP,
	IMAGE_WHITE_ROCK,
	IMAGE_WHITE_QUEEN,
	IMAGE_WHITE_KING,
	IMAGE_MAX
};