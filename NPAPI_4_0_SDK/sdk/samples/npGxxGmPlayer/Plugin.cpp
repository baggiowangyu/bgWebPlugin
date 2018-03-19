#include "Plugin.h"
#include <windowsX.h>

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


	// NPAPI默认创建的是Windowed插件
	// 我们要创建winless插件，则需要将 bWindowed 手动设置为 FALSE
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
// 插件对象的具体实现

// 消息响应函数
static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);  
static WNDPROC lpOldProc = NULL; 

CPlugin::CPlugin(void)
{
}

CPlugin::CPlugin(NPP pNPInstance)
: nsPluginInstanceBase()
, m_pNPInstance(pNPInstance)
, m_bInitialized(FALSE)
, m_hWnd(NULL)
{
}

CPlugin::~CPlugin(void)
{
}

NPBool CPlugin::init(NPWindow* pNPWindow)
{

#ifdef _DEBUG
	MessageBoxA(NULL, "插件初始化，等待调试器接入", "调试", 0);
#endif

	m_Window = pNPWindow;
	m_hWnd = (HWND)pNPWindow->window;

	if (m_hWnd == NULL)
		return FALSE;

	// 将窗口子类化，这样就可以对消息进行处理，并在窗口中绘制了
	lpOldProc = (WNDPROC)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LPARAM)(WNDPROC)PluginWinProc);

	// 将窗口与 Plugin 对象关联，这样就可以再窗口处理中访问 Plugin 对象了
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
	// 保存插件窗口指针
	m_Window = pNPWindow;
	return NPERR_NO_ERROR;
}

NPObject * CPlugin::GetScriptableObject()
{
	if (!m_pScriptableObject) {
		m_pScriptableObject = NPN_CreateObject(m_pNPInstance,	GET_NPOBJECT_CLASS(ScriptablePluginObject));
	}

	if (m_pScriptableObject) {
		NPN_RetainObject(m_pScriptableObject);
	}

	return m_pScriptableObject;
}

static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char messag[4096] = {0};
	sprintf_s(messag, 4096, "[npGxxGmPlayer MESSAGE] MSG:%d, WPARAM:%d, LPARAM:%d\n", msg, wParam, lParam);
	OutputDebugStringA(messag);

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
				char *s = "按下键盘任意键，开始播放视频 !";
				DrawTextA(hDC, s, strlen(s), &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}

			EndPaint(hWnd, &ps);
		}
		break;
	//case WM_MOUSEACTIVATE:
	//	{
	//		CPlugin *p = (CPlugin *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	//		// 键盘按下，这里处理键盘消息
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


//////////////////////////////////////////////////////////////////////////
//
// 这里处理与JavaScript交互的部分

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
	if (name == sBar_id) {
		printf ("bar set\n");

		return true;
	}

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
bool
ScriptablePluginObjectBase::_Enumerate(NPObject *npobj,
									   NPIdentifier **identifier,
									   uint32_t *count)
{
	return ((ScriptablePluginObjectBase *)npobj)->Enumerate(identifier, count);
}

// static
bool
ScriptablePluginObjectBase::_Construct(NPObject *npobj, const NPVariant *args,
									   uint32_t argCount, NPVariant *result)
{
	return ((ScriptablePluginObjectBase *)npobj)->Construct(args, argCount,
		result);
}
