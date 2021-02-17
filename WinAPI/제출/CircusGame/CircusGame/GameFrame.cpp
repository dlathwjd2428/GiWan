#include "GameFrame.h"

GameFrame::GameFrame()
{
	srand((unsigned)time(NULL));
}

void GameFrame::SetGame(HDC hdc)
{
    //리소스등록
	Res_MG::GetInstance()->Init(hdc);
	//게임프레임설정
	m_hFrameDC = CreateCompatibleDC(hdc);
	m_hFrame = CreateCompatibleBitmap(hdc, WIN_SIZE, WIN_SIZE);
	m_hOldFrame = (HBITMAP)SelectObject(m_hFrameDC, m_hFrame);
	//오브젝트설정
	for (int i = OBJECT_START; i < OBJECT_MAX; i++)
	{
		switch (i)
		{
		case OBJECT_LANE:
			m_arrObject[i] = new Lane;
			break;
		case OBJECT_PEOPLE:
			m_arrObject[i] = new People;
			break;
		case OBJECT_MITER:
			m_arrObject[i] = new Miter;
			break;
		case OBJECT_GOAL:
			m_arrObject[i] = new Goal;
			break;
		case OBJECT_FIREPOT:
			m_arrObject[i] = new FirePot;
			break;
		case OBJECT_RING:
			m_arrObject[i] = new Ring;
			break;
		}
		m_arrObject[i]->SetObject(hdc);
	}
	//캐릭터설정
	m_Char.SetChar();
	//게임기본설정
	m_iClock = clock();
	m_iDirection = NULL;
	m_bGameState = true;
	m_iScore = 0;
}

void GameFrame::UpdateGame(HDC hdc, HWND hWnd)
{
	if (clock() - m_iClock >= 50 && m_bGameState == true)
	{
		Move();
		CollideCheck(hWnd, hdc);
		Draw(hdc);
		m_iClock = clock();
	}
}

void GameFrame::Draw(HDC hdc)
{
	WCHAR buf[256];
	for (int i = OBJECT_START; i < OBJECT_MAX; i++)
		m_arrObject[i]->Draw(m_hFrameDC);
	m_Char.DrawChar(m_hFrameDC);
	if (m_Char.GetState() == CHAR_JUMP)
		m_arrObject[OBJECT_RING]->Draw(m_hFrameDC);
	wsprintf(buf, L"Score : %d", m_iScore);
	Font_Back_MG::GetInstance()->FontBackSet(m_hFrameDC, 47, 157, 39);
	Font_Back_MG::GetInstance()->FontSizeSet(m_hFrameDC, 50);
	Font_Back_MG::GetInstance()->FontColorSet(m_hFrameDC, 0, 0, 0);
	TextOut(m_hFrameDC, 200, 200, buf, lstrlen(buf));
	BitBlt(hdc, 0, 0, WIN_SIZE, WIN_SIZE, m_hFrameDC, 0, 0, SRCCOPY);
	Font_Back_MG::GetInstance()->Reset(m_hFrameDC);
}

void GameFrame::Move()
{
	if (m_Char.GetState() != CHAR_JUMP)
	{
		m_Char.SetState(CHAR_IDLE);
		m_iDirection = NULL;
		if (GetKeyState(VK_LEFT) & 0x8000)
			m_iDirection = LEFT;
		if (GetKeyState(VK_RIGHT) & 0x8000)
			m_iDirection = RIGHT;
		if (m_iDirection != NULL)
			m_Char.SetState(CHAR_MOVE);
		if (GetKeyState(VK_SPACE) & 0x8000)
			m_Char.Jump();
	}
	else
		m_Char.Jump();
	for (int i = OBJECT_START; i < OBJECT_MAX; i++)
		m_arrObject[i]->Move(m_iDirection);
}

void GameFrame::CollideCheck(HWND hWnd, HDC hdc)
{
	int Result;
	if (m_arrObject[OBJECT_GOAL]->CollideCheck(m_Char.GetRect()) == WIN)
	{
		m_bGameState = false;
		m_Char.SetState(CHAR_WIN);
		Draw(hdc);
		if (MessageBox(hWnd, TEXT("승리!!! 다시하시겠습니까?"), TEXT("승리!!"), MB_OKCANCEL) == IDOK)
			SetGame(hdc);
		else
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		return;
	}
	Result = m_arrObject[OBJECT_FIREPOT]->CollideCheck(m_Char.GetRect());
	if (Result == DIE)
	{
		m_bGameState = false;
		m_Char.SetState(CHAR_DIE);
		Draw(hdc);
		if (MessageBox(hWnd, TEXT("패배!!! 다시하시겠습니까?"), TEXT("패배!!"), MB_OKCANCEL) == IDOK)
		{
			SetGame(hdc);
			return;
		}
		else
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);	
	}
	else
		m_iScore += Result;
	Result = NULL;
	Result = m_arrObject[OBJECT_RING]->CollideCheck(m_Char.GetRect());
	if (Result == DIE)
	{
		m_bGameState = false;
		m_Char.SetState(CHAR_DIE);
		Draw(hdc);
		if (MessageBox(hWnd, TEXT("패배!!! 다시하시겠습니까?"), TEXT("패배!!"), MB_OKCANCEL) == IDOK)
		{
			SetGame(hdc);
			return;
		}
		else
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);	
	}
	else
		m_iScore += Result;
}

GameFrame::~GameFrame()
{
}