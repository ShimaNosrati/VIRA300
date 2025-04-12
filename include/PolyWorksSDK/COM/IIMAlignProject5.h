﻿/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 7.00.0555 */
/* at Thu Dec 06 11:42:57 2012
 */
/* Compiler settings for ..\..\Interfaces\IIMAlignProject5.idl:
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

#ifndef __IIMAlignProject5_h__
#define __IIMAlignProject5_h__

#if defined( _MSC_VER ) && ( _MSC_VER >= 1020 )
#pragma once
#endif

/* Forward Declarations */

#ifndef __IIMAlignProject5_FWD_DEFINED__
#define __IIMAlignProject5_FWD_DEFINED__
typedef interface IIMAlignProject5 IIMAlignProject5;
#endif  /* __IIMAlignProject5_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "IIMAlignProject4.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifndef __IIMAlignProject5_INTERFACE_DEFINED__
#define __IIMAlignProject5_INTERFACE_DEFINED__

/* interface IIMAlignProject5 */
/* [helpstring][uuid][object] */


EXTERN_C const IID IID_IIMAlignProject5;

#if defined( __cplusplus ) && !defined( CINTERFACE )

MIDL_INTERFACE( "26E3A305-50C7-4934-8408-A7BE08302614" )
IIMAlignProject5 : public IIMAlignProject4
{
public:
    virtual HRESULT STDMETHODCALLTYPE ActiveDevicePositionDimensionsConvert(
        /* [out][in] */ SAFEARRAY * *pArrayDimensions_,
        /* [in] */ ECoordinateSystem sourceCoordSystem_,
        /* [in] */ ECoordinateSystem destinationCoordSystem_ ) = 0;

};

#else   /* C style interface */

typedef struct IIMAlignProject5Vtbl
{
    BEGIN_INTERFACE HRESULT ( STDMETHODCALLTYPE* QueryInterface )(
        IIMAlignProject5 * This,
        /* [in] */ REFIID riid,
        /* [annotation][iid_is][out] */
        __RPC__deref_out  void** ppvObject );

    ULONG( STDMETHODCALLTYPE * AddRef )(
        IIMAlignProject5 * This );

    ULONG( STDMETHODCALLTYPE * Release )(
        IIMAlignProject5 * This );

    HRESULT( STDMETHODCALLTYPE * CommandCenterCreate )(
        IIMAlignProject5 * This,
        /* [out] */ IIMCommandCenter** ppIIMCommandCenter_ );

    HRESULT( STDMETHODCALLTYPE * ImageCreateAsPlanarGrid )(
        IIMAlignProject5 * This,
        /* [out] */ IIMPlanarGrid** ppIIMPlanarGrid_,
        /* [full][unique][string][in] */ const OLECHAR* pImagesBaseName_,
        /* [full][unique][string][in] */ const OLECHAR* pSharedMatrixName_,
        /* [in] */ double maxEdgeLength_,
        /* [in] */ double step_,
        /* [in] */ double maxAngle_,
        /* [defaultvalue][in] */ VARIANT_BOOL isInteractive_ );

    HRESULT( STDMETHODCALLTYPE * ImageCreateAsLineScan )(
        IIMAlignProject5 * This,
        /* [out] */ IIMLineScan** ppIIMLineScan_,
        /* [full][unique][string][in] */ const OLECHAR* pImagesBaseName_,
        /* [full][unique][string][in] */ const OLECHAR* pSharedMatrixName_,
        /* [in] */ double maxEdgeLength_,
        /* [in] */ double step_,
        /* [in] */ double maxAngle_,
        /* [defaultvalue][in] */ VARIANT_BOOL isTestingMode_,
        /* [defaultvalue][in] */ VARIANT_BOOL isInteractive_ );

    HRESULT( STDMETHODCALLTYPE * ActiveDevicePositionMatrixGet )(
        IIMAlignProject5 * This,
        /* [out][in] */ SAFEARRAY** pTransMat_ );

    HRESULT( STDMETHODCALLTYPE * ActiveDevicePositionMatrixSet )(
        IIMAlignProject5 * This,
        /* [in] */ SAFEARRAY** pTransMat_ );

    HRESULT( STDMETHODCALLTYPE * ActiveDevicePositionCoordsConvert )(
        IIMAlignProject5 * This,
        /* [out][in] */ SAFEARRAY** pArrayCoords_,
        /* [in] */ ECoordinateSystem sourceCoordSystem_,
        /* [in] */ ECoordinateSystem destinationCoordSystem_ );

    HRESULT( STDMETHODCALLTYPE * ActiveDevicePositionNormalsConvert )(
        IIMAlignProject5 * This,
        /* [out][in] */ SAFEARRAY** pArrayNormals_,
        /* [in] */ ECoordinateSystem sourceCoordSystem_,
        /* [in] */ ECoordinateSystem destinationCoordSystem_ );

    HRESULT( STDMETHODCALLTYPE * ActiveDevicePositionDimensionsConvert )(
        IIMAlignProject5 * This,
        /* [out][in] */ SAFEARRAY** pArrayDimensions_,
        /* [in] */ ECoordinateSystem sourceCoordSystem_,
        /* [in] */ ECoordinateSystem destinationCoordSystem_ );

    END_INTERFACE
} IIMAlignProject5Vtbl;

interface IIMAlignProject5
{
    CONST_VTBL struct IIMAlignProject5Vtbl* lpVtbl;
};



#ifdef COBJMACROS


#define IIMAlignProject5_QueryInterface( This, riid, ppvObject )    \
    ( ( This )->lpVtbl->QueryInterface( This, riid, ppvObject ) )

#define IIMAlignProject5_AddRef( This )   \
    ( ( This )->lpVtbl->AddRef( This ) )

#define IIMAlignProject5_Release( This )  \
    ( ( This )->lpVtbl->Release( This ) )


#define IIMAlignProject5_CommandCenterCreate( This, ppIIMCommandCenter_ )  \
    ( ( This )->lpVtbl->CommandCenterCreate( This, ppIIMCommandCenter_ ) )


#define IIMAlignProject5_ImageCreateAsPlanarGrid( This, ppIIMPlanarGrid_, pImagesBaseName_, pSharedMatrixName_, maxEdgeLength_, step_, maxAngle_, isInteractive_ )   \
    ( ( This )->lpVtbl->ImageCreateAsPlanarGrid( This, ppIIMPlanarGrid_, pImagesBaseName_, pSharedMatrixName_, maxEdgeLength_, step_, maxAngle_, isInteractive_ ) )

#define IIMAlignProject5_ImageCreateAsLineScan( This, ppIIMLineScan_, pImagesBaseName_, pSharedMatrixName_, maxEdgeLength_, step_, maxAngle_, isTestingMode_, isInteractive_ )    \
    ( ( This )->lpVtbl->ImageCreateAsLineScan( This, ppIIMLineScan_, pImagesBaseName_, pSharedMatrixName_, maxEdgeLength_, step_, maxAngle_, isTestingMode_, isInteractive_ ) )


#define IIMAlignProject5_ActiveDevicePositionMatrixGet( This, pTransMat_ ) \
    ( ( This )->lpVtbl->ActiveDevicePositionMatrixGet( This, pTransMat_ ) )

#define IIMAlignProject5_ActiveDevicePositionMatrixSet( This, pTransMat_ ) \
    ( ( This )->lpVtbl->ActiveDevicePositionMatrixSet( This, pTransMat_ ) )


#define IIMAlignProject5_ActiveDevicePositionCoordsConvert( This, pArrayCoords_, sourceCoordSystem_, destinationCoordSystem_ )   \
    ( ( This )->lpVtbl->ActiveDevicePositionCoordsConvert( This, pArrayCoords_, sourceCoordSystem_, destinationCoordSystem_ ) )

#define IIMAlignProject5_ActiveDevicePositionNormalsConvert( This, pArrayNormals_, sourceCoordSystem_, destinationCoordSystem_ ) \
    ( ( This )->lpVtbl->ActiveDevicePositionNormalsConvert( This, pArrayNormals_, sourceCoordSystem_, destinationCoordSystem_ ) )


#define IIMAlignProject5_ActiveDevicePositionDimensionsConvert( This, pArrayDimensions_, sourceCoordSystem_, destinationCoordSystem_ )   \
    ( ( This )->lpVtbl->ActiveDevicePositionDimensionsConvert( This, pArrayDimensions_, sourceCoordSystem_, destinationCoordSystem_ ) )

#endif /* COBJMACROS */


#endif  /* C style interface */




#endif  /* __IIMAlignProject5_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long*, unsigned long, LPSAFEARRAY* );
unsigned char* __RPC_USER LPSAFEARRAY_UserMarshal(  unsigned long*, unsigned char*, LPSAFEARRAY* );
unsigned char* __RPC_USER LPSAFEARRAY_UserUnmarshal( unsigned long*, unsigned char*, LPSAFEARRAY* );
void __RPC_USER           LPSAFEARRAY_UserFree(     unsigned long*, LPSAFEARRAY* );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif // ifndef __IIMAlignProject5_h__
