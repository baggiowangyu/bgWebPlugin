#include "ppapi_plugin_object.h"

bool bgChromePluginObject::Init(uint32_t argc, const char* argn[], const char* argv[])
{
	//
	return true;
}

void bgChromePluginObject::DidChangeView(const pp::View& view)
{
	//
}

void bgChromePluginObject::DidChangeView(const pp::Rect& position, const pp::Rect& clip)
{
	//
}

void bgChromePluginObject::DidChangeFocus(bool has_focus)
{
	//
}

bool bgChromePluginObject::HandleInputEvent(const pp::InputEvent& event)
{
	//
	return true;
}

bool bgChromePluginObject::HandleDocumentLoad(const pp::URLLoader& url_loader)
{
	//
	return true;
}

void bgChromePluginBase::HandleMessage(const pp::Var& message_data)
{
	//
}