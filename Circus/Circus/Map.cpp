#include "Map.h"

Map::Map()
{

}

void Map::SetMap(HDC hdc)
{	
	//맵비트맵설정
	m_Screen.Init(hdc, L"", BACK, WIN_X * 10, WIN_Y);
	m_ScreenInfo.m_iPoint = { 0, 0 };
	m_ScreenInfo.m_iSize = { WIN_X * 10, WIN_Y };
	//스크린비트맵설정

	//레인그림 설정
	m_Lane.m_iIndex = IMAGE_BACK;
	m_Lane.m_iPoint = { 0, WIN_Y / 2 };
	m_Lane.m_iSize = { WIN_X * 10, WIN_Y / 2 };
	//레인그림 설정

	//관중석 설정
	m_Gallery.m_iIndex = IMAGE_BACK_NORMAL;
	m_Gallery.m_iPoint = { 0, WIN_Y / 2 - 100 };
	m_Gallery.m_iSize = { 100, 100 };
	//관중석 설정

	//미터설정
	m_Miter.m_iIndex = IMAGE_MITER;
	m_Miter.m_iPoint = {150, WIN_Y - 100};
	m_Miter.m_iSize = { 86, 30 };
	//미터설정

	//그림들 합치기
	//관중석
	for (int i = 0; i < 100; i++)
	{
		if (i != 0 && i % 10 == 0)
			BitMapManager::GetInstance()->Draw(m_Screen.GetMemDC(), IMAGE_BACK_DECO, m_Gallery.m_iPoint, m_Gallery.m_iSize);
		else
			BitMapManager::GetInstance()->Draw(m_Screen.GetMemDC(), IMAGE_BACK_NORMAL, m_Gallery.m_iPoint, m_Gallery.m_iSize);
		m_Gallery.m_iPoint.x += 100;
	}
	//관중석

	//레인
	BitMapManager::GetInstance()->Draw(m_Screen.GetMemDC(), m_Lane.m_iIndex, m_Lane.m_iPoint, m_Lane.m_iSize);
	//레인

	//미터
	WCHAR buf[256];
	for (int i = 0; i < MITER_MAX; i++)
	{
		wsprintf(buf, L"%d", 100 - i * 10);
		BitMapManager::GetInstance()->Draw(m_Screen.GetMemDC(), m_Miter.m_iIndex, m_Miter.m_iPoint, m_Miter.m_iSize);
		TextOut(m_Screen.GetMemDC(), m_Miter.m_iPoint.x + 20, m_Miter.m_iPoint.y + 5, buf, lstrlen(buf));
		m_Miter.m_iPoint.x += WIN_X;
	}
	//미터
	//그림들 합치기

	
}

void Map::DrawMap(HDC hdc)
{
	m_Screen.Draw(hdc, m_ScreenInfo.m_iPoint, m_ScreenInfo.m_iSize);
}

void Map::MapMove(int Direction)
{
	if (Direction == LEFT)
	{
		if (m_ScreenInfo.m_iPoint.x != 0)
			m_ScreenInfo.m_iPoint.x += 10;
	}
	else
		m_ScreenInfo.m_iPoint.x -= 10;
}

Map::~Map()
{
}
