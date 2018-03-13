// bgIEActiveXPluginCtrl.cpp : CbgIEActiveXPluginCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "bgIEActiveXPlugin.h"
#include "bgIEActiveXPluginCtrl.h"
#include "bgIEActiveXPluginPropPage.h"
#include <process.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CbgIEActiveXPluginCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CbgIEActiveXPluginCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_THREADFIREEVENT, OnCtrlCallback)
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CbgIEActiveXPluginCtrl, COleControl)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "GmGetVersion", dispidGmGetVersion, GmGetVersion, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "GmPlay", dispidGmPlay, GmPlay, VT_UI4, VTS_BSTR)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "GmInit", dispidGmInit, GmInit, VT_UI4, VTS_NONE)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "invoke", dispidinvoke, invoke, VT_EMPTY, VTS_I2)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CbgIEActiveXPluginCtrl, COleControl)
	EVENT_CUSTOM_ID("calljs", eventidcalljs, calljs, VTS_I2)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CbgIEActiveXPluginCtrl, 1)
	PROPPAGEID(CbgIEActiveXPluginPropPage::guid)
END_PROPPAGEIDS(CbgIEActiveXPluginCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CbgIEActiveXPluginCtrl, "BGIEACTIVEXPLUGI.bgIEActiveXPlugiCtrl.1",
	0xe5496c7e, 0x61e7, 0x4f0b, 0x96, 0x49, 0x9b, 0x18, 0x35, 0x4c, 0xfb, 0x67)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CbgIEActiveXPluginCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DbgIEActiveXPlugin =
		{ 0x41C9269F, 0x5608, 0x45C2, { 0xA1, 0xCD, 0xAB, 0x4F, 0x62, 0x8, 0x65, 0x25 } };
const IID BASED_CODE IID_DbgIEActiveXPluginEvents =
		{ 0x2F4791F4, 0x29AA, 0x46F4, { 0xA2, 0x9A, 0x98, 0x45, 0xF2, 0xEA, 0xD4, 0x3D } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwbgIEActiveXPluginOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CbgIEActiveXPluginCtrl, IDS_BGIEACTIVEXPLUGIN, _dwbgIEActiveXPluginOleMisc)



// CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CbgIEActiveXPluginCtrl ��ϵͳע�����

BOOL CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_BGIEACTIVEXPLUGIN,
			IDB_BGIEACTIVEXPLUGIN,
			afxRegApartmentThreading,
			_dwbgIEActiveXPluginOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrl - ���캯��

CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrl()
{
	InitializeIIDs(&IID_DbgIEActiveXPlugin, &IID_DbgIEActiveXPluginEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CbgIEActiveXPluginCtrl::~CbgIEActiveXPluginCtrl - ��������

CbgIEActiveXPluginCtrl::~CbgIEActiveXPluginCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CbgIEActiveXPluginCtrl::OnDraw - ��ͼ����

void CbgIEActiveXPluginCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CbgIEActiveXPluginCtrl::DoPropExchange - �־���֧��

void CbgIEActiveXPluginCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CbgIEActiveXPluginCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CbgIEActiveXPluginCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CbgIEActiveXPluginCtrl::AboutBox - ���û���ʾ�����ڡ���

void CbgIEActiveXPluginCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_BGIEACTIVEXPLUGIN);
	dlgAbout.DoModal();
}



// CbgIEActiveXPluginCtrl ��Ϣ�������

LONG CbgIEActiveXPluginCtrl::GmGetVersion(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	TRACE("CbgIEActiveXPluginCtrl::GmGetVersion()\n");
	::PostMessage(this->m_hWnd, WM_THREADFIREEVENT, (WPARAM)NULL, (LPARAM)NULL);

	return 999;
}

ULONG CbgIEActiveXPluginCtrl::GmPlay(BSTR url)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	m_cMainDlg.Play(url);

	return 0;
}

ULONG CbgIEActiveXPluginCtrl::GmInit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	//m_cMainDlg.DoModal();

	return 0;
}

int CbgIEActiveXPluginCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_cMainDlg.Create(IDD_MAIN_DIALOG, this);

	return 0;
}

void CbgIEActiveXPluginCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	RECT activex_rect;
	GetClientRect(&activex_rect);
	m_cMainDlg.MoveWindow(&activex_rect);
}

LRESULT CbgIEActiveXPluginCtrl::OnCtrlCallback(WPARAM wParam, LPARAM lParam)
{
	this->calljs(100);
	return TRUE;
}

void CbgIEActiveXPluginCtrl::OnSetClientSite()
{
	COleControl::OnSetClientSite();
}

void f(void *r)
{
	CbgIEActiveXPluginCtrl *ctrl = (CbgIEActiveXPluginCtrl *)r;
	Sleep(5000);
	PostMessage(ctrl->m_hWnd, WM_THREADFIREEVENT, (WPARAM)NULL, (LPARAM)NULL);

	return ;
}

void CbgIEActiveXPluginCtrl::invoke(SHORT a)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	_beginthread(f, 0, (void*)this);
}
