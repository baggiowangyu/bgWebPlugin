#ifndef _ppMediaPlayerExBusiness_H_
#define _ppMediaPlayerExBusiness_H_

#include "json/json.h"

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
};

#endif//_ppMediaPlayerExBusiness_H_
