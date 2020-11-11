#include "Piece.h"

Piece::Piece()
{
}

void Piece::SetPiece(int Index, POINT pt)
{
	//리소스이미지인덱스,rect설정
	m_Image.m_iIndex = Index;
	m_Image.m_Rect = { pt.x, pt.y, pt.x + IMAGE_SIZE, pt.y + IMAGE_SIZE };
	//클릭상태초기값설정
	m_bClickState = false;
	//이동횟수초기값설정
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
	//이동범위확인후 이동
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
	//공격범위확인후 이동
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
		//공격범위설정
		if (IntersectRect(&nullRect, &Player[i], &atkRect) == false && IntersectRect(&nullRect, &Enemy[i], &atkRect) == true)
			m_vAtkRange.push_back(atkRect);
		//이동범위설정
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
	//초기값설정 및 벡터초기화
	SetManager();
	moveRect = m_Image.m_Rect;
	//이동, 공격범위 설정
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
	//초기값설정 및 벡터초기화
	SetManager();
	for (int i = 0; i < 8; i++)
	{
		moveRect = m_Image.m_Rect;
		switch (i)
		{
		case 0:	//상단좌측
			moveRect.left = m_Image.m_Rect.left - IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + 2 * m_iAdd;
			break;
		case 1:	//상단우측
			moveRect.left = m_Image.m_Rect.left + IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + 2 * m_iAdd;
			break;
		case 2:	//우측좌측
			moveRect.left = m_Image.m_Rect.left + 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + m_iAdd;
			break;
		case 3:	//우측우측
			moveRect.left = m_Image.m_Rect.left + 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top - m_iAdd;
			break;
		case 4:	//좌측좌측
			moveRect.left = m_Image.m_Rect.left - 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top - m_iAdd;
			break;
		case 5:	//좌측우측
			moveRect.left = m_Image.m_Rect.left - 2 * IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top + m_iAdd;
			break;
		case 6:	//하단좌측
			moveRect.left = m_Image.m_Rect.left - IMAGE_SIZE;
			moveRect.top = m_Image.m_Rect.top - 2 * m_iAdd;
			break;
		case 7:	//하단우측
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
	//초기값설정 및 벡터초기화
	SetManager();
	for (int i = 0; i < 4; i++)
	{
		moveRect = m_Image.m_Rect;
		while (true)
		{
			if (i == 0)//상단우측
			{
				moveRect.top += m_iAdd;
				moveRect.left += IMAGE_SIZE;
			}
			else if (i == 1)//상단좌측
			{
				moveRect.top += m_iAdd;
				moveRect.left -= IMAGE_SIZE;
			}
			else if (i == 2)//하단우측
			{
				moveRect.top -= m_iAdd;
				moveRect.left += IMAGE_SIZE;
			}
			else//하단좌측
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
	//초기값설정 및 벡터초기화
	SetManager();
	for (int i = 0; i < 4; i++)
	{
		moveRect = m_Image.m_Rect;
		while (true)
		{
			if (i == 0)//상단
				moveRect.top += m_iAdd;
			else if (i == 1)//하단
				moveRect.top -= m_iAdd;
			else if (i == 2)//우측
				moveRect.left += IMAGE_SIZE;
			else//좌측
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
	//초기값설정 및 벡터초기화
	SetManager();
	for (int i = 0; i < 8; i++)
	{
		moveRect = m_Image.m_Rect;
		while (true)
		{
			if (i < 3)//상단, 상단좌측, 상단우측
			{
				moveRect.top += m_iAdd;
				if (i == 1)//상단 좌측
					moveRect.left -= IMAGE_SIZE;
				else if(i == 2)//상단 우측
					moveRect.left += IMAGE_SIZE;
			}
			else if (i >=  3 && i < 6)//하단, 하단좌측, 하단우측
			{
				moveRect.top -= m_iAdd;
				if (i == 4)//하단 좌측
					moveRect.left -= IMAGE_SIZE;
				else if(i == 5)//하단 우측
					moveRect.left += IMAGE_SIZE;
			}
			else if (i == 6)//좌측
				moveRect.left -= IMAGE_SIZE;
			else//우측
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
	//초기값설정 및 벡터초기화
	SetManager();
	for (int i = 0; i < 8; i++)
	{
		moveRect = m_Image.m_Rect;
		switch (i)
		{
		case 0:	//상단
			moveRect.top += m_iAdd;
			break;
		case 1:	//좌측상단
			moveRect.top += m_iAdd;
			moveRect.left -= IMAGE_SIZE;
			break;
		case 2:	//우측상단
			moveRect.top += m_iAdd;
			moveRect.left += IMAGE_SIZE;
			break;
		case 3:	//좌측
			moveRect.left -= IMAGE_SIZE;
			break;
		case 4:	//우측
			moveRect.left += IMAGE_SIZE;
			break;
		case 5:	//하단
			moveRect.top -= m_iAdd;
			break;
		case 6:	//좌측하단
			moveRect.top -= m_iAdd;
			moveRect.left -= IMAGE_SIZE;
			break;
		case 7:	//우측하단
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