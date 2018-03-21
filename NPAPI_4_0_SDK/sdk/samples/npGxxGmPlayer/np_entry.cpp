/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are subject to the Mozilla Public License Version
* 1.1 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* The Original Code is mozilla.org code.
*
* The Initial Developer of the Original Code is
* Netscape Communications Corporation.
* Portions created by the Initial Developer are Copyright (C) 1998
* the Initial Developer. All Rights Reserved.
*
* Contributor(s):
*
* Alternatively, the contents of this file may be used under the terms of
* either the GNU General Public License Version 2 or later (the "GPL"), or
* the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
* in which case the provisions of the GPL or the LGPL are applicable instead
* of those above. If you wish to allow use of your version of this file only
* under the terms of either the GPL or the LGPL, and not to allow others to
* use your version of this file under the terms of the MPL, indicate your
* decision by deleting the provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */

// Main plugin entry point implementation - exports from the plugin library

#include "npapi.h"
#include "npfunctions.h"
#include "npplat.h"
#include "pluginbase.h"
#include "Plugin.h"
#include "output.h"

#ifndef HIBYTE
#define HIBYTE(x) ((((uint32_t)(x)) & 0xff00) >> 8)
#endif

NPNetscapeFuncs NPNFuncs;

#ifdef XP_WIN

// 
// 入口函数
// 初始化浏览器调用插件的函数表，以NPP（np plugin）开头
NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* aNPPFuncs)
{
	SetupMiniDumpMonitor("D:\\npGxxGmPlayer.dmp");

#ifdef _DEBUG
	MessageBoxA(NULL, "插件已启动，等待接入调试器", "调试", 0);
#endif

	if (!aNPPFuncs)
		return NPERR_INVALID_FUNCTABLE_ERROR;

	if(aNPPFuncs->size < sizeof(NPPluginFuncs))
		return NPERR_INVALID_FUNCTABLE_ERROR;

	// Set up the plugin function table that Netscape will use to call us.
	aNPPFuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
	aNPPFuncs->newp          = NPP_New;
	aNPPFuncs->destroy       = NPP_Destroy;
	aNPPFuncs->setwindow     = NPP_SetWindow;
	aNPPFuncs->newstream     = NPP_NewStream;
	aNPPFuncs->destroystream = NPP_DestroyStream;
	aNPPFuncs->asfile        = NPP_StreamAsFile;
	aNPPFuncs->writeready    = NPP_WriteReady;
	aNPPFuncs->write         = NPP_Write;
	aNPPFuncs->print         = NPP_Print;
	aNPPFuncs->event         = NPP_HandleEvent;
	aNPPFuncs->urlnotify     = NPP_URLNotify;
	aNPPFuncs->getvalue      = NPP_GetValue;
	aNPPFuncs->setvalue      = NPP_SetValue;
	aNPPFuncs->javaClass	 = NULL;

	return NPERR_NO_ERROR;
}

#endif//XP_WIN

char *NPP_GetMIMEDescription();

char *NP_GetMIMEDescription()
{
	return NPP_GetMIMEDescription();
}

NPError NP_GetValue(void* future, NPPVariable variable, void *value)
{
	return NPP_GetValue((NPP_t *)future, variable, value);
}

//
// 初始化插件，在NP_GetEntryPoints()后被调用
// 初始化插件调用浏览器的函数表，参数aNPNFuncs带有该函数表信息
// 我们可以自定义一个对象保存这些信息，今后就可以通过该对象调用方法来实现对浏览器的一些操作
NPError OSCALL NP_Initialize(NPNetscapeFuncs* aNPNFuncs
#ifdef XP_UNIX
	, NPPluginFuncs *aNPPFuncs
#endif
)
{
	if (!aNPNFuncs)
		return NPERR_INVALID_FUNCTABLE_ERROR;

	if (HIBYTE(aNPNFuncs->version) > NP_VERSION_MAJOR)
		return NPERR_INCOMPATIBLE_VERSION_ERROR;

	if (aNPNFuncs->size < sizeof(NPNetscapeFuncs))
		return NPERR_INVALID_FUNCTABLE_ERROR;

	NPNFuncs.size					= aNPNFuncs->size;
	NPNFuncs.version				= aNPNFuncs->version;
	NPNFuncs.geturlnotify			= aNPNFuncs->geturlnotify;
	NPNFuncs.geturl					= aNPNFuncs->geturl;
	NPNFuncs.posturlnotify			= aNPNFuncs->posturlnotify;
	NPNFuncs.posturl				= aNPNFuncs->posturl;
	NPNFuncs.requestread			= aNPNFuncs->requestread;
	NPNFuncs.newstream				= aNPNFuncs->newstream;
	NPNFuncs.write					= aNPNFuncs->write;
	NPNFuncs.destroystream			= aNPNFuncs->destroystream;
	NPNFuncs.status					= aNPNFuncs->status;
	NPNFuncs.uagent					= aNPNFuncs->uagent;
	NPNFuncs.memalloc				= aNPNFuncs->memalloc;
	NPNFuncs.memfree				= aNPNFuncs->memfree;
	NPNFuncs.memflush				= aNPNFuncs->memflush;
	NPNFuncs.reloadplugins			= aNPNFuncs->reloadplugins;
	NPNFuncs.getJavaEnv				= NULL;
	NPNFuncs.getJavaPeer			= NULL;
	NPNFuncs.getvalue				= aNPNFuncs->getvalue;
	NPNFuncs.setvalue				= aNPNFuncs->setvalue;
	NPNFuncs.invalidaterect			= aNPNFuncs->invalidaterect;
	NPNFuncs.invalidateregion		= aNPNFuncs->invalidateregion;
	NPNFuncs.forceredraw			= aNPNFuncs->forceredraw;
	NPNFuncs.getstringidentifier	= aNPNFuncs->getstringidentifier;
	NPNFuncs.getstringidentifiers	= aNPNFuncs->getstringidentifiers;
	NPNFuncs.getintidentifier		= aNPNFuncs->getintidentifier;
	NPNFuncs.identifierisstring		= aNPNFuncs->identifierisstring;
	NPNFuncs.utf8fromidentifier		= aNPNFuncs->utf8fromidentifier;
	NPNFuncs.intfromidentifier		= aNPNFuncs->intfromidentifier;
	NPNFuncs.createobject			= aNPNFuncs->createobject;
	NPNFuncs.retainobject			= aNPNFuncs->retainobject;
	NPNFuncs.releaseobject			= aNPNFuncs->releaseobject;
	NPNFuncs.invoke					= aNPNFuncs->invoke;
	NPNFuncs.invokeDefault			= aNPNFuncs->invokeDefault;
	NPNFuncs.evaluate				= aNPNFuncs->evaluate;
	NPNFuncs.getproperty			= aNPNFuncs->getproperty;
	NPNFuncs.setproperty			= aNPNFuncs->setproperty;
	NPNFuncs.removeproperty			= aNPNFuncs->removeproperty;
	NPNFuncs.hasproperty			= aNPNFuncs->hasproperty;
	NPNFuncs.hasmethod				= aNPNFuncs->hasmethod;
	NPNFuncs.releasevariantvalue	= aNPNFuncs->releasevariantvalue;
	NPNFuncs.setexception			= aNPNFuncs->setexception;

#ifdef XP_UNIX
	/*
	* Set up the plugin function table that Netscape will use to
	* call us.  Netscape needs to know about our version and size
	* and have a UniversalProcPointer for every function we
	* implement.
	*/
	aNPPFuncs->version				= (NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR;
	aNPPFuncs->size					= sizeof(NPPluginFuncs);
	aNPPFuncs->newp					= (NPP_NewProcPtr)(NPP_New);
	aNPPFuncs->destroy				= (NPP_DestroyProcPtr)(NPP_Destroy);
	aNPPFuncs->setwindow			= (NPP_SetWindowProcPtr)(NPP_SetWindow);
	aNPPFuncs->newstream			= (NPP_NewStreamProcPtr)(NPP_NewStream);
	aNPPFuncs->destroystream		= (NPP_DestroyStreamProcPtr)(NPP_DestroyStream);
	aNPPFuncs->asfile				= (NPP_StreamAsFileProcPtr)(NPP_StreamAsFile);
	aNPPFuncs->writeready			= (NPP_WriteReadyProcPtr)(NPP_WriteReady);
	aNPPFuncs->write				= (NPP_WriteProcPtr)(NPP_Write);
	aNPPFuncs->print				= (NPP_PrintProcPtr)(NPP_Print);
	aNPPFuncs->urlnotify			= (NPP_URLNotifyProcPtr)(NPP_URLNotify);
	aNPPFuncs->event				= NULL;
	aNPPFuncs->getvalue				= (NPP_GetValueProcPtr)(NPP_GetValue);
	aNPPFuncs->javaClass			= NULL;

	NPP_Initialize();
#endif

	// NS_PluginInitialize()是我们自己实现的函数
	return NS_PluginInitialize();
}

//
// 释放资源
NPError OSCALL NP_Shutdown()
{
	// NS_PluginShutdown()是我们自己实现的函数
	NS_PluginShutdown();
	return NPERR_NO_ERROR;
}


#ifdef XP_MAC
short gResFile; // Refnum of the plugin's resource file

NPError Private_Initialize(void)
{
	NPError rv = NS_PluginInitialize();
	return rv;
}

void Private_Shutdown(void)
{
	NS_PluginShutdown();
	__destroy_global_chain();
}

NPError main(NPNetscapeFuncs* aNPNFuncs, NPPluginFuncs* aNPPFuncs, NPP_ShutdownUPP* aUnloadUpp)
{
	NPError rv = NPERR_NO_ERROR;

	if (!aUnloadUpp)
		rv = NPERR_INVALID_FUNCTABLE_ERROR;

	if (rv == NPERR_NO_ERROR)
		rv = fillNetscapeFunctionTable(aNPNFuncs);

	if (rv == NPERR_NO_ERROR) {
		// defer static constructors until the global functions are initialized.
		__InitCode__();
		rv = fillPluginFunctionTable(aNPPFuncs);
	}

	*aUnloadUpp = NewNPP_ShutdownProc(Private_Shutdown);
	gResFile = CurResFile();
	rv = Private_Initialize();

	return rv;
}
#endif // XP_MAC
