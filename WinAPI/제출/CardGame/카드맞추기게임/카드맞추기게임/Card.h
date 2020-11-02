#pragma once
#include"BitMapManager.h"

#define OK 1
#define RESET 0
enum CARD
{
	CARD_FRONT,
	CARD_REAR,
	CARD_OK,
	CARD_END
};

class Card
{
private:
	int m_iCardIndex;
	CARD m_eCardState;
	int m_ix;
	int m_iy;
	RECT m_CardRect;
	BitMap *m_BitMap[CARD_END];
public:
	void Set_Card(int Index, int x, int y);
	void Draw_Card(HDC hdc);
	inline SIZE Get_BitMapSize() { return m_BitMap[CARD_FRONT]->GetSize(); }
	int ColliderCheck(POINT pt);
	void SetCardState(int Option = -1, int Index = -1);
	bool CardCheck();
	Card();
	~Card();
};

