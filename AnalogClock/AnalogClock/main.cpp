#include<windows.h>
#include<math.h>
#pragma comment(lib, "msimg32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("AnalogClock");

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

POINT CenterPoint = { 500, 350 };
int ClockR = 300;
int HourR = 200;
int MinR = 150;
int SecR = 130;
double Radian = 3.14 / 180;
void TimeDraw(HDC hdc, SYSTEMTIME time)
{
	MoveToEx(hdc, CenterPoint.x, CenterPoint.y, NULL);	
	LineTo(hdc, CenterPoint.x + HourR * cos((90 + 0.1f * time.wMinute) * Radian), CenterPoint.y + HourR * sin((90 + 0.1f * time.wMinute) * Radian));
	MoveToEx(hdc, CenterPoint.x, CenterPoint.y, NULL);
	LineTo(hdc, CenterPoint.x + MinR * cos((270 + 6 * time.wMinute) * Radian), CenterPoint.y + MinR * sin((270 + 6 * time.wMinute) * Radian));
	MoveToEx(hdc, CenterPoint.x, CenterPoint.y, NULL);
	LineTo(hdc, CenterPoint.x + SecR * cos((270 + 6 * time.wSecond) * Radian), CenterPoint.y + SecR * sin((270 + 6 * time.wSecond) * Radian));
}

void DrawClock(HDC hdc)
{
	int Add1, Add2;
	TCHAR buf[256];
	Ellipse(hdc, CenterPoint.x - ClockR, CenterPoint.y - ClockR, CenterPoint.x + ClockR, CenterPoint.y + ClockR);
	for (int i = 12; i > 0; i--)
	{
		wsprintf(buf, L"%d", i);
		TextOut(hdc, CenterPoint.x + ClockR * cos(30 * (i - 3) * Radian), CenterPoint.y + ClockR * sin(30 * (i - 3) * Radian), buf, lstrlen(buf));
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static SYSTEMTIME Time;
	static TCHAR buf[256];
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawClock(hdc);
		TimeDraw(hdc, Time);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		GetLocalTime(&Time);
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

