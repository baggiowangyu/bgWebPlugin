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
	// ÕâÀï¼ÓÔØË³Ğò»¹ÓĞ½²¾¿£¬²»È»»á¼ÓÔØÊ§°Ü
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

	hMod_avcodec_ = LoadLibraryA(libavcodec_path.c_str());
	if (hMod_avcodec_ == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "¼ÓÔØ %s Ê§°Ü£¡´íÎóÂë£º%d\n", libavformat_path.c_str(), errCode);
		OutputDebugStringA(msg);
	}

	hMod_avformat_ = LoadLibraryA(libavformat_path.c_str());
	if (hMod_avformat_ == nullptr)
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

	// ÔØÈëº¯ÊıÖ¸Õë
	//////////////////////////////////////////////////////////////////////////
	// avformat
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
	if (ptr_avformat_find_stream_info == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_find_stream_info", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_close_input = (_avformat_close_input)GetProcAddress(hMod_avformat_, "avformat_close_input");
	if (ptr_avformat_close_input == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_close_input", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_flush = (_avformat_flush)GetProcAddress(hMod_avformat_, "avformat_flush");
	if (ptr_avformat_flush == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_flush", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_read_play = (_av_read_play)GetProcAddress(hMod_avformat_, "av_read_play");
	if (ptr_av_read_play == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_read_play", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_read_pause = (_av_read_pause)GetProcAddress(hMod_avformat_, "av_read_pause");
	if (ptr_av_read_pause == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_read_pause", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_write_header = (_avformat_write_header)GetProcAddress(hMod_avformat_, "avformat_write_header");
	if (ptr_avformat_write_header == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_find_stream_info", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_init_output = (_avformat_init_output)GetProcAddress(hMod_avformat_, "avformat_init_output");
	if (ptr_avformat_init_output == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_init_output", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_write_frame = (_av_write_frame)GetProcAddress(hMod_avformat_, "av_write_frame");
	if (ptr_av_write_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_write_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_interleaved_write_frame = (_av_interleaved_write_frame)GetProcAddress(hMod_avformat_, "av_interleaved_write_frame");
	if (ptr_av_interleaved_write_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_interleaved_write_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_write_uncoded_frame = (_av_write_uncoded_frame)GetProcAddress(hMod_avformat_, "av_write_uncoded_frame");
	if (ptr_av_write_uncoded_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_write_uncoded_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_interleaved_write_uncoded_frame = (_av_interleaved_write_uncoded_frame)GetProcAddress(hMod_avformat_, "av_interleaved_write_uncoded_frame");
	if (ptr_av_interleaved_write_uncoded_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_interleaved_write_uncoded_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_write_uncoded_frame_query = (_av_write_uncoded_frame_query)GetProcAddress(hMod_avformat_, "av_write_uncoded_frame_query");
	if (ptr_av_write_uncoded_frame_query == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_write_uncoded_frame_query", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_write_trailer = (_av_write_trailer)GetProcAddress(hMod_avformat_, "av_write_trailer");
	if (ptr_av_write_trailer == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_write_trailer", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_guess_format = (_av_guess_format)GetProcAddress(hMod_avformat_, "av_guess_format");
	if (ptr_av_guess_format == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_guess_format", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_guess_codec = (_av_guess_codec)GetProcAddress(hMod_avformat_, "av_guess_codec");
	if (ptr_av_guess_codec == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_guess_codec", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_read_frame = (_av_read_frame)GetProcAddress(hMod_avformat_, "av_read_frame");
	if (ptr_av_read_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_read_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_packet_alloc = (_av_packet_alloc)GetProcAddress(hMod_avformat_, "av_packet_alloc");
	if (ptr_av_packet_alloc == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_packet_alloc", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_seek_frame = (_av_seek_frame)GetProcAddress(hMod_avformat_, "av_seek_frame");
	if (ptr_av_seek_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_seek_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avformat_seek_file = (_avformat_seek_file)GetProcAddress(hMod_avformat_, "avformat_seek_file");
	if (ptr_avformat_seek_file == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avformat_seek_file", errCode);
		OutputDebugStringA(msg);
	}

	//////////////////////////////////////////////////////////////////////////
	// avcodec
	ptr_avcodec_register_all = (_avcodec_register_all)GetProcAddress(hMod_avcodec_, "avcodec_register_all");
	if (ptr_avcodec_register_all == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_find_decoder", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_find_decoder = (_avcodec_find_decoder)GetProcAddress(hMod_avcodec_, "avcodec_find_decoder");
	if (ptr_avformat_open_input == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_find_decoder", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_alloc_context3 = (_avcodec_alloc_context3)GetProcAddress(hMod_avcodec_, "avcodec_alloc_context3");
	if (ptr_avcodec_alloc_context3 == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_alloc_context3", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_close = (_avcodec_close)GetProcAddress(hMod_avcodec_, "avcodec_close");
	if (ptr_avcodec_close == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_close", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_free_context = (_avcodec_free_context)GetProcAddress(hMod_avcodec_, "avcodec_free_context");
	if (ptr_avcodec_free_context == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_free_context", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_open2 = (_avcodec_open2)GetProcAddress(hMod_avcodec_, "avcodec_open2");
	if (ptr_avcodec_open2 == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_open2", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_decode_video2 = (_avcodec_decode_video2)GetProcAddress(hMod_avcodec_, "avcodec_decode_video2");
	if (ptr_avcodec_decode_video2 == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_decode_video2", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_decode_audio4 = (_avcodec_decode_audio4)GetProcAddress(hMod_avcodec_, "avcodec_decode_audio4");
	if (ptr_avcodec_decode_audio4 == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_decode_audio4", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_decode_subtitle2 = (_avcodec_decode_subtitle2)GetProcAddress(hMod_avcodec_, "avcodec_decode_subtitle2");
	if (ptr_avcodec_decode_subtitle2 == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_decode_subtitle2", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_send_packet = (_avcodec_send_packet)GetProcAddress(hMod_avcodec_, "avcodec_send_packet");
	if (ptr_avcodec_send_packet == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_send_packet", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_receive_frame = (_avcodec_receive_frame)GetProcAddress(hMod_avcodec_, "avcodec_receive_frame");
	if (ptr_avcodec_receive_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_receive_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_send_frame = (_avcodec_send_frame)GetProcAddress(hMod_avcodec_, "avcodec_send_frame");
	if (ptr_avcodec_send_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_send_frame", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_receive_packet = (_avcodec_receive_packet)GetProcAddress(hMod_avcodec_, "avcodec_receive_packet");
	if (ptr_avcodec_receive_packet == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_find_decoder", errCode);
		OutputDebugStringA(msg);
	}

	ptr_avcodec_copy_context = (_avcodec_copy_context)GetProcAddress(hMod_avcodec_, "avcodec_copy_context");
	if (ptr_avcodec_copy_context == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "avcodec_copy_context", errCode);
		OutputDebugStringA(msg);
	}

	//////////////////////////////////////////////////////////////////////////
	// avutil
	ptr_av_frame_alloc = (_av_frame_alloc)GetProcAddress(hMod_avutil_, "av_frame_alloc");
	if (ptr_avcodec_send_frame == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_frame_alloc", errCode);
		OutputDebugStringA(msg);
	}

	ptr_av_frame_free = (_av_frame_free)GetProcAddress(hMod_avutil_, "av_frame_free");
	if (ptr_avcodec_receive_packet == nullptr)
	{
		errCode = GetLastError();
		sprintf_s(msg, 4096, "ÔØÈëº¯Êı %s Ê§°Ü£¡´íÎóÂë£º%d\n", "av_frame_free", errCode);
		OutputDebugStringA(msg);
	}

	// Ö±½Óµ÷ÓÃ³õÊ¼»¯ÁË
	ptr_av_register_all();
	ptr_avformat_network_init();
	ptr_avcodec_register_all();

	return errCode;
}