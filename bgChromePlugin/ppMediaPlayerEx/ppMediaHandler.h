#ifndef _ppMediaHandler_H_
#define _ppMediaHandler_H_

struct AVFormatContext;
struct AVStream;
struct AVCodecContext;
struct AVCodec;

class ffmpeg_stub;

class ppMediaHandler
{
public:
	ppMediaHandler(ffmpeg_stub *stub);
	~ppMediaHandler();

public:
	int Demuxing(const char *url);

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
};

#endif//_ppMediaHandler_H_
