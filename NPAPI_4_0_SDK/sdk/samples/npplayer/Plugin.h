#pragma once
#include "pluginbase.h"

class CPlugin : public nsPluginInstanceBase
{
private:
	NPP m_pNPInstance;
	NPBool m_bInitialized;

public:
	CPlugin(NPP pNPInstance);
	~CPlugin();

	NPBool init(NPWindow* pNPWindow)  {  m_bInitialized = TRUE;  return TRUE;}
	void shut()  {  m_bInitialized = FALSE;  }
	NPBool isInitialized()  {  return m_bInitialized;  }
};
