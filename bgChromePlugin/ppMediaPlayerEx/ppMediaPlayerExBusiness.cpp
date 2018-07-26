#include "ppMediaPlayerExBusiness.h"

#include "ppapi/cpp/var.h"
#include "ffmpeg_stub.h"
#include "ppMediaHandler.h"
#include <Windows.h>

ppMediaPlayerExBusiness::ppMediaPlayerExBusiness()
	: ffmpeg_stub_(new ffmpeg_stub())
	, media_handler_(new ppMediaHandler(ffmpeg_stub_))
{

}

ppMediaPlayerExBusiness::~ppMediaPlayerExBusiness()
{

}

/*
内部协议定义如下：

- 请求命令：
{
	"command":"",
	"request_id":"",
	"":""
}

- 应答命令：
{
	"command":"",
	"request_id":"",
	"":""
}
*/
bool ppMediaPlayerExBusiness::CommandHandler(Json::Value command_root, Json::Value &result)
{
	bool ret = 0;

	std::string cmd = command_root["command"].asString();
	if (cmd.compare("init") == 0)
	{
		ret = this->Initialize(result);
	}
	else if (cmd.compare("play") == 0)
	{
		ret = this->Play(command_root, result);
	}

	result["command"] = command_root["command"];
	result["request_id"] = command_root["request_id"];

	return ret;
}

//////////////////////////////////////////////////////////////////////////
bool ppMediaPlayerExBusiness::Initialize(Json::Value &result)
{
	char msg[4096] = {0};

	// 这里从注册表读取ffmpeg的安装位置
	// 我们默认放置到SOFTWARE
	HKEY hKey = nullptr;
	DWORD dwDisposition = 0;
	LSTATUS lStatus = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\GxxGm\\FFmpeg", &hKey);
	if (lStatus != ERROR_SUCCESS)
	{
		// 检查错误，并输出
		sprintf_s(msg, 4096, "打开注册表 %s 失败！错误码：%d\n", "SOFTWARE\\GxxGm\\FFmpeg", lStatus);
		OutputDebugStringA(msg);
		result["result"] = Json::Value("OPEN REG FAILED.");
		result["errcode"] = Json::Value(lStatus);
		return true;
	}

	DWORD dwType = 0;
	DWORD dwcbData = 4096;
	char location[4096] = {0};
	lStatus = RegQueryValueExA(hKey, "Location", nullptr, &dwType, (LPBYTE)location, &dwcbData);
	RegCloseKey(hKey);
	if (lStatus != ERROR_SUCCESS)
	{
		// 检查错误，并输出
		sprintf_s(msg, 4096, "读取注册表 %s->%s 失败！错误码：%d\n", "SOFTWARE\\GxxGm\\FFmpeg", "Location", lStatus);
		OutputDebugStringA(msg);
		result["result"] = "READ REG FAILED.";
		result["errcode"] = Json::Value(-1);
		return true;
	}

	ffmpeg_lib_location_ = location;

	// 初始化ffmpeg_stub
	int errCode = ffmpeg_stub_->Initialize(location);
	if (errCode != 0)
	{
		result["result"] = "INITIALIZE VIDEO DECODER FAILED.";
		result["errcode"] = Json::Value(errCode);
	}

	result["result"] = "SUCCESS";
	result["errcode"] = Json::Value(0);

	return true;
}

bool ppMediaPlayerExBusiness::Play(Json::Value command_root, Json::Value &result)
{
	if (command_root["url"].empty())
		return false;

	std::string url = command_root["url"].asString();
	int errCode = media_handler_->Demuxing(url.c_str());
	if (errCode != 0)
	{
		result["result"] = "DEMUXING FAILED.";
		result["errcode"] = Json::Value(errCode);

		return true;
	}
#ifdef _DEBUG
 	else
 	{
 		result["result"] = "DEMUXING SUCCESS.";
 		result["errcode"] = Json::Value(errCode);
 	}
#endif

	// 调用播放接口

	return true;
}