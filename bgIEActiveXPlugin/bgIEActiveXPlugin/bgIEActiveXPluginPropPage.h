#pragma once

// bgIEActiveXPluginPropPage.h : CbgIEActiveXPluginPropPage ����ҳ���������


// CbgIEActiveXPluginPropPage : �й�ʵ�ֵ���Ϣ������� bgIEActiveXPluginPropPage.cpp��

class CbgIEActiveXPluginPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CbgIEActiveXPluginPropPage)
	DECLARE_OLECREATE_EX(CbgIEActiveXPluginPropPage)

// ���캯��
public:
	CbgIEActiveXPluginPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_BGIEACTIVEXPLUGIN };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

