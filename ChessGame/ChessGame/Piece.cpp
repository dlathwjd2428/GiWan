#include "Piece.h"

Piece::Piece()
{
    m_iAdd = -100;
    m_iEnemyColor = WHITE;
}

void Piece::Draw(HDC hdc)
{
    Res_MG::GetInstance()->Draw(hdc, m_iIndex, m_Point);
    if (m_bClick == true)
    {
        for (int i = 0; i < m_vMove.size(); i++)
            Res_MG::GetInstance()->Draw(hdc, IMAGE_BACK3, m_vMove[i].m_Point);
    }
}

bool Piece::ClickCheck(POINT pt)
{
    m_bClick = false;
    if (PtInRect(&m_Rect, pt))
    {
        m_bClick = true;
        m_SavePoint = m_Point;
    }
    return m_bClick;
}

Piece::~Piece()
{
}

//Pawn
Pawn::Pawn()
{
    m_iMoveCount = 0;
}

void Pawn::SetPiece(int Player, POINT pt)
{
    if (Player == BLACK)
        m_iIndex = IMAGE_B_PAWN;
    else
    {
        m_iIndex = IMAGE_W_PANW;
        m_iAdd = 100;
        m_iEnemyColor = BLACK;
    }
    m_Point = pt;
    m_SavePoint = m_Point;
    m_Rect = { m_Point.x, m_Point.y, m_Point.x + IMAGE_SIZE, m_Point.y + IMAGE_SIZE };
}

void Pawn::SetRange()
{
    Range tmpRange;
    //Move
    tmpRange.m_Point = { m_SavePoint.x, m_SavePoint.y + m_iAdd };
    tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
        tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
    if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE)
        m_vMove.push_back(tmpRange);
    if (m_iMoveCount == 0)
    {
        tmpRange.m_Point = { m_SavePoint.x, m_SavePoint.y + (m_iAdd * 2) };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE)
            m_vMove.push_back(tmpRange);
    }
    //Atk
    //Right
    tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y + m_iAdd };
    tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
        tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
    if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
        m_vAtk.push_back(tmpRange);
    //Left
    tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y + m_iAdd };
    tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
        tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
    if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
        m_vAtk.push_back(tmpRange);
}

Pawn::~Pawn()
{
}
//Pawn

//Knight
Knight::Knight()
{
}

void Knight::SetPiece(int Player, POINT pt)
{
    if (Player == BLACK)
        m_iIndex = IMAGE_B_KNIGHT;
    else
    {
        m_iIndex = IMAGE_W_KNIGHT;
        m_iAdd = 100;
        m_iEnemyColor = BLACK;
    }
    m_Point = pt;
    m_SavePoint = m_Point;
    m_Rect = { m_Point.x, m_Point.y, m_Point.x + IMAGE_SIZE, m_Point.y + IMAGE_SIZE };
}

void Knight::SetRange()
{
    Range tmpRange;
    //Move
    //Right
    tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y + ( 2 * m_iAdd) };
    tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
        tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
    if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE)
        m_vMove.push_back(tmpRange);
    else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
       m_vAtk.push_back(tmpRange);
    tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y - (2 * m_iAdd) };
    tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
        tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
    if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE)
        m_vMove.push_back(tmpRange);
    else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
        m_vAtk.push_back(tmpRange);
    //Left
    tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y + ( 2 * m_iAdd) };
    tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
        tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
    if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE)
        m_vMove.push_back(tmpRange);
    else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
        m_vAtk.push_back(tmpRange);
    tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y - (2 * m_iAdd) };
    tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
        tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y + IMAGE_SIZE };
    if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE)
        m_vMove.push_back(tmpRange);
    else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
        m_vAtk.push_back(tmpRange);
}

Knight::~Knight()
{
}
//Knight

//Bishop
Bishop::Bishop()
{
}

void Bishop::SetPiece(int Player, POINT pt)
{
    if (Player == BLACK)
        m_iIndex = IMAGE_B_BISHOP;
    else
    {
        m_iIndex = IMAGE_W_BISHOP;
        m_iAdd = 100;
        m_iEnemyColor = BLACK;
    }
    m_Point = pt;
    m_SavePoint = m_Point;
    m_Rect = { m_Point.x, m_Point.y, m_Point.x + IMAGE_SIZE, m_Point.y + IMAGE_SIZE };
}

void Bishop::SetRange()
{
    Range tmpRange; 
    //Move
    //RightFront
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y + m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0
            && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //LeftFront
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y + m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0
            && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //RightBack
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y - m_iAdd};
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0
            && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //LEFTBack
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y - m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0
            && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
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

void Rock::SetPiece(int Player, POINT pt)
{
    if (Player == BLACK)
        m_iIndex = IMAGE_B_ROCK;
    else
    {
        m_iIndex = IMAGE_W_ROCK;
        m_iAdd = 100;
        m_iEnemyColor = BLACK;
    }
    m_Point = pt;
    m_Rect = { m_Point.x, m_Point.y, m_Point.x + IMAGE_SIZE, m_Point.y + IMAGE_SIZE };
}

void Rock::SetRange()
{
    Range tmpRange;
    //Move
    //Right
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //Left
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //Front
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x, m_SavePoint.y + m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //Back
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x, m_SavePoint.y - m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
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

void Queen::SetPiece(int Player, POINT pt)
{
    if (Player == BLACK)
        m_iIndex = IMAGE_B_QUEEN;
    else
    {
        m_iIndex = IMAGE_W_QUEEN;
        m_iAdd = 100;
        m_iEnemyColor = BLACK;
    }
    m_Point = pt;
    m_SavePoint = m_Point;
    m_Rect = { m_Point.x, m_Point.y, m_Point.x + IMAGE_SIZE, m_Point.y + IMAGE_SIZE };
}

void Queen::SetRange()
{
    Range tmpRange;
    //Move
     //Right
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //Left
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //Front
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x, m_SavePoint.y + m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //Back
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x, m_SavePoint.y - m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y + m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0
            && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //LeftFront
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y + m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0
            && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //RightBack
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x + IMAGE_SIZE, m_SavePoint.y - m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0
            && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
    }
    //LEFTBack
    tmpRange = { m_SavePoint.x, m_SavePoint.y };
    while (true)
    {
        tmpRange.m_Point = { m_SavePoint.x - IMAGE_SIZE, m_SavePoint.y - m_iAdd };
        tmpRange.m_Rect = { tmpRange.m_Point.x,  tmpRange.m_Point.y,
            tmpRange.m_Point.x + IMAGE_SIZE,  tmpRange.m_Point.y };
        if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == NONE && tmpRange.m_Point.y <= 700 && tmpRange.m_Point.y >= 0
            && tmpRange.m_Point.x <= 700 && tmpRange.m_Point.x >= 0)
            m_vMove.push_back(tmpRange);
        else if (Board::GetInstance()->CheckBoard(tmpRange.m_Point) == m_iEnemyColor)
            m_vAtk.push_back(tmpRange);
        else
            break;
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

void King::SetPiece(int Player, POINT pt)
{
    if (Player == BLACK)
        m_iIndex = IMAGE_B_KING;
    else
    {
        m_iIndex = IMAGE_W_KING;
        m_iAdd = 100;
        m_iEnemyColor = BLACK;
    }
    m_Point = pt;
    m_SavePoint = m_Point;
    m_Rect = { m_Point.x, m_Point.y, m_Point.x + IMAGE_SIZE, m_Point.y + IMAGE_SIZE };
}

void King::SetRange()
{

}

King::~King()
{
}
//King