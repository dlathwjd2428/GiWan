#pragma once
#include"Card.h"
#include<vector>
#include<time.h>
#define CARD_MAX 20
#define EMPTY 0
#define FULL 1
#define FALSE -1
struct Point
{
	POINT pt;
	int m_iPointState;
};

class CardManager
{
private:
	std::vector<Card> m_Card;
	int m_arriCardIndex[2];
	static CardManager* m_sCardManager;
	Point m_CardPoint[CARD_MAX];
public:
	static CardManager* GetCardManager()
	{
		if (m_sCardManager == NULL)
			m_sCardManager = new CardManager;
		return m_sCardManager;
	}
	void CardReset();
	bool CardOKCheck();
	bool CheckCorrectCard(int& Count);
	void SetCard();
	void DrawCard(HDC hdc);
	void SetCardState(int Option = -1, int Index = -1);
	void ColliderCheck(POINT pt, int& Count);
	CardManager();
	~CardManager();
};

