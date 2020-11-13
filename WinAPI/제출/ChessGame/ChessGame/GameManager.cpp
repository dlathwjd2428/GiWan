#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::LoadingGame(HWND hWnd)
{
	//비트맵이미지로딩
	BitMapManager::GetBManager()->SetBitMapArr(hWnd);
	//맵타일정보설정
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
	//턴수설정
	m_iTurn = 1;
	//플레이어정보설정
	m_arrPlayer[TYPE_BLACK].SetPlayer(TYPE_BLACK);
	m_arrPlayer[TYPE_WHITE].SetPlayer(TYPE_WHITE);
	//게임초기업데이트
	UpdateGame();
	//말 선택상태 초기화
	m_bSelectState = false;
}

void GameManager::UpdateGame()
{
	//플레이어업데이트
	m_arrPlayer[TYPE_BLACK].UpdatePlayer(m_arrPlayer[TYPE_WHITE].GetRectArr());
	m_arrPlayer[TYPE_WHITE].UpdatePlayer(m_arrPlayer[TYPE_BLACK].GetRectArr());	
	//현재플레이어와 적군 설정
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
	//맵그리기
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
	//말들그리기
	m_arrPlayer[TYPE_BLACK].DrawPieceArr(hdc);
	m_arrPlayer[TYPE_WHITE].DrawPieceArr(hdc);
}

void GameManager::DrawRange(HDC hdc)
{
	//범위그리기(말이 선택됬을때만)
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
		EnemyIndex = m_arrPlayer[m_iPlayer].MovePiece(pt); //움직이기
		if (EnemyIndex != NONE)
		{	
			m_iTurn++;
			UpdateGame();
			m_arrPlayer[m_iPlayer].DeletePiece(m_arrPlayer[m_iEnemy].GetRectArr()[EnemyIndex]);	 //받아온 인덱스값을 통해 상대 플레이어의 말이있으면 삭제	
			return true;
		}
	}
	return false;
}

bool GameManager::GameCheck(HWND hWnd)
{
	//true: 게임재시작, false: 게임그대로진행
	UpdateGame();
	//폰체크
	m_arrPlayer[m_iEnemy].PawnCheck(hWnd);
	//킹 체크메이트확인
	if (m_arrPlayer[m_iEnemy].KingCheck(m_arrPlayer[m_iPlayer].GetRectArr()[m_iKingIndex]) == true)
	{
		if (MessageBox(hWnd, L"체크메이트 계속 하시겠습니까?", L"체크메이트", MB_OKCANCEL) == IDCANCEL)
			return true; 
	}
	//왕생존체크
	LPCWSTR str;
	if (m_iPlayer == TYPE_WHITE)
		str = L"Black플레이어승리!!";
	else
		str = L"White플레이어승리!!";
	if (m_arrPlayer[m_iPlayer].GetRectArr()[m_iKingIndex].left == -1000)
	{
		if (MessageBox(hWnd, L"다시하시겠습니까?", str, MB_OKCANCEL) == IDCANCEL)
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		else
			return true;
	}
	return false;
}

GameManager::~GameManager()
{
}
