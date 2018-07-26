#ifndef _ppMediaHandler_H_
#define _ppMediaHandler_H_

struct AVFormatContext;
struct AVStream;
struct AVCodecContext;
struct AVCodec;
struct AVRational;

class ffmpeg_stub;

class ppMediaHandler
{
public:
	ppMediaHandler(ffmpeg_stub *stub);
	~ppMediaHandler();

public:
	int Demuxing(const char *url);
	int Decode();

public:
	ffmpeg_stub *stub_;
public:
	AVFormatContext *input_fmtctx_;
	int video_index_;
	int audio_index_;
	AVStream *video_stream_;
	AVStream *audio_stream_;
	AVCodecContext *video_codec_ctx_;
	AVCodecContext *audio_codec_ctx_;
	AVCodec *video_codec_;
	AVCodec *audio_codec_;

public:
	// 解复用后的数据
	float video_framerate_;
	__int64 video_bitrate_;
	int video_width_;
	int video_height_;
	AVRational *video_time_base_;

	int audio_samplerate_;
	int audio_channels_;
	__int64 audio_bitrate_;

};

#endif//_ppMediaHandler_H_
