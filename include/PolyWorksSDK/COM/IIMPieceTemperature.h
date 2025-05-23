﻿/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 7.00.0555 */
/* at Wed Apr 24 12:28:57 2013
 */
/* Compiler settings for ..\..\Interfaces\IIMPieceTemperature.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555
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

#ifndef __IIMPieceTemperature_h__
#define __IIMPieceTemperature_h__

#if defined( _MSC_VER ) && ( _MSC_VER >= 1020 )
#pragma once
#endif

/* Forward Declarations */

#ifndef __IIMPieceTemperature_FWD_DEFINED__
#define __IIMPieceTemperature_FWD_DEFINED__
typedef interface IIMPieceTemperature IIMPieceTemperature;
#endif  /* __IIMPieceTemperature_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __IIMPieceTemperature_INTERFACE_DEFINED__
#define __IIMPieceTemperature_INTERFACE_DEFINED__

/* interface IIMPieceTemperature */
/* [helpstring][uuid][object] */


EXTERN_C const IID IID_IIMPieceTemperature;

#if defined( __cplusplus ) && !defined( CINTERFACE )

MIDL_INTERFACE( "D3990CE6-3171-48C4-8E13-E207740ADB8B" )
IIMPieceTemperature : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE HasPieceTemperature(
        /* [retval][out] */ VARIANT_BOOL * pHasPieceTemperature_ ) = 0;

    virtual HRESULT STDMETHODCALLTYPE PieceTemperatureGet(
        /* [retval][out] */ double* pPieceTemperature_ ) = 0;

};

#else   /* C style interface */

typedef struct IIMPieceTemperatureVtbl
{
    BEGIN_INTERFACE HRESULT ( STDMETHODCALLTYPE* QueryInterface )(
        IIMPieceTemperature * This,
        /* [in] */ REFIID riid,
        /* [annotation][iid_is][out] */
        __RPC__deref_out  void** ppvObject );

    ULONG( STDMETHODCALLTYPE * AddRef )(
        IIMPieceTemperature * This );

    ULONG( STDMETHODCALLTYPE * Release )(
        IIMPieceTemperature * This );

    HRESULT( STDMETHODCALLTYPE * HasPieceTemperature )(
        IIMPieceTemperature * This,
        /* [retval][out] */ VARIANT_BOOL* pHasPieceTemperature_ );

    HRESULT( STDMETHODCALLTYPE * PieceTemperatureGet )(
        IIMPieceTemperature * This,
        /* [retval][out] */ double* pPieceTemperature_ );

    END_INTERFACE
} IIMPieceTemperatureVtbl;

interface IIMPieceTemperature
{
    CONST_VTBL struct IIMPieceTemperatureVtbl* lpVtbl;
};



#ifdef COBJMACROS


#define IIMPieceTemperature_QueryInterface( This, riid, ppvObject ) \
    ( ( This )->lpVtbl->QueryInterface( This, riid, ppvObject ) )

#define IIMPieceTemperature_AddRef( This )    \
    ( ( This )->lpVtbl->AddRef( This ) )

#define IIMPieceTemperature_Release( This )   \
    ( ( This )->lpVtbl->Release( This ) )


#define IIMPieceTemperature_HasPieceTemperature( This, pHasPieceTemperature_ ) \
    ( ( This )->lpVtbl->HasPieceTemperature( This, pHasPieceTemperature_ ) )

#define IIMPieceTemperature_PieceTemperatureGet( This, pPieceTemperature_ )    \
    ( ( This )->lpVtbl->PieceTemperatureGet( This, pPieceTemperature_ ) )

#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IIMPieceTemperature_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif // ifndef __IIMPieceTemperature_h__
