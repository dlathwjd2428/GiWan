#include"GameFrame.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCSTR lpszClass = TEXT("NewChess");
GameFrame g_GameFrame;
POINT g_Point = { DIE, DIE };
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInst;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = g_hInst;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = 0;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIN_SIZE + 16, WIN_SIZE + 38,
		NULL, (HMENU)0, g_hInst, NULL);
	ShowWindow(hWnd, nCmdShow);

	HDC hdc;
	hdc = GetDC(hWnd);
	g_GameFrame.SetGame(hdc);
	while (true)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			g_GameFrame.UpdateGame(hWnd, hdc, g_Point);
		}
	}
	ReleaseDC(hWnd, hdc);
	g_GameFrame.EndGame();
	return(int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static bool g_Click = false;
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		g_Click = true;
		return 0;
	case WM_LBUTTONUP:
		g_Click = false;
		g_Point = { DIE, DIE };
		return 0;
	case WM_MOUSEMOVE:
		if (g_Click == true)
		{
			g_Point.x = LOWORD(lParam);
			g_Point.y = HIWORD(lParam);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}