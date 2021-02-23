#pragma once
#pragma comment(lib, "msimg32.lib")
#include<windows.h>
#include<time.h>

#define WIN_X 500
#define WIN_Y 720
#define IMAGE_X 100
#define IMAGE_Y 120
#define X 4
#define Y 5
#define NONE -10
#define CARD_MAX 20
#define GAP 20

enum IMAGE
{
	IMAGE_START,
	IMAGE_DOG = 0,
	IMAGE_TIGER,
	IMAGE_DUCK,
	IMAGE_ELEPHANT,
	IMAGE_COW,
	IMAGE_HORSE,
	IMAGE_CAT,
	IMAGE_MONKEY,
	IMAGE_FROG,
	IMAGE_CHICKEN,
	IMAGE_BLACK,
	IMAGE_BACK,
	IMAGE_MAX
};

enum CARD_STATE
{
	CARD_STATE_CLOSE,
	CARD_STATE_OPEN,
	CARD_STATE_FIX
};

enum CLICK
{
	CLICK_NONE,
	CLICK_ONE,
	CLICK_TWO
};

struct Card
{
	int m_iIndex;
	int m_iCardState;
	POINT m_Point;
	RECT m_Rect;
};