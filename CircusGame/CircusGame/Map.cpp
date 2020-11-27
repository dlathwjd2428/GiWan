#include "Map.h"

Map::Map()
{
}

void Map::SetMap(HDC hdc)
{
	//관중석MemDC설정
	m_GalleryBit.Init(hdc, L"", BACK, GALLERY_X, GALLERY_Y);
	m_GalleryPoint = { - 500, WIN_Y / 2 - 100 };
	m_GallerySize = { GALLERY_X , GALLERY_Y };
	//관중석 그림합치기(코끼리좌표가운데 기준 좌우 11칸씩)
	POINT tmpPoint = { 0, 0 };
	SIZE tmpSize = { DEFAULT_SIZE, DEFAULT_SIZE };
	for (int i = 0; i < GALLERY_MAX; i++)
	{
		if (i == 12)
			BitManager::GetInstance()->Draw(m_GalleryBit.GetDC(), IMAGE_DECO, tmpPoint, tmpSize);
		else
			BitManager::GetInstance()->Draw(m_GalleryBit.GetDC(), IMAGE_PEOPLE1, tmpPoint, tmpSize);
		tmpPoint.x += 100;
	}
	//레인설정
	m_Lane.m_iIndex = IMAGE_LANE;
	m_Lane.m_Point = { 0, WIN_Y / 2 };
	m_Lane.m_Size = { WIN_X, WIN_Y / 2 };
}

void Map::Draw(HDC hdc)
{
	m_GalleryBit.Draw(hdc, m_GalleryPoint, m_GallerySize);
	BitManager::GetInstance()->Draw(hdc, m_Lane.m_iIndex, m_Lane.m_Point, m_Lane.m_Size);
}

void Map::Move(int Direction)
{
	if (m_GalleryPoint.x < -1300)
		m_GalleryPoint.x = 0;
	if (m_GalleryPoint.x > 0)
		m_GalleryPoint.x = -1300;
	if (Direction == RIGHT)
		m_GalleryPoint.x -= 5;
	if (Direction == LEFT)
		m_GalleryPoint.x += 5;
}
Map::~Map()
{
}