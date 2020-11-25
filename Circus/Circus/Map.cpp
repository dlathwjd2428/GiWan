#include "Map.h"

Map::Map()
{

}

void Map::SetMap(HDC hdc)
{	
	//���߼� �׸��� ��ġ��
	POINT tmpPoint = { 0, 0 };
	SIZE tmpSize = { 100, 100 };

	m_Gallery.Init(hdc, L"", BACK, WIN_X, 100);
	m_GalleryInfo.m_iPoint = { 0, WIN_Y / 2 - 100 };
	m_GalleryInfo.m_iSize = { WIN_X, 100 };

	for (int i = 0; i < 16; i++)
	{
		if (1 != 0 && i & 7 == 0)
			BitMapManager::GetInstance()->Draw(m_Gallery.GetMemDC(), IMAGE_BACK_DECO, tmpPoint, tmpSize);
		else
			BitMapManager::GetInstance()->Draw(m_Gallery.GetMemDC(), IMAGE_BACK_NORMAL, tmpPoint, tmpSize);
		tmpPoint.x += 100;
	}
	//���߼� �׸��� ��ġ��

	//���α׸� ����
	m_Lane.m_iIndex = IMAGE_BACK;
	m_Lane.m_iPoint = { 0, WIN_Y / 2 };
	m_Lane.m_iSize = { WIN_X, WIN_Y };
	//���α׸� ����
}

void Map::DrawMap(HDC hdc)
{
	BitMapManager::GetInstance()->Draw(hdc, m_Lane.m_iIndex, m_Lane.m_iPoint, m_Lane.m_iSize);
	m_Gallery.Draw(hdc, m_GalleryInfo.m_iPoint, m_GalleryInfo.m_iSize);
}

Map::~Map()
{
}
