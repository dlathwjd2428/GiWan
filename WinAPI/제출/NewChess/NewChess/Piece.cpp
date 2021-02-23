#include "Piece.h"

Piece::Piece()
{
}

void Piece::SetPiece(int Exist, int Enemy, int Index, int Add, POINT pt)
{
	m_Piece.m_iExist = Exist;
	m_Piece.m_iIndex = Index;
	m_Piece.m_Point = pt;
	m_Piece.m_Rect = { m_Piece.m_Point.x,m_Piece.m_Point.y, m_Piece.m_Point.x + IMAGE_SIZE, m_Piece.m_Point.y + IMAGE_SIZE };
	m_bClick = false;
	m_iMoveCount = 0;
	m_iAdd = Add;
	m_iEnemyColor = Enemy;
	m_SavePt = m_Piece.m_Point;
}

void Piece::Draw(HDC hdc)
{
	Res_MG::GetInstance()->Draw(hdc, m_Piece.m_iIndex, m_Piece.m_Point);
	if (m_bClick == true)
	{
		for (int i = 0; i < m_vMove.size(); i++)
			Res_MG::GetInstance()->Draw(hdc, IMAGE_BACK3, m_vMove[i].m_Point);
		for (int i = 0; i < m_vAtk.size(); i++)
			Res_MG::GetInstance()->Draw(hdc, IMAGE_BACK3, m_vAtk[i].m_Point);
	}
}

bool Piece::Click(POINT pt)
{
	if (PtInRect(&m_Piece.m_Rect, pt) == true)
		m_bClick = true;
	return m_bClick;
}

bool Piece::Move(POINT pt)
{
	if (pt.x == DIE)//마우스클릭을 놓았을때
		return Fix();
	else
	{
		m_Piece.m_Point = { pt.x - IMAGE_SIZE / 2, pt.y - IMAGE_SIZE / 2 };
		return false;
	}
}

bool Piece::Fix()
{
	m_bClick = false;
	if (MoveRangeFix() == true)	//이동범위안일경우해당위치고정(true반환), m_iMoveCount++
	{
		Board::GetInstance()->UpdateBoard(m_Piece.m_iExist, m_SavePt, m_Piece.m_Point);
		m_SavePt = m_Piece.m_Point;
		m_iMoveCount++;
		return true;
	}
	else //아닐경우원래위치로 조정(false반환)
	{
		m_Piece.m_Point = m_SavePt;
		return false;
	}
}

void Piece::ResetRange()
{
	while (!m_vMove.empty())
		m_vMove.pop_back();
	while (!m_vAtk.empty())
		m_vAtk.pop_back();
}

bool Piece::CheckRange(Range range, int Option)
{
	if (Option == MOVE)
	{
		if (Board::GetInstance()->GetExist(range.m_Point.x, range.m_Point.y) == EXIST_EMPTY)
		{
			range.m_Rect = { range.m_Point.x, range.m_Point.y, range.m_Point.x + IMAGE_SIZE, range.m_Point.y + IMAGE_SIZE };
			m_vMove.push_back(range);
			return true;
		}
	}
	else
	{
		if (Board::GetInstance()->GetExist(range.m_Point.x, range.m_Point.y) == m_iEnemyColor ||
			Board::GetInstance()->GetExist(range.m_Point.x, range.m_Point.y) == m_iEnemyColor + 2)
		{
			range.m_Rect = { range.m_Point.x, range.m_Point.y, range.m_Point.x + IMAGE_SIZE, range.m_Point.y + IMAGE_SIZE };
			m_vAtk.push_back(range);
			return true;
		}
	}
	return false;
}

bool Piece::MoveRangeFix()
{
	POINT pt = { m_Piece.m_Point.x + IMAGE_SIZE / 2, m_Piece.m_Point.y + IMAGE_SIZE / 2 };
	for (int i = 0; i < m_vMove.size(); i++)
	{
		if (PtInRect(&m_vMove[i].m_Rect, pt) == true)
		{
			m_Piece.m_Point = m_vMove[i].m_Point;
			m_Piece.m_Rect = m_vMove[i].m_Rect;
			return true;
		}
	}
	for (int i = 0; i < m_vAtk.size(); i++)
	{
		if (PtInRect(&m_vAtk[i].m_Rect, pt) == true)
		{
			Board::GetInstance()->SetKillPoint(m_vAtk[i].m_Point);
			m_Piece.m_Point = m_vAtk[i].m_Point;
			m_Piece.m_Rect = m_vAtk[i].m_Rect;
			return true;
		}
	}
	return false;
}

bool Piece::KingCheck()
{
	for (int i = 0; i < m_vAtk.size(); i++)
	{
		if (Board::GetInstance()->GetExist(m_vAtk[i].m_Point.x, m_vAtk[i].m_Point.y) == EXIST_BLACK_KING ||
			Board::GetInstance()->GetExist(m_vAtk[i].m_Point.x, m_vAtk[i].m_Point.y) == EXIST_WHITE_KING)
			return true;
	}
	return false;
}

bool Piece::Die(POINT pt)
{
	if (m_Piece.m_Point.x == pt.x && m_Piece.m_Point.y == pt.y)
	{
		m_Piece.m_Point = { DIE, DIE};
		m_SavePt = m_Piece.m_Point;
		m_Piece.m_Rect = { DIE - IMAGE_SIZE, DIE - IMAGE_SIZE, DIE, DIE };
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

void Pawn::SetRange()
{
	ResetRange();
	Range tmp;
	//MoveRange
	tmp.m_Point = { m_Piece.m_Point.x, m_Piece.m_Point.y + m_iAdd };
	CheckRange(tmp, MOVE);
	if (m_iMoveCount == 0)
	{
		tmp.m_Point.y += m_iAdd;
		CheckRange(tmp, MOVE);
	}
	//AttackRange
	int i = 0;
	while (i < 2)
	{
		tmp.m_Point = m_Piece.m_Point;
		switch (i)
		{
		case 0://LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		case 1://RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		}
		CheckRange(tmp, ATTACK);
		i++;
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

void Knight::SetRange()
{
	ResetRange();
	Range tmp;
	//Move And AttackRange
	int i = 0;
	while (i < 8)
	{
		tmp.m_Point = m_Piece.m_Point;
		switch (i)
		{
		case 0://UP_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd * 2;
			break;
		case 1://UP_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd * 2;
			break;
		case 2://DOWN_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd * 2;
			break;
		case 3://DOWN_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd * 2;
			break;
		case 4://LEFT_UP
			tmp.m_Point.x -= IMAGE_SIZE * 2;
			tmp.m_Point.y += m_iAdd;
			break;
		case 5://LEFT_DOWN
			tmp.m_Point.x -= IMAGE_SIZE * 2;
			tmp.m_Point.y -= m_iAdd;
			break;
		case 6://RIGHT_UP
			tmp.m_Point.x += IMAGE_SIZE * 2;
			tmp.m_Point.y += m_iAdd;
			break;
		case 7://RIGHT_DOWN
			tmp.m_Point.x += IMAGE_SIZE * 2;
			tmp.m_Point.y -= m_iAdd;
			break;
		}
		CheckRange(tmp, MOVE);
		CheckRange(tmp, ATTACK);
		i++;
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

void Bishop::SetRange()
{
	ResetRange();
	Range tmp;
	//Move And Attack
	int i = 0;
	tmp.m_Point = m_Piece.m_Point;
	while (i < 4)
	{	
		switch (i)
		{
		case 0://UP_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		case 1://UP_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		case 2://DOWN_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd;
			break;
		case 3://DOWN_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd;
			break;
		}
		if (CheckRange(tmp, ATTACK) == true || CheckRange(tmp, MOVE) == false)
		{
			i++;
			tmp.m_Point = m_Piece.m_Point;
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

void Rock::SetRange()
{
	ResetRange();
	Range tmp;
	//Move And Attack
	int i = 0;
	tmp.m_Point = m_Piece.m_Point;
	while (i < 4)
	{
		switch (i)
		{
		case 0://UP
			tmp.m_Point.y += m_iAdd;
			break;
		case 1://DOWN
			tmp.m_Point.y -= m_iAdd;
			break;
		case 2://LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			break;
		case 3://RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			break;
		}
		if (CheckRange(tmp, ATTACK) == true || CheckRange(tmp, MOVE) == false)
		{
			i++;
			tmp.m_Point = m_Piece.m_Point;
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

void Queen::SetRange()
{
	ResetRange();
	Range tmp;
	//Move And Attack
	int i = 0;
	tmp.m_Point = m_Piece.m_Point;
	while (i < 8)
	{
		switch (i)
		{
		case 0://UP_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		case 1://UP_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		case 2://DOWN_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd;
			break;
		case 3://DOWN_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd;
			break;
		case 4://UP
			tmp.m_Point.y += m_iAdd;
			break;
		case 5://DOWN
			tmp.m_Point.y -= m_iAdd;
			break;
		case 6://LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			break;
		case 7://RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			break;
		}
		if (CheckRange(tmp, ATTACK) == true || CheckRange(tmp, MOVE) == false)
		{
			i++;
			tmp.m_Point = m_Piece.m_Point;
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

void King::SetRange()
{
	ResetRange();
	Range tmp;
	//Move And Attack
	int i = 0;
	tmp.m_Point = m_Piece.m_Point;
	while (i < 8)
	{
		switch (i)
		{
		case 0://UP_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		case 1://UP_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y += m_iAdd;
			break;
		case 2://DOWN_LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd;
			break;
		case 3://DOWN_RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			tmp.m_Point.y -= m_iAdd;
			break;
		case 4://UP
			tmp.m_Point.y += m_iAdd;
			break;
		case 5://DOWN
			tmp.m_Point.y -= m_iAdd;
			break;
		case 6://LEFT
			tmp.m_Point.x -= IMAGE_SIZE;
			break;
		case 7://RIGHT
			tmp.m_Point.x += IMAGE_SIZE;
			break;
		}
		CheckRange(tmp, ATTACK);
		CheckRange(tmp, MOVE);
		i++;
		tmp.m_Point = m_Piece.m_Point;
	}
}

King::~King()
{
}
//King