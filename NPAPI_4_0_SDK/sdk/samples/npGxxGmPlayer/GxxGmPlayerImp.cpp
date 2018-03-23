#include "GxxGmPlayerImp.h"

GxxGmPlayerImp gxx_gm_player_;


GxxGmPlayerImp::GxxGmPlayerImp()
: player_core_type_(PlayerCore_vlc)
, m_vlcInst(NULL)
, m_vlcMplay(NULL)
, m_vlcMedia(NULL)
{

}

GxxGmPlayerImp::~GxxGmPlayerImp()
{

}

int GxxGmPlayerImp::Initialize(HWND screen_handle, _PlayerCore_ core /* = PlayerCore_vlc */)
{
	int errCode = 0;

	switch (core)
	{
	case PlayerCore_vlc:
		{
			const char* const m_vlcArgs[] = {
				"-I", "dummy",
				"--ignore-config",
			};

			m_vlcInst = libvlc_new(sizeof(m_vlcArgs) / sizeof(m_vlcArgs[0]), m_vlcArgs);
			m_vlcMplay = libvlc_media_player_new(m_vlcInst);
			libvlc_media_player_set_hwnd(m_vlcMplay, screen_handle);
		}
		break;
	case PlayerCore_ffplay:
		errCode = ERROR_NOT_SUPPORTED;
		break;
	case PlayerCore_gxx:
		errCode = ERROR_NOT_SUPPORTED;
		break;
	default:
		break;
	}

	return errCode;
}

void GxxGmPlayerImp::Destroy()
{
	// 先尝试停止播放
	Stop();

	// 按顺序清理掉相应的资源
	//libvlc_media_release(m_vlcMedia);
	libvlc_media_player_release(m_vlcMplay);
	libvlc_release(m_vlcInst);
}

int GxxGmPlayerImp::PlayLocalFile(const char *path)
{
	int errCode = 0;

	switch (player_core_type_)
	{
	case PlayerCore_vlc:
		{
			PlayUrl(path);
		}
		break;
	case PlayerCore_ffplay:
		errCode = ERROR_NOT_SUPPORTED;
		break;
	case PlayerCore_gxx:
		errCode = ERROR_NOT_SUPPORTED;
		break;
	default:
		break;
	}

	return errCode;
}

int GxxGmPlayerImp::PlayUrl(const char *url)
{
	int errCode = 0;

	switch (player_core_type_)
	{
	case PlayerCore_vlc:
		{
			m_vlcMedia = libvlc_media_new_location(m_vlcInst, url);
			libvlc_media_player_set_media (m_vlcMplay, m_vlcMedia);
			libvlc_media_release(m_vlcMedia);
			libvlc_media_player_play(m_vlcMplay);
		}
		break;
	case PlayerCore_ffplay:
		errCode = ERROR_NOT_SUPPORTED;
		break;
	case PlayerCore_gxx:
		errCode = ERROR_NOT_SUPPORTED;
		break;
	default:
		break;
	}

	return errCode;
}

int GxxGmPlayerImp::Stop()
{
	libvlc_media_player_stop(m_vlcMplay);
	return 0;
}