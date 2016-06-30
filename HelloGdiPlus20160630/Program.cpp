#include <windows.h>
#include <tchar.h>

#include <sti.h>
#include <gdiplus.h>
using namespace Gdiplus;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassNme[] = _T("HelloGdiPlus20160630");

GdiplusStartupInput gdiSI;
ULONG_PTR gdiToken;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
                   LPSTR lpszCmdLine, int nCmdShow)
{
	GdiplusStartup(&gdiToken, &gdiSI, NULL);

    HWND hWnd;
    MSG msg;
    WNDCLASS myProg;
    if (!hPreInst) {
        myProg.style            = CS_HREDRAW | CS_VREDRAW;
        myProg.lpfnWndProc      = WndProc;
        myProg.cbClsExtra       = 0;
        myProg.cbWndExtra       = 0;
        myProg.hInstance        = hInstance;
        myProg.hIcon            = NULL;
        myProg.hCursor          = LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
        myProg.lpszMenuName     = NULL;
        myProg.lpszClassName    = szClassNme;
        if (!RegisterClass(&myProg))
            return FALSE;
    }
    hWnd = CreateWindow(szClassNme,	// class名
		_T("Hello GDI+"),		// タイトル
        WS_OVERLAPPEDWINDOW,		// Style
        CW_USEDEFAULT,				// X
        CW_USEDEFAULT,				// Y
        CW_USEDEFAULT,				// Width
        CW_USEDEFAULT,				// Height
        NULL,						// 親ウィンドウまたはオーナーウィンドウのハンドル
        NULL,						// メニューハンドルまたは子ウィンドウ ID
        hInstance,					// アプリケーションインスタンスのハンドル
        NULL);						// ウィンドウ作成データ
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
	
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	GdiplusShutdown(gdiToken);

    return (msg.wParam);
}

void OnPaint(HDC hdc)
{
    Graphics g(hdc);

    Pen pen1(Color(255, 255, 0, 0), 5);
	Pen pen2(Color(100, 0, 255, 0), 40);

    g.DrawLine(&pen1, 20, 20, 250, 50);
    g.DrawLine(&pen2, 40, 50, 220, 50);

    return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            OnPaint(hdc);
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return(DefWindowProc(hWnd, msg, wParam, lParam));
    }
    return (0L);
}
