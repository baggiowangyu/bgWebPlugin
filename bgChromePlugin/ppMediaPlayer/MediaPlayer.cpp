#include "MediaPlayer.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#ifdef __cplusplus
};
#endif

MediaPlayer::MediaPlayer()
	: input_fmtctx_(nullptr)
{
	av_register_all();
	avformat_network_init();
	avcodec_register_all();
}

MediaPlayer::~MediaPlayer()
{
	if (input_fmtctx_ != nullptr)
	{
		//
	}
}

int MediaPlayer::Open(const char *url)
{
	int errCode = 0;

	errCode = avformat_open_input(&input_fmtctx_, url, nullptr, nullptr);
	if (errCode < 0)
	{
		return errCode;
	}

	errCode = avformat_find_stream_info(input_fmtctx_, nullptr);
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
			video_codec_ = avcodec_find_decoder(stream->codec->codec_id);
		}
		else if (stream->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_stream_ = stream;
			audio_codec_ = avcodec_find_decoder(stream->codec->codec_id);
		}
	}

	return errCode;
}