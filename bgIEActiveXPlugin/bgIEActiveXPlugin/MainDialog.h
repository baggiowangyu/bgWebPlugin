#pragma once
#include "afxwin.h"
#include "vlc\vlc.h"


// CMainDialog 对话框

class CMainDialog : public CDialog
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDialog();

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cPlayer;

private:
	libvlc_instance_t*	m_vlcInst;
	libvlc_media_player_t*	m_vlcMplay;
	libvlc_media_t*	m_vlcMedia;

public:
	void Play(WCHAR *url);
	afx_msg void OnDestroy();
};
