// AIEngine.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AIEngine.h"
#include "World.h"
#include "Cgdi.h"
#include "PrecisionTimer.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;													// current instance
WCHAR szTitle[MAX_LOADSTRING]			= TEXT("AI Engine");		// The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]		= TEXT("AIEngine");			// the main window class name

World* g_World;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_AIENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
	HWND hWnd = InitInstance(hInstance, nCmdShow);
    if (!hWnd)
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AIENGINE));

    MSG msg;

	PrecisionTimer timer;
	// timer.SmoothUpdatesOn();
	timer.Start();

	bool bDone = false;

	std::vector<double> times;
	times.reserve(10000);

	while (!bDone)
	{
		// Main message loop:
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}

		if (msg.message != WM_QUIT)
		{
			double elapsed = timer.TimeElapsed();
			times.push_back(elapsed);
			g_World->Update(elapsed);
			InvalidateRect(hWnd, NULL, false);
			UpdateWindow(hWnd);
			Sleep(2);
		}
	}

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AIENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_AIENGINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_DLGFRAME,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (hWnd)
   {
	   ShowWindow(hWnd, nCmdShow);
	   UpdateWindow(hWnd);
   }

   return hWnd;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int clientWidth, clientHeight;
	static HDC hdcBackBuffer;
	static HBITMAP hBitmap, hOldBitmap;

    switch (message)
    {
	case WM_CREATE:
		{
			RECT rect;
			GetClientRect(hWnd, &rect);
			clientWidth = rect.right;
			clientHeight = rect.bottom;
			hdcBackBuffer = CreateCompatibleDC(NULL);
			HDC hdc = GetDC(hWnd);
			hBitmap = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);
			ReleaseDC(hWnd, hdc);

			g_World = new World(clientWidth, clientHeight);
		}
		break;

	case WM_LBUTTONDOWN:
		{
			POINTS Position = MAKEPOINTS(lParam);
			g_World->SetGoalPosition(Vec2(Position.x, Position.y));
		}
		break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'S': if (GetAsyncKeyState(VK_SHIFT)) { g_World->DisableSeek();	}	else { g_World->EnableSeek(); }		break;
		case 'A': if (GetAsyncKeyState(VK_SHIFT)) { g_World->DisableArrive(); }	else { g_World->EnableArrive(); }	break;
		case 'F': if (GetAsyncKeyState(VK_SHIFT)) { g_World->DisableFlee(); }	else { g_World->EnableFlee(); }		break;
		}
	}
	break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
			BitBlt(hdcBackBuffer, 0, 0, clientWidth, clientHeight, NULL, NULL, NULL, BLACKNESS);
			gdi->StartDrawing(hdcBackBuffer);
			g_World->Render();
			gdi->StopDrawing(hdcBackBuffer);
			BitBlt(ps.hdc, 0, 0, clientWidth, clientHeight, hdcBackBuffer, 0, 0, SRCCOPY);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:

		SelectObject(hdcBackBuffer, hOldBitmap);
		DeleteDC(hdcBackBuffer);
		DeleteObject(hBitmap);

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
