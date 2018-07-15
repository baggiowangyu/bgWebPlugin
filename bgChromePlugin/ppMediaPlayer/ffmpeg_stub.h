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
	_avformat_open_input ptr_avformat_open_input;

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
