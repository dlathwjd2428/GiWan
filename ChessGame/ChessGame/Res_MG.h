#pragma once
#include"BitMap.h"

class Res_MG
{
private:
	static Res_MG* m_hThis;
	BitMap m_arrIMG[IMAGE_MAX];
public:
	static Res_MG* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new Res_MG;
		return m_hThis;
	}
	void Init(HDC hdc);
	void Draw(HDC hdc, int Index, POINT pt);
	Res_MG();
	~Res_MG();
};

