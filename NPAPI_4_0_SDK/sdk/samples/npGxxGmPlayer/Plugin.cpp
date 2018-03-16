#include "Plugin.h"


//////////////////////////////////////////////////////////////////////////
//
// 首先实现四个函数
// 这四个函数都在pluginbase.h(81)中有定义
// 
// 以下函数需要在每个指定的插件中被实现
// 首先是创建或销毁基类派生出来的对象
//
//		nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct);
//		void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin);
//
// 全局插件初始化或销毁
// 
//		NPError NS_PluginInitialize();
//		void NS_PluginShutdown();
// 

NPError NS_PluginInitialize()
{
	// 这里啥都不干
	// 我想这里的实现应该不是单纯的空函数
	OutputDebugStringA("NS_PluginInitialize");
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
	// 这里啥都不干
	OutputDebugStringA("NS_PluginShutdown");
}

nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
	OutputDebugStringA("NS_NewPluginInstance");
	if(!aCreateDataStruct)
		return NULL;

	CPlugin * plugin = new CPlugin(aCreateDataStruct->instance);

	// NPAPI默认创建的是Windowed插件
	// 我们要创建winless插件，则需要手动设置一下
	BOOL bWindowed = FALSE;
	NPN_SetValue(aCreateDataStruct->instance, NPPVpluginTransparentBool, (void *)bWindowed);

	return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin)
{
	OutputDebugStringA("NS_DestroyPluginInstance");
	if(aPlugin)
		delete (CPlugin *)aPlugin;
}



//////////////////////////////////////////////////////////////////////////
//
// 插件对象的具体实现

CPlugin::CPlugin(void)
{
}

CPlugin::CPlugin(NPP pNPInstance)
: m_pNPInstance(pNPInstance)
, m_bInitialized(FALSE)
{
}

CPlugin::~CPlugin(void)
{
}

NPBool CPlugin::init(NPWindow* pNPWindow)
{
	OutputDebugStringA("CPlugin::init");
	m_bInitialized = TRUE;
	return TRUE;
}

void CPlugin::shut()
{
	OutputDebugStringA("CPlugin::shut");
	m_bInitialized = FALSE;
}

NPBool CPlugin::isInitialized()
{
	OutputDebugStringA("CPlugin::isInitialized");
	return m_bInitialized;
}