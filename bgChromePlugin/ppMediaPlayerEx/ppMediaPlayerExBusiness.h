#ifndef _ppMediaPlayerExBusiness_H_
#define _ppMediaPlayerExBusiness_H_

#include "json/json.h"

class ffmpeg_stub;
class ppMediaHandler;

class ppMediaPlayerExBusiness
{
public:
	ppMediaPlayerExBusiness();
	~ppMediaPlayerExBusiness();

public:
	// ÃüÁî·Ö·¢Ä£¿é
	bool CommandHandler(Json::Value command_root, Json::Value &result);

public:
	bool Initialize(Json::Value &result);

public:
	bool Play(Json::Value command_root, Json::Value &result);

private:
	std::string ffmpeg_lib_location_;
	ffmpeg_stub *ffmpeg_stub_;
	ppMediaHandler *media_handler_;
};

#endif//_ppMediaPlayerExBusiness_H_
