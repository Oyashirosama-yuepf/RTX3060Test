#include <windows.h> 
#include <stdio.h>
#include <tchar.h>

#define BUFFER_SIZE 4096

int _tmain(void)
{
	TCHAR szBuffer[BUFFER_SIZE];
	DWORD dwRead = 0;
	DWORD dwWritten = 0;
	DWORD dwMode = PIPE_READMODE_MESSAGE;
	LPTSTR szPipename = _T("\\\\.\\pipe\\basicMPI");
	LPTSTR szMessage = _T("Message from client.");
	DWORD dwToWrite = _tcslen(szMessage) * sizeof(TCHAR);

	HANDLE hPipe = CreateFile(szPipename, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	WaitNamedPipe(szPipename, INFINITE);

	SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);

	if (!WriteFile(hPipe, szMessage, dwToWrite, &dwWritten, NULL))
	{
		_tprintf(_T("WriteFile failed! Error code: [%u]\n"), GetLastError());
		return -1;
	}

	_tprintf(_T("Message sent to server, receiving reply as follows:\n"));

	while (ReadFile(hPipe, szBuffer, BUFFER_SIZE * sizeof(TCHAR), &dwRead, NULL) && GetLastError() != ERROR_MORE_DATA)
	{
		_tprintf(_T("%s"), szBuffer);
	}

	_tprintf(_T("\nSuccess!\nPress ENTER to exit."));
	scanf_s("%c", szBuffer);

	CloseHandle(hPipe);

	return 0;
}
