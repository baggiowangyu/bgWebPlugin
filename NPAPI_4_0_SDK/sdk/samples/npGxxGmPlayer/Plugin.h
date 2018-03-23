#pragma once
#include "pluginbase.h"
#include "npJsInterface.h"


class CPlugin :
	public nsPluginInstanceBase
{
public:
	//CPlugin(void);
	CPlugin(NPP pNPInstance);
	~CPlugin(void);

public:
	NPBool init(NPWindow* pNPWindow);  
	void shut();  
	NPBool isInitialized();

	NPError SetWindow(NPWindow* pNPWindow);

	// 只有Winless插件会使用这个派生函数来处理消息
	// Windowed插件由窗口自己来接收消息，不需要使用本函数
	//uint16_t HandleEvent(void* event);

	NPObject *GetScriptableObject();

public:  
	NPP m_pNPInstance;  
	NPBool m_bInitialized; 

	// 窗口句柄
	NPWindow *m_Window;
	HWND m_hWnd;

	// Javascript交互对象
	NPObject *m_pScriptableObject;
	NPObject *m_pJsCallbackObject;
};

// 这里声明一个全局的插件对象
extern CPlugin *global_plugin_;

// Helper class that can be used to map calls to the NPObject hooks
// into virtual methods on instances of classes that derive from this
// class.
class ScriptablePluginObjectBase : public NPObject
{
public:
	ScriptablePluginObjectBase(NPP npp)
		: mNpp(npp) {}

	virtual ~ScriptablePluginObjectBase() {}

	// Virtual NPObject hooks called through this base class. Override
	// as you see fit.
	virtual void Invalidate();
	virtual bool HasMethod(NPIdentifier name);
	virtual bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool HasProperty(NPIdentifier name);
	virtual bool GetProperty(NPIdentifier name, NPVariant *result);
	virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
	virtual bool RemoveProperty(NPIdentifier name);
	virtual bool Enumerate(NPIdentifier **identifier, uint32_t *count);
	virtual bool Construct(const NPVariant *args, uint32_t argCount, NPVariant *result);

public:
	static void _Deallocate(NPObject *npobj);
	static void _Invalidate(NPObject *npobj);
	static bool _HasMethod(NPObject *npobj, NPIdentifier name);
	static bool _Invoke(NPObject *npobj, NPIdentifier name,	const NPVariant *args, uint32_t argCount, NPVariant *result);
	static bool _InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);
	static bool _HasProperty(NPObject * npobj, NPIdentifier name);
	static bool _GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result);
	static bool _SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value);
	static bool _RemoveProperty(NPObject *npobj, NPIdentifier name);
	static bool _Enumerate(NPObject *npobj, NPIdentifier **identifier, uint32_t *count);
	static bool _Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);

protected:
	NPP mNpp;
};

#define DECLARE_NPOBJECT_CLASS_WITH_BASE(_class, ctor)                        \
	static NPClass s##_class##_NPClass = {                                        \
	NP_CLASS_STRUCT_VERSION_CTOR,                                               \
	ctor,                                                                       \
	ScriptablePluginObjectBase::_Deallocate,                                    \
	ScriptablePluginObjectBase::_Invalidate,                                    \
	ScriptablePluginObjectBase::_HasMethod,                                     \
	ScriptablePluginObjectBase::_Invoke,                                        \
	ScriptablePluginObjectBase::_InvokeDefault,                                 \
	ScriptablePluginObjectBase::_HasProperty,                                   \
	ScriptablePluginObjectBase::_GetProperty,                                   \
	ScriptablePluginObjectBase::_SetProperty,                                   \
	ScriptablePluginObjectBase::_RemoveProperty,                                \
	ScriptablePluginObjectBase::_Enumerate,                                     \
	ScriptablePluginObjectBase::_Construct                                      \
}

#define GET_NPOBJECT_CLASS(_class) &s##_class##_NPClass

class ConstructablePluginObject : public ScriptablePluginObjectBase
{
public:
	ConstructablePluginObject(NPP npp)
		: ScriptablePluginObjectBase(npp) {}

	virtual bool Construct(const NPVariant *args, uint32_t argCount, NPVariant *result);
};


//////////////////////////////////////////////////////////////////////////
//
// 这里定义一个映射结构体
// 初始化时，我们需要将此结构体进行填充

enum _JsFuncType_
{
	JsFuncType_None,
	JsFuncType_Interface,
	JsFuncType_Property
};

// 定义js处理函数
typedef void (__stdcall * _Func_Js)(const NPVariant *args, uint32_t argCount, NPVariant *result);

typedef struct _JS_PARAMS_
{
	int index_;						// 索引，从0开始
	NPIdentifier npId_;				// 接口ID，初始化时通过接口名称计算出来
	const char *interfaceName_;		// 接口名称，这里之前用了NULL，导致出现了一个大坑，就是在初始化std::string的时候用NULL初始化了，导致插件直接崩溃了...真是悲剧
	_Func_Js jsFunc_;				// 接口处理函数
	enum _JsFuncType_ jsFuncType_;	// 
} JsParams;


class ScriptablePluginObject : public ScriptablePluginObjectBase
{
public:
	ScriptablePluginObject(NPP npp);

	virtual bool HasMethod(NPIdentifier name);
	virtual bool HasProperty(NPIdentifier name);
	virtual bool GetProperty(NPIdentifier name, NPVariant *result);
	virtual bool SetProperty(NPIdentifier name, const NPVariant *value);
	virtual bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
	virtual bool InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);
};