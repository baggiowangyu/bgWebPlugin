#include "MediaPlayer.h"
#include "ffmpeg_stub.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#ifdef __cplusplus
};
#endif

MediaPlayer::MediaPlayer(const char *location)
	: input_fmtctx_(nullptr)
	, ffmpeg_stub_(new ffmpeg_stub())
{
	
}

MediaPlayer::~MediaPlayer()
{
	if (input_fmtctx_ != nullptr)
	{
		//
	}
}

int MediaPlayer::Initialize(const char *location)
{
	int errCode = ffmpeg_stub_->Initialize(location);
	if (errCode != 0)
		return errCode;

	ffmpeg_stub_->ptr_av_register_all();
	ffmpeg_stub_->ptr_avformat_network_init();
	ffmpeg_stub_->ptr_avcodec_register_all();

	return 0;
}

int MediaPlayer::Open(const char *url)
{
	int errCode = 0;

	errCode = ffmpeg_stub_->ptr_avformat_open_input(&input_fmtctx_, url, nullptr, nullptr);
	if (errCode < 0)
	{
		return errCode;
	}

	errCode = ffmpeg_stub_->ptr_avformat_find_stream_info(input_fmtctx_, nullptr);
	if (errCode < 0)
	{
		return errCode;
	}

	for (int index = 0; index < input_fmtctx_->nb_streams; ++index)
	{
		AVStream *stream = input_fmtctx_->streams[index];

		if (stream->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_stream_ = stream;
			video_codec_ = ffmpeg_stub_->ptr_avcodec_find_decoder(stream->codec->codec_id);
		}
		else if (stream->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_stream_ = stream;
			audio_codec_ = ffmpeg_stub_->ptr_avcodec_find_decoder(stream->codec->codec_id);
		}
	}

	return errCode;
}