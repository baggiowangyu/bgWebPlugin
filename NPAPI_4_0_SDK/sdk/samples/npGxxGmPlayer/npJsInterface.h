#ifndef _npJsInterface_H_
#define _npJsInterface_H_

#include "pluginbase.h"

//////////////////////////////////////////////////////////////////////////
//
// ���ﶨ���ṩ��Javascriptʹ�õĽӿ�

void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result);
void __stdcall NPAPI_GetPluginDescript(const NPVariant *args, uint32_t argCount, NPVariant *result);

#endif//_npJsInterface_H_
