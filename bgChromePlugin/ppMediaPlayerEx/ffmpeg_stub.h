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
	// avformat.h
	_av_register_all ptr_av_register_all;
	_avformat_network_init ptr_avformat_network_init;
	_avformat_network_deinit ptr_avformat_network_deinit;
	_avformat_open_input ptr_avformat_open_input;
	_avformat_find_stream_info ptr_avformat_find_stream_info;
	_avformat_close_input ptr_avformat_close_input;
	_avformat_flush ptr_avformat_flush;
	_av_read_play ptr_av_read_play;
	_av_read_pause ptr_av_read_pause;
	_avformat_write_header ptr_avformat_write_header;
	_avformat_init_output ptr_avformat_init_output;
	_av_write_frame ptr_av_write_frame;
	_av_interleaved_write_frame ptr_av_interleaved_write_frame;
	_av_write_uncoded_frame ptr_av_write_uncoded_frame;
	_av_interleaved_write_uncoded_frame ptr_av_interleaved_write_uncoded_frame;
	_av_write_uncoded_frame_query ptr_av_write_uncoded_frame_query;
	_av_write_trailer ptr_av_write_trailer;
	_av_guess_format ptr_av_guess_format;
	_av_guess_codec ptr_av_guess_codec;
	_av_read_frame ptr_av_read_frame;
	_av_packet_alloc ptr_av_packet_alloc;
	_av_seek_frame ptr_av_seek_frame;
	_avformat_seek_file ptr_avformat_seek_file;

	// avcodec.h
	_avcodec_register_all ptr_avcodec_register_all;
	_avcodec_find_decoder ptr_avcodec_find_decoder;
	_avcodec_alloc_context3 ptr_avcodec_alloc_context3;
	_avcodec_close ptr_avcodec_close;
	_avcodec_free_context ptr_avcodec_free_context;
	_avcodec_open2 ptr_avcodec_open2;
	_avcodec_decode_video2 ptr_avcodec_decode_video2;
	_avcodec_decode_audio4 ptr_avcodec_decode_audio4;
	_avcodec_decode_subtitle2 ptr_avcodec_decode_subtitle2;
	_avcodec_send_packet ptr_avcodec_send_packet;
	_avcodec_receive_frame ptr_avcodec_receive_frame;
	_avcodec_send_frame ptr_avcodec_send_frame;
	_avcodec_receive_packet ptr_avcodec_receive_packet;
	_avcodec_copy_context ptr_avcodec_copy_context;

	// frame.h
	_av_frame_alloc ptr_av_frame_alloc;
	_av_frame_free ptr_av_frame_free;

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
