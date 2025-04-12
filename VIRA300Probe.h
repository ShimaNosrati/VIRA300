

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Apr 12 12:30:12 2025
 */
/* Compiler settings for VIRA300Probe.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __VIRA300Probe_h__
#define __VIRA300Probe_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVIRA300ProbePlugin_FWD_DEFINED__
#define __IVIRA300ProbePlugin_FWD_DEFINED__
typedef interface IVIRA300ProbePlugin IVIRA300ProbePlugin;

#endif 	/* __IVIRA300ProbePlugin_FWD_DEFINED__ */


#ifndef __VIRA300ProbePlugin_FWD_DEFINED__
#define __VIRA300ProbePlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class VIRA300ProbePlugin VIRA300ProbePlugin;
#else
typedef struct VIRA300ProbePlugin VIRA300ProbePlugin;
#endif /* __cplusplus */

#endif 	/* __VIRA300ProbePlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IVIRA300ProbePlugin_INTERFACE_DEFINED__
#define __IVIRA300ProbePlugin_INTERFACE_DEFINED__

/* interface IVIRA300ProbePlugin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVIRA300ProbePlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9491108D-561A-4565-81A5-5E5216915AFC")
    IVIRA300ProbePlugin : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IVIRA300ProbePluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVIRA300ProbePlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVIRA300ProbePlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVIRA300ProbePlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVIRA300ProbePlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVIRA300ProbePlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVIRA300ProbePlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVIRA300ProbePlugin * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IVIRA300ProbePluginVtbl;

    interface IVIRA300ProbePlugin
    {
        CONST_VTBL struct IVIRA300ProbePluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVIRA300ProbePlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVIRA300ProbePlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVIRA300ProbePlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVIRA300ProbePlugin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IVIRA300ProbePlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IVIRA300ProbePlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IVIRA300ProbePlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVIRA300ProbePlugin_INTERFACE_DEFINED__ */



#ifndef __VIRA300PROBELib_LIBRARY_DEFINED__
#define __VIRA300PROBELib_LIBRARY_DEFINED__

/* library VIRA300PROBELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VIRA300PROBELib;

EXTERN_C const CLSID CLSID_VIRA300ProbePlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("EC2CE725-CD92-4174-81C1-58C51292D9D0")
VIRA300ProbePlugin;
#endif
#endif /* __VIRA300PROBELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


