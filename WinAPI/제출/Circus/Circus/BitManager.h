#pragma once
#include"BitMap.h"

class BitManager
{
private:
	static BitManager* m_hThis;
	BitMap m_arrBit[IMAGE_MAX];
public:
	static BitManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitManager;
		return m_hThis;
	}
	void Init(HDC hdc);
	void Draw(HDC hdc, int Index, POINT pt, SIZE Size);
	BitManager();
	~BitManager();
};

