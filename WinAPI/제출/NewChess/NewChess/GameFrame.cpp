#include "GameFrame.h"

GameFrame::GameFrame()
{
}

void GameFrame::SetGame(HDC hdc)
{
	//리소스등록
	Res_MG::GetInstance()->Init(hdc);
	//게임보드 초기설정
	Board::GetInstance()->SetBoard();
	//게임프레임설정(더블버퍼링용)
	m_hGameFrame= CreateCompatibleDC(hdc);
	m_hFrame = CreateCompatibleBitmap(hdc, WIN_SIZE, WIN_SIZE);
	m_hOldFrame = (HBITMAP)SelectObject(m_hGameFrame, m_hFrame);
	//플레이어설정(체스말들포함)
	m_arrPlayer[EXIST_WHITE].SetPlayer(EXIST_WHITE);
	m_arrPlayer[EXIST_BLACK].SetPlayer(EXIST_BLACK);
	//게임초기설정
	m_iClock = clock();
	m_iTurn = 1;
}

void GameFrame::UpdateGame(HWND hWnd, HDC hdc, POINT pt)
{
	if (clock() - m_iClock >= 25)
	{
		Click(hWnd, pt);
		if (Board::GetInstance()->KingCheck(hWnd))
			SetGame(hdc);
		Draw(hdc);
		m_iClock = clock();
	}
}

void GameFrame::Draw(HDC hdc)
{
	//게임판(보드)그리기
	Board::GetInstance()->DrawBoard(m_hGameFrame);
	//플레이어(체스말)그리기
	m_arrPlayer[EXIST_WHITE].Draw(m_hGameFrame);
	m_arrPlayer[EXIST_BLACK].Draw(m_hGameFrame);
	//더블버퍼링(고속복사)
	BitBlt(hdc, 0, 0, WIN_SIZE, WIN_SIZE, m_hGameFrame, 0, 0, SRCCOPY);
}

void GameFrame::Click(HWND hWnd, POINT pt)
{
	if (m_arrPlayer[m_iTurn % 2].Click(hWnd, pt, m_iTurn) == true)
	{
		if (Board::GetInstance()->GetKillPoint().x != DIE)
			m_arrPlayer[m_iTurn % 2].Die(Board::GetInstance()->GetKillPoint());
		m_arrPlayer[EXIST_WHITE].RangeUpdate();
		m_arrPlayer[EXIST_BLACK].RangeUpdate();
	}
}

void GameFrame::EndGame()
{
	m_arrPlayer[EXIST_WHITE].DeletePiece();
	m_arrPlayer[EXIST_BLACK].DeletePiece();
	delete Res_MG::GetInstance();
	delete Board::GetInstance();
}

GameFrame::~GameFrame()
{
	DeleteObject(m_hFrame);
	SelectObject(m_hGameFrame, m_hOldFrame);
	DeleteDC(m_hGameFrame);
}