#include "npJsInterface.h"
#include "output.h"
#include "GxxGmPlayerImp.h"


void __stdcall NPAPI_GetVersion(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_GetVersion() >>> \"1.0.0.1\"\n");
}

void __stdcall NPAPI_GetPluginDescript(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_GetPluginDescript >>> \"This is a NPAPI plugin for Gosuncn-Goldmsg media player...\"\n");
}

void __stdcall NPAPI_JsCallback(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_NPAPI_JsCallback >>> \"Install a javascript callback function...\"\n");

	// 拿到插件对象
	if (global_plugin_)
	{
		if (global_plugin_->m_pJsCallbackObject == NULL)
			global_plugin_->m_pJsCallbackObject = NPN_RetainObject(NPVARIANT_TO_OBJECT(*args));
	}
}

void __stdcall NPAPI_TestJsCallback(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_TestJsCallback >>> \"Test Js's callback function...\"\n");

	if (global_plugin_)
	{
		if (!(!global_plugin_->m_pJsCallbackObject))  
		{  
			NPVariant result;
			NPN_InvokeDefault(global_plugin_->m_pNPInstance, global_plugin_->m_pJsCallbackObject, NULL, 0, &result); 
			NPN_ReleaseVariantValue(&result);
		}  
	}
	
}

void __stdcall NPAPI_InitializeMediaPlayer(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_InitializeMediaPlayer >>> \"Initialize player...\"\n");

	_PlayerCore_ core_type = PlayerCore_vlc;
	NPString type = NPVARIANT_TO_STRING(*args);
	if (_stricmp(type.UTF8Characters, "vlc") == 0)
	{
		// 
		core_type = PlayerCore_vlc;
	}
	else if (_stricmp(type.UTF8Characters, "ffplay") == 0)
	{
		 //
		core_type = PlayerCore_ffplay;
	}
	else if (_stricmp(type.UTF8Characters, "gxx") == 0)
	{
		// 
		core_type = PlayerCore_gxx;
	}
	else
	{
		// 
	}

	gxx_gm_player_.Initialize(global_plugin_->m_hWnd, core_type);
}

void __stdcall NPAPI_DestroyMediaPlayer(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_DestroyMediaPlayer >>> \"Destroy player...\"\n");

	gxx_gm_player_.Destroy();
}

void __stdcall NPAPI_MediaPlayerPlayByLocalPath(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_MediaPlayerPlayByLocalPath >>> \"Play media by local path...\"\n");

	NPString path = NPVARIANT_TO_STRING(*args);
	gxx_gm_player_.PlayLocalFile(path.UTF8Characters);
}

void __stdcall NPAPI_MediaPlayerPlayByUrl(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_MediaPlayerPlayByUrl >>> \"Play media by url...\"\n");

	NPString url = NPVARIANT_TO_STRING(*args);
	gxx_gm_player_.PlayUrl(url.UTF8Characters);
}

void __stdcall NPAPI_MediaPlayerStop(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	DebugStringOutput("NPAPI_MediaPlayerStop >>> \"Stop play...\"\n");

	gxx_gm_player_.Stop();
}