#pragma once
#include"Res_MG.h"

class Map
{
public:
	Room m_arrMap[ROOM][ROOM];
	void SetMap();
	void DrawMap(HDC hdc);
	Map();
	~Map();
};

