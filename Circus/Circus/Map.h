#pragma once
#include"BitManager.h"
#define MITER_MAX 10
#define GALLERY_MAX 30
class Map
{
private:
	int m_iCount;
	bool m_bCheer;
	BitMap m_Gallery;
	MyIMG m_GalleryInfo;
	MyIMG m_arrMiter[MITER_MAX];
	MyIMG m_Lane;
public:
	void SetMap(HDC hdc);
	void DrawMap(HDC hdc);
	void Move(int Direction);
	void MoveMiter(int Add);
	void JumpMove(bool MoveState);
	inline void SetCheer() { m_bCheer = true; }
	Map();
	~Map();
};

