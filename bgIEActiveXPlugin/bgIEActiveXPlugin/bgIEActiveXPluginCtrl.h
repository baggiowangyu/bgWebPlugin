#pragma once

// bgIEActiveXPluginCtrl.h : CbgIEActiveXPluginCtrl ActiveX 控件类的声明。

#include "MainDialog.h"


// CbgIEActiveXPluginCtrl : 有关实现的信息，请参阅 bgIEActiveXPluginCtrl.cpp。

#define WM_THREADFIREEVENT WM_USER+101

class CbgIEActiveXPluginCtrl : public COleControl
{
	DECLARE_DYNCREATE(CbgIEActiveXPluginCtrl)

// 构造函数
public:
	CbgIEActiveXPluginCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CbgIEActiveXPluginCtrl();

	DECLARE_OLECREATE_EX(CbgIEActiveXPluginCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CbgIEActiveXPluginCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CbgIEActiveXPluginCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CbgIEActiveXPluginCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

public:
	CMainDialog m_cMainDlg;

// 调度和事件 ID
public:
	enum {
		eventidcalljs = 1L,
		dispidinvoke = 4L,
		dispidGmInit = 3L,
		dispidGmPlay = 2L,
		dispidGmGetVersion = 1L

	};

public:
	LRESULT OnCtrlCallback(WPARAM wParam, LPARAM lParam);

protected:

	LONG GmGetVersion(void);
	ULONG GmPlay(BSTR url);
	ULONG GmInit(void);
	void invoke(SHORT a);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnSetClientSite();
protected:
	

	void calljs(SHORT ret)
	{
		FireEvent(eventidcalljs, EVENT_PARAM(VTS_I2), ret);
	}
};

