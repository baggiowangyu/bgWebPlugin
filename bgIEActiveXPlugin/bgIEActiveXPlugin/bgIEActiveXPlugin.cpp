// bgIEActiveXPlugin.cpp : CbgIEActiveXPluginApp �� DLL ע���ʵ�֡�

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



// CbgIEActiveXPluginApp::InitInstance - DLL ��ʼ��

BOOL CbgIEActiveXPluginApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CbgIEActiveXPluginApp::ExitInstance - DLL ��ֹ

int CbgIEActiveXPluginApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
