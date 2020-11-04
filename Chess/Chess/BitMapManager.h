#pragma once
#include"BitMap.h"

#define IMAGE_MAX 15

class BitMapManager
{
private:
	BitMap m_Images[15];
	static BitMapManager* m_BitManager;
public:
	static BitMapManager* GetBitManager()
	{
		if (m_BitManager == NULL)
			m_BitManager = new BitMapManager;
		return m_BitManager;
	}
	void SetBitMaps(HWND hWnd, HINSTANCE hInst);
	void ShowBitMaps(HDC hdc);
	BitMapManager();
	~BitMapManager();
};

