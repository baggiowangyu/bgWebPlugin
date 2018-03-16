#include "Plugin.h"


//////////////////////////////////////////////////////////////////////////
//
// ����ʵ���ĸ�����
// ���ĸ���������pluginbase.h(81)���ж���
// 
// ���º�����Ҫ��ÿ��ָ���Ĳ���б�ʵ��
// �����Ǵ��������ٻ������������Ķ���
//
//		nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct);
//		void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin);
//
// ȫ�ֲ����ʼ��������
// 
//		NPError NS_PluginInitialize();
//		void NS_PluginShutdown();
// 

NPError NS_PluginInitialize()
{
	// ����ɶ������
	// ���������ʵ��Ӧ�ò��ǵ����Ŀպ���
	OutputDebugStringA("NS_PluginInitialize");
	return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
	// ����ɶ������
	OutputDebugStringA("NS_PluginShutdown");
}

nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
	OutputDebugStringA("NS_NewPluginInstance");
	if(!aCreateDataStruct)
		return NULL;

	CPlugin * plugin = new CPlugin(aCreateDataStruct->instance);

	// NPAPIĬ�ϴ�������Windowed���
	// ����Ҫ����winless���������Ҫ�ֶ�����һ��
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
// �������ľ���ʵ��

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