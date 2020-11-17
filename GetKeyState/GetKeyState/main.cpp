#include"Character.h"
#pragma comment(lib, "msimg32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("GetKeyState");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; //예약영역
	WndClass.cbWndExtra = 0; //예약영역 (신경x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static Character s_Character;
	static int Count = 0;
	switch (iMessage)
	{
	case WM_CREATE:
		s_Character.SetDefaultChar(hWnd);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		s_Character.Draw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_KEYDOWN:
		if (s_Character.GetMoveState() == false)
		{
			SetTimer(hWnd, 1, 100, NULL);
			s_Character.SetMoveState(true);
		}
		return 0;
	case WM_KEYUP:
		s_Character.SetMoveState(false);
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_TIMER:
		if (wParam == 1)
		{
			if (GetKeyState(VK_LEFT) & 0x8000)
				s_Character.Move(LEFT);
			if (GetKeyState(VK_RIGHT) & 0x8000)
				s_Character.Move(RIGHT);
			if (GetKeyState(VK_UP) & 0x8000)
				s_Character.Move(UP);
			if (GetKeyState(VK_DOWN) & 0x8000)
				s_Character.Move(DOWN);
			if (GetKeyState(VK_RETURN) & 0x8000)
			{
				if (Count == 0)
				{
					s_Character.Move(JUMP);
					KillTimer(hWnd, 1);
					SetTimer(hWnd, 2, 30, NULL);
				}
			}
		}
		else if (wParam == 2)
		{
			s_Character.Jump(Count);
			Count++;
			if (Count > 20)
			{
				Count = 0;
				KillTimer(hWnd, 2);
			}
		}
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
