#include "framework.h"
#include "카드맞추기게임.h"
#include"BitMapManager.h"
#include"CardManager.h"
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    srand((unsigned)time(NULL));
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

   
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg;


    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    POINT pt;
    static RECT GameStartRect = { 200, 300, 400, 400 };
    static int Count = 0;
    static bool s_bGameState = false;
    switch (message)
    {
    case WM_CREATE:
        BitMapManager::GetBitMapManager()->Set_BitMap(hWnd, hInst);
        CardManager::GetCardManager()->SetCard();
        break;
    case WM_LBUTTONDOWN:
        if (s_bGameState == false)
        {
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            if(PtInRect(&GameStartRect, pt))
                s_bGameState = true;
        }
        else if (s_bGameState == true && Count != 2)
        {
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            CardManager::GetCardManager()->ColliderCheck(pt, Count);   
            if (Count == 2 && CardManager::GetCardManager()->CheckCorrectCard(Count) == false)
            {
                SetTimer(hWnd, 1, 1000, NULL);
            }
            if (CardManager::GetCardManager()->CardOKCheck() == true)
            {
                InvalidateRect(hWnd, NULL, false);
                if (MessageBox(hWnd, "클리어!!! 다시하시겠습니까??", "클리어!!!", MB_OKCANCEL) == IDOK)
                {
                    s_bGameState = false;
                    CardManager::GetCardManager()->CardReset();
                    Count = 0;
                    InvalidateRect(hWnd, NULL, true);
                    break;
                }
                else
                    SendMessage(hWnd, WM_DESTROY, NULL, NULL);
            }
        }
        InvalidateRect(hWnd, NULL,false);
        break;
    case WM_TIMER:
            CardManager::GetCardManager()->SetCardState();
            InvalidateRect(hWnd, NULL, false);
            Count = 0;
            KillTimer(hWnd, 1);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        if (s_bGameState == false)
        {
            Rectangle(hdc, 250, 290, 350, 325);
            DrawText(hdc, "게임시작", strlen("게임시작"), &GameStartRect, DT_CENTER);         
        }
        else
        {
            BitMapManager::GetBitMapManager()->DrawBackGround(hdc);
            CardManager::GetCardManager()->DrawCard(hdc);
        }
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        delete BitMapManager::GetBitMapManager();
        delete CardManager::GetCardManager();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
