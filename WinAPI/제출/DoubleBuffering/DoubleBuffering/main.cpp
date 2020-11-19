#include"Character.h"
#pragma comment(lib, "msimg32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DoubleBuffering");

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
	static Character s_Char;
	static BitMap s_Bit;
	static BitMap s_BitBack;
	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		s_Char.SetDefault(hdc);
		s_Bit.SetImage(hdc, TEXT(""), BACK);
		s_BitBack.SetImage(hdc, TEXT(""), BACK);
		SetTimer(hWnd, 1, 100, NULL);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_TIMER:
		if (wParam == 1)
		{
			if (GetKeyState(VK_LEFT) & 0x8000)
				s_Char.Move(LEFT);
			if (GetKeyState(VK_RIGHT) & 0x8000)
				s_Char.Move(RIGHT);
			if (GetKeyState(VK_UP) & 0x8000)
				s_Char.Move(UP);
			if (GetKeyState(VK_DOWN) & 0x8000)
				s_Char.Move(DOWN);
			if (GetKeyState(VK_RETURN) & 0x8000)
				SetTimer(hWnd, 2, 50, NULL);
		}
		else
			if (s_Char.Jump() == false)
			{
				KillTimer(hWnd, 2);
				s_Char.SetJumpState(false);
			}
		InvalidateRect(hWnd, NULL, false);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(s_Bit.GetMemDC(), 0, 0, 1048, 768, s_BitBack.GetMemDC(), 0, 0, SRCCOPY);
		s_Char.Draw(s_Bit.GetMemDC());
		BitBlt(hdc, 0, 0, 1048, 768, s_Bit.GetMemDC(), 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

