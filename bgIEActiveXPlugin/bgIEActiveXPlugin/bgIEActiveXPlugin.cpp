// bgIEActiveXPlugin.cpp : CbgIEActiveXPluginApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "bgIEActiveXPlugin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CbgIEActiveXPluginApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x329B0C84, 0x4B32, 0x4CD0, { 0xAE, 0x19, 0x30, 0xB9, 0x39, 0x88, 0x2C, 0xF6 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CbgIEActiveXPluginApp::InitInstance - DLL 初始化

BOOL CbgIEActiveXPluginApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CbgIEActiveXPluginApp::ExitInstance - DLL 终止

int CbgIEActiveXPluginApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
