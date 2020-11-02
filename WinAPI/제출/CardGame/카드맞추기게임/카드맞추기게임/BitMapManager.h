#pragma once
#include"BitMap.h"
#include"Card.h"
#include<vector>

enum IMAGE
{
	IMAGE_START,
	IMAGE_DOG = 0,
	IMAGE_TIGER,
	IMAGE_DUCK,
	IMAGE_ELEPHANT,
	IMAGE_COW,
	IMAGE_HORSE,
	IMAGE_CAT,
	IMAGE_MONKEY,
	IMAGE_FROG,
	IMAGE_CHICKEN,
	IMAGE_BLACK,
	IMAGE_BACKGROUND,
	IMAGE_END
};

class BitMapManager
{
private:
	std::vector<BitMap> m_Image;
	static BitMapManager* m_sBitMapManager;
public:
public:
	static BitMapManager* GetBitMapManager()
	{
		if (m_sBitMapManager == NULL)
			m_sBitMapManager = new BitMapManager;
		return m_sBitMapManager;
	}
	void Set_BitMap(HWND hWnd, HINSTANCE hInst);
	void DrawBackGround(HDC hdc);
	BitMap* Get_Image(int Index);
	BitMapManager();
	~BitMapManager();
};

