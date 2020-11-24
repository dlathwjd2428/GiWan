#pragma once
#include"BitMap.h"

class BitMapManager
{
private:
	static BitMapManager* m_hThis;
	BitMap m_arrImage[IMAGE_MAX];
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	void Init(HWND hWnd);
	void DrawImage(HDC hdc, int Index, POINT pt, SIZE Size);
	BitMapManager();
	~BitMapManager();
};

