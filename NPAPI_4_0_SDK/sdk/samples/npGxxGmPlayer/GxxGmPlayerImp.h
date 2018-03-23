#ifndef _GxxGmPlayerImp_H_
#define _GxxGmPlayerImp_H_

#include "vlc/vlc.h"
#include <Windows.h>

enum _PlayerCore_
{
	PlayerCore_vlc,			// VLC 解码渲染播放核心
	PlayerCore_ffplay,		// ffmpeg + SDL2 解码渲染播放核心
	PlayerCore_gxx			// 高新兴 解码渲染播放核心
};

class GxxGmPlayerImp
{
public:
	GxxGmPlayerImp();
	~GxxGmPlayerImp();

public:
	int Initialize(HWND screen_handle, _PlayerCore_ core = PlayerCore_vlc);
	void Destroy();

public:
	int PlayLocalFile(const char *path);
	int PlayUrl(const char *url);

	int Stop();

public:
	enum _PlayerCore_ player_core_type_;

public:
	libvlc_instance_t		*m_vlcInst;
	libvlc_media_player_t	*m_vlcMplay;
	libvlc_media_t			*m_vlcMedia;
};

extern GxxGmPlayerImp gxx_gm_player_;

#endif//GxxGmPlayerImp
