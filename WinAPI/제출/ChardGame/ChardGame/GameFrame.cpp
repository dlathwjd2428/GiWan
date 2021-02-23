#include "GameFrame.h"

GameFrame::GameFrame()
{
}

void GameFrame::SetGame(HDC hdc)
{
	 //리소스등록
	Res_MG::GetInstance()->Init(hdc);
	//더블버퍼링용 프레임설정
	RECT rt = { 0, 0, WIN_X, WIN_Y };
	m_hFrameDC = CreateCompatibleDC(hdc);
	m_hFrame = CreateCompatibleBitmap(hdc, WIN_X, WIN_Y);
	m_hOldFrame = (HBITMAP)SelectObject(m_hFrameDC, m_hFrame);
	FillRect(m_hFrameDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));
	//게임초기설정
	m_Board.SetBoard();
	m_iClick = CLICK_NONE;
	m_iClock = clock();
	m_iStopClock = clock();
}

void GameFrame::UpdateGame(HWND hWnd, HDC hdc, POINT& pt)
{	
	if (clock() - m_iClock >= 50)
	{
		if (clock() - m_iStopClock >= 0)
		{
			m_Board.CloseCard();
			Click(pt);
			Draw(hdc);
			if (m_Board.WinCheck())
			{
				if (MessageBox(hWnd, "승리!!!다시하시겠습니까?", "승리!!!", MB_OKCANCEL) == IDOK)
					SetGame(hdc);
				else
				{
					EndGame();
					SendMessage(hWnd, WM_DESTROY, NULL, NULL);
				}
			}
		}
		m_iClock = clock();
		pt = { NONE, NONE };
	}
}

void GameFrame::Draw(HDC hdc)
{
	POINT tmpPoint = { 0, 0 };
	SIZE tmpSize = { WIN_X, WIN_Y };
	Res_MG::GetInstance()->Draw(m_hFrameDC, IMAGE_BACK, tmpPoint, tmpSize);
	m_Board.Draw(m_hFrameDC);
	BitBlt(hdc, 0, 0, WIN_X, WIN_Y, m_hFrameDC, 0, 0, SRCCOPY);
}

void GameFrame::Click(POINT pt)
{
	int Result;
	if (pt.x != NONE)
	{
		Result = m_Board.ClickCheck(pt, m_iClick);
		if (Result == FALSE)
			m_iStopClock = clock() + 1000;
	}
}

void GameFrame::EndGame()
{
	delete Res_MG::GetInstance();
}

GameFrame::~GameFrame()
{
	DeleteObject(m_hFrame);
	SelectObject(m_hFrameDC, m_hOldFrame);
	DeleteDC(m_hFrameDC);
}