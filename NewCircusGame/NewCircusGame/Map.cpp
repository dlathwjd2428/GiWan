#include "Map.h"

Map::Map()
{
}

void Map::SetMap()
{
	//레인설정
	m_Lane.m_iIndex = IMAGE_LANE;
	m_Lane.m_Point = { 0, WIN_SIZE / 2 };
	m_Lane.m_Size = { WIN_SIZE, WIN_SIZE / 2 };
	//관중석설정
	int tmpIndex;
	POINT tmpPoint = { 0, WIN_SIZE / 2 - 100 };
	for (int i = 0; i < GALLERY_MAX; i++)
	{
		if (i == 0)
			tmpIndex = IMAGE_DECO;
		else
			tmpIndex = IMAGE_PEOPLE1;
		m_arrGallery[i].m_iIndex = tmpIndex;
		m_arrGallery[i].m_Point = tmpPoint;
		m_arrGallery[i].m_Size = { 100, 100 };
		tmpPoint.x += 100;
	}
}

void Map::Draw(HDC hdc)
{
	//레인그리기
	ResManager::GetInstance()->DrawBitMap(hdc, m_Lane.m_iIndex, m_Lane.m_Point, m_Lane.m_Size);
	//관중석그리기
	for (int i = 0; i < GALLERY_MAX; i++)
		ResManager::GetInstance()->DrawBitMap(hdc, m_arrGallery[i].m_iIndex, m_arrGallery[i].m_Point, m_arrGallery[i].m_Size);
}

void Map::Move(int Direction)
{
	for (int i = 0; i < GALLERY_MAX; i++)
	{
		m_arrGallery[i].m_Point.x += Direction;
		if (m_arrGallery[i].m_Point.x <= -100)
			m_arrGallery[i].m_Point.x = WIN_SIZE;
		else if (m_arrGallery[i].m_Point.x >= WIN_SIZE)
			m_arrGallery[i].m_Point.x = -100;
	}
}

Map::~Map()
{
}
