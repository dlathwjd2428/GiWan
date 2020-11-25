#pragma once
#include"BitMap.h"

class BitMapManager
{
private:
	static BitMapManager* m_hThis;
	BitMap m_arrBitMap[IMAGE_MAX];
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	void Init(HDC hdc);
	void Draw(HDC hdc, int Index, POINT pt, SIZE Size);
	BitMapManager();
	~BitMapManager();
};

