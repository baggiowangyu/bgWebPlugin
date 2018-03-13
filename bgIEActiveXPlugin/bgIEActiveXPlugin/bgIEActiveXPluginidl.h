

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Mar 06 17:24:50 2018
 */
/* Compiler settings for .\bgIEActiveXPlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __bgIEActiveXPluginidl_h__
#define __bgIEActiveXPluginidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DbgIEActiveXPlugin_FWD_DEFINED__
#define ___DbgIEActiveXPlugin_FWD_DEFINED__
typedef interface _DbgIEActiveXPlugin _DbgIEActiveXPlugin;
#endif 	/* ___DbgIEActiveXPlugin_FWD_DEFINED__ */


#ifndef ___DbgIEActiveXPluginEvents_FWD_DEFINED__
#define ___DbgIEActiveXPluginEvents_FWD_DEFINED__
typedef interface _DbgIEActiveXPluginEvents _DbgIEActiveXPluginEvents;
#endif 	/* ___DbgIEActiveXPluginEvents_FWD_DEFINED__ */


#ifndef __bgIEActiveXPlugin_FWD_DEFINED__
#define __bgIEActiveXPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class bgIEActiveXPlugin bgIEActiveXPlugin;
#else
typedef struct bgIEActiveXPlugin bgIEActiveXPlugin;
#endif /* __cplusplus */

#endif 	/* __bgIEActiveXPlugin_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __bgIEActiveXPluginLib_LIBRARY_DEFINED__
#define __bgIEActiveXPluginLib_LIBRARY_DEFINED__

/* library bgIEActiveXPluginLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_bgIEActiveXPluginLib;

#ifndef ___DbgIEActiveXPlugin_DISPINTERFACE_DEFINED__
#define ___DbgIEActiveXPlugin_DISPINTERFACE_DEFINED__

/* dispinterface _DbgIEActiveXPlugin */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DbgIEActiveXPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("41C9269F-5608-45C2-A1CD-AB4F62086525")
    _DbgIEActiveXPlugin : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DbgIEActiveXPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DbgIEActiveXPlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DbgIEActiveXPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DbgIEActiveXPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DbgIEActiveXPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DbgIEActiveXPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DbgIEActiveXPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DbgIEActiveXPlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DbgIEActiveXPluginVtbl;

    interface _DbgIEActiveXPlugin
    {
        CONST_VTBL struct _DbgIEActiveXPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DbgIEActiveXPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DbgIEActiveXPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DbgIEActiveXPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DbgIEActiveXPlugin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DbgIEActiveXPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DbgIEActiveXPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DbgIEActiveXPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DbgIEActiveXPlugin_DISPINTERFACE_DEFINED__ */


#ifndef ___DbgIEActiveXPluginEvents_DISPINTERFACE_DEFINED__
#define ___DbgIEActiveXPluginEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DbgIEActiveXPluginEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DbgIEActiveXPluginEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2F4791F4-29AA-46F4-A29A-9845F2EAD43D")
    _DbgIEActiveXPluginEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DbgIEActiveXPluginEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DbgIEActiveXPluginEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DbgIEActiveXPluginEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DbgIEActiveXPluginEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DbgIEActiveXPluginEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DbgIEActiveXPluginEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DbgIEActiveXPluginEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DbgIEActiveXPluginEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DbgIEActiveXPluginEventsVtbl;

    interface _DbgIEActiveXPluginEvents
    {
        CONST_VTBL struct _DbgIEActiveXPluginEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DbgIEActiveXPluginEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DbgIEActiveXPluginEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DbgIEActiveXPluginEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DbgIEActiveXPluginEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DbgIEActiveXPluginEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DbgIEActiveXPluginEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DbgIEActiveXPluginEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DbgIEActiveXPluginEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_bgIEActiveXPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("E5496C7E-61E7-4F0B-9649-9B18354CFB67")
bgIEActiveXPlugin;
#endif
#endif /* __bgIEActiveXPluginLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


