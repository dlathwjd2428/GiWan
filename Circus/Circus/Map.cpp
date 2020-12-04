#include "Map.h"

Map::Map()
{
}

void Map::SetMap(HDC hdc)
{
	//������������
	m_Lane.m_iIndex = IMAGE_LANE;
	m_Lane.m_Point = { 0, WIN_SIZE / 2 };
	m_Lane.m_Size = { WIN_SIZE, WIN_SIZE / 2 };
	//������������
	int x = CHAR_PT_X;
	for (int i = 0; i < MITER_MAX; i++)
	{
		m_arrMiter[i].m_iIndex = IMAGE_MITER;
		m_arrMiter[i].m_Point = { x, CHAR_PT_Y + 110 };
		m_arrMiter[i].m_Size = { 100, IMAGE_SIZE / 2 };
		x += WIN_SIZE;
	}
	//���߼�����
	m_GalleryInfo.m_Point = { -500, WIN_SIZE / 2 - 100 };
	m_GalleryInfo.m_Size = { 3000, 100 };
	m_Gallery.Init(hdc, L"", BACK, 3000, 100);
	POINT tmpPoint = { 0, 0 };
	SIZE tmpSize = { IMAGE_SIZE, IMAGE_SIZE };
	for (int i = 0; i < GALLERY_MAX; i++)
	{
		if (i == 15)
			BitManager::GetInstance()->Draw(m_Gallery.GetDC(), IMAGE_DECO, tmpPoint, tmpSize);
		else
			BitManager::GetInstance()->Draw(m_Gallery.GetDC(), IMAGE_GALLERY1, tmpPoint, tmpSize);
		tmpPoint.x += 100;
	}
}

void Map::DrawMap(HDC hdc)
{
	//���߼��׸���
	m_Gallery.Draw(hdc, m_GalleryInfo.m_Point, m_GalleryInfo.m_Size);
	//���α׸���
	BitManager::GetInstance()->Draw(hdc, m_Lane.m_iIndex, m_Lane.m_Point, m_Lane.m_Size);
	//����ǥ�ñ׸���
	WCHAR buf[256];
	for (int i = 0; i < MITER_MAX; i++)
	{
		wsprintf(buf, L"%d", 100 - 10 * i);
		BitManager::GetInstance()->Draw(hdc, m_arrMiter[i].m_iIndex, m_arrMiter[i].m_Point, m_arrMiter[i].m_Size);
		TextOut(hdc, m_arrMiter[i].m_Point.x + 30, m_arrMiter[i].m_Point.y + 15, buf, lstrlen(buf));
	}
}

void Map::Move()
{
  
}

Map::~Map()
{
}
