#pragma once
#include"ResManager.h"

class Map
{
private:
	MyIMG m_Lane;
	MyIMG m_arrGallery[GALLERY_MAX];
public:
	void SetMap();
	void Draw(HDC hdc);
	void Move(int Direction);
	Map();
	~Map();
};

