#include "MapTool.h"

MapTool::MapTool()
{
}

void MapTool::MapDraw(HDC hdc)
{
	m_Map.DrawMap(hdc);
}

void MapTool::Click(POINT pt, int Index, int State)
{
	for (int y = 0; y < ROOM; y++)
	{
		for (int x = 0; x < ROOM; x++)
		{
			
		}
	}
}

MapTool::~MapTool()
{
}