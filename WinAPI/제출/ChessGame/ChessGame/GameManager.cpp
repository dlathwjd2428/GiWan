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
	m_iTurn = 1;
	//�÷��̾���������
	m_arrPlayer[TYPE_BLACK].SetPlayer(TYPE_BLACK);
	m_arrPlayer[TYPE_WHITE].SetPlayer(TYPE_WHITE);
	//�����ʱ������Ʈ
	UpdateGame();
	//�� ���û��� �ʱ�ȭ
	m_bSelectState = false;
}

void GameManager::UpdateGame()
{
	//�÷��̾������Ʈ
	m_arrPlayer[TYPE_BLACK].UpdatePlayer(m_arrPlayer[TYPE_WHITE].GetRectArr());
	m_arrPlayer[TYPE_WHITE].UpdatePlayer(m_arrPlayer[TYPE_BLACK].GetRectArr());	
	//�����÷��̾�� ���� ����
	if (m_iTurn % 2 == 1)
	{
		m_iPlayer = TYPE_BLACK;
		m_iEnemy = TYPE_WHITE;
		m_iKingIndex = BLACK_KING;
	}
	else
	{
		m_iPlayer = TYPE_WHITE;
		m_iEnemy = TYPE_BLACK;
		m_iKingIndex = WHITE_KING;
	}
}

void GameManager::DrawMap(HDC hdc)
{
	//�ʱ׸���
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
	//����׸���
	m_arrPlayer[TYPE_BLACK].DrawPieceArr(hdc);
	m_arrPlayer[TYPE_WHITE].DrawPieceArr(hdc);
}

void GameManager::DrawRange(HDC hdc)
{
	//�����׸���(���� ���É�������)
	if (m_bSelectState == true)
		m_arrPlayer[m_iEnemy].DrawAtkPiece(hdc, m_arrPlayer[m_iPlayer].DrawRange(hdc));
}

bool GameManager::Click(POINT pt)
{
	int EnemyIndex;
	if (m_bSelectState == false)
		m_bSelectState = m_arrPlayer[m_iPlayer].Click(pt);
	else
	{
		m_bSelectState = false;
		EnemyIndex = m_arrPlayer[m_iPlayer].MovePiece(pt); //�����̱�
		if (EnemyIndex != NONE)
		{	
			m_iTurn++;
			UpdateGame();
			m_arrPlayer[m_iPlayer].DeletePiece(m_arrPlayer[m_iEnemy].GetRectArr()[EnemyIndex]);	 //�޾ƿ� �ε������� ���� ��� �÷��̾��� ���������� ����	
			return true;
		}
	}
	return false;
}

bool GameManager::GameCheck(HWND hWnd)
{
	//true: ���������, false: ���ӱ״������
	UpdateGame();
	//��üũ
	m_arrPlayer[m_iEnemy].PawnCheck(hWnd);
	//ŷ üũ����ƮȮ��
	if (m_arrPlayer[m_iEnemy].KingCheck(m_arrPlayer[m_iPlayer].GetRectArr()[m_iKingIndex]) == true)
	{
		if (MessageBox(hWnd, L"üũ����Ʈ ��� �Ͻðڽ��ϱ�?", L"üũ����Ʈ", MB_OKCANCEL) == IDCANCEL)
			return true; 
	}
	//�ջ���üũ
	LPCWSTR str;
	if (m_iPlayer == TYPE_WHITE)
		str = L"Black�÷��̾�¸�!!";
	else
		str = L"White�÷��̾�¸�!!";
	if (m_arrPlayer[m_iPlayer].GetRectArr()[m_iKingIndex].left == -1000)
	{
		if (MessageBox(hWnd, L"�ٽ��Ͻðڽ��ϱ�?", str, MB_OKCANCEL) == IDCANCEL)
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		else
			return true;
	}
	return false;
}

GameManager::~GameManager()
{
}
