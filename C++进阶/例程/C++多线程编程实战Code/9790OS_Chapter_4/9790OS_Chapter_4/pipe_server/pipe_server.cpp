#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>

#define BUFFER_SIZE 4096

DWORD WINAPI StartAddress(LPVOID lpParameter);

int _tmain(void)
{
	LPTSTR szPipename = _T("\\\\.\\pipe\\basicMPI");

	while (TRUE)
	{
		_tprintf(_T("basicMPI: waiting client connection\n"));

		HANDLE hPipe = CreateNamedPipe(szPipename, PIPE_ACCESS_DUPLEX, PIPE_WAIT | PIPE_READMODE_MESSAGE | PIPE_TYPE_MESSAGE, PIPE_UNLIMITED_INSTANCES, BUFFER_SIZE, BUFFER_SIZE, 0, NULL);

		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreateNamedPipe failed! Error code: [%u]\n"), GetLastError());
			return 2;
		}

		if (ConnectNamedPipe(hPipe, NULL))
		{
			_tprintf(_T("Connection succeeded.\n"));

			HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAddress, hPipe, 0, NULL);

			CloseHandle(hThread);
		}
	}

	return 0;
}

DWORD WINAPI StartAddress(LPVOID lpParameter)
{
	HANDLE hPipe = (HANDLE)lpParameter;

	PTCHAR szRequest = (PTCHAR)HeapAlloc(GetProcessHeap(), 0, BUFFER_SIZE * sizeof(TCHAR));
	PTCHAR szReply = (PTCHAR)HeapAlloc(GetProcessHeap(), 0, BUFFER_SIZE * sizeof(TCHAR));
	DWORD dwBytesRead = 0;
	DWORD dwReplyBytes = 0;
	DWORD dwBytesWritten = 0;

	_tprintf(_T("Waiting messages.\n"));

	if (!ReadFile(hPipe, szRequest, BUFFER_SIZE * sizeof(TCHAR), &dwBytesRead, NULL))
	{
		_tprintf(_T("ReadFile failed! Error code: [%u]\n"), GetLastError());
		return 2L;
	}

	// do some processing

	_tprintf(_T("Client request:\"%s\"\n"), szRequest);

	_tcscpy_s(szReply, BUFFER_SIZE, _T("default answer from server"));

	dwReplyBytes = (_tcslen(szReply) + 1) * sizeof(TCHAR);

	if (!WriteFile(hPipe, szReply, dwReplyBytes, &dwBytesWritten, NULL))
	{
		_tprintf(_T("WriteFile failed! Error code: [%u]"), GetLastError());
		return 2L;
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);

	HeapFree(GetProcessHeap(), 0, szRequest);
	HeapFree(GetProcessHeap(), 0, szReply);

	_tprintf(_T("Success.\n"));

	return 0L;
}
