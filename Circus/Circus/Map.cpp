#include "Map.h"

Map::Map()
{

}

void Map::SetMap(HDC hdc)
{	
	//관중석 그림들 합치기
	POINT tmpPoint = { 0, 0 };
	SIZE tmpSize = { 100, 100 };

	m_Gallery.Init(hdc, L"", BACK, WIN_X * 2, 100);
	m_GalleryInfo.m_iPoint = { - WIN_X, WIN_Y / 2 - 100 };
	m_GalleryInfo.m_iSize = { WIN_X * 2 + 200, 100 };

	for (int i = 0; i < 30; i++)
	{
		if (i == 10)
			BitMapManager::GetInstance()->Draw(m_Gallery.GetMemDC(), IMAGE_BACK_DECO, tmpPoint, tmpSize);
		else
			BitMapManager::GetInstance()->Draw(m_Gallery.GetMemDC(), IMAGE_BACK_NORMAL, tmpPoint, tmpSize);
		tmpPoint.x += 100;
	}
	//관중석 그림들 합치기

	//레인그림 설정
	m_Lane.m_iIndex = IMAGE_BACK;
	m_Lane.m_iPoint = { 0, WIN_Y / 2 };
	m_Lane.m_iSize = { WIN_X, WIN_Y / 2 };
	//레인그림 설정
}

void Map::DrawMap(HDC hdc)
{
	BitMapManager::GetInstance()->Draw(hdc, m_Lane.m_iIndex, m_Lane.m_iPoint, m_Lane.m_iSize);
	m_Gallery.Draw(hdc, m_GalleryInfo.m_iPoint, m_GalleryInfo.m_iSize);
}

void Map::MapMove(int Direction)
{
	if (m_GalleryInfo.m_iPoint.x < -1200)
		m_GalleryInfo.m_iPoint.x = -100;
	if (m_GalleryInfo.m_iPoint.x > 0)
		m_GalleryInfo.m_iPoint.x = -1200;
	if(Direction == LEFT)
		m_GalleryInfo.m_iPoint.x += 10;
	else
		m_GalleryInfo.m_iPoint.x -= 10;

}

Map::~Map()
{
}
