

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_bgIEActiveXPluginLib,0x329B0C84,0x4B32,0x4CD0,0xAE,0x19,0x30,0xB9,0x39,0x88,0x2C,0xF6);


MIDL_DEFINE_GUID(IID, DIID__DbgIEActiveXPlugin,0x41C9269F,0x5608,0x45C2,0xA1,0xCD,0xAB,0x4F,0x62,0x08,0x65,0x25);


MIDL_DEFINE_GUID(IID, DIID__DbgIEActiveXPluginEvents,0x2F4791F4,0x29AA,0x46F4,0xA2,0x9A,0x98,0x45,0xF2,0xEA,0xD4,0x3D);


MIDL_DEFINE_GUID(CLSID, CLSID_bgIEActiveXPlugin,0xE5496C7E,0x61E7,0x4F0B,0x96,0x49,0x9B,0x18,0x35,0x4C,0xFB,0x67);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



