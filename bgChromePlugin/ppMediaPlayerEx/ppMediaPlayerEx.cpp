// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#include <Windows.h>

// When compiling natively on Windows, PostMessage can be #define-d to
// something else.
#ifdef PostMessage
#undef PostMessage
#endif

// This is a simple C++ Pepper plugin that demonstrates HandleMessage and
// PostMessage.

// This object represents one time the page says <embed>.
class MyInstance : public pp::Instance {
public:
	explicit MyInstance(PP_Instance instance) : pp::Instance(instance) {}
	virtual ~MyInstance() {}
	virtual void HandleMessage(const pp::Var& message_data);
};

// HandleMessage gets invoked when postMessage is called on the DOM element
// associated with this plugin instance.
// In this case, if we are given a string, we'll post a message back to
// JavaScript indicating whether or not that string is a palindrome.
void MyInstance::HandleMessage(const pp::Var& message_data) {
	if (message_data.is_string()) {
		std::string string_copy(message_data.AsString());

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
			return ;
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
			return ;
		}

		sprintf_s(msg, 4096, "读取到安装路径%s！\n", location);
		OutputDebugStringA(msg);

		PostMessage(pp::Var(location));
	}
}

// This object is the global object representing this plugin library as long
// as it is loaded.
class MyModule : public pp::Module {
public:
	MyModule() : pp::Module() {}
	virtual ~MyModule() {}

	// Override CreateInstance to create your customized Instance object.
	virtual pp::Instance* CreateInstance(PP_Instance instance) {
		return new MyInstance(instance);
	}
};

namespace pp {

	// Factory function for your specialization of the Module object.
	Module* CreateModule() {
		return new MyModule();
	}

}  // namespace pp

