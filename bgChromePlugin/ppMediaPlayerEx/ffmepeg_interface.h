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
typedef void ( * _av_register_all)(void);
typedef int ( * _avformat_network_init)(void);
typedef int ( * _avformat_network_deinit)(void);
typedef int ( * _avformat_open_input)(AVFormatContext **ps, const char *url, AVInputFormat *fmt, AVDictionary **options);
typedef int ( * _avformat_find_stream_info)(AVFormatContext *ic, AVDictionary **options);
typedef void ( * _avformat_close_input)(AVFormatContext **s);
typedef int ( * _avformat_flush)(AVFormatContext *s);
typedef int ( * _av_read_play)(AVFormatContext *s);
typedef int ( * _av_read_pause)(AVFormatContext *s);
typedef int ( * _avformat_write_header)(AVFormatContext *s, AVDictionary **options);
typedef int ( * _avformat_init_output)(AVFormatContext *s, AVDictionary **options);
typedef int ( * _av_write_frame)(AVFormatContext *s, AVPacket *pkt);
typedef int ( * _av_interleaved_write_frame)(AVFormatContext *s, AVPacket *pkt);
typedef int ( * _av_write_uncoded_frame)(AVFormatContext *s, int stream_index, AVFrame *frame);
typedef int ( * _av_interleaved_write_uncoded_frame)(AVFormatContext *s, int stream_index, AVFrame *frame);
typedef int ( * _av_write_uncoded_frame_query)(AVFormatContext *s, int stream_index);
typedef int ( * _av_write_trailer)(AVFormatContext *s);
typedef AVOutputFormat* ( * _av_guess_format)(const char *short_name, const char *filename, const char *mime_type);
typedef enum AVCodecID ( * _av_guess_codec)(AVOutputFormat *fmt, const char *short_name, const char *filename, const char *mime_type, enum AVMediaType type);
typedef int ( * _av_read_frame)(AVFormatContext *s, AVPacket *pkt);
typedef AVPacket* ( * _av_packet_alloc)(void);
typedef int ( * _av_seek_frame)(AVFormatContext *s, int stream_index, int64_t timestamp, int flags);
typedef int ( * _avformat_seek_file)(AVFormatContext *s, int stream_index, int64_t min_ts, int64_t ts, int64_t max_ts, int flags);

//////////////////////////////////////////////////////////////////////////
// avcodec.h
typedef void ( * _avcodec_register_all)(void);
typedef AVCodec* ( * _avcodec_find_decoder)(enum AVCodecID id);
typedef AVCodecContext* ( * _avcodec_alloc_context3)(const AVCodec *codec);
typedef int ( * _avcodec_close)(AVCodecContext *avctx);
typedef void ( * _avcodec_free_context)(AVCodecContext **avctx);
typedef int ( * _avcodec_open2)(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
typedef int ( * _avcodec_decode_video2)(AVCodecContext *avctx, AVFrame *picture, int *got_picture_ptr, const AVPacket *avpkt);
typedef int ( * _avcodec_decode_audio4)(AVCodecContext *avctx, AVFrame *frame, int *got_frame_ptr, const AVPacket *avpkt);
typedef int ( * _avcodec_decode_subtitle2)(AVCodecContext *avctx, AVSubtitle *sub, int *got_sub_ptr, AVPacket *avpkt);
typedef int ( * _avcodec_send_packet)(AVCodecContext *avctx, const AVPacket *avpkt);
typedef int ( * _avcodec_receive_frame)(AVCodecContext *avctx, AVFrame *frame);
typedef int ( * _avcodec_send_frame)(AVCodecContext *avctx, const AVFrame *frame);
typedef int ( * _avcodec_receive_packet)(AVCodecContext *avctx, AVPacket *avpkt);
typedef int ( * _avcodec_copy_context)(AVCodecContext *dest, const AVCodecContext *src);

//////////////////////////////////////////////////////////////////////////
// frame.h
typedef AVFrame* ( * _av_frame_alloc)(void);
typedef void ( * _av_frame_free)(AVFrame **frame);

#endif//_ffmepeg_interface_H_
