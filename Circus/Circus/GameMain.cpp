#include"GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCWSTR lpszClass = TEXT("Circus");
GameManager s_GManager;
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIN_SIZE, WIN_SIZE, NULL, (HMENU)0, g_hInst, 0);
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
			s_GManager.UpdateGame();
		}
	}
	return(int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static BitMap s_Bit;
	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		s_Bit.Init(hdc, L"", BACK);
		s_GManager.SetGame(hdc);	
		SetTimer(hWnd, 1, 50, NULL);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_TIMER:
		s_GManager.Move();
		InvalidateRect(hWnd, NULL, false);
		return 0;
	case WM_PAINT:	
		hdc = BeginPaint(hWnd, &ps);
		s_GManager.Draw(s_Bit.GetDC());
		BitBlt(hdc, 0, 0, WIN_SIZE, WIN_SIZE, s_Bit.GetDC(), 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}