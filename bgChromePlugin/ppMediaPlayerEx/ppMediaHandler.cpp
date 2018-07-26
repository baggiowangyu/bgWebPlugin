#include "ppMediaHandler.h"
#include "ffmpeg_stub.h"

ppMediaHandler::ppMediaHandler(ffmpeg_stub *stub)
	: stub_(stub), input_fmtctx_(nullptr), video_index_(-1), audio_index_(-1), video_stream_(nullptr)
	, audio_stream_(nullptr), video_codec_ctx_(nullptr), audio_codec_ctx_(nullptr), video_codec_(nullptr)
	, audio_codec_(nullptr), video_framerate_(0), video_bitrate_(0), video_width_(0), video_height_(0)
	, video_time_base_(nullptr)
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

			video_codec_ctx_ = stub_->ptr_avcodec_alloc_context3(video_codec_);
			if (video_codec_ctx_ == nullptr)
			{
				break;
			}

			errCode = stub_->ptr_avcodec_copy_context(video_codec_ctx_, video_stream_->codec);
			if (errCode < 0)
			{
				break;
			}

			errCode = stub_->ptr_avcodec_open2(video_codec_ctx_, video_codec_, nullptr);
			if (errCode < 0)
			{
				break;
			}

			// 这里可以统计帧率
			video_framerate_ = (float)video_stream_->r_frame_rate.num / (float)video_stream_->r_frame_rate.den;

			// 码率
			video_bitrate_ = video_codec_ctx_->bit_rate;

			// 宽高
			video_width_ = video_codec_ctx_->width;
			video_height_ = video_codec_ctx_->height;

			// 时间基
			if (video_time_base_ == nullptr)
				video_time_base_ = new AVRational;
			video_time_base_->num = video_stream_->time_base.num;
			video_time_base_->den = video_stream_->time_base.den;

			// ...
		}
		else if (stream->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_index_ = index;
			audio_stream_ = stream;

			audio_codec_ = stub_->ptr_avcodec_find_decoder(audio_stream_->codec->codec_id);
			if (audio_codec_ == nullptr)
			{
				break;
			}

			audio_codec_ctx_ = stub_->ptr_avcodec_alloc_context3(audio_codec_);
			if (audio_codec_ctx_ == nullptr)
			{
				break;
			}

			errCode = stub_->ptr_avcodec_copy_context(audio_codec_ctx_, audio_stream_->codec);
			if (errCode < 0)
			{
				break;
			}

			errCode = stub_->ptr_avcodec_open2(audio_codec_ctx_, audio_codec_, nullptr);
			if (errCode < 0)
			{
				break;
			}

			// 这里可以统计采样率
			audio_samplerate_ = audio_codec_ctx_->sample_rate;
			// 码率
			audio_bitrate_ = audio_codec_ctx_->bit_rate == 0 ? audio_codec_ctx_->bit_rate_tolerance : audio_codec_ctx_->bit_rate;
			// 声音格式
			audio_codec_ctx_->sample_fmt;
			// 声道数
			audio_channels_ = audio_codec_ctx_->channels;
			// ...
		}
	}

	return errCode;
}

int ppMediaHandler::Decode()
{
	int errCode = 0;

	while (true)
	{
		AVPacket pkt;
		errCode = stub_->ptr_av_read_frame(input_fmtctx_, &pkt);
		if (errCode < 0)
			break;
		
		if (pkt.stream_index == video_index_)
		{
			// 视频帧，入队？
		}
		else if (pkt.stream_index == audio_index_)
		{
			// 音频帧，入队？
		}
	}

	return errCode;
}