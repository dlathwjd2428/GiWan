#include "Board.h"

Board* Board::m_hThis = NULL;
Board::Board()
{
}

void Board::SetBoard()
{
	//보드초기설정
	int Index = IMAGE_BACK1;
	int Exist;
	for (int y = 0; y < ROOM; y++)
	{
		for (int x = 0; x < ROOM; x++)
		{
			if (y == 0 || y == 1)
			{
				Exist = EXIST_WHITE;
				if (y == 0 && x == 3)
					Exist = EXIST_WHITE_KING;
			}
			else if (y == 6 || y == 7)
			{
				Exist = EXIST_BLACK;
				if (y == 7 && x == 4)
					Exist = EXIST_BLACK_KING;
			}
			else
				Exist = EXIST_EMPTY;
			m_arrBoard[y][x].m_iExist = Exist;
			m_arrBoard[y][x].m_iIndex = Index;
			m_arrBoard[y][x].m_Point = { IMAGE_SIZE * x, IMAGE_SIZE * y };
			m_arrBoard[y][x].m_Size = { IMAGE_SIZE, IMAGE_SIZE };
			m_arrBoard[y][x].m_Rect = { m_arrBoard[y][x].m_Point.x, m_arrBoard[y][x].m_Point.y,
				m_arrBoard[y][x].m_Point.x + m_arrBoard[y][x].m_Size.cx, m_arrBoard[y][x].m_Point.y + m_arrBoard[y][x].m_Size.cy };
			if (x != ROOM - 1)
			{
				if (Index == IMAGE_BACK1)
					Index++;
				else
					Index--;
			}
		}
	}
}

void Board::UpdateBoard(int Exist, POINT PrevPt, POINT CurPt)
{
	m_arrBoard[PrevPt.y / 100][PrevPt.x / 100].m_iExist = EXIST_EMPTY;
	m_arrBoard[CurPt.y / 100][CurPt.x / 100].m_iExist = Exist;
}

void Board::DrawBoard(HDC hdc)
{
	for (int y = 0; y < ROOM; y++)
		for (int x = 0; x < ROOM; x++)
			Res_MG::GetInstance()->Draw(hdc, m_arrBoard[y][x].m_iIndex, m_arrBoard[y][x].m_Point);
}

bool Board::KingCheck(HWND hWnd)
{
	bool White = false, Black = false;
	for (int y = 0; y < ROOM; y++)
	{
		for (int x = 0; x < ROOM; x++)
		{
			if (m_arrBoard[y][x].m_iExist == EXIST_BLACK_KING)
				Black = true;
			if (m_arrBoard[y][x].m_iExist == EXIST_WHITE_KING)
				White = true;
		}
	}
	if (!White)
	{
		if (MessageBox(hWnd, "Black플레이어승리!!다시하시겠습니까?", "승리!!", MB_OKCANCEL) == IDOK)
			return true;
		else
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
	}
	if (!Black)
	{
		if (MessageBox(hWnd, "White플레이어승리!!다시하시겠습니까?", "승리!!", MB_OKCANCEL) == IDOK)
			return true;
		else
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
	}
	return false;
}

bool Board::FindExist(int Exist)
{
	for (int y = 0; y < ROOM; y++)
	{
		for (int x = 0; x < ROOM; x++)
		{
			if (m_arrBoard[y][x].m_iExist == Exist)
				return true;
		}
	}
	return false;
}
Board::~Board()
{
}