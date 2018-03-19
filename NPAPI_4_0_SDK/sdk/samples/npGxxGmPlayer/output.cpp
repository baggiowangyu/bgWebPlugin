#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <objbase.h>
#include <tchar.h>
#include <DbgHelp.h>
#include "output.h"

#pragma comment(lib, "Dbghelp.lib")

#pragma comment(lib, "Dbghelp.lib")

using namespace std;

#define DEBUG_OUTPUT_BUFFER_LENGTH	10240

void __stdcall DebugStringOutputA(const char *format, ...)
{
	va_list argvs;
	char *value = new char[DEBUG_OUTPUT_BUFFER_LENGTH];
	ZeroMemory(value, sizeof(char) * DEBUG_OUTPUT_BUFFER_LENGTH);
	va_start(argvs, format);
	int n = vsprintf_s(value, DEBUG_OUTPUT_BUFFER_LENGTH, format, argvs);
	OutputDebugStringA(value);
	printf(value);
	va_end(argvs);

	delete [] value;
}

void __stdcall DebugStringOutputW(const wchar_t *format, ...)
{
	va_list argvs;
	wchar_t *value = new wchar_t[DEBUG_OUTPUT_BUFFER_LENGTH];
	ZeroMemory(value, sizeof(wchar_t) * DEBUG_OUTPUT_BUFFER_LENGTH);
	va_start(argvs, format);
	int n = vswprintf_s(value, DEBUG_OUTPUT_BUFFER_LENGTH, format, argvs);
	OutputDebugStringW(value);
	wprintf(value);
	va_end(argvs);

	delete [] value;
}


//////////////////////////////////////////////////////////////////////////
//
// Dump���

/**
 * ȫ�ֱ���
 */
TCHAR g_MiniDumpPath[MAX_PATH] = {0};

/**
 * ����С�ڴ�ת���ļ� 
 *
 * ������
 *	@aMiniDumpPath	Dump�ļ�����·��
 *	@pException		�����׳����쳣
 */
LONG CreateDumpFile(EXCEPTION_POINTERS *aException)  
{
	if (_tcslen(g_MiniDumpPath) <= 0)
		return -1;

	// ����Dump�ļ�  
	HANDLE hDumpFile = CreateFile(g_MiniDumpPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hDumpFile == INVALID_HANDLE_VALUE)
		return -2;

	// Dump��Ϣ
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = aException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;  

	// д��Dump�ļ�����
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);

	return 0;
}

void SetupMiniDumpMonitor(const TCHAR *aMiniDumpSavePath)
{
	// �����ñ���·��
	if (_tcslen(aMiniDumpSavePath) <= 0)
		return ;

	_tcscpy_s(g_MiniDumpPath, MAX_PATH, aMiniDumpSavePath);

	// ע��Dump�ص�
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CreateDumpFile);

	return ;
}