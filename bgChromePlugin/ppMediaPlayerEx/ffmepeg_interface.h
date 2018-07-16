#ifndef _ffmepeg_interface_H_
#define _ffmepeg_interface_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////
// avformat.h
typedef void (__stdcall * _av_register_all)(void);
typedef int (__stdcall * _avformat_network_init)(void);
typedef int (__stdcall * _avformat_network_deinit)(void);
typedef int (__stdcall * _avformat_open_input)(AVFormatContext **ps, const char *url, AVInputFormat *fmt, AVDictionary **options);
typedef int (__stdcall * _avformat_find_stream_info)(AVFormatContext *ic, AVDictionary **options);

//////////////////////////////////////////////////////////////////////////
// avcodec.h
typedef void (__stdcall * _avcodec_register_all)(void);
typedef AVCodec* (__stdcall * _avcodec_find_decoder)(enum AVCodecID id);
typedef AVCodecContext* (__stdcall * _avcodec_alloc_context3)(const AVCodec *codec);
typedef int (__stdcall * _avcodec_close)(AVCodecContext *avctx);
typedef void (__stdcall * _avcodec_free_context)(AVCodecContext **avctx);
typedef int (__stdcall * _avcodec_open2)(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);

#endif//_ffmepeg_interface_H_
