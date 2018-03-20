#include "Plugin.h"

//////////////////////////////////////////////////////////////////////////
//
// 首先实现四个函数
// 这四个函数都在pluginbase.h(81)中有定义
// 
// 以下函数需要在每个指定的插件中被实现
// 首先是创建或销毁基类派生出来的对象
// nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct);
// void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin);
//
// 全局插件初始化或销毁
// NPError NS_PluginInitialize();
// void NS_PluginShutdown();
//

NPError NS_PluginInitialize()
{
	// 这里啥都不干
	// 我想这里的实现应该不是单纯的空函数
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
	// 这里啥都不干
}

nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
	if(!aCreateDataStruct)
		return NULL;

	CPlugin * plugin = new CPlugin(aCreateDataStruct->instance);
	return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin)
{
	if(aPlugin)
		delete (CPlugin *)aPlugin;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//
// 这里是我们具体的插件对象
// 插件的具体事务应当在此对象范围内进行处理

CPlugin::CPlugin(NPP pNPInstance) : nsPluginInstanceBase(),
m_pNPInstance(pNPInstance),
m_bInitialized(FALSE)
{
	// 这里啥都不干
}

CPlugin::~CPlugin()
{
	// 这里啥都不干
}

//////////////////////////////////////////////////////////////////////////