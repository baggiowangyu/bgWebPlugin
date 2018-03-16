#include "Plugin.h"

//////////////////////////////////////////////////////////////////////////
//
// ����ʵ���ĸ�����
// ���ĸ���������pluginbase.h(81)���ж���
// 
// ���º�����Ҫ��ÿ��ָ���Ĳ���б�ʵ��
// �����Ǵ��������ٻ������������Ķ���
// nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct);
// void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin);
//
// ȫ�ֲ����ʼ��������
// NPError NS_PluginInitialize();
// void NS_PluginShutdown();
//

NPError NS_PluginInitialize()
{
	// ����ɶ������
	// ���������ʵ��Ӧ�ò��ǵ����Ŀպ���
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
	// ����ɶ������
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
// ���������Ǿ���Ĳ������
// ����ľ�������Ӧ���ڴ˶���Χ�ڽ��д���

CPlugin::CPlugin(NPP pNPInstance) : nsPluginInstanceBase(),
m_pNPInstance(pNPInstance),
m_bInitialized(FALSE)
{
	// ����ɶ������
}

CPlugin::~CPlugin()
{
	// ����ɶ������
}

//////////////////////////////////////////////////////////////////////////