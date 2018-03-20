#include "Plugin.h"
#include "output.h"
#include <windowsX.h>
#include "npruntime.h"


static NPObject *sWindowObj;

//////////////////////////////////////////////////////////////////////////
//
// NPAPI ����� Javascript �����ӿڶ���

JsParams js_params[] = {
	{ 0,	NULL,	"GetVersion",			NPAPI_GetVersion		},
	{ 1,	NULL,	"GetPluginDescript",	NPAPI_GetPluginDescript },
	{ -1,	NULL,	NULL,					NULL					}
};

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

	// NPAPIĬ�ϴ�������Windowed���
	// ����Ҫ����winless���������Ҫ�� bWindowed �ֶ�����Ϊ FALSE
	BOOL bWindowed = TRUE;
	NPN_SetValue(aCreateDataStruct->instance, NPPVpluginTransparentBool, (void *)bWindowed);

	return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin)
{
	if(aPlugin)
		delete (CPlugin *)aPlugin;
}


//////////////////////////////////////////////////////////////////////////
//
// ���ﴦ����JavaScript�����Ĳ���

void ScriptablePluginObjectBase::Invalidate()
{
}

bool ScriptablePluginObjectBase::HasMethod(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObjectBase::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

bool ScriptablePluginObjectBase::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

bool ScriptablePluginObjectBase::HasProperty(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObjectBase::GetProperty(NPIdentifier name, NPVariant *result)
{
	return false;
}

bool ScriptablePluginObjectBase::SetProperty(NPIdentifier name, const NPVariant *value)
{
	//if (name == sBar_id) {
	//	printf ("bar set\n");
	//	return true;
	//}

	return false;
}

bool ScriptablePluginObjectBase::RemoveProperty(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObjectBase::Enumerate(NPIdentifier **identifier, uint32_t *count)
{
	return false;
}

bool ScriptablePluginObjectBase::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

// static
void ScriptablePluginObjectBase::_Deallocate(NPObject *npobj)
{
	// Call the virtual destructor.
	delete (ScriptablePluginObjectBase *)npobj;
}

// static
void ScriptablePluginObjectBase::_Invalidate(NPObject *npobj)
{
	((ScriptablePluginObjectBase *)npobj)->Invalidate();
}

// static
bool ScriptablePluginObjectBase::_HasMethod(NPObject *npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->HasMethod(name);
}

// static
bool ScriptablePluginObjectBase::_Invoke(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->Invoke(name, args, argCount, result);
}

// static
bool ScriptablePluginObjectBase::_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->InvokeDefault(args, argCount, result);
}

// static
bool ScriptablePluginObjectBase::_HasProperty(NPObject * npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->HasProperty(name);
}

// static
bool ScriptablePluginObjectBase::_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->GetProperty(name, result);
}

// static
bool ScriptablePluginObjectBase::_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	return ((ScriptablePluginObjectBase *)npobj)->SetProperty(name, value);
}

// static
bool ScriptablePluginObjectBase::_RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return ((ScriptablePluginObjectBase *)npobj)->RemoveProperty(name);
}

// static
bool ScriptablePluginObjectBase::_Enumerate(NPObject *npobj, NPIdentifier **identifier, uint32_t *count)
{
	return ((ScriptablePluginObjectBase *)npobj)->Enumerate(identifier, count);
}

// static
bool ScriptablePluginObjectBase::_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->Construct(args, argCount, result);
}


//////////////////////////////////////////////////////////////////////////
//
//

static NPObject * AllocateConstructablePluginObject(NPP npp, NPClass *aClass)
{
	return new ConstructablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ConstructablePluginObject, AllocateConstructablePluginObject);

bool ConstructablePluginObject::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	printf("Creating new ConstructablePluginObject!\n");

	NPObject *myobj = NPN_CreateObject(mNpp, GET_NPOBJECT_CLASS(ConstructablePluginObject));
	if (!myobj)
		return false;

	OBJECT_TO_NPVARIANT(myobj, *result);

	return true;
}

//////////////////////////////////////////////////////////////////////////
//
//


static NPObject * AllocateScriptablePluginObject(NPP npp, NPClass *aClass)
{
	return new ScriptablePluginObject(npp);
}


DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject, AllocateScriptablePluginObject);

ScriptablePluginObject::ScriptablePluginObject(NPP npp)
: ScriptablePluginObjectBase(npp)
{
	// ���������ӿ�ӳ��
	int index = 0;
	while(js_params[index].index_ != -1)
	{
		DebugStringOutput("ScriptablePluginObject::ScriptablePluginObject() >>> Map %s Js interface...\n", js_params[index].interfaceName_.c_str());
		js_params[index].npId_ = NPN_GetStringIdentifier(js_params[index].interfaceName_.c_str());
		++index;
	}
}

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
	bool has_method = false;

	int index = 0;
	while(js_params[index].index_ != -1)
	{
		if (js_params[index].npId_ == name)
		{
			has_method = true;
			break;
		}

		++index;
	}

	return has_method;
}

bool ScriptablePluginObject::HasProperty(NPIdentifier name)
{
	return false;
}

bool ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
	VOID_TO_NPVARIANT(*result);

	return true;
}

bool ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	// ����������ĵ���
	bool res = false;
	int index = 0;
	while(js_params[index].index_ != -1)
	{
		if (js_params[index].npId_ == name)
		{
			_Func_Js js_handler = js_params[index].jsFunc_;
			js_handler(args, argCount, result);
			res = true;
			break;
		}

		++index;
	}

	return res;
}

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	printf ("ScriptablePluginObject default method called!\n");

	const char* outString = "default method return val";
	char* npOutString = (char *)NPN_MemAlloc(strlen(outString) + 1);
	if (!npOutString)
		return false;
	strcpy(npOutString, outString);
	STRINGZ_TO_NPVARIANT(npOutString, *result);

	return true;
}



//////////////////////////////////////////////////////////////////////////
//
// �������ľ���ʵ��

// ��Ϣ��Ӧ����
static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);  
static WNDPROC lpOldProc = NULL; 

//CPlugin::CPlugin(void)
//{
//}

CPlugin::CPlugin(NPP pNPInstance)
: nsPluginInstanceBase()
, m_pNPInstance(pNPInstance)
, m_bInitialized(FALSE)
, m_hWnd(NULL)
, m_pScriptableObject(NULL)
{
	NPN_GetValue(m_pNPInstance, NPNVWindowNPObject, &sWindowObj);

	// ���ﶨ��������ŵĽӿ�
}

CPlugin::~CPlugin(void)
{
	// �ͷ�Js����
	NPN_ReleaseObject(m_pScriptableObject);
}

NPBool CPlugin::init(NPWindow* pNPWindow)
{
	m_Window = pNPWindow;
	m_hWnd = (HWND)pNPWindow->window;

	if (m_hWnd == NULL)
		return FALSE;

	// ���������໯�������Ϳ��Զ���Ϣ���д������ڴ����л�����
	lpOldProc = (WNDPROC)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LPARAM)(WNDPROC)PluginWinProc);

	// �������� Plugin ��������������Ϳ����ٴ��ڴ����з��� Plugin ������
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	m_bInitialized = TRUE;
	return TRUE;
}

void CPlugin::shut()
{
	SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LPARAM)(WNDPROC)lpOldProc);

	m_hWnd = NULL;
	m_bInitialized = FALSE;
}

NPBool CPlugin::isInitialized()
{
	return m_bInitialized;
}

NPError CPlugin::SetWindow(NPWindow* pNPWindow)
{
	// ����������ָ��
	m_Window = pNPWindow;
	return NPERR_NO_ERROR;
}

NPObject * CPlugin::GetScriptableObject()
{
	// ��������� NPObject �������½�һ��
	if (!m_pScriptableObject) {
		m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));
	}

	// ��ȡ����ֵ
	if (m_pScriptableObject) {
		NPN_RetainObject(m_pScriptableObject);
	}

	return m_pScriptableObject;
}

static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DebugStringOutput("[npGxxGmPlayer MESSAGE] MSG:%d, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);

	switch (msg)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);

			RECT rc;
			GetClientRect(hWnd, &rc);
			FillRect(hDC, &rc, (HBRUSH)(COLOR_WINDOW));
			FrameRect(hDC, &rc, GetStockBrush(BLACK_BRUSH));

			CPlugin *p = (CPlugin *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (p)
			{
				char *s = "���¼������������ʼ������Ƶ !";
				DrawTextA(hDC, s, strlen(s), &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}

			EndPaint(hWnd, &ps);
		}
		break;
		//case WM_MOUSEACTIVATE:
		//	{
		//		CPlugin *p = (CPlugin *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		//		// ���̰��£����ﴦ�������Ϣ
		//		const char* const m_vlcArgs[] = {
		//			"-I", "dummy",
		//			"--ignore-config",
		//		};

		//		p->m_vlcInst = libvlc_new(sizeof(m_vlcArgs) / sizeof(m_vlcArgs[0]), m_vlcArgs);

		//		p->m_vlcMedia = libvlc_media_new_location(p->m_vlcInst, "rtmp://live.hkstv.hk.lxdns.com/live/hks");
		//		p->m_vlcMplay = libvlc_media_player_new(p->m_vlcInst);
		//		libvlc_media_player_set_media (p->m_vlcMplay, p->m_vlcMedia);
		//		libvlc_media_release(p->m_vlcMedia);
		//		libvlc_media_player_set_hwnd(p->m_vlcMplay, p->m_hWnd);
		//		libvlc_media_player_play(p->m_vlcMplay);
		//	}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}