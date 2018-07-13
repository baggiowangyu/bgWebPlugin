#include "ppapi_framework.h"


bool bgChromePluginBase::Init(uint32_t argc, const char* argn[], const char* argv[])
{
	//
	return true;
}

void bgChromePluginBase::DidChangeView(const pp::View& view)
{
	//
}

void bgChromePluginBase::DidChangeView(const pp::Rect& position, const pp::Rect& clip)
{
	//
}

void bgChromePluginBase::DidChangeFocus(bool has_focus)
{
	//
}

bool bgChromePluginBase::HandleInputEvent(const pp::InputEvent& event)
{
	//
	return true;
}

bool bgChromePluginBase::HandleDocumentLoad(const pp::URLLoader& url_loader)
{
	//
	return true;
}

void bgChromePluginBase::HandleMessage(const pp::Var& message_data)
{
	//
}