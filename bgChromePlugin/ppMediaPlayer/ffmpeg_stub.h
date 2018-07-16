#ifndef _ffmpeg_stub_H_
#define _ffmpeg_stub_H_

#include <Windows.h>
#include "ffmepeg_interface.h"

class ffmpeg_stub
{
public:
	ffmpeg_stub();
	~ffmpeg_stub();

public:
	int Initialize(const char *root_dir);

public:
	_av_register_all ptr_av_register_all;
	_avformat_network_init ptr_avformat_network_init;
	_avformat_network_deinit ptr_avformat_network_deinit;
	_avformat_open_input ptr_avformat_open_input;
	_avformat_find_stream_info ptr_avformat_find_stream_info;

	_avcodec_register_all ptr_avcodec_register_all;
	_avcodec_find_decoder ptr_avcodec_find_decoder;

private:
	HMODULE hMod_avformat_;
	HMODULE hMod_avcodec_;
	HMODULE hMod_avfilter_;
	HMODULE hMod_avutil_;
	HMODULE hMod_avdevice_;
	HMODULE hMod_postproc_;
	HMODULE hMod_swresample_;
	HMODULE hMod_swscale_;
};
#endif//_ffmpeg_stub_H_
