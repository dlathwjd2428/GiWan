#pragma once
#include"BitManager.h"

class Map
{
private:
	POINT m_GalleryPoint;
	SIZE m_GallerySize;
	BitMap m_GalleryBit;
	MyIMG m_Lane;
	MyIMG m_arrMiter[MITER_MAX];
public:
	void SetMap(HDC hdc);
	void Draw(HDC hdc);
	void Move(int Direction);
	void MoveMiter(int Direction);
	Map();
	~Map();
};

