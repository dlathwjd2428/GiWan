#include "Board.h"

Board* Board::m_hThis = NULL;
Board::Board()
{
}

void Board::SetBoard()
{
	ResetBoard();
	int tmpIndex = IMAGE_BACK1;
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			m_arrBoard[y][x].m_iExist = NONE;
			m_arrBoard[y][x].m_iIndex = tmpIndex;
			m_arrBoard[y][x].m_Point = { x * IMAGE_SIZE, y * IMAGE_SIZE };
			if (x != MAX - 1)
			{
				if (tmpIndex == IMAGE_BACK1)
					tmpIndex++;
				else
					tmpIndex--;
			}
		}
	}
}

void Board::DrawBoard(HDC hdc)
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			Res_MG::GetInstance()->Draw(hdc, m_arrBoard[y][x].m_iIndex, m_arrBoard[y][x].m_Point);
		}
	}
}

void Board::ResetBoard()
{
	for (int y = 0; y < MAX; y++)
		for (int x = 0; x < MAX; x++)
			m_arrBoard[y][x].m_iExist = NONE;
}

void Board::UpdateBoard(int Player, POINT pt)
{
	m_arrBoard[pt.y][pt.x].m_iExist = Player;
}

Board::~Board()
{
}