#include"GameManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("CircusGame");

GameManager s_GManager;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT
		, WIN_X, WIN_Y, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

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
			s_GManager.UpdateGame(hWnd);
		}
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static BitMap s_Bit;
	static bool Timer = false;
	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		s_Bit.Init(hdc, L"", BACK);
		s_GManager.SetGame(hWnd);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_KEYDOWN:
		if (Timer == false)
		{
			SetTimer(hWnd, 1, 80, NULL);
			Timer = true;
		}
		return 0;
	case WM_KEYUP:
		if (wParam != VK_RETURN)
		{
			if (s_GManager.GetJump() == false)
				KillTimer(hWnd, 1);
			Timer = false;
			s_GManager.SetMessageState();
		}
		return 0;
	case WM_TIMER:
		if (s_GManager.GetGameState() == GAME_STATE_TRUE)
		{
			s_GManager.Move();	
			InvalidateRect(hWnd, NULL, false);
			s_GManager.CollideCheck(hWnd);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (s_GManager.GetGameState() == GAME_STATE_TRUE)
			s_GManager.Draw(s_Bit.GetDC());
		else  if (s_GManager.GetGameState() == GAME_STATE_FALSE)
			s_GManager.Draw(s_Bit.GetDC(), DIE);
		else
			s_GManager.Draw(s_Bit.GetDC(), WIN);
		BitBlt(hdc, 0, 0, WIN_X, WIN_Y, s_Bit.GetDC(), 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}