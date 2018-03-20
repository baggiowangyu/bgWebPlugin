#include "npJsInterface.h"
#include "output.h"

void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_GetVersion() >>> \"1.0.0.1\"\n");
}

void __stdcall NPAPI_GetPluginDescript(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_GetPluginDescript >>> \"This is a NPAPI plugin for Gosuncn-Goldmsg media player...\"\n");
}