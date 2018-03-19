#ifndef _output_H_
#define _output_H_

/////////////////////////////////////////////////////////////////
// 这里定义了导出符号
#define EXPORT_API_C    extern "C"__declspec(dllexport)
#ifdef EXPORT_MODULE
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif

/**
 * 输出调试信息
 */
void __stdcall DebugStringOutputA(const char *format, ...);
void __stdcall DebugStringOutputW(const wchar_t *format, ...);

#ifdef UNICODE
#define DebugStringOutput DebugStringOutputW
#else
#define DebugStringOutput DebugStringOutputA
#endif


/**
 * 安装Dump监视器，并指定Dump保存位置
 * @Param	aMiniDumpSavePath	Dump文件保存位置
 */
void SetupMiniDumpMonitor(const TCHAR *aMiniDumpSavePath);

#endif//_output_H_