// bgIEActiveXPluginPropPage.cpp : CbgIEActiveXPluginPropPage 属性页类的实现。

#include "stdafx.h"
#include "bgIEActiveXPlugin.h"
#include "bgIEActiveXPluginPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CbgIEActiveXPluginPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CbgIEActiveXPluginPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CbgIEActiveXPluginPropPage, "BGIEACTIVEXPLU.bgIEActiveXPluPropPage.1",
	0x3b109208, 0x6adc, 0x4a47, 0xb5, 0xd, 0xcd, 0xc3, 0xf4, 0xc8, 0x2d, 0xe9)



// CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPageFactory::UpdateRegistry -
// 添加或移除 CbgIEActiveXPluginPropPage 的系统注册表项

BOOL CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_BGIEACTIVEXPLUGIN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPage - 构造函数

CbgIEActiveXPluginPropPage::CbgIEActiveXPluginPropPage() :
	COlePropertyPage(IDD, IDS_BGIEACTIVEXPLUGIN_PPG_CAPTION)
{
}



// CbgIEActiveXPluginPropPage::DoDataExchange - 在页和属性间移动数据

void CbgIEActiveXPluginPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CbgIEActiveXPluginPropPage 消息处理程序
