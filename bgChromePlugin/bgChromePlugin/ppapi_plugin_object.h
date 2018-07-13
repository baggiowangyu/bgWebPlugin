#ifndef _ppapi_plugin_object_H_
#define _ppapi_plugin_object_H_

#include "ppapi_framework.h"

class bgChromePluginObject : public bgChromePluginBase
{
public:
	explicit bgChromePluginObject(PP_Instance instance) : bgChromePluginBase(instance) {}
	~bgChromePluginObject() {}

public:
	virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);
	virtual void DidChangeView(const pp::View& view);
	virtual void DidChangeView(const pp::Rect& position, const pp::Rect& clip);
	virtual void DidChangeFocus(bool has_focus);
	virtual bool HandleInputEvent(const pp::InputEvent& event);
	virtual bool HandleDocumentLoad(const pp::URLLoader& url_loader);
	virtual void HandleMessage(const pp::Var& message_data);
};

#endif//_ppapi_plugin_object_H_
