#pragma once
#include"BitMapManager.h"

class Map
{
private:
	BitMap m_Screen;
	MyIMG m_ScreenInfo;
	MyIMG m_Gallery;
	MyIMG m_Lane;
	MyIMG m_Miter;
public:
	void SetMap(HDC hdc);
	void DrawMap(HDC hdc);
	void MapMove(int Direction);
	Map();
	~Map();
};

