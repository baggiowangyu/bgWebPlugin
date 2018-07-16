// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#include "ppMediaPlayerExBusiness.h"
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

private:
	ppMediaPlayerExBusiness bussiness_;
};

// HandleMessage gets invoked when postMessage is called on the DOM element
// associated with this plugin instance.
// In this case, if we are given a string, we'll post a message back to
// JavaScript indicating whether or not that string is a palindrome.
void MyInstance::HandleMessage(const pp::Var& message_data) {
	if (message_data.is_string()) {
		std::string string_copy(message_data.AsString());

		Json::Reader reader;
		Json::Value root;
		Json::Value result;

		if (!reader.parse(string_copy, root))
		{
			// 解析失败
			const char *ret = "{\"result\":\"failed\",\"errcode\":\"-1\"}";
			PostMessage(pp::Var(ret));
			return ;
		}

		// 解析成功，将消息传入消息分发层
		if (!bussiness_.CommandHandler(root, result))
		{
			char msg[4096] = {0};
			sprintf_s(msg, 4096, "命令分发失败！\n");
			OutputDebugStringA(msg);
		}

		// 
		Json::FastWriter writer;
		PostMessage(pp::Var(writer.write(result)));
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

