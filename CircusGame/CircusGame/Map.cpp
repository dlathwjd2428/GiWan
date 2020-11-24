#include "Map.h"

Map::Map()
{
}

void Map::SetMapInfo()
{
	m_Back.m_iIndex = IMAGE_BACK;
	m_Back.m_iDrawPt = { 0, WIN_SIZE_Y / 2 };
	m_Back.m_iSize = { WIN_SIZE_X, WIN_SIZE_Y / 2 };
	int x = 0;
	
	for (int i = 0; i < 16; i++)
	{
		if (i == 7)
		{
			m_BackDeco2.m_iIndex = IMAGE_BACK_DECO;
			m_BackDeco2.m_iDrawPt = { x, WIN_SIZE_Y / 2 - 100 };
			m_BackDeco2.m_iSize = { WIN_SIZE_X, 100 };
		}
		else
		{
			m_BackDeco[i].m_iIndex = IMAGE_BACK_NORMAL;
			m_BackDeco[i].m_iDrawPt = { x, WIN_SIZE_Y / 2 - 100 };
			m_BackDeco[i].m_iSize = { 100, 100 };
		}
		x += 100;
	}
}

void Map::DrawMap(HDC hdc)
{
	BitMapManager::GetInstance()->DrawImage(hdc, m_Back.m_iIndex, m_Back.m_iDrawPt, m_Back.m_iSize);
	for (int i = 0; i < 16; i++)
		BitMapManager::GetInstance()->DrawImage(hdc, m_BackDeco[i].m_iIndex, m_BackDeco[i].m_iDrawPt, m_BackDeco[i].m_iSize);
}

void Map::Move()
{
	for (int i = 0; i < 16; i++)
	{
		if (m_BackDeco[i].m_iDrawPt.x <= 0)
			m_BackDeco[i].m_iDrawPt.x = WIN_SIZE_X;
		m_BackDeco[i].m_iDrawPt.x -= 10;
	}
}
Map::~Map()
{
}
