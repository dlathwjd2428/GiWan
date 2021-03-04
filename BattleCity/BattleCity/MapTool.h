#pragma once
#include"Map.h"

class MapTool
{
private:
	Map m_Map;
public:
	void Draw(HDC hdc);
	MapTool();
	~MapTool();
};