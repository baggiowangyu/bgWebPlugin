// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

#include "MediaPlayer.h"

// When compiling natively on Windows, PostMessage can be #define-d to
// something else.
#ifdef PostMessage
#undef PostMessage
#endif

// This is a simple C++ Pepper plugin that demonstrates HandleMessage and
// PostMessage.

// This object represents one time the page says <embed>.
class ppMediaPlayerInstance : public pp::Instance {
public:
	explicit ppMediaPlayerInstance(PP_Instance instance) : pp::Instance(instance) {}
	virtual ~ppMediaPlayerInstance() {}
	virtual void HandleMessage(const pp::Var& message_data);

public:
	MediaPlayer player;
};

// HandleMessage gets invoked when postMessage is called on the DOM element
// associated with this plugin instance.
// In this case, if we are given a string, we'll post a message back to
// JavaScript indicating whether or not that string is a palindrome.
void ppMediaPlayerInstance::HandleMessage(const pp::Var& message_data) {
	if (message_data.is_string()) {
		std::string string_copy(message_data.AsString());
		int errCode = player.Open(string_copy.c_str());
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
		return new ppMediaPlayerInstance(instance);
	}
};

namespace pp {

	// Factory function for your specialization of the Module object.
	Module* CreateModule() {
		return new MyModule();
	}

}  // namespace pp

