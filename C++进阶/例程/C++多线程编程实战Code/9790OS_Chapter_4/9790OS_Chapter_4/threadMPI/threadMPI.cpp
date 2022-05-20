#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "CQueue.h"
#include <commctrl.h>

#pragma comment ( lib, "comctl32.lib" )
#pragma comment ( linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"" )

#define BUFFER_SIZE		4096

#define BUTTON_CLOSE	100

#define T_MESSAGE		WM_USER		+ 1
#define T_ENDTASK		T_MESSAGE	+ 1

#define EVENT_NAME		_T( "__t_event__" )

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI StartAddress(LPVOID lpParameter);

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

	HWND hWnd = CreateWindow(szWindowClass, _T("Basic Message Passing Interface"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 200, 200, 440, 300, NULL, NULL, wndEx.hInstance, NULL);

	if (!hWnd)
	{
		return NULL;
	}

	HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, BALTIC_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Microsoft Sans Serif"));

	HWND hButton = CreateWindow(_T("BUTTON"), _T("Send message"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, 310, 210, 100, 25, hWnd, (HMENU)BUTTON_CLOSE, wndEx.hInstance, NULL);

	SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);

	ShowWindow(hWnd, iWndShow);

	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME);

	DWORD dwThreadId = 0;

	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAddress, hWnd, 0, &dwThreadId);

	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&dwThreadId);

	WaitForSingleObject(hEvent, INFINITE);
	CloseHandle(hEvent);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(wndEx.lpszClassName, wndEx.hInstance);

	PostThreadMessage(dwThreadId, T_ENDTASK, 0, 0);
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
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
			case BUTTON_CLOSE:
			{
				DWORD* pdwThreadId = (DWORD*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
				PostThreadMessage(*pdwThreadId, T_MESSAGE, 0, 0);
				break;
			}
			}
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

DWORD WINAPI StartAddress(LPVOID lpParameter)
{
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME);

	if (hEvent != NULL)
	{
		SetEvent(hEvent);
	}
	CloseHandle(hEvent);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		switch (msg.message)
		{
			case T_MESSAGE:
			{
				// TO DO
				// add some message processing here
				MessageBox(NULL, _T("Hi.\nI've just received a message."), _T("Thread"), MB_OK);
				break;
			}
			case T_ENDTASK:
			{
				// main thread is exiting
				// return immediately
				return 0L;
			}
		}
	}
	return 0L;
}
