#pragma once
#include"BitManager.h"
#define MITER_MAX 10
#define GALLERY_MAX 30
class Map
{
private:
	BitMap m_Gallery;
	MyIMG m_GalleryInfo;
	MyIMG m_arrMiter[MITER_MAX];
	MyIMG m_Lane;
public:
	void SetMap(HDC hdc);
	void DrawMap(HDC hdc);
	void Move();
	Map();
	~Map();
};

