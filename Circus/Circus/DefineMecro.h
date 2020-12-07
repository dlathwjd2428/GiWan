#pragma once
#pragma comment(lib, "msimg32.lib")
#include<windows.h>
#include<time.h>
#include<math.h>
#define NORMAL 0
#define BACK 1
#define WIN_SIZE 1000
#define IMAGE_SIZE 100
#define CHAR_PT_X 150
#define CHAR_PT_Y WIN_SIZE - 250
#define LEFT 1
#define RIGHT 2
#define JUMP 40
#define OB_MAX 10
#define TEXT_COLOR 0
#define BACK_COLOR 1
#define BRUSH_COLOR 2
#define GRAVITY -5
#define NORMAL_SPEED 10
#define HIGH_SPEED 17
#define LOW_SPEED 5
enum IMAGE
{
	IMAGE_START,
	IMAGE_LANE = 0,
	IMAGE_DECO,
	IMAGE_GALLERY1,
	IMAGE_GALLERY2,
	IMAGE_MONEY,
	IMAGE_DIE,
	IMAGE_WIN1,
	IMAGE_WIN2,
	IMAGE_GOAL,
	IMAGE_ENEMY1,
	IMAGE_ENEMY1_RIGHT,
	IMAGE_ENEMY2,
	IMAGE_ENEMY2_RIGHT,
	IMAGE_ENEMY3,
	IMAGE_ENEMY3_RIGHT,
	IMAGE_FIRE1,
	IMAGE_FIRE2,
	IMAGE_MITER,
	IMAGE_CHAR1,
	IMAGE_CHAR2,
	IMAGE_CHAR3,
	IMAGE_MAX
};

struct MyIMG
{
	int m_iIndex;
	POINT m_Point;
	SIZE m_Size;
	RECT m_Rect1;
	RECT m_Rect2;
};


