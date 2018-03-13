// MainDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "bgIEActiveXPlugin.h"
#include "MainDialog.h"


// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialog)

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDialog::IDD, pParent)
{

}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PLAYER, m_cPlayer);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMainDialog 消息处理程序
BOOL CMainDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	

	return TRUE;
}

void CMainDialog::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if(m_vlcMplay)
	{
		libvlc_media_player_release(m_vlcMplay);
		m_vlcMplay = NULL;
	}

	if(m_vlcInst)
	{
		libvlc_release(m_vlcInst);
		m_vlcInst = NULL;
	}
}

void CMainDialog::Play(WCHAR *url)
{
	const char* const m_vlcArgs[] = {
		"-I", "dummy",
		"--ignore-config",
	};

	m_vlcInst = libvlc_new(sizeof(m_vlcArgs) / sizeof(m_vlcArgs[0]), m_vlcArgs);

	USES_CONVERSION;
	m_vlcMedia = libvlc_media_new_location(m_vlcInst, W2A(url));
	m_vlcMplay = libvlc_media_player_new (m_vlcInst);
	libvlc_media_player_set_media (m_vlcMplay, m_vlcMedia);
	libvlc_media_release(m_vlcMedia);
	libvlc_media_player_set_hwnd(m_vlcMplay, m_cPlayer.GetSafeHwnd());
	libvlc_media_player_play(m_vlcMplay);
}

