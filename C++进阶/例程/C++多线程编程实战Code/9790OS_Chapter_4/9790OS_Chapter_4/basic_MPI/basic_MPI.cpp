#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#include <commctrl.h>

#pragma comment ( lib, "comctl32.lib" )
#pragma comment ( linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' \
version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")

#define BUTTON_MSG		100
#define BUTTON_CLOSE	101
#define LABEL_TEXT		102

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hThis, HINSTANCE hPrev, LPTSTR szCommandLine, int iWndShow)
{
	UNREFERENCED_PARAMETER(hPrev);
	UNREFERENCED_PARAMETER(szCommandLine);

	TCHAR* szWindowClass = _T("__basic_MPI_wnd_class__");

	WNDCLASSEX wndEx = { 0 };
	wndEx.cbSize = sizeof(WNDCLASSEX);
	wndEx.style = CS_HREDRAW | CS_VREDRAW;
	wndEx.lpfnWndProc = WindowProcedure;
	wndEx.cbClsExtra = 0;
	wndEx.cbWndExtra = 0;
	wndEx.hInstance = hThis;
	wndEx.hIcon = LoadIcon(wndEx.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wndEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndEx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndEx.lpszMenuName = NULL;
	wndEx.lpszClassName = szWindowClass;
	wndEx.hIconSm = LoadIcon(wndEx.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wndEx))
	{
		return 1;
	}

	InitCommonControls();

	HWND hWnd = CreateWindow(szWindowClass, _T("Basic Message Passing Interface"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 200, 200, 440, 340, NULL, NULL, wndEx.hInstance, NULL);

	if (!hWnd)
	{
		return NULL;
	}

	HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, BALTIC_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Microsoft Sans Serif"));

	HWND hButtonMsg = CreateWindow(_T("BUTTON"), _T("Show msg"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 190, 260, 100, 25, hWnd, (HMENU)BUTTON_MSG, wndEx.hInstance, NULL);

	HWND hButtonClose = CreateWindow(_T("BUTTON"), _T("Close me"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 310, 260, 100, 25, hWnd, (HMENU)BUTTON_CLOSE, wndEx.hInstance, NULL);

	HWND hText = CreateWindow(_T("STATIC"), NULL, WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER, 15, 20, 390, 220, hWnd, (HMENU)LABEL_TEXT, wndEx.hInstance, NULL);

	SendMessage(hButtonMsg, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hButtonClose, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hText, WM_SETFONT, (WPARAM)hFont, TRUE);

	ShowWindow(hWnd, iWndShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	 
	UnregisterClass(wndEx.lpszClassName, wndEx.hInstance);

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case BUTTON_MSG:
			{
				MessageBox(hWnd, _T("Hello!"), _T("Basic MPI"), MB_OK | MB_TOPMOST);
				break;
			}
			case BUTTON_CLOSE:
			{
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}
			}
			break;
		}

		case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			TCHAR szBuffer[4096];
			wsprintf(szBuffer, _T("\n\n\tCursor X position:\t%d\n\tCursor Y position:\t%d"), xPos, yPos);

			HWND hText = GetDlgItem(hWnd, LABEL_TEXT);
			SetWindowText(hText, szBuffer);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	return 0;
}
