#include "WindowCreator.h"

#include <tchar.h>

HWND ghMainWnd = 0;
HINSTANCE ghInstance = 0;

bool GenerateWindow(WNDPROC WndProc, int width, int height);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool GenerateWindow(int ScreenWidth, int ScreenHeight)
{
    return GenerateWindow(WndProc, ScreenWidth, ScreenHeight);
}

bool GenerateWindow(WNDPROC WndProc, int width, int height)
{
    static TCHAR szWindowClass[] = _T("opengl_setup");
    static TCHAR szTitle[] = _T("OpenGL setup test");

    HINSTANCE inst = GetModuleHandle(NULL);

    RECT windowSize = {0, 0, width, height};
    AdjustWindowRect(&windowSize, CS_HREDRAW | CS_VREDRAW, FALSE);	

    WNDCLASSEX  wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW; //redraw if resized or moved that changes height or width
    wcex.lpfnWndProc    = WndProc;                 
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = inst;
    wcex.hIcon          = LoadIcon(inst, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if(!RegisterClassEx(&wcex))
    {
        MessageBox(0, L"FAILURE: RegisterClass failed.", 0, 0);
        return false;
    }

    ghInstance = inst;

    //Create Window - get an HWND
    ghMainWnd = CreateWindow(
        szWindowClass,                          // Registered WNDCLASS instance to use.
        szTitle,                                // window title
        WS_OVERLAPPEDWINDOW,                    // style flags
        CW_USEDEFAULT,                          // x-coordinate for new window
        CW_USEDEFAULT,                          // y-coordinate for new window
        windowSize.right - windowSize.left,     // width
        windowSize.bottom - windowSize.top,     // height
        0,                                      // parent window
        0,                                      // menu handle
        inst,                                   // app instance
        0                                       // extra creation parameters
    ); 

    if(ghMainWnd == 0)
    {
        MessageBox(0, L"FAILURE: CreateWindow failed.", 0, 0);
        return false;
    }

    return true;
}

void ActivateWindow()	//Activate the game window so it is actually visible
{
    ShowWindow(ghMainWnd, SW_SHOWDEFAULT);
    UpdateWindow(ghMainWnd);
}

void CheckMessagePump()
{
    MSG msg = {0};
    
    while( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );

        if (msg.message == WM_QUIT)
        {
            //TODO exit
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   
    switch(msg)
    {
        case WM_LBUTTONDOWN:
            MessageBox(0, L"Hello, World", L"Hello", MB_OK);
            break;

        case WM_KEYDOWN:
        case WM_KEYUP:
            //TODO handle keyboard input
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}