#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::SetGame(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	//�̹����ε�
	BitManager::GetInstance()->Init(hdc);
	//�⺻�ʼ���
	m_Map.SetMap(hdc);
	//ĳ���ͼ���
	m_Character.SetCharacter();
	//��ֹ�����
	m_Obstacle.SetObstacle();
	//����۽� ���ͷ� �Ҵ�� ���� �缳��
	m_Obstacle.DeleteRing();
	//������Ʈ�Լ� ����� �ð����� ����
	m_iClock = clock();
	//����������� ����
	m_bMessageState = false;
	m_bGameState = true;
	ReleaseDC(hWnd, hdc);
}

void GameManager::SetMessageState()
{
	m_bMessageState = false;
	if (GetJump() != true)
		m_Character.Default();
}

void GameManager::UpdateGame(HWND hWnd)
{
	if (m_bMessageState == false && clock() - m_iClock > CREATE_SPEED)
	{
		m_Obstacle.CreateRing();
		m_Obstacle.Update();
		InvalidateRect(hWnd, NULL, false);
		m_iClock = clock() + CREATE_SPEED;
	}
}

void GameManager::Draw(HDC hdc)
{
	//�ʱ׸���
	m_Map.Draw(hdc);
	//��ֹ��׸���
	m_Obstacle.Draw(hdc);
	//ĳ���ͱ׸���
	m_Character.Draw(hdc);
	//ĳ���ͻ��°� �����̸� ���� ������ �ѹ� �� �׷��ֱ�
	if (m_Character.GetJumpState() == true)
		m_Obstacle.RightDraw(hdc);
}

void GameManager::Move()
{
	//���̵��ӵ� �ʱ�ȭ
	m_Obstacle.SetRingSpeed();
	//����
	if ((GetKeyState(VK_RETURN) & 0x8000) && m_Character.GetJumpState() == false)
		m_Character.Jump();
	if (m_Character.GetJumpState() == true)
		m_Character.Jump();
	//�̵��Է�
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
	if (m_bGameState == true)
	{
		Check = m_Obstacle.CollideCheck(m_Character.GetCharRect());
		//��ֹ��� �ε�����
		if (Check == DIE)
		{
			m_bGameState = false;
			if (MessageBox(hWnd, TEXT("����...�ٽ��Ͻðڽ��ϱ�?"), TEXT("����..."), MB_OKCANCEL) == IDOK)
				SetGame(hWnd);
			else
				SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		//���������� �ε�����
		else if (Check == WIN)
		{
			m_bGameState = false;
			if (MessageBox(hWnd, TEXT("�¸�!!!�ٽ��Ͻðڽ��ϱ�?"), TEXT("�¸�!!!"), MB_OKCANCEL) == IDOK)
				SetGame(hWnd);
			else
				SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
	}
}

GameManager::~GameManager()
{
}