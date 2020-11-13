#pragma once
#include"BitMap.h"

class BitMapManager
{
private:
	static BitMapManager* m_hThis;
	BitMap m_arrBitMap[IMAGE_MAX];
public:
	static BitMapManager* GetBManager()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	void SetBitMapArr(HWND hWnd);
	void DrawBitMap(HDC hdc, int Index, RECT rect, int Option = NORMAL);
	BitMapManager();
	~BitMapManager();
};

