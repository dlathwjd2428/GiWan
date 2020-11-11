#include "Piece.h"

Piece::Piece()
{
}

void Piece::SetPiece(int Index, POINT pt)
{
	//���ҽ��̹����ε���,rect����
	m_Image.m_iIndex = Index;
	m_Image.m_Rect = { pt.x, pt.y, pt.x + IMAGE_SIZE, pt.y + IMAGE_SIZE };
	//Ŭ�������ʱⰪ����
	m_bClickState = false;
	//�̵�Ƚ���ʱⰪ����
	m_iMoveCount = 0;
}

void Piece::DrawPiece(HDC hdc) { BitMapManager::GetInstance()->DrawBitMap(hdc, m_Image.m_iIndex, m_Image.m_Rect); }

void Piece::DrawRange(HDC hdc)
{
	if (m_bClickState == true)
	{
		for (int i = 0; i < m_vMoveRange.size(); i++)
			BitMapManager::GetInstance()->DrawBitMap(hdc, IMAGE_BLOCK_PINK, m_vMoveRange[i]);
		for (int i = 0; i < m_vAtkRange.size(); i++)
			BitMapManager::GetInstance()->DrawBitMap(hdc, IMAGE_BLOCK_PINK, m_vAtkRange[i]);
	}
}

void Piece::SetManager()
{
	m_iAdd = IMAGE_SIZE;
	if (m_Image.m_iIndex < IMAGE_WHITE_PAWN)
		m_iAdd = -IMAGE_SIZE;
	while (!m_vMoveRange.empty())
		m_vMoveRange.pop_back();
	while (!m_vAtkRange.empty())
		m_vAtkRange.pop_back();
}

bool Piece::Move(POINT pt)
{
	//�̵�����Ȯ���� �̵�
	for (int i = 0; i < m_vMoveRange.size(); i++)
	{
		if (PtInRect(&m_vMoveRange[i], pt) == true)
		{
			m_Image.m_Rect = m_vMoveRange[i];
			m_iMoveCount++;
			m_bClickState = false;
			return true;
		}
	}
	//���ݹ���Ȯ���� �̵�
	for (int i = 0; i < m_vAtkRange.size(); i++)
	{
		if (PtInRect(&m_vAtkRange[i], pt) == true)
		{
			m_Image.m_Rect = m_vAtkRange[i];
			m_iMoveCount++;
			m_bClickState = false;
			return true;
		}
	}
	return false;
}

bool Piece::ClickCheck(POINT pt)
{
	if (PtInRect(&m_Image.m_Rect, pt))
		return true;
	return false;
}

bool Piece::Delete(RECT rect)
{
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &rect, &m_Image.m_Rect) == true)
	{
		m_Image.m_Rect = { -1000, -1000, -1000, -1000 };
		m_Image.m_iIndex = IMAGE_BLOCK_PINK;
		m_bClickState = false;
		m_iMoveCount = 0;
		while (!m_vAtkRange.empty())
			m_vAtkRange.pop_back();
		while (!m_vMoveRange.empty())
			m_vMoveRange.pop_back();
		return true;
	}
}
bool Piece::MoveSizeCheck()
{
	if (m_vAtkRange.size() != 0 || m_vMoveRange.size() != 0)
		return true;
	return false;
}

int Piece::CheckIntersectRect(RECT* Player, RECT* Enemy, RECT atkRect, RECT moveRect)
{
	RECT nullRect;
	int Check = 0;
	for (int i = 0; i < PIECE_MAX; i++)
	{
		//���ݹ�������
		if (IntersectRect(&nullRect, &Player[i], &atkRect) == false && IntersectRect(&nullRect, &Enemy[i], &atkRect) == true)
			m_vAtkRange.push_back(atkRect);
		//�̵���������
		if (IntersectRect(&nullRect, &moveRect, &Player[i]) == true || IntersectRect(&nullRect, &moveRect, &Enemy[i]) == true)
			Check++;
	}
	return Check;
}

bool Piece::KingCheck(RECT rect)
{
	RECT null;
	for (int i = 0; i < m_vAtkRange.size(); i++)
	{
		if (IntersectRect(&null, &rect, &m_vAtkRange[i]) == true)
			return true;
	}
	return false;
}

bool Piece::PieceCheck()
{
	if (m_Image.m_iIndex == IMAGE_BLOCK_PINK)
		return true;
	return false;
}

void Piece::PawnChange()
{
	if (m_Image.m_iIndex == IMAGE_WHITE_PAWN)
	{
		if (m_Image.m_Rect.bottom == IMAGE_SIZE * 8)
			system("pause");
	}
	else if(m_Image.m_iIndex == IMAGE_BLACK_PAWN)
	{
		if (m_Image.m_Rect.top == 0)
			system("pause");
	}
}
Piece::~Piece()
{
}

//Pawn
Pawn::Pawn()
{
}

void Pawn::SetRange(RECT* Player, RECT* Enemy)
{
	RECT moveRect, atkRect, nullRect;
	int Check;
	//�ʱⰪ���� �� �����ʱ�ȭ
	SetManager();
	moveRect = m_Image.m_Rect;
	//�̵�, ���ݹ��� ����
	for (int i = 0; i < 2; i++)
	{
		moveRect.left = m_Image.m_Rect.left;
		moveRect.right = moveRect.left + IMAGE_SIZE;
		moveRect.top += m_iAdd;
		moveRect.bottom = moveRect.top + IMAGE_SIZE;
		if (i == 0)
		{
			atkRect.left = m_Image.m_Rect.left - IMAGE_SIZE;
			atkRect.right = atkRect.left + IMAGE_SIZE;
			atkRect.top = m_Image.m_Rect.top + m_iAdd;
			atkRect.bottom = atkRect.top + IMAGE_SIZE;
		}
		else
		{
			atkRect.left = m_Image.m_Rect.left + IMAGE_SIZE;
			atkRect.right = atkRect.left + IMAGE_SIZE;
			atkRect.top = m_Image.m_Rect.top + m_iAdd;
			atkRect.bottom = atkRect.top + IMAGE_SIZE;
		}
		Check = CheckIntersectRect(Player, Enemy, atkRect, moveRect);
		if (Check == 0)
		{
			if (i == 0)
				m_vMoveRange.push_back(moveRect);
			else if(i != 0 && m_iMoveCount == 0)
				m_vMoveRange.push_back(moveRect);
		}
	}
}


Pawn::~Pawn()
{
}
//Pawn

//Knight
Knight::Knight()
{
}

void Knight::SetRange(RECT* Player, RECT* Enemy)
{
	RECT moveRect, atkRect;
	int Check;
	//�ʱⰪ���� �� �����ʱ�ȭ
	SetManager();
	for (int i = 0; i < 8; i++)
	{
		moveRect = m_Image.m_Rect;
		switch (i)
		{
		case 0:	//�������
			moveRect.left = m_Image.m_Rect.left - IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + 2 * m_iAdd;
			break;
		case 1:	//��ܿ���
			moveRect.left = m_Image.m_Rect.left + IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + 2 * m_iAdd;
			break;
		case 2:	//��������
			moveRect.left = m_Image.m_Rect.left + 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + m_iAdd;
			break;
		case 3:	//��������
			moveRect.left = m_Image.m_Rect.left + 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top - m_iAdd;
			break;
		case 4:	//��������
			moveRect.left = m_Image.m_Rect.left - 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top - m_iAdd;
			break;
		case 5:	//��������
			moveRect.left = m_Image.m_Rect.left - 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + m_iAdd;
			break;
		case 6:	//�ϴ�����
			moveRect.left = m_Image.m_Rect.left - IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top - 2 * m_iAdd;
			break;
		case 7:	//�ϴܿ���
			moveRect.left = m_Image.m_Rect.left + IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top - 2 * m_iAdd;
			break;
		}
		moveRect.bottom = moveRect.top + IMAGE_SIZE;
		moveRect.right = moveRect.left + IMAGE_SIZE;
		atkRect = moveRect;
		if (moveRect.left < 0 || moveRect.right > IMAGE_SIZE * 8 + 16 || moveRect.top < 0 || moveRect.bottom > IMAGE_SIZE * 8 + 38)
			continue;
		Check = CheckIntersectRect(Player, Enemy, atkRect, moveRect);
		if (Check == 0)
			m_vMoveRange.push_back(moveRect);
	}
}

Knight::~Knight()
{
}
//Knight

//Bishop
Bishop::Bishop()
{
}

void Bishop::SetRange(RECT* Player, RECT* Enemy)
{
	RECT moveRect, atkRect;
	int Check;
	//�ʱⰪ���� �� �����ʱ�ȭ
	SetManager();
	for (int i = 0; i < 4; i++)
	{
		moveRect = m_Image.m_Rect;
		while (true)
		{
			if (i == 0)//��ܿ���
			{
				moveRect.top += m_iAdd;
				moveRect.left += IMAGE_SIZE;
			}
			else if (i == 1)//�������
			{
				moveRect.top += m_iAdd;
				moveRect.left -= IMAGE_SIZE;
			}
			else if (i == 2)//�ϴܿ���
			{
				moveRect.top -= m_iAdd;
				moveRect.left += IMAGE_SIZE;
			}
			else//�ϴ�����
			{
				moveRect.top -= m_iAdd;
				moveRect.left -= IMAGE_SIZE;
			}
			moveRect.bottom = moveRect.top + IMAGE_SIZE;
			moveRect.right = moveRect.left + IMAGE_SIZE;
			atkRect = moveRect;
			if (moveRect.left < 0 || moveRect.right > IMAGE_SIZE * 8 + 16 || moveRect.top < 0 || moveRect.bottom > IMAGE_SIZE * 8 + 38)
				break;
			Check = CheckIntersectRect(Player, Enemy, atkRect, moveRect);
			if (Check == 0)
				m_vMoveRange.push_back(moveRect);
			else
				break;
		}
	}
}

Bishop::~Bishop()
{
}
//Bishop

//Rock
Rock::Rock()
{
}

void Rock::SetRange(RECT* Player, RECT* Enemy)
{
	RECT moveRect = m_Image.m_Rect, atkRect;
	int Check;
	//�ʱⰪ���� �� �����ʱ�ȭ
	SetManager();
	for (int i = 0; i < 4; i++)
	{
		moveRect = m_Image.m_Rect;
		while (true)
		{
			if (i == 0)//���
				moveRect.top += m_iAdd;
			else if (i == 1)//�ϴ�
				moveRect.top -= m_iAdd;
			else if (i == 2)//����
				moveRect.left += IMAGE_SIZE;
			else//����
				moveRect.left -= IMAGE_SIZE;
			moveRect.bottom = moveRect.top + IMAGE_SIZE;
			moveRect.right = moveRect.left + IMAGE_SIZE;
			atkRect = moveRect;
			if (moveRect.left < 0 || moveRect.right > IMAGE_SIZE * 8 + 16 || moveRect.top < 0 || moveRect.bottom > IMAGE_SIZE * 8 + 38)
				break;
			Check = CheckIntersectRect(Player, Enemy, atkRect, moveRect);
			if (Check == 0)
				m_vMoveRange.push_back(moveRect);
			else
				break;
		}
	}
}

Rock::~Rock()
{
}
//Rock

//Queen
Queen::Queen()
{
}

void Queen::SetRange(RECT* Player, RECT* Enemy)
{
	RECT moveRect, atkRect;
	int Check;
	//�ʱⰪ���� �� �����ʱ�ȭ
	SetManager();
	for (int i = 0; i < 8; i++)
	{
		moveRect = m_Image.m_Rect;
		while (true)
		{
			if (i < 3)//���, �������, ��ܿ���
			{
				moveRect.top += m_iAdd;
				if (i == 1)//��� ����
					moveRect.left -= IMAGE_SIZE;
				else if(i == 2)//��� ����
					moveRect.left += IMAGE_SIZE;
			}
			else if (i >=  3 && i < 6)//�ϴ�, �ϴ�����, �ϴܿ���
			{
				moveRect.top -= m_iAdd;
				if (i == 4)//�ϴ� ����
					moveRect.left -= IMAGE_SIZE;
				else if(i == 5)//�ϴ� ����
					moveRect.left += IMAGE_SIZE;
			}
			else if (i == 6)//����
				moveRect.left -= IMAGE_SIZE;
			else//����
				moveRect.left += IMAGE_SIZE;
			moveRect.bottom = moveRect.top + IMAGE_SIZE;
			moveRect.right = moveRect.left + IMAGE_SIZE;
			atkRect = moveRect;
			if (moveRect.left < 0 || moveRect.right > IMAGE_SIZE * 8 + 16 || moveRect.top < 0 || moveRect.bottom > IMAGE_SIZE * 8 + 38)
				break;
			Check = CheckIntersectRect(Player, Enemy, atkRect, moveRect);
			if (Check == 0)
				m_vMoveRange.push_back(moveRect);
			else
				break;
		}
	}
}

Queen::~Queen()
{
}
//Queen

//King
King::King()
{
}

void King::SetRange(RECT* Player, RECT* Enemy)
{
	RECT moveRect, atkRect;
	int Check;
	//�ʱⰪ���� �� �����ʱ�ȭ
	SetManager();
	for (int i = 0; i < 8; i++)
	{
		moveRect = m_Image.m_Rect;
		switch (i)
		{
		case 0:	//���
			moveRect.top += m_iAdd;
			break;
		case 1:	//�������
			moveRect.top += m_iAdd;
			moveRect.left -= IMAGE_SIZE;
			break;
		case 2:	//�������
			moveRect.top += m_iAdd;
			moveRect.left += IMAGE_SIZE;
			break;
		case 3:	//����
			moveRect.left -= IMAGE_SIZE;
			break;
		case 4:	//����
			moveRect.left += IMAGE_SIZE;
			break;
		case 5:	//�ϴ�
			moveRect.top -= m_iAdd;
			break;
		case 6:	//�����ϴ�
			moveRect.top -= m_iAdd;
			moveRect.left -= IMAGE_SIZE;
			break;
		case 7:	//�����ϴ�
			moveRect.top -= m_iAdd;
			moveRect.left += IMAGE_SIZE;
			break;

		}
		moveRect.bottom = moveRect.top + IMAGE_SIZE;
		moveRect.right = moveRect.left + IMAGE_SIZE;
		atkRect = moveRect;
		if (moveRect.left < 0 || moveRect.right > IMAGE_SIZE * 8 + 16 || moveRect.top < 0 || moveRect.bottom > IMAGE_SIZE * 8 + 38)
			break;
		Check = CheckIntersectRect(Player, Enemy, atkRect, moveRect);
		if (Check == 0)
			m_vMoveRange.push_back(moveRect);
	}
}

King::~King()
{
}
//King