#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::SetGame(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	//이미지로드
	BitManager::GetInstance()->Init(hdc);
	//기본맵세팅
	m_Map.SetMap(hdc);
	//캐릭터설정
	m_Character.SetCharacter();
	//장애물설정
	m_Obstacle.SetObstacle();
	//재시작시 벡터로 할당된 링들 재설정
	m_Obstacle.DeleteRing();
	//업데이트함수 제어용 시간변수 설정
	m_iClock = clock();
	//게임진행상태 설정
	m_bMessageState = false;
	m_iGameState = GAME_STATE_TRUE;
	ReleaseDC(hWnd, hdc);
}

void GameManager::SetMessageState()
{
	m_bMessageState = false;
	if (GetJump() != true)
		m_Character.Default(IMAGE_CHARACTER1);
}

void GameManager::UpdateGame(HWND hWnd)
{
	if (m_bMessageState == false && clock() - m_iClock > CREATE_SPEED)
	{
		m_Obstacle.SetRingSpeed();
		m_Obstacle.CreateRing();
		m_Obstacle.Update();
		InvalidateRect(hWnd, NULL, false);
		m_iClock = clock() + CREATE_SPEED;
	}
}

void GameManager::Draw(HDC hdc, int Option)
{
	//맵그리기
	m_Map.Draw(hdc);
	//장애물그리기
	m_Obstacle.Draw(hdc);
	//캐릭터그리기
	if (Option == WIN)
	{
		m_Character.Default(IMAGE_WIN1);
		m_Character.Draw(hdc, WIN);
	}
	else if(Option == DIE)
	{
		m_Character.Default(IMAGE_DIE);
		m_Character.Draw(hdc, DIE);
	}
	else
		m_Character.Draw(hdc);
	//캐릭터상태가 점프이면 링의 우측편만 한번 더 그려주기
	if (m_Character.GetJumpState() == true)
		m_Obstacle.RightDraw(hdc);
	
}

void GameManager::Move()
{
	//점프
	if ((GetKeyState(VK_RETURN) & 0x8000) && m_Character.GetJumpState() == false)
		m_Character.Jump();
	if (m_Character.GetJumpState() == true)
		m_Character.Jump();
	//이동입력
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_Map.Move(LEFT);
		m_Character.Move();
		m_Obstacle.Move(LEFT);
		m_bMessageState = true;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_Map.Move(RIGHT);
		m_Character.Move();
		m_Obstacle.Move(RIGHT);
		m_bMessageState = true;
	}

}

void GameManager::CollideCheck(HWND hWnd)
{
	int Check;
	if (m_iGameState == GAME_STATE_TRUE)
	{
		Check = m_Obstacle.CollideCheck(m_Character.GetCharRect());
		//장애물에 부딪히면
		if (Check == DIE)
		{
			m_Character.Default(IMAGE_DIE);
			m_iGameState = GAME_STATE_FALSE;
			if (MessageBox(hWnd, TEXT("죽음...다시하시겠습니까?"), TEXT("죽음..."), MB_OKCANCEL) == IDOK)
				SetGame(hWnd);
			else
				SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		//골인지점에 부딪히면
		if (Check == WIN)
		{
			m_iGameState = GAME_STATE_PAUSE;
			//InvalidateRect(hWnd, NULL, true);
			if (MessageBox(hWnd, TEXT("승리!!!다시하시겠습니까?"), TEXT("승리!!!"), MB_OKCANCEL) == IDOK)
				SetGame(hWnd);
			else
				SendMessage(hWnd, WM_DESTROY, 0, 0);
		
		}
	}
}

GameManager::~GameManager()
{
}