#pragma once
#include"Res_MG.h"

class Map
{
private:
	Room m_arrMap[ROOM][ROOM];
public:
	void DrawMap(HDC hdc);
	Map();
	~Map();
};

