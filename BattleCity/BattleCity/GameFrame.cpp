#include "GameFrame.h"

GameFrame::GameFrame()
{
}

void GameFrame::SetGame(HDC hdc)
{
	//리소스등록
	Res_MG::GetInstance()->Init(hdc);
	//게임프레임창설정
	m_hFrameDC = CreateCompatibleDC(hdc);
	m_hFrame = CreateCompatibleBitmap(hdc, WIN_X, WIN_Y);
	m_hOldFrame = (HBITMAP)SelectObject(m_hFrameDC, m_hFrame);
	//맵초기설정
	for (int i = 0; i < MAP_MAX; i++)
		m_arrMap[i].SetMap();
}

void GameFrame::UpdateGame(HDC hdc)
{

}

void GameFrame::Draw(HDC hdc)
{
	m_arrMap[0].DrawMap(m_hFrameDC);
	//고속복사
	BitBlt(hdc, 0, 0, WIN_X, WIN_Y, m_hFrameDC, 0, 0, SRCCOPY);
}

void GameFrame::EndGame()
{
}

GameFrame::~GameFrame()
{
	DeleteObject(m_hFrame);
	SelectObject(m_hFrameDC, m_hOldFrame);
	DeleteDC(m_hFrameDC);
}