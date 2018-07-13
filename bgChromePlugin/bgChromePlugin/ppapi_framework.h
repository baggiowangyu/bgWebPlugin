#ifndef _ppapi_framework_H_
#define _ppapi_framework_H_

#include <string.h>
#include <iostream>
#include <sstream>

#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/var.h"

class bgChromePluginBase : public pp::Instance
{
public:
	explicit bgChromePluginBase(PP_Instance instance) : pp::Instance(instance) {}
	virtual ~bgChromePluginBase() {}

public:
	virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);
	virtual void DidChangeView(const pp::View& view);
	virtual void DidChangeView(const pp::Rect& position, const pp::Rect& clip);
	virtual void DidChangeFocus(bool has_focus);
	virtual bool HandleInputEvent(const pp::InputEvent& event);
	virtual bool HandleDocumentLoad(const pp::URLLoader& url_loader);
	virtual void HandleMessage(const pp::Var& message_data);
};

#endif//_ppapi_framework_H_
