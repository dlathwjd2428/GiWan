#include "Piece.h"

Piece::Piece()
{
}

void Piece::SetInfo(int Index, POINT pt)
{
	//이동횟수초기화
	m_iMoveCount = 0;
	//말 이미지주소, rect설정
	m_Image.m_iImageIndex = Index;
	m_Image.m_ImageRect = { pt.x, pt.y, pt.x + IMAGE_SIZE, pt.y + IMAGE_SIZE };
	//Y축 + 값설정
	AddY = IMAGE_SIZE;
	if (m_Image.m_iImageIndex < IMAGE_WHITE_PAWN)
		AddY = -IMAGE_SIZE;
}

void Piece::SetDefault()
{
	while (!m_vAtkRange.empty())
		m_vAtkRange.pop_back();
	while (!m_vMoveRange.empty())
		m_vMoveRange.pop_back();
}

void Piece::DrawPiece(HDC hdc) { BitMapManager::GetBManager()->DrawBitMap(hdc, m_Image.m_iImageIndex, m_Image.m_ImageRect); }

std::vector<RECT> Piece::DrawRange(HDC hdc)
{
	for (int i = 0; i < m_vMoveRange.size(); i++)
		BitMapManager::GetBManager()->DrawBitMap(hdc, IMAGE_BLOCK_PINK, m_vMoveRange[i], PINK);	
	return m_vAtkRange;
}

int Piece::CheckRectForRange(RECT* player, RECT* enemy, RECT Move, RECT Atk)
{
	RECT null;
	int Check = 0;
	for (int i = 0; i < PIECE_MAX; i++)
	{
		if (IntersectRect(&null, &Move, &player[i]) == true || IntersectRect(&null, &Move, &enemy[i]) == true
			|| (Move.left < 0 || Move.right > IMAGE_SIZE * 8 + 16 || Move.top < 0 || Move.bottom > IMAGE_SIZE * 8 + 38))
			Check++;
		if (IntersectRect(&null, &Atk, &player[i]) == false && IntersectRect(&null, &Atk, &enemy[i]) == true)
			m_vAtkRange.push_back(Atk);
	}
	return Check;
}

bool Piece::ClickCheck(POINT pt)
{
	if (PtInRect(&m_Image.m_ImageRect, pt))
		return true;
	return false;
}

bool Piece::Move(POINT pt)
{
	for (int i = 0; i < m_vMoveRange.size(); i++)
	{
		if (PtInRect(&m_vMoveRange[i], pt) == true)
		{
			m_Image.m_ImageRect = m_vMoveRange[i];
			m_iMoveCount++;
			return true;
		}
	}
	for (int i = 0; i < m_vAtkRange.size(); i++)
	{
		if (PtInRect(&m_vAtkRange[i], pt) == true)
		{
			m_Image.m_ImageRect = m_vAtkRange[i];
			m_iMoveCount++;
			return true;
		}
	}
	return false;
}

void Piece::RectCheck(std::vector<RECT> rect, HDC hdc)
{
	RECT tmp;
	for (int i = 0; i < rect.size(); i++)
	{
		if (IntersectRect(&tmp, &rect[i], &m_Image.m_ImageRect) == true)
			BitMapManager::GetBManager()->DrawBitMap(hdc, m_Image.m_iImageIndex, m_Image.m_ImageRect, PINK);
	}
}

bool Piece::Delete(RECT rect)
{
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &rect, &m_Image.m_ImageRect) == true)
	{
		m_Image.m_ImageRect = { -1000, -1000, -1000, -1000 };
		m_Image.m_iImageIndex = IMAGE_BLOCK_PINK;
		m_iMoveCount = 0;
		while (!m_vAtkRange.empty())
			m_vAtkRange.pop_back();
		while (!m_vMoveRange.empty())
			m_vMoveRange.pop_back();
		return true;
	}
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

Piece::~Piece()
{
}

//Pawn
Pawn::Pawn()
{
}

void Pawn::SetRange(RECT* player, RECT* enemy)
{
	RECT tmpMove, tmpAtk;
	SetDefault();
	tmpMove = m_Image.m_ImageRect;
	for (int i = 0; i < 2; i++)
	{
		tmpAtk = m_Image.m_ImageRect;
		if (i == 0)
		{
			tmpAtk.left -= IMAGE_SIZE;
			tmpAtk.top += AddY;
		}
		else
		{
			tmpAtk.left += IMAGE_SIZE;
			tmpAtk.top += AddY;
		}
		tmpMove.top += AddY;
		tmpMove.bottom = tmpMove.top + IMAGE_SIZE;
		tmpAtk.right = tmpAtk.left + IMAGE_SIZE;
		tmpAtk.bottom = tmpAtk.top + IMAGE_SIZE;
		if (CheckRectForRange(player, enemy, tmpMove, tmpAtk) == 0)
		{
			if (i == 0)
				m_vMoveRange.push_back(tmpMove);
			else if (i != 0 && m_iMoveCount == 0)
				m_vMoveRange.push_back(tmpMove);
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

void Knight::SetRange(RECT* player, RECT* enemy)
{
	//초기값설정 및 벡터초기화
	RECT tmpMove, tmpAtk;
	SetDefault();
	for (int i = 0; i < 8; i++)
	{
		tmpMove = m_Image.m_ImageRect;
		switch (i)
		{
		case 0:	//상단좌측
			tmpMove.left = m_Image.m_ImageRect.left - IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top + 2 * AddY;
			break;
		case 1:	//상단우측
			tmpMove.left = m_Image.m_ImageRect.left + IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top + 2 * AddY;
			break;
		case 2:	//우측좌측
			tmpMove.left = m_Image.m_ImageRect.left + 2 * IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top + AddY;
			break;
		case 3:	//우측우측
			tmpMove.left = m_Image.m_ImageRect.left + 2 * IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top - AddY;
			break;
		case 4:	//좌측좌측
			tmpMove.left = m_Image.m_ImageRect.left - 2 * IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top - AddY;
			break;
		case 5:	//좌측우측
			tmpMove.left = m_Image.m_ImageRect.left - 2 * IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top + AddY;
			break;
		case 6:	//하단좌측
			tmpMove.left = m_Image.m_ImageRect.left - IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top - 2 * AddY;
			break;
		case 7:	//하단우측
			tmpMove.left = m_Image.m_ImageRect.left + IMAGE_SIZE;
			tmpMove.top = m_Image.m_ImageRect.top - 2 * AddY;
			break;
		}
		tmpMove.bottom = tmpMove.top + IMAGE_SIZE;
		tmpMove.right = tmpMove.left + IMAGE_SIZE;
		tmpAtk = tmpMove;
		if (CheckRectForRange(player, enemy, tmpMove, tmpAtk) == 0)
			m_vMoveRange.push_back(tmpMove);
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

void Bishop::SetRange(RECT* player, RECT* enemy)
{
	//초기값설정 및 벡터초기화
	RECT tmpMove, tmpAtk;
	SetDefault();
	for (int i = 0; i < 4; i++)
	{
		tmpMove = m_Image.m_ImageRect;
		while (true)
		{
			if (i == 0)//상단우측
			{
				tmpMove.top += AddY;
				tmpMove.left += IMAGE_SIZE;
			}
			else if (i == 1)//상단좌측
			{
				tmpMove.top += AddY;
				tmpMove.left -= IMAGE_SIZE;
			}
			else if (i == 2)//하단우측
			{
				tmpMove.top -= AddY;
				tmpMove.left += IMAGE_SIZE;
			}
			else//하단좌측
			{
				tmpMove.top -= AddY;
				tmpMove.left -= IMAGE_SIZE;
			}
			tmpMove.bottom = tmpMove.top + IMAGE_SIZE;
			tmpMove.right = tmpMove.left + IMAGE_SIZE;
			tmpAtk = tmpMove;	
			if (CheckRectForRange(player, enemy, tmpMove, tmpAtk) == 0)
				m_vMoveRange.push_back(tmpMove);
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

void Rock::SetRange(RECT* player, RECT* enemy)
{
	//초기값설정 및 벡터초기화
	RECT tmpMove, tmpAtk;
	SetDefault();
	for (int i = 0; i < 4; i++)
	{
		tmpMove = m_Image.m_ImageRect;
		while (true)
		{
			if (i == 0)//상단
				tmpMove.top += AddY;
			else if (i == 1)//하단
				tmpMove.top -= AddY;
			else if (i == 2)//우측
				tmpMove.left += IMAGE_SIZE;
			else//좌측
				tmpMove.left -= IMAGE_SIZE;
			tmpMove.bottom = tmpMove.top + IMAGE_SIZE;
			tmpMove.right = tmpMove.left + IMAGE_SIZE;
			tmpAtk = tmpMove;
			if (CheckRectForRange(player, enemy, tmpMove, tmpAtk) == 0)
				m_vMoveRange.push_back(tmpMove);
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

void Queen::SetRange(RECT* player, RECT* enemy)
{
	//초기값설정 및 벡터초기화
	RECT tmpMove, tmpAtk;
	SetDefault();
	for (int i = 0; i < 8; i++)
	{
		tmpMove = m_Image.m_ImageRect;
		while (true)
		{
			if (i < 3)//상단, 상단좌측, 상단우측
			{
				tmpMove.top += AddY;
				if (i == 1)//상단 좌측
					tmpMove.left -= IMAGE_SIZE;
				else if (i == 2)//상단 우측
					tmpMove.left += IMAGE_SIZE;
			}
			else if (i >= 3 && i < 6)//하단, 하단좌측, 하단우측
			{
				tmpMove.top -= AddY;
				if (i == 4)//하단 좌측
					tmpMove.left -= IMAGE_SIZE;
				else if (i == 5)//하단 우측
					tmpMove.left += IMAGE_SIZE;
			}
			else if (i == 6)//좌측
				tmpMove.left -= IMAGE_SIZE;
			else//우측
				tmpMove.left += IMAGE_SIZE;
			tmpMove.bottom = tmpMove.top + IMAGE_SIZE;
			tmpMove.right = tmpMove.left + IMAGE_SIZE;
			tmpAtk = tmpMove;
			if (CheckRectForRange(player, enemy, tmpMove, tmpAtk) == 0)
				m_vMoveRange.push_back(tmpMove);
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

void King::SetRange(RECT* player, RECT* enemy)
{
	//초기값설정 및 벡터초기화
	RECT tmpMove, tmpAtk;
	SetDefault();
	for (int i = 0; i < 8; i++)
	{
		tmpMove = m_Image.m_ImageRect;
		switch (i)
		{
		case 0:	//상단
			tmpMove.top += AddY;
			break;
		case 1:	//좌측상단
			tmpMove.top += AddY;
			tmpMove.left -= IMAGE_SIZE;
			break;
		case 2:	//우측상단
			tmpMove.top += AddY;
			tmpMove.left += IMAGE_SIZE;
			break;
		case 3:	//좌측
			tmpMove.left -= IMAGE_SIZE;
			break;
		case 4:	//우측
			tmpMove.left += IMAGE_SIZE;
			break;
		case 5:	//하단
			tmpMove.top -= AddY;
			break;
		case 6:	//좌측하단
			tmpMove.top -= AddY;
			tmpMove.left -= IMAGE_SIZE;
			break;
		case 7:	//우측하단
			tmpMove.top -= AddY;
			tmpMove.left += IMAGE_SIZE;
			break;
		}
		tmpMove.bottom = tmpMove.top + IMAGE_SIZE;
		tmpMove.right = tmpMove.left + IMAGE_SIZE;
		tmpAtk = tmpMove;
		if (CheckRectForRange(player, enemy, tmpMove, tmpAtk) == 0)
			m_vMoveRange.push_back(tmpMove);
	}
}

King::~King()
{
}
//King