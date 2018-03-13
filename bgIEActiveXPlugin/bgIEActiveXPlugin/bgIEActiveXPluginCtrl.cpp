// bgIEActiveXPluginCtrl.cpp : CbgIEActiveXPluginCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "bgIEActiveXPlugin.h"
#include "bgIEActiveXPluginCtrl.h"
#include "bgIEActiveXPluginPropPage.h"
#include <process.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CbgIEActiveXPluginCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CbgIEActiveXPluginCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_THREADFIREEVENT, OnCtrlCallback)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CbgIEActiveXPluginCtrl, COleControl)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "GmGetVersion", dispidGmGetVersion, GmGetVersion, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "GmPlay", dispidGmPlay, GmPlay, VT_UI4, VTS_BSTR)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "GmInit", dispidGmInit, GmInit, VT_UI4, VTS_NONE)
	DISP_FUNCTION_ID(CbgIEActiveXPluginCtrl, "invoke", dispidinvoke, invoke, VT_EMPTY, VTS_I2)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CbgIEActiveXPluginCtrl, COleControl)
	EVENT_CUSTOM_ID("calljs", eventidcalljs, calljs, VTS_I2)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CbgIEActiveXPluginCtrl, 1)
	PROPPAGEID(CbgIEActiveXPluginPropPage::guid)
END_PROPPAGEIDS(CbgIEActiveXPluginCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CbgIEActiveXPluginCtrl, "BGIEACTIVEXPLUGI.bgIEActiveXPlugiCtrl.1",
	0xe5496c7e, 0x61e7, 0x4f0b, 0x96, 0x49, 0x9b, 0x18, 0x35, 0x4c, 0xfb, 0x67)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CbgIEActiveXPluginCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_DbgIEActiveXPlugin =
		{ 0x41C9269F, 0x5608, 0x45C2, { 0xA1, 0xCD, 0xAB, 0x4F, 0x62, 0x8, 0x65, 0x25 } };
const IID BASED_CODE IID_DbgIEActiveXPluginEvents =
		{ 0x2F4791F4, 0x29AA, 0x46F4, { 0xA2, 0x9A, 0x98, 0x45, 0xF2, 0xEA, 0xD4, 0x3D } };



// 控件类型信息

static const DWORD BASED_CODE _dwbgIEActiveXPluginOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CbgIEActiveXPluginCtrl, IDS_BGIEACTIVEXPLUGIN, _dwbgIEActiveXPluginOleMisc)



// CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrlFactory::UpdateRegistry -
// 添加或移除 CbgIEActiveXPluginCtrl 的系统注册表项

BOOL CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

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



// CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrl - 构造函数

CbgIEActiveXPluginCtrl::CbgIEActiveXPluginCtrl()
{
	InitializeIIDs(&IID_DbgIEActiveXPlugin, &IID_DbgIEActiveXPluginEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CbgIEActiveXPluginCtrl::~CbgIEActiveXPluginCtrl - 析构函数

CbgIEActiveXPluginCtrl::~CbgIEActiveXPluginCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CbgIEActiveXPluginCtrl::OnDraw - 绘图函数

void CbgIEActiveXPluginCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CbgIEActiveXPluginCtrl::DoPropExchange - 持久性支持

void CbgIEActiveXPluginCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CbgIEActiveXPluginCtrl::OnResetState - 将控件重置为默认状态

void CbgIEActiveXPluginCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CbgIEActiveXPluginCtrl::AboutBox - 向用户显示“关于”框

void CbgIEActiveXPluginCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_BGIEACTIVEXPLUGIN);
	dlgAbout.DoModal();
}



// CbgIEActiveXPluginCtrl 消息处理程序

LONG CbgIEActiveXPluginCtrl::GmGetVersion(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	TRACE("CbgIEActiveXPluginCtrl::GmGetVersion()\n");
	::PostMessage(this->m_hWnd, WM_THREADFIREEVENT, (WPARAM)NULL, (LPARAM)NULL);

	return 999;
}

ULONG CbgIEActiveXPluginCtrl::GmPlay(BSTR url)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_cMainDlg.Play(url);

	return 0;
}

ULONG CbgIEActiveXPluginCtrl::GmInit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	//m_cMainDlg.DoModal();

	return 0;
}

int CbgIEActiveXPluginCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_cMainDlg.Create(IDD_MAIN_DIALOG, this);

	return 0;
}

void CbgIEActiveXPluginCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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

	// TODO: 在此添加调度处理程序代码
	_beginthread(f, 0, (void*)this);
}
