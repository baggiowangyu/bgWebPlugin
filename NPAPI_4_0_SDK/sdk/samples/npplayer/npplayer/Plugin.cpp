#include "Plugin.h"

////// functions /////////
NPError NS_PluginInitialize()
{
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
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

////// CPlugin /////////
CPlugin::CPlugin(NPP pNPInstance) : nsPluginInstanceBase(),
m_pNPInstance(pNPInstance),
m_bInitialized(FALSE)
{
}

CPlugin::~CPlugin()
{
}