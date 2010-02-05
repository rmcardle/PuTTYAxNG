

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PuttyAx_h__
#define __PuttyAx_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPuttyAxObj_FWD_DEFINED__
#define __IPuttyAxObj_FWD_DEFINED__
typedef interface IPuttyAxObj IPuttyAxObj;
#endif 	/* __IPuttyAxObj_FWD_DEFINED__ */


#ifndef ___IPuttyAxObjEvents_FWD_DEFINED__
#define ___IPuttyAxObjEvents_FWD_DEFINED__
typedef interface _IPuttyAxObjEvents _IPuttyAxObjEvents;
#endif 	/* ___IPuttyAxObjEvents_FWD_DEFINED__ */


#ifndef __PuttyAxObj_FWD_DEFINED__
#define __PuttyAxObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class PuttyAxObj PuttyAxObj;
#else
typedef struct PuttyAxObj PuttyAxObj;
#endif /* __cplusplus */

#endif 	/* __PuttyAxObj_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IPuttyAxObj_INTERFACE_DEFINED__
#define __IPuttyAxObj_INTERFACE_DEFINED__

/* interface IPuttyAxObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPuttyAxObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("716B2BB3-55B5-4CB8-9E2A-275B29B982A8")
    IPuttyAxObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Connected( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Server( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Server( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecuteCommand( 
            /* [in] */ BSTR cmdText,
            /* [retval][out] */ BSTR *pRetVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsInitialized( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPuttyAxObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPuttyAxObj * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPuttyAxObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPuttyAxObj * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPuttyAxObj * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPuttyAxObj * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPuttyAxObj * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPuttyAxObj * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IPuttyAxObj * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IPuttyAxObj * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Connected )( 
            IPuttyAxObj * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Server )( 
            IPuttyAxObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Server )( 
            IPuttyAxObj * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteCommand )( 
            IPuttyAxObj * This,
            /* [in] */ BSTR cmdText,
            /* [retval][out] */ BSTR *pRetVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsInitialized )( 
            IPuttyAxObj * This,
            /* [retval][out] */ BOOL *pVal);
        
        END_INTERFACE
    } IPuttyAxObjVtbl;

    interface IPuttyAxObj
    {
        CONST_VTBL struct IPuttyAxObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPuttyAxObj_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPuttyAxObj_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPuttyAxObj_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPuttyAxObj_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPuttyAxObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPuttyAxObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPuttyAxObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPuttyAxObj_Connect(This)	\
    ( (This)->lpVtbl -> Connect(This) ) 

#define IPuttyAxObj_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IPuttyAxObj_get_Connected(This,pVal)	\
    ( (This)->lpVtbl -> get_Connected(This,pVal) ) 

#define IPuttyAxObj_get_Server(This,pVal)	\
    ( (This)->lpVtbl -> get_Server(This,pVal) ) 

#define IPuttyAxObj_put_Server(This,newVal)	\
    ( (This)->lpVtbl -> put_Server(This,newVal) ) 

#define IPuttyAxObj_ExecuteCommand(This,cmdText,pRetVal)	\
    ( (This)->lpVtbl -> ExecuteCommand(This,cmdText,pRetVal) ) 

#define IPuttyAxObj_get_IsInitialized(This,pVal)	\
    ( (This)->lpVtbl -> get_IsInitialized(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPuttyAxObj_INTERFACE_DEFINED__ */



#ifndef __PUTTYAXLib_LIBRARY_DEFINED__
#define __PUTTYAXLib_LIBRARY_DEFINED__

/* library PUTTYAXLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PUTTYAXLib;

#ifndef ___IPuttyAxObjEvents_DISPINTERFACE_DEFINED__
#define ___IPuttyAxObjEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPuttyAxObjEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPuttyAxObjEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E317EEDE-B3A3-458E-BD1C-1DFB979A8773")
    _IPuttyAxObjEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPuttyAxObjEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IPuttyAxObjEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IPuttyAxObjEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IPuttyAxObjEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IPuttyAxObjEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IPuttyAxObjEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IPuttyAxObjEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IPuttyAxObjEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IPuttyAxObjEventsVtbl;

    interface _IPuttyAxObjEvents
    {
        CONST_VTBL struct _IPuttyAxObjEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPuttyAxObjEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IPuttyAxObjEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IPuttyAxObjEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IPuttyAxObjEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IPuttyAxObjEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IPuttyAxObjEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IPuttyAxObjEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPuttyAxObjEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PuttyAxObj;

#ifdef __cplusplus

class DECLSPEC_UUID("5CC7C29A-80DB-44B9-9A90-48EEA39B4717")
PuttyAxObj;
#endif
#endif /* __PUTTYAXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


