#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include "CQueue.h"
#include <commctrl.h>

#pragma comment ( lib, "comctl32.lib" )
#pragma comment ( linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"" )

#define BUFFER_SIZE		4096

#define LABEL_TEXT		100

#define WM_PLOTDATA	WM_USER		+ 1
#define WM_ENDTASK	WM_PLOTDATA + 1

#define THREAD_NUMBER	4
#define MAX_MSGCOUNT	10

#define CALCULATION_TIME	1000
#define DRAWING_TIME		2300

#define EVENT_NAME		_T( "__t_event__" )

typedef struct tagPLOTDATA
{
	int value;
	DWORD dwThreadId;
	int iMsgID;
} PLOTDATA, *PPLOTDATA;

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI StartAddress(LPVOID lpParameter);
DWORD WINAPI DrawPlot(LPVOID lpParameter);

int iMessageID = 0;
HANDLE gEvent = NULL;
HANDLE hThreads[THREAD_NUMBER];
HANDLE hThread = NULL;

CRITICAL_SECTION cs;
CQueue<PLOTDATA> queue;

int WINAPI _tWinMain(HINSTANCE hThis, HINSTANCE hPrev, LPTSTR szCommandLine, int iWndShow)
{
	UNREFERENCED_PARAMETER(hPrev);
	UNREFERENCED_PARAMETER(szCommandLine);

	InitializeCriticalSection(&cs);

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

	HWND hText = CreateWindow(_T("STATIC"), NULL, WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER, 15, 20, 390, 220, hWnd, (HMENU)LABEL_TEXT, wndEx.hInstance, NULL);

	SendMessage(hText, WM_SETFONT, (WPARAM)hFont, TRUE);

	ShowWindow(hWnd, iWndShow);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(wndEx.lpszClassName, wndEx.hInstance);

	WaitForMultipleObjects(THREAD_NUMBER, hThreads, TRUE, INFINITE);

	for (int iIndex = 0; iIndex < THREAD_NUMBER; iIndex++)
	{
		CloseHandle(hThreads[iIndex]);
	}

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(gEvent);

	DeleteCriticalSection(&cs);

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		gEvent = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME);

		for (int iIndex = 0; iIndex < THREAD_NUMBER; iIndex++)
		{
			hThreads[iIndex] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAddress, hWnd, 0, NULL);
		}

		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DrawPlot, hWnd, 0, NULL);
		break;
	}
	case WM_PLOTDATA:
	{
		PPLOTDATA pData = (PPLOTDATA)lParam;

		HWND hLabel = GetDlgItem(hWnd, LABEL_TEXT);

		TCHAR szBuffer[BUFFER_SIZE];
		GetWindowText(hLabel, szBuffer, BUFFER_SIZE);

		wsprintf(szBuffer, _T("%ws\n\n\tMessage has been received. Msg ID:\t%d"), szBuffer, pData->iMsgID);
		SetWindowText(hLabel, szBuffer);

		break;
	}
	case WM_ENDTASK:
	{
		HWND hLabel = GetDlgItem(hWnd, LABEL_TEXT);

		TCHAR szBuffer[BUFFER_SIZE];

		wsprintf(szBuffer, _T("\n\n\tPlot is drawn. You can close the window now."));
		SetWindowText(hLabel, szBuffer);
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
	HWND hWnd = (HWND)lpParameter;

	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME);

	if (hEvent != NULL)
	{
		SetEvent(hEvent);
	}

	CloseHandle(hEvent);

	int iCount = 0;
	while (iCount++ < MAX_MSGCOUNT)
	{
		// perform calculation
		Sleep(CALCULATION_TIME);

		// assembly result into PLOTDATA structure
		PPLOTDATA pData = new PLOTDATA();
		pData->value = (rand() % 0xFFFF) - iMessageID;
		pData->dwThreadId = GetCurrentThreadId();
		pData->iMsgID = ++iMessageID;

		EnterCriticalSection(&cs);
		queue.Enqueue(pData);
		LeaveCriticalSection(&cs);

		PostMessage(hWnd, WM_PLOTDATA, 0, (LPARAM)pData);
	}

	return 0L;
}

DWORD WINAPI DrawPlot(LPVOID lpParameter)
{
	HWND hWnd = (HWND)lpParameter;

	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME);

	WaitForSingleObject(hEvent, INFINITE);
	CloseHandle(hEvent);

	int iCount = 0;
	while (iCount++ < MAX_MSGCOUNT * THREAD_NUMBER)
	{
		EnterCriticalSection(&cs);
		PPLOTDATA pData = queue.Dequeue();
		LeaveCriticalSection(&cs);

		if (!pData)
		{
			break;
		}

		// perform drawing
		Sleep(DRAWING_TIME);

		HWND hLabel = GetDlgItem(hWnd, LABEL_TEXT);

		TCHAR szBuffer[BUFFER_SIZE];

		wsprintf(szBuffer, _T("\n\n\tThread ID:\t%u\n\tCurrent value:\t%d\n\tMessage ID:\t%d"), (DWORD)pData->dwThreadId, (int)pData->value, pData->iMsgID);
		SetWindowText(hLabel, szBuffer);

		delete pData;
	}

	PostMessage(hWnd, WM_ENDTASK, 0, 0);

	return 0L;
}
