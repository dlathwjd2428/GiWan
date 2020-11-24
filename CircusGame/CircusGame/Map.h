#pragma once
#include"BitMapManager.h"

class Map
{
private:
	MyIMG m_Back;
	MyIMG m_BackDeco[16];
	MyIMG m_BackDeco2;
public:
	void SetMapInfo();
	void DrawMap(HDC hdc);
	void Move();
	Map();
	~Map();
};

