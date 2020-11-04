#include<windows.h>
#pragma comment(lib, "msimg32.lib")
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TransparentBlt");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
	
		TranslateMessage(&Message);
		DispatchMessageW(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HDC hMemDC;
	HBITMAP hImage, hOldBitmap;
	static POINT CharacterPoint = { 650, 300 };
	static POINT ImagePoint = { 0, 0 };
	static int iDirection = NULL;
	static bool b_MoveState = false;
	int bx, by;
	BITMAP bit;
	switch (iMessage)
	{
	case WM_KEYDOWN:
		if (b_MoveState == false)
		{
			SetTimer(hWnd, 1, 100, 0);
			b_MoveState = true;
		}
		switch (wParam)
		{	
		case VK_LEFT:
			if (iDirection != LEFT)
			{
				ImagePoint.x = 0;
				ImagePoint.y = 2;
				iDirection = LEFT;
			}
			CharacterPoint.x -= 5;
			break;
		case VK_RIGHT:
			if (iDirection != RIGHT)
			{
				ImagePoint.x = 0;
				ImagePoint.y = 3;
				iDirection = RIGHT;
			}
			CharacterPoint.x += 5;
			break;
		case VK_UP:
			if (iDirection != UP)
			{
				ImagePoint.x = 0;
				ImagePoint.y = 1;
				iDirection = UP;
			}
			CharacterPoint.y -= 5;
			break;
		case VK_DOWN:
			if (iDirection != DOWN)
			{
				ImagePoint.x = 0;
				ImagePoint.y = 0;
				iDirection = DOWN;
			}
			CharacterPoint.y += 5;
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_KEYUP:
		ImagePoint.x = 0;
		b_MoveState = false;
		KillTimer(hWnd, 1);
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_TIMER:
		if (iDirection != NULL)
		{
			ImagePoint.x++;
			if (ImagePoint.x > 3)
				ImagePoint.x = 0;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc);

		hImage = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

		GetObject(hImage, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		TransparentBlt(hdc, CharacterPoint.x, CharacterPoint.y, bx / 4, by / 4,
			hMemDC, (bx / 4) * ImagePoint.x, (by / 4) * ImagePoint.y, bx / 4, by / 4, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hImage);
		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}