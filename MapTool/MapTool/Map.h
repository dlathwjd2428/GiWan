#pragma once
#include"Res_MG.h"

class Map
{
protected:
	
public:
	Room m_arrMap[ROOM][ROOM];
	void DrawMap(HDC hdc);
	Map();
	~Map();
};

