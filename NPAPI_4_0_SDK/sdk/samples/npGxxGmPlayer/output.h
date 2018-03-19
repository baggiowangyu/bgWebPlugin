#ifndef _output_H_
#define _output_H_

/////////////////////////////////////////////////////////////////
// ���ﶨ���˵�������
#define EXPORT_API_C    extern "C"__declspec(dllexport)
#ifdef EXPORT_MODULE
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif

/**
 * ���������Ϣ
 */
void __stdcall DebugStringOutputA(const char *format, ...);
void __stdcall DebugStringOutputW(const wchar_t *format, ...);

#ifdef UNICODE
#define DebugStringOutput DebugStringOutputW
#else
#define DebugStringOutput DebugStringOutputA
#endif


/**
 * ��װDump����������ָ��Dump����λ��
 * @Param	aMiniDumpSavePath	Dump�ļ�����λ��
 */
void SetupMiniDumpMonitor(const TCHAR *aMiniDumpSavePath);

#endif//_output_H_