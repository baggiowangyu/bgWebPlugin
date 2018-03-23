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

	// ֻ��Winless�����ʹ���������������������Ϣ
	// Windowed����ɴ����Լ���������Ϣ������Ҫʹ�ñ�����
	//uint16_t HandleEvent(void* event);

	NPObject *GetScriptableObject();

public:  
	NPP m_pNPInstance;  
	NPBool m_bInitialized; 

	// ���ھ��
	NPWindow *m_Window;
	HWND m_hWnd;

	// Javascript��������
	NPObject *m_pScriptableObject;
	NPObject *m_pJsCallbackObject;
};

// ��������һ��ȫ�ֵĲ������
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
// ���ﶨ��һ��ӳ��ṹ��
// ��ʼ��ʱ��������Ҫ���˽ṹ��������

enum _JsFuncType_
{
	JsFuncType_None,
	JsFuncType_Interface,
	JsFuncType_Property
};

// ����js������
typedef void (__stdcall * _Func_Js)(const NPVariant *args, uint32_t argCount, NPVariant *result);

typedef struct _JS_PARAMS_
{
	int index_;						// ��������0��ʼ
	NPIdentifier npId_;				// �ӿ�ID����ʼ��ʱͨ���ӿ����Ƽ������
	const char *interfaceName_;		// �ӿ����ƣ�����֮ǰ����NULL�����³�����һ����ӣ������ڳ�ʼ��std::string��ʱ����NULL��ʼ���ˣ����²��ֱ�ӱ�����...���Ǳ���
	_Func_Js jsFunc_;				// �ӿڴ�����
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