#include"GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCWSTR lpszClass = TEXT("NewCircusGame");
GameManager s_GManager;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = g_hInst;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIN_SIZE, WIN_SIZE, NULL, (HMENU)0, g_hInst, NULL);
	ShowWindow(hWnd, nCmdShow);

	HDC hdc;
	POINT tmp = { 100, 100 };
	SIZE tmpS = { 100, 100 };
	hdc = GetDC(hWnd);
	s_GManager.LoadingGame(hdc);
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
			s_GManager.UpdateGame(hdc);
		}
	}
	ReleaseDC(hWnd, hdc);
	return(int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	bool b_DownState = false;
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 50, NULL);
		return 0;
	case WM_TIMER:
		if (wParam == 1)
			s_GManager.Move();
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
