#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::LoadingGame(HWND hWnd)
{
	//이미지파일 로딩
	BitMapManager::GetInstance()->SetBitMapArr(hWnd);
	//맵타일설정
	RECT tmpRect = { 0, 0, tmpRect.left + IMAGE_SIZE, tmpRect.top + IMAGE_SIZE };
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			if ((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0))
				m_arrMap[y][x].m_iIndex = IMAGE_BLOCK_BROWN;
			else
				m_arrMap[y][x].m_iIndex = IMAGE_BLOCK_IVORY;
			m_arrMap[y][x].m_Rect = tmpRect;
			tmpRect.left += IMAGE_SIZE;
		}
		tmpRect.left = 0;
		tmpRect.top += IMAGE_SIZE;
	}
	//플레이어설정
	m_arrPlayer[PLAYER_BLACK].SetPlayer(PLAYER_BLACK);
	m_arrPlayer[PLAYER_WHITE].SetPlayer(PLAYER_WHITE);
}

void GameManager::DrawMap(HDC hdc)
{
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			BitMapManager::GetInstance()->DrawBitMap(hdc, m_arrMap[y][x].m_iIndex, m_arrMap[y][x].m_Rect);
		}
	}
}

void GameManager::DrawPiece(HDC hdc)
{
	m_arrPlayer[PLAYER_BLACK].DrawPiece(hdc);
	m_arrPlayer[PLAYER_WHITE].DrawPiece(hdc);
}

GameManager::~GameManager()
{
}