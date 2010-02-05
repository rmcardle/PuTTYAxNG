

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Feb 05 00:17:46 2010
 */
/* Compiler settings for .\PuttyAx.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

MIDL_DEFINE_GUID(IID, IID_IPuttyAxObj,0x716B2BB3,0x55B5,0x4CB8,0x9E,0x2A,0x27,0x5B,0x29,0xB9,0x82,0xA8);


MIDL_DEFINE_GUID(IID, LIBID_PUTTYAXLib,0xB2211620,0x5305,0x4544,0x85,0xDC,0xA2,0x79,0xD2,0x8D,0xEA,0x12);


MIDL_DEFINE_GUID(IID, DIID__IPuttyAxObjEvents,0xE317EEDE,0xB3A3,0x458E,0xBD,0x1C,0x1D,0xFB,0x97,0x9A,0x87,0x73);


MIDL_DEFINE_GUID(CLSID, CLSID_PuttyAxObj,0x5CC7C29A,0x80DB,0x44B9,0x9A,0x90,0x48,0xEE,0xA3,0x9B,0x47,0x17);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



