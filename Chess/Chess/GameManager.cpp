#include "GameManager.h"

GameManager::GameManager()
{
	m_iTurn = 1;
	m_bSelectState = false;
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
	//정보업데이트
	UpdateGame();
}

void GameManager::UpdateGame()
{
	//플레이어 턴 업데이트
	if (m_iTurn % 2 == 0)
	{
		m_iPlayer = PLAYER_WHITE;
		m_iEnemy = PLAYER_BLACK;
	}
	else
	{
		m_iPlayer = PLAYER_BLACK;
		m_iEnemy = PLAYER_WHITE;
	}	
	//플레이어 정보들 업데이트
	m_arrPlayer[PLAYER_BLACK].UpdatePlayer(m_arrPlayer[PLAYER_WHITE].GetRectArr());
	m_arrPlayer[PLAYER_WHITE].UpdatePlayer(m_arrPlayer[PLAYER_BLACK].GetRectArr());
}

void GameManager::GameDraw(HDC hdc)
{
	//맵그리기
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			BitMapManager::GetInstance()->DrawBitMap(hdc, m_arrMap[y][x].m_iIndex, m_arrMap[y][x].m_Rect);
		}
	}
	//플레이어말그리기
	m_arrPlayer[PLAYER_BLACK].DrawPiece(hdc);
	m_arrPlayer[PLAYER_WHITE].DrawPiece(hdc);

	//움직임범위그리기
	if (m_bSelectState == true)
		m_arrPlayer[m_iPlayer].DrawRange(hdc);
}

void GameManager::ClicK(POINT pt)
{
	int EnemyIndex;
	UpdateGame();
	m_bSelectState = m_arrPlayer[m_iPlayer].Click(pt);
	if (m_bSelectState == true)
	{
		EnemyIndex = m_arrPlayer[m_iPlayer].Move(pt);	
		if (EnemyIndex != FALSE)
		{
			UpdateGame();
			m_arrPlayer[m_iEnemy].DeletePiece(m_arrPlayer[m_iPlayer].GetRectArr()[EnemyIndex]);
			m_iTurn++;
			m_bSelectState = false;			
		}
		
	}
}

GameManager::~GameManager()
{
}