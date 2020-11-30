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
	//미터설정 및 골인지점설정
	tmpPoint = { POINT_X, POINT_Y + 100 };
	for (int i = 0; i < MITER_MAX; i++)
	{
		m_arrMiter[i].m_iIndex = IMAGE_MITER;
		m_arrMiter[i].m_Point = tmpPoint;
		m_arrMiter[i].m_Size = { 80, 50 };
		tmpPoint.x += 1000;
	}
}

void Map::Draw(HDC hdc)
{
	//관중석그리기
	m_GalleryBit.Draw(hdc, m_GalleryPoint, m_GallerySize);
	//레인그리기
	BitManager::GetInstance()->Draw(hdc, m_Lane.m_iIndex, m_Lane.m_Point, m_Lane.m_Size);
	//미터그리기
	WCHAR buf[256];
	for (int i = 0; i < MITER_MAX; i++)
	{
		wsprintf(buf, L"%d", 100 - 10 * i);
		BitManager::GetInstance()->Draw(hdc, m_arrMiter[i].m_iIndex, m_arrMiter[i].m_Point, m_arrMiter[i].m_Size);
		TextOut(hdc, m_arrMiter[i].m_Point.x + 20, m_arrMiter[i].m_Point.y + 10, buf, lstrlen(buf));
	}
}

void Map::Move(int Direction)
{
	//관중석 범위제어
	if (m_GalleryPoint.x < -1300)
		m_GalleryPoint.x = 0;
	if (m_GalleryPoint.x > 0)
		m_GalleryPoint.x = -1300;
	//관중석움직이기
	if (Direction == RIGHT)
	{
		m_GalleryPoint.x -= 20;
		MoveMiter(RIGHT);	//미터표시좌표이동
	}
	if (Direction == LEFT)
	{
		m_GalleryPoint.x += 10;
		MoveMiter(LEFT);	//미터표시좌표이동
	}
}

void Map::MoveMiter(int Direction)
{
	for (int i = 0; i < MITER_MAX; i++)
	{
		if (Direction == LEFT)
			m_arrMiter[i].m_Point.x += 10;
		else
			m_arrMiter[i].m_Point.x -= 20;
	}
}

Map::~Map()
{
}