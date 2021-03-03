#include "MapTool.h"

MapTool* MapTool::m_hThis = NULL;
MapTool::MapTool()
{
	int tmpIndex;
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		switch (i)
		{
		case 0:
			tmpIndex = IMAGE_EMPTY;
			break;
		case 1:
			tmpIndex = IMAGE_BLOCK1;
			break;
		case 2:
			tmpIndex = IMAGE_BLOCK2;
			break;
		}
		m_arrButton[i].m_iIndex = tmpIndex;
		m_arrButton[i].m_Point = { 750 + i * IMG_SIZE, 50 };
		m_arrButton[i].m_Rect = { m_arrButton[i].m_Point.x, m_arrButton[i].m_Point.y,
		m_arrButton[i].m_Point.x + IMG_SIZE, m_arrButton[i].m_Point.y + IMG_SIZE };
	}
	m_iTileSelect = EMPTY;
}

void MapTool::RoomDraw(HDC hdc)
{
	for (int i = 0; i < BUTTON_MAX; i++)
		Res_MG::GetInstance()->Draw(m_arrButton[i].m_iIndex, hdc, m_arrButton[i].m_Point);
	m_Map.DrawMap(hdc);
}

bool MapTool::Click(POINT pt)
{
	//타일선택
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (PtInRect(&m_arrButton[i].m_Rect, pt))
		{
			m_iTileSelect = m_arrButton[i].m_iIndex;
			return false;
		}
	}
	//타일그리기
	if (m_iTileSelect != EMPTY)
	{
		for (int y = 0; y < ROOM; y++)
		{
			for (int x = 0; x < ROOM; x++)
			{
				if (PtInRect(&m_Map.m_arrMap[y][x].m_Rect, pt))
				{
					m_Map.m_arrMap[y][x].m_iIndex = m_iTileSelect;
					m_Map.m_arrMap[y][x].m_iState = STATE_FULL;
					return true;
				}
			}
		}
	}
	return false;
}

void MapTool::Reset()
{
	for (int y = 0; y < ROOM; y++)
	{
		for (int x = 0; x < ROOM; x++)
		{
			m_Map.m_arrMap[y][x].m_iIndex = IMAGE_EMPTY;
			m_Map.m_arrMap[y][x].m_iState = STATE_EMPTY;
			m_Map.m_arrMap[y][x].m_Point = { (x + 1) * IMG_SIZE, (y + 1) * IMG_SIZE };
			m_Map.m_arrMap[y][x].m_Size = { IMG_SIZE, IMG_SIZE };
			m_Map.m_arrMap[y][x].m_Rect = { m_Map.m_arrMap[y][x].m_Point.x, m_Map.m_arrMap[y][x].m_Point.y,
				m_Map.m_arrMap[y][x].m_Point.x + m_Map.m_arrMap[y][x].m_Size.cx,m_Map.m_arrMap[y][x].m_Point.y + m_Map.m_arrMap[y][x].m_Size.cy };
		}
	}
}

void MapTool::Save(LPCSTR FileName)
{
	HANDLE hFile;
	DWORD dWord;
	hFile = CreateFile(FileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	for (int y = 0; y < ROOM; y++)
		for(int x = 0; x < ROOM; x++)
			WriteFile(hFile, &m_Map.m_arrMap[y][x], sizeof(Map), &dWord, NULL);
	CloseHandle(hFile);
}

void MapTool::Load()
{
	HANDLE hFile;
	DWORD dWord;
	hFile = CreateFile("Test1.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	memset(m_Map.m_arrMap, NULL, sizeof(m_Map));
	for (int y = 0; y < ROOM; y++)
		for (int x = 0; x < ROOM; x++)
			ReadFile(hFile, &m_Map.m_arrMap[y][x], sizeof(Map), &dWord, NULL);
	CloseHandle(hFile);
}

MapTool::~MapTool()
{
}