#pragma once

// bgIEActiveXPluginCtrl.h : CbgIEActiveXPluginCtrl ActiveX �ؼ����������

#include "MainDialog.h"


// CbgIEActiveXPluginCtrl : �й�ʵ�ֵ���Ϣ������� bgIEActiveXPluginCtrl.cpp��

#define WM_THREADFIREEVENT WM_USER+101

class CbgIEActiveXPluginCtrl : public COleControl
{
	DECLARE_DYNCREATE(CbgIEActiveXPluginCtrl)

// ���캯��
public:
	CbgIEActiveXPluginCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CbgIEActiveXPluginCtrl();

	DECLARE_OLECREATE_EX(CbgIEActiveXPluginCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CbgIEActiveXPluginCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CbgIEActiveXPluginCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CbgIEActiveXPluginCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

public:
	CMainDialog m_cMainDlg;

// ���Ⱥ��¼� ID
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

