#include "Board.h"

Board::Board()
{
	srand((unsigned)time(NULL));
}

void Board::SetBoard()
{
	//보드초기화
	for (int y = 0; y < Y; y++)
		for (int x = 0; x < X; x++)
			m_arrBoard[y][x].m_iIndex = NONE;
	m_Save[0] = { NONE, NONE };
	m_Save[1] = { NONE, NONE };
	//보드에 무작위 카드배치
	int i = 0;
	int RNum;
	while (i < CARD_MAX)
	{
		for (int y = 0; y < Y; y++)
		{
			for (int x = 0; x < X; x++)
			{
				RNum = rand() % 100 + 1;
				if (RNum <= 30 && m_arrBoard[y][x].m_iIndex == NONE)
				{
					m_arrBoard[y][x].m_iCardState = CARD_STATE_CLOSE;
					m_arrBoard[y][x].m_iIndex = i % 10;
					m_arrBoard[y][x].m_Point = { x * IMAGE_X + (x + 1) * GAP, y * IMAGE_Y + (y + 1) * GAP };
					m_arrBoard[y][x].m_Rect = { m_arrBoard[y][x].m_Point.x, m_arrBoard[y][x].m_Point.y,
					m_arrBoard[y][x].m_Point.x + IMAGE_X, m_arrBoard[y][x].m_Point.y + IMAGE_Y };
					i++;
				}
			}
		}
	}
}

void Board::Draw(HDC hdc)
{
	int tmpIndex;
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			if (m_arrBoard[y][x].m_iCardState == CARD_STATE_CLOSE)
				tmpIndex = IMAGE_BLACK;
			else
				tmpIndex = m_arrBoard[y][x].m_iIndex;
			Res_MG::GetInstance()->Draw(hdc, tmpIndex, m_arrBoard[y][x].m_Point);
		}
	}
}

int Board::ClickCheck(POINT pt, int& Count)
{
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			if (PtInRect(&m_arrBoard[y][x].m_Rect, pt))
			{
				m_arrBoard[y][x].m_iCardState = CARD_STATE_OPEN;
				m_Save[Count++] = { x, y };
				if (Count == 2)
				{
					Count = 0;
					return CorrectCheck();
				}
				return NONE;
			}
		}
	}
	return NONE;
}

bool Board::CorrectCheck()
{
	if (m_arrBoard[m_Save[0].y][m_Save[0].x].m_iIndex == m_arrBoard[m_Save[1].y][m_Save[1].x].m_iIndex)
	{
		m_arrBoard[m_Save[0].y][m_Save[0].x].m_iCardState = CARD_STATE_FIX;
		m_arrBoard[m_Save[1].y][m_Save[1].x].m_iCardState = CARD_STATE_FIX;
		m_Save[0] = { NONE, NONE };
		m_Save[1] = { NONE, NONE };
		return TRUE;
	}
	return FALSE;
}

void Board::CloseCard()
{
	if (m_Save[0].x != NONE && m_Save[1].x != NONE)
	{
		m_arrBoard[m_Save[0].y][m_Save[0].x].m_iCardState = CARD_STATE_CLOSE;
		m_arrBoard[m_Save[1].y][m_Save[1].x].m_iCardState = CARD_STATE_CLOSE;
		m_Save[0] = { NONE, NONE };
		m_Save[1] = { NONE, NONE };
	}
}

bool Board::WinCheck()
{
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			if (m_arrBoard[y][x].m_iCardState != CARD_STATE_FIX)
				return false;
		}
	}
	return true;
}
Board::~Board()
{
}