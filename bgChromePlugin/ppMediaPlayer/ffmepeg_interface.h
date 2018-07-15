#ifndef _ffmepeg_interface_H_
#define _ffmepeg_interface_H_

//////////////////////////////////////////////////////////////////////////
// avformat.h
typedef int (__stdcall * _avformat_open_input)(AVFormatContext **ps, const char *url, AVInputFormat *fmt, AVDictionary **options);
typedef int (__stdcall * _avformat_find_stream_info)(AVFormatContext *ic, AVDictionary **options);

//////////////////////////////////////////////////////////////////////////
// avcodec.h
typedef AVCodec* (__stdcall * _avcodec_find_decoder)(enum AVCodecID id);

#endif//_ffmepeg_interface_H_
