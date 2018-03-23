#ifndef _npJsInterface_H_
#define _npJsInterface_H_

#include "pluginbase.h"
#include "Plugin.h"

//////////////////////////////////////////////////////////////////////////
//
// 这里定义提供给Javascript使用的接口

void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetPluginDescript(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_JsCallback(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_TestJsCallback(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_InitializeMediaPlayer(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_DestroyMediaPlayer(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_MediaPlayerPlayByLocalPath(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_MediaPlayerPlayByUrl(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_MediaPlayerStop(const NPVariant *args, uint32_t argCount, NPVariant *result);

#endif//_npJsInterface_H_
