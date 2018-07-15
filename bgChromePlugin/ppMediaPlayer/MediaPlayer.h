#ifndef _MediaPlayer_H_
#define _MediaPlayer_H_

struct AVFormatContext;
struct AVStream;
struct AVCodecContext;
struct AVCodec;

class MediaPlayer
{
public:
	MediaPlayer();
	~MediaPlayer();

public:
	int Open(const char *url);

private:
	AVFormatContext *input_fmtctx_;

	int video_stream_index_;
	int audio_stream_index_;

	AVStream *video_stream_;
	AVStream *audio_stream_;

	AVCodecContext *video_codec_ctx_;
	AVCodecContext *audio_codec_ctx_;

	AVCodec *video_codec_;
	AVCodec *audio_codec_;

private:
};

#endif//_MediaPlayer_H_
