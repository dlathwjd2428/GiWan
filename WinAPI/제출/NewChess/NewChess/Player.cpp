#include "Player.h"

Player::Player()
{
}

void Player::SetPlayer(int Color)
{
	//�÷��̾�⺻����
	int Add = 0, AddSize = 100, Index;
	POINT pt = { 0, 600 };
	m_iColor = Color;
	if (Color == EXIST_BLACK)
		m_iEnemy = EXIST_WHITE;
	else
		m_iEnemy = EXIST_BLACK;
	if (m_iColor == EXIST_WHITE)
	{
		Add = 6;
		pt = { 0, 100 };
		AddSize = -100;
	}
	m_iAdd = -AddSize;
	m_iSaveIndex = DIE;
	//���� ����
	int KingAdd = 0;
	for (int i = 0; i < PIECE_MAX; i++)
	{
		KingAdd = 0;
		if (i < 8)
		{
			Index = IMAGE_B_PAWN;
			m_parrPiece[i] = new Pawn;
		}
		else if (i == 8 || i == PIECE_MAX - 1)
		{
			Index = IMAGE_B_ROCK;
			m_parrPiece[i] = new Rock;
		}
		else if (i == 9 || i == PIECE_MAX - 2)
		{
			Index = IMAGE_B_BISHOP;
			m_parrPiece[i] = new Bishop;
		}
		else if (i == 10 || i == PIECE_MAX - 3)
		{
			Index = IMAGE_B_KNIGHT;
			m_parrPiece[i] = new Knight;
		}
		else if (i == 11)
		{
			if (m_iColor == EXIST_BLACK)
			{
				Index = IMAGE_B_QUEEN;
				m_parrPiece[i] = new Queen;
			}
			else
			{
				KingAdd = 2;
				Index = IMAGE_B_KING;
				m_parrPiece[i] = new King;
			}
		}
		else
		{
			if (m_iColor == EXIST_BLACK)
			{
				KingAdd = 2;
				Index = IMAGE_B_KING;
				m_parrPiece[i] = new King;
			}
			else
			{
				Index = IMAGE_B_QUEEN;
				m_parrPiece[i] = new Queen;
			}
		}
		if (m_iColor == EXIST_WHITE)
			Index += 6;
		m_parrPiece[i]->SetPiece(m_iColor + KingAdd, m_iEnemy, Index, m_iAdd, pt);
		pt.x += IMAGE_SIZE;
		if (i == 7)
		{
			pt.x = 0;
			pt.y += AddSize;
		}
	}
	//���� ���ݹ�������
	RangeUpdate();
}

void Player::Draw(HDC hdc)
{
	for (int i = 0; i < PIECE_MAX; i++)
		m_parrPiece[i]->Draw(hdc);
}

bool Player::Click(HWND hWnd, POINT pt, int& Turn)
{
	if (m_iSaveIndex == DIE)	//����Ŭ���� �ش� ��ġ�� �����ϸ� �� index�� �����Ѵ�
	{
		for (int i = 0; i < PIECE_MAX; i++)
		{
			if (m_parrPiece[i]->Click(pt) == true)
			{
				m_iSaveIndex = i;
				break;
			}
		}
	}
	else	//����Ŭ���� �ƴҰ�� ����� index��ȣ�� ���� �����δ�
	{
		if (m_parrPiece[m_iSaveIndex]->Move(pt) == true)//���� ����������
		{
			m_parrPiece[m_iSaveIndex]->SetRange();
			KingCheck(hWnd);
			PawnChange();
			Turn++;
			return true;
		}
		if(pt.x == DIE)//���� ���������ʾ�����
			m_iSaveIndex = DIE;
	}
	return false;
}

void Player::RangeUpdate()
{
	for (int i = 0; i < PIECE_MAX; i++)
		m_parrPiece[i]->SetRange();
}

void Player::Die(POINT pt)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (m_parrPiece[i]->Die(pt) == true)
		{
			pt = { DIE, DIE };
			Board::GetInstance()->SetKillPoint(pt);
			break;
		}
	}
}

void Player::PawnChange()
{
	POINT pt = m_parrPiece[m_iSaveIndex]->GetPoint();
	int Index = m_parrPiece[m_iSaveIndex]->GetIndex();
	if (Board::GetInstance()->FindExist(m_iEnemy + 2)
		&& (Index == IMAGE_B_PAWN || Index == IMAGE_W_PAWN) && (pt.y == 0 || pt.y == 700))
	{
		POINT tmpPoint = m_parrPiece[m_iSaveIndex]->GetPoint();
		int Add = 0;
		if (m_iColor == EXIST_WHITE)
			Add = 6;
		delete m_parrPiece[m_iSaveIndex];
		while (true)
		{
			if (MessageBox(NULL, "������ �ٲٽðڽ��ϱ�?", "������ ����!!", MB_OKCANCEL) == IDOK)
			{
				m_parrPiece[m_iSaveIndex] = new Pawn;
				m_parrPiece[m_iSaveIndex]->SetPiece(m_iColor, m_iEnemy, IMAGE_B_PAWN + Add, m_iAdd, tmpPoint);
				break;
			}
			if (MessageBox(NULL, "����Ʈ���� �ٲٽðڽ��ϱ�?", "������ ����!!", MB_OKCANCEL) == IDOK)
			{
				m_parrPiece[m_iSaveIndex] = new Knight;
				m_parrPiece[m_iSaveIndex]->SetPiece(m_iColor, m_iEnemy, IMAGE_B_KNIGHT + Add, m_iAdd, tmpPoint);
				break;
			}
			if (MessageBox(NULL, "������ �ٲٽðڽ��ϱ�?", "������ ����!!", MB_OKCANCEL) == IDOK)
			{
				m_parrPiece[m_iSaveIndex] = new Rock;
				m_parrPiece[m_iSaveIndex]->SetPiece(m_iColor, m_iEnemy, IMAGE_B_ROCK + Add, m_iAdd, tmpPoint);
				break;
			}
			if (MessageBox(NULL, "������� �ٲٽðڽ��ϱ�?", "������ ����!!", MB_OKCANCEL) == IDOK)
			{
				m_parrPiece[m_iSaveIndex] = new Bishop;
				m_parrPiece[m_iSaveIndex]->SetPiece(m_iColor, m_iEnemy, IMAGE_B_BISHOP + Add, m_iAdd, tmpPoint);
				break;
			}
			if (MessageBox(NULL, "������ �ٲٽðڽ��ϱ�?", "������ ����!!", MB_OKCANCEL) == IDOK)
			{
				m_parrPiece[m_iSaveIndex] = new Queen;
				m_parrPiece[m_iSaveIndex]->SetPiece(m_iColor, m_iEnemy, IMAGE_B_QUEEN + Add, m_iAdd, tmpPoint);	
				break;
			}
		}
	}
}

void Player::KingCheck(HWND hWnd)
{
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (m_parrPiece[i]->KingCheck() == true)
		{
			if (MessageBox(hWnd, "üũ����Ʈ!!�ٽ��Ͻðڽ��ϱ�?", "üũ����Ʈ", MB_OKCANCEL) == IDOK)
				SendMessage(hWnd, WM_DESTROY, NULL, NULL);
		}
	}
}

void Player::DeletePiece()
{
	for (int i = 0; i < PIECE_MAX; i++)
		delete m_parrPiece[i];
}

Player::~Player()
{
}