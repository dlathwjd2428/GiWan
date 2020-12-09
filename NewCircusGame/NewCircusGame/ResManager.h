#pragma once
#include"BitMap.h"

class ResManager
{
private:
	static ResManager* m_hThis;
	BitMap m_arrBit[IMAGE_MAX];
public:
	static ResManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new ResManager;
		return m_hThis;
	}
	void InitBitMap(HDC hdc);
	void DrawBitMap(HDC hdc, int Index, POINT pt, SIZE Size);
	ResManager();
	~ResManager();
};

