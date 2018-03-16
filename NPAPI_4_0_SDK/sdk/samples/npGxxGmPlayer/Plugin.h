#pragma once
#include "pluginbase.h"

class CPlugin :
	public nsPluginInstanceBase
{
public:
	CPlugin(void);
	CPlugin(NPP pNPInstance);
	~CPlugin(void);

public:
	virtual NPBool init(NPWindow* pNPWindow);  
	virtual void shut();  
	virtual NPBool isInitialized();

	virtual uint16_t HandleEvent(void* event);

private:  
	NPP m_pNPInstance;  
	NPBool m_bInitialized; 
};
