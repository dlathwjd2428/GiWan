#pragma once
#include"BitMapManager.h"

class Map
{
private:
	BitMap m_Gallery;
	MyIMG m_GalleryInfo;
	MyIMG m_Lane;
public:
	void SetMap(HDC hdc);
	void DrawMap(HDC hdc);
	void MapMove(int Direction);
	Map();
	~Map();
};

