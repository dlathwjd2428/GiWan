#include "CardManager.h"

CardManager* CardManager::m_sCardManager = NULL;

CardManager::CardManager()
{
	Card tmpCard;
	m_arriCardIndex[0] = -1;
	m_arriCardIndex[1] = -1;
	int x = 25, y = 50;
	tmpCard.Set_Card(0, 0, 0);
	for (int i = 0; i < CARD_MAX; i++)
	{
		m_CardPoint[i].m_iPointState = EMPTY;
		m_CardPoint[i].pt.x = x;
		m_CardPoint[i].pt.y = y;
		x += tmpCard.Get_BitMapSize().cx * 0.6f;
		if ((i + 1) % 5 == 0)
		{
			x = 25;
			y += tmpCard.Get_BitMapSize().cy * 0.6f;
		}
	}
}

void CardManager::SetCard()
{
	Card tmpCard;
	int RNum;
	int Count = 0;
	for(int i = IMAGE_START; i < IMAGE_BLACK;)
	{
		for (int j = 0; j < CARD_MAX; j++)
		{
			RNum = rand() % 100 + 1;
			if (RNum <= 30 && m_CardPoint[j].m_iPointState == EMPTY)
			{
				m_CardPoint[j].m_iPointState = FULL;
				tmpCard.Set_Card(i, m_CardPoint[j].pt.x, m_CardPoint[j].pt.y);
				//tmpCard.SetCardState(RESET);
				m_Card.push_back(tmpCard);
				Count++;
				if (Count == 2)
				{
					i++;
					Count = 0;
					break;
				}
			}
		}
	}
}

void CardManager::DrawCard(HDC hdc)
{
	for (auto iter = m_Card.begin(); iter != m_Card.end(); iter++)
	{
		iter->Draw_Card(hdc);
	}
}

void CardManager::ColliderCheck(POINT pt, int& Count)
{	
	int tmpIndex;
	for (int i = 0; i < CARD_MAX; i++)
	{
		tmpIndex = m_Card[i].ColliderCheck(pt);
		if (tmpIndex != FALSE)
		{
			m_arriCardIndex[Count] = tmpIndex;
			Count++;	
			break;
		}
	}
}

void CardManager::SetCardState(int Option, int Index)
{
	for (int i = 0; i < CARD_MAX; i++)
	{
		m_Card[i].SetCardState(Option, Index);
	}
}

bool CardManager::CheckCorrectCard(int& Count)
{
	if (m_arriCardIndex[0] != -1 && m_arriCardIndex[1] != -1 && m_arriCardIndex[0] == m_arriCardIndex[1])
	{
		for (int i = 0; i < CARD_MAX; i++)
		{
			m_Card[i].SetCardState(OK, m_arriCardIndex[0]);
		}	
		Count = 0;
		return true;
	}
	m_arriCardIndex[0] = -1;
	m_arriCardIndex[1] = -1;
	return false;
}

bool CardManager::CardOKCheck()
{
	for (auto iter = m_Card.begin(); iter != m_Card.end(); iter++)
	{
		if (iter->CardCheck() == false)
			return false;
	}
	return true;
}

void CardManager::CardReset()
{
	for (int i = 0; i < CARD_MAX; i++)
	{
		m_CardPoint[i].m_iPointState = EMPTY;
	}
	while (!m_Card.empty())
	{
		m_Card.pop_back();
	}
	SetCard();
}

CardManager::~CardManager()
{
}