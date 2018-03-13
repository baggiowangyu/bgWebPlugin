#pragma once

// bgIEActiveXPluginPropPage.h : CbgIEActiveXPluginPropPage 属性页类的声明。


// CbgIEActiveXPluginPropPage : 有关实现的信息，请参阅 bgIEActiveXPluginPropPage.cpp。

class CbgIEActiveXPluginPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CbgIEActiveXPluginPropPage)
	DECLARE_OLECREATE_EX(CbgIEActiveXPluginPropPage)

// 构造函数
public:
	CbgIEActiveXPluginPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_BGIEACTIVEXPLUGIN };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

