#pragma once
#include"Map.h"

class MapTool
{
private:
	Map m_Map;
public:
	void MapDraw(HDC hdc);
	void Click(POINT pt, int Index, int State);		    
	MapTool();
	~MapTool();
};

