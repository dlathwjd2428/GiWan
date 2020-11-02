#include "Card.h"

Card::Card()
{
	m_eCardState = CARD_REAR;
}

void Card::Set_Card(int Index, int x, int y)
{
	m_iCardIndex = Index;
	m_BitMap[CARD_FRONT] = BitMapManager::GetBitMapManager()->Get_Image(Index);
	m_BitMap[CARD_OK] = BitMapManager::GetBitMapManager()->Get_Image(Index);
	m_BitMap[CARD_REAR] = BitMapManager::GetBitMapManager()->Get_Image(IMAGE_BLACK);
	m_ix = x;
	m_iy = y;
	m_CardRect = { m_ix, m_iy, (LONG)(m_ix + m_BitMap[CARD_FRONT]->GetSize().cx * 0.6f), (LONG)(m_iy + m_BitMap[CARD_FRONT]->GetSize().cy * 0.6f) };
}

void Card::Draw_Card(HDC hdc)
{
	if (m_eCardState == CARD_FRONT)
		m_BitMap[CARD_FRONT]->Draw(hdc, m_ix, m_iy);
	else if(m_eCardState == CARD_REAR)
		m_BitMap[CARD_REAR]->Draw(hdc, m_ix, m_iy);
	else
		m_BitMap[CARD_OK]->Draw(hdc, m_ix, m_iy);
}

int Card::ColliderCheck(POINT pt)
{
	if (PtInRect(&m_CardRect, pt))
	{
		if (m_eCardState == CARD_REAR)
		{
			m_eCardState = CARD_FRONT;
			return m_iCardIndex;
		}
	}
	return -1;
}

void Card::SetCardState(int Option, int Index)
{
	if (Index == m_iCardIndex)
		m_eCardState = CARD_OK;
	else if (m_eCardState == CARD_FRONT)
		m_eCardState = CARD_REAR;
	else if (Option == RESET)
		m_eCardState = CARD_REAR;
}

bool Card::CardCheck()
{
	if (m_eCardState == CARD_OK)
		return true;
	else
		return false;
}
Card::~Card()
{
}