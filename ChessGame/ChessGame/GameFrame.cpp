#include "GameFrame.h"

GameFrame::GameFrame()
{
}

void GameFrame::SetGame(HDC hdc)
{
	//리소스등록
	Res_MG::GetInstance()->Init(hdc);
	//더블버퍼링용 창 설정
	m_hFrameDC = CreateCompatibleDC(hdc);
	m_hFrame = CreateCompatibleBitmap(hdc, WIN_SIZE, WIN_SIZE);
	m_hOldFrame = (HBITMAP)SelectObject(m_hFrameDC, m_hFrame);
	//보드설정
	Board::GetInstance()->SetBoard();
	//플레이어설정
	m_arrPlayer[WHITE].SetPlayer(WHITE);
	m_arrPlayer[BLACK].SetPlayer(BLACK);
	//게임기본설정
	m_iTurn = 1;
	m_iClock = clock();
}

void GameFrame::UpdateGame(HDC hdc, POINT pt)
{
	if (clock() - m_iClock >= 50)
	{
		Draw(hdc);
		Click(pt);
		m_iClock = clock();
	}
}

void GameFrame::Draw(HDC hdc)
{
	Board::GetInstance()->DrawBoard(m_hFrameDC);
	m_arrPlayer[WHITE].DrawPiece(m_hFrameDC);
	m_arrPlayer[BLACK].DrawPiece(m_hFrameDC);
	BitBlt(hdc, 0, 0, WIN_SIZE, WIN_SIZE, m_hFrameDC, 0, 0, SRCCOPY);
}

void GameFrame::Click(POINT pt)
{
	m_arrPlayer[m_iTurn % 2].Click(pt);
}

void GameFrame::EndGame()
{
	DeleteObject(m_hFrame);
	SelectObject(m_hFrameDC, m_hOldFrame);
	DeleteDC(m_hFrameDC);
	delete Res_MG::GetInstance();
}

GameFrame::~GameFrame()
{
}