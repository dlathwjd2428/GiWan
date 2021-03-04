#include "GameFrame.h"

GameFrame::GameFrame()
{
}

void GameFrame::SetGame(HDC hdc)
{
	//���ҽ����
	Res_MG::GetInstance()->Init(hdc);
	//����������â����
	m_hFrameDC = CreateCompatibleDC(hdc);
	m_hFrame = CreateCompatibleBitmap(hdc, WIN_X, WIN_Y);
	m_hOldFrame = (HBITMAP)SelectObject(m_hFrameDC, m_hFrame);
	//���ʱ⼳��
	for (int i = 0; i < MAP_MAX; i++)
		m_arrMap[i].SetMap();
}

void GameFrame::UpdateGame(HDC hdc)
{

}

void GameFrame::Draw(HDC hdc)
{
	m_arrMap[0].DrawMap(m_hFrameDC);
	//��Ӻ���
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