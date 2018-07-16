#include "ffmpeg_stub.h"

#include <string>

ffmpeg_stub::ffmpeg_stub()
{
	//
}

ffmpeg_stub::~ffmpeg_stub()
{
	//
}

int ffmpeg_stub::Initialize(const char *root_dir)
{
	char msg[4096] = {0};
	int errCode = 0;

	std::string libavformat_path = root_dir;
	std::string libavcodec_path = root_dir;
	std::string libavfilter_path = root_dir;
	std::string libavdevice_path = root_dir;
	std::string libavutil_path = root_dir;
	std::string libpostproc_path = root_dir;
	std::string libswresample_path = root_dir;
	std::string libswscale_path = root_dir;

	libavformat_path.append("avformat-57.dll");
	libavcodec_path.append("avcodec-57.dll");
	libavfilter_path.append("avfilter-6.dll");
	libavdevice_path.append("avdevice-57.dll");
	libavutil_path.append("avutil-55.dll");
	libpostproc_path.append("postproc-54.dll");
	libswresample_path.append("swresample-2.dll");
	libswscale_path.append("swscale-4.dll");

	// ¸ù¾İ¸ùÄ¿Â¼¼ÓÔØ¿â
	hMod_avformat_ = LoadLibraryA(libavformat_path.c_str());
	if (hMod_avformat_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_avcodec_ = LoadLibraryA(libavcodec_path.c_str());
	if (hMod_avcodec_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_avfilter_ = LoadLibraryA(libavfilter_path.c_str());
	if (hMod_avfilter_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_avdevice_ = LoadLibraryA(libavdevice_path.c_str());
	if (hMod_avdevice_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_avutil_ = LoadLibraryA(libavutil_path.c_str());
	if (hMod_avutil_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_postproc_ = LoadLibraryA(libpostproc_path.c_str());
	if (hMod_postproc_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_swresample_ = LoadLibraryA(libswresample_path.c_str());
	if (hMod_swresample_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_swscale_ = LoadLibraryA(libswscale_path.c_str());
	if (hMod_swscale_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	// ÔØÈëº¯ÊıÖ¸Õë
	ptr_av_register_all = (_av_register_all)GetProcAddress(hMod_avformat_, "av_register_all");
	if (ptr_av_register_all == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_register_all", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_network_init = (_avformat_network_init)GetProcAddress(hMod_avformat_, "avformat_network_init");
	if (ptr_avformat_network_init == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_network_init", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_network_deinit = (_avformat_network_deinit)GetProcAddress(hMod_avformat_, "avformat_network_deinit");
	if (ptr_avformat_network_deinit == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_network_deinit", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_open_input = (_avformat_open_input)GetProcAddress(hMod_avformat_, "avformat_open_input");
	if (ptr_avformat_open_input == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_open_input", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_find_stream_info = (_avformat_find_stream_info)GetProcAddress(hMod_avformat_, "avformat_find_stream_info");
	if (ptr_avformat_open_input == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_find_stream_info", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_register_all = (_avcodec_register_all)GetProcAddress(hMod_avformat_, "avcodec_register_all");
	if (ptr_avcodec_register_all == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_find_decoder", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_find_decoder = (_avcodec_find_decoder)GetProcAddress(hMod_avformat_, "avcodec_find_decoder");
	if (ptr_avformat_open_input == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_find_decoder", errCode);
		OutputDebugStringA(msg);
	}


	return errCode;
}