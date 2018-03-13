#pragma once
#include "afxwin.h"
#include "vlc\vlc.h"


// CMainDialog �Ի���

class CMainDialog : public CDialog
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDialog();

// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
