#include "ppMediaPlayerExBusiness.h"

#include "ppapi/cpp/var.h"
#include "ffmpeg_stub.h"
#include <Windows.h>

ppMediaPlayerExBusiness::ppMediaPlayerExBusiness()
	: ffmpeg_stub_(new ffmpeg_stub())
{

}

ppMediaPlayerExBusiness::~ppMediaPlayerExBusiness()
{

}

/*
�ڲ�Э�鶨�����£�

- �������
{
	"command":"",
	"request_id":"",
	"":""
}

- Ӧ�����
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

	// �����ע�����ȡffmpeg�İ�װλ��
	// ����Ĭ�Ϸ��õ�SOFTWARE
	HKEY hKey = nullptr;
	DWORD dwDisposition = 0;
	LSTATUS lStatus = RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\GxxGm\\FFmpeg", &hKey);
	if (lStatus != ERROR_SUCCESS)
	{
		// �����󣬲����
		sprintf_s(msg, 4096, "��ע��� %s ʧ�ܣ������룺%d\n", "SOFTWARE\\GxxGm\\FFmpeg", lStatus);
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
		// �����󣬲����
		sprintf_s(msg, 4096, "��ȡע��� %s->%s ʧ�ܣ������룺%d\n", "SOFTWARE\\GxxGm\\FFmpeg", "Location", lStatus);
		OutputDebugStringA(msg);
		result["result"] = "READ REG FAILED.";
		result["errcode"] = Json::Value(-1);
		return true;
	}

	ffmpeg_lib_location_ = location;

	// ��ʼ��ffmpeg_stub
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


	return true;
}