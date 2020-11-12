#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::LoadingGame(HWND hWnd)
{
	//��Ʈ���̹����ε�
	BitMapManager::GetBManager()->SetBitMapArr(hWnd);
	//��Ÿ����������
	POINT tmpPoint = {0, 0};
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
				m_arrMap[y][x].m_iImageIndex = IMAGE_BLOCK_BROWN;
			else
				m_arrMap[y][x].m_iImageIndex = IMAGE_BLOCK_IVORY;
			m_arrMap[y][x].m_ImageRect = { tmpPoint.x, tmpPoint.y, tmpPoint.x + IMAGE_SIZE, tmpPoint.y + IMAGE_SIZE };
			tmpPoint.x += IMAGE_SIZE;
		}
		tmpPoint.x = 0;
		tmpPoint.y += IMAGE_SIZE;
	}
	//�ϼ�����
	m_iTurn = 0;
	//�÷��̾���������
	m_arrPlayer[TYPE_BLACK].SetPlayer(TYPE_BLACK);
	m_arrPlayer[TYPE_WHITE].SetPlayer(TYPE_WHITE);
	//�����ʱ������Ʈ
	UpdateGame();
}

void GameManager::UpdateGame()
{
	//�ϼ����������� ���࿹���̹Ƿ�
	m_iTurn++;
	//�����÷��̾�� ���� ����
	if (m_iTurn % 2 == 1)
	{
		m_iPlayer = TYPE_BLACK;
		m_iEnemy = TYPE_WHITE;
	}
	else
	{
		m_iPlayer = TYPE_WHITE;
		m_iEnemy = TYPE_BLACK;
	}
	//�÷��̾������Ʈ
	m_arrPlayer[TYPE_BLACK].UpdatePlayer(m_arrPlayer[TYPE_WHITE].GetRectArr());
	m_arrPlayer[TYPE_WHITE].UpdatePlayer(m_arrPlayer[TYPE_BLACK].GetRectArr());
}

void GameManager::DrawMap(HDC hdc)
{
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			BitMapManager::GetBManager()->DrawBitMap(hdc, m_arrMap[y][x].m_iImageIndex, m_arrMap[y][x].m_ImageRect);
		}
	}
}

void GameManager::DrawPiece(HDC hdc)
{
	m_arrPlayer[TYPE_BLACK].DrawPieceArr(hdc);
	m_arrPlayer[TYPE_WHITE].DrawPieceArr(hdc);
}

void GameManager::Click(POINT pt)
{
	m_arrPlayer[m_iPlayer].Click(pt);
}
GameManager::~GameManager()
{
}
