#include "Map.h"

Map::Map()
{
}

void Map::SetMap(HDC hdc)
{
	//레인정보설정
	m_Lane.m_iIndex = IMAGE_LANE;
	m_Lane.m_Point = { 0, WIN_SIZE / 2 };
	m_Lane.m_Size = { WIN_SIZE, WIN_SIZE / 2 };
	//미터정보설정
	int x = CHAR_PT_X;
	for (int i = 0; i < MITER_MAX; i++)
	{
		m_arrMiter[i].m_iIndex = IMAGE_MITER;
		m_arrMiter[i].m_Point = { x, CHAR_PT_Y + 160 };
		m_arrMiter[i].m_Size = { 100, IMAGE_SIZE / 2 };
		x += WIN_SIZE;
	}
	//관중석설정
	m_bCheer = false;
	m_iCount = 0;
	m_GalleryInfo.m_Point = { -1000, WIN_SIZE / 2 - 100 };
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
	//관중석그리기
	int i = 0;
	if (m_bCheer == false)
		i = 0;
	else
	{
		if (i == 0)
			i++;
		else
			i--;
	}
	m_Gallery.Draw(hdc, m_GalleryInfo.m_Point, m_GalleryInfo.m_Size);
	//레인그리기
	BitManager::GetInstance()->Draw(hdc, m_Lane.m_iIndex, m_Lane.m_Point, m_Lane.m_Size);
	//미터표시그리기
	TextAndFont::GetInstance()->FontSize(hdc, 30);
	TextAndFont::GetInstance()->ColorSet(hdc, BACK_COLOR, 0, 0, 0);
	TextAndFont::GetInstance()->ColorSet(hdc, TEXT_COLOR, 255, 94, 0);
	WCHAR buf[256];
	for (int i = 0; i < MITER_MAX; i++)
	{
		wsprintf(buf, L"%d", 100 - 10 * i);
		BitManager::GetInstance()->Draw(hdc, m_arrMiter[i].m_iIndex, m_arrMiter[i].m_Point, m_arrMiter[i].m_Size);
		TextOut(hdc, m_arrMiter[i].m_Point.x + 15, m_arrMiter[i].m_Point.y + 10, buf, lstrlen(buf));
	}
	//점수판그리기
	TextAndFont::GetInstance()->ColorSet(hdc, BRUSH_COLOR, 255, 193, 158);
	Rectangle(hdc, 100, 100, 900, WIN_SIZE / 2 - 200);
	TextAndFont::GetInstance()->Reset(hdc);
}

void Map::Move(int Direction)
{
	int Add = NULL;
	if (m_GalleryInfo.m_Point.x <= -1600)
		m_GalleryInfo.m_Point.x = -500;
	else if (m_GalleryInfo.m_Point.x >= -500)
		m_GalleryInfo.m_Point.x = -1600;
	switch (Direction)
	{
	case LEFT:
		Add = 15;
		break;
	case RIGHT:
		Add = -20;
		break;
	}
	m_GalleryInfo.m_Point.x += Add;
	MoveMiter(Add);
}

void Map::MoveMiter(int Add)
{
	for (int i = 0; i < MITER_MAX; i++)
		m_arrMiter[i].m_Point.x += Add;
}

void Map::JumpMove(bool MoveState)
{
	int Add = 0;
	if (MoveState == true)
		Add = -20;
	m_GalleryInfo.m_Point.x += Add;
	MoveMiter(Add);
}

Map::~Map()
{
}
