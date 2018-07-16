#include "ppMediaHandler.h"
#include "ffmpeg_stub.h"

ppMediaHandler::ppMediaHandler(ffmpeg_stub *stub)
	: stub_(stub)
	, input_fmtctx_(nullptr)
	, video_index_(-1)
	, audio_index_(-1)
	, video_stream_(nullptr)
	, audio_stream_(nullptr)
	, video_codec_ctx_(nullptr)
	, audio_codec_ctx_(nullptr)
	, video_codec_(nullptr)
	, audio_codec_(nullptr)
{

}

ppMediaHandler::~ppMediaHandler()
{

}

int ppMediaHandler::Demuxing(const char *url)
{
	char msg[4096] = {0};
	int errCode = stub_->ptr_avformat_open_input(&input_fmtctx_, url, nullptr, nullptr);
	if (errCode < 0)
	{
		//av_make_error_string(msg, AV_ERROR_MAX_STRING_SIZE, errCode);
		return errCode;
	}

	errCode = stub_->ptr_avformat_find_stream_info(input_fmtctx_, nullptr);
	if (errCode < 0)
	{
		//av_make_error_string(msg, AV_ERROR_MAX_STRING_SIZE, errCode);
		return errCode;
	}

	for (int index = 0; index < input_fmtctx_->nb_streams; ++index)
	{
		AVStream *stream = input_fmtctx_->streams[index];

		if (stream->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_index_ = index;
			video_stream_ = stream;

			video_codec_ = stub_->ptr_avcodec_find_decoder(video_stream_->codec->codec_id);
			if (video_codec_ == nullptr)
			{
				break;
			}

			avcodec_open2()
		}
	}
}