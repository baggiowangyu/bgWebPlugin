// bgIEActiveXPluginPropPage.cpp : CbgIEActiveXPluginPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "bgIEActiveXPlugin.h"
#include "bgIEActiveXPluginPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CbgIEActiveXPluginPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CbgIEActiveXPluginPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CbgIEActiveXPluginPropPage, "BGIEACTIVEXPLU.bgIEActiveXPluPropPage.1",
	0x3b109208, 0x6adc, 0x4a47, 0xb5, 0xd, 0xcd, 0xc3, 0xf4, 0xc8, 0x2d, 0xe9)



// CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CbgIEActiveXPluginPropPage ��ϵͳע�����

BOOL CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_BGIEACTIVEXPLUGIN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPage - ���캯��

CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPage() :
	COlePropertyPage(IDD, IDS_BGIEACTIVEXPLUGIN_PPG_CAPTION)
{
}



// CbgIEActiveXPluginPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CbgIEActiveXPluginPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CbgIEActiveXPluginPropPage ��Ϣ�������
