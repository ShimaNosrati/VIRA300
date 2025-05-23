﻿// =================================================================================================
// Implementation of the class for COM command parameters enumeration
//
// Copyright © InnovMetric Logiciels Inc. 2009 All Rights Reserved
// -------------------------------------------------------------------------------------------------

// =================================================================================================
// ======================================= INCLUDED FILES ==========================================

#include "CComCommandParameterEnumImpl.h"

// =================================================================================================
// ========================================= NAMESPACES ============================================

// =================================================================================================
// =========================================== MACROS ==============================================

// =================================================================================================
// ====================================== CONSTANTS, ENUMS =========================================

// =================================================================================================
// ================================ TYPES, CLASSES, STRUCTURES =====================================

// =================================================================================================
// ================================== STATIC MEMBER VARIABLES ======================================

// =================================================================================================
// ===================================== GLOBAL VARIABLES ==========================================

// =================================================================================================
// =================================== FUNCTIONS PROTOTYPES ========================================

// =================================================================================================
// =================================== FUNCTIONS DEFINITIONS =======================================

/* *****************************************************************************
 *                           IIMCommandParameterEnum Interface
 * -------------------------------------------------------------------------- */

// =============================================================================
// See CComCommandParameterEnum::ParamsGetNb
// -----------------------------------------------------------------------------
STDMETHODIMP CComCommandParameterEnumImpl::ParamsGetNb(
    /* [retval][out] */ long* pParamNb_ )
{
    if ( pParamNb_ != nullptr )
    {
        *pParamNb_ = static_cast< long >( m_parameters.size() );
        return S_OK;
    }
    return S_FALSE;
}

// =============================================================================
// See CComCommandParameterEnum::ParamGet
// -----------------------------------------------------------------------------
STDMETHODIMP CComCommandParameterEnumImpl::ParamGet(
    /* [in] */ long                   number_,
    /* [out] */ IIMCommandParameter** pIIMCommandParameter_ )
{
    if ( pIIMCommandParameter_ != nullptr )
    {
        *pIIMCommandParameter_ = nullptr;

        size_t numberToUse = number_;
        if ( ( numberToUse >= 0 ) && ( numberToUse < m_parameters.size() ) )
        {
            *pIIMCommandParameter_ = m_parameters[ numberToUse ];
            ( *pIIMCommandParameter_ )->AddRef();

            return S_OK;
        }
    }

    return S_FALSE;
}

/* *****************************************************************************
 *              CComCommandParameterEnumImpl specific methods
 * -------------------------------------------------------------------------- */

// =============================================================================
// Constructor
// -----------------------------------------------------------------------------
CComCommandParameterEnumImpl::CComCommandParameterEnumImpl()
{
}

// =============================================================================
// Destructor
// -----------------------------------------------------------------------------
CComCommandParameterEnumImpl::~CComCommandParameterEnumImpl()
{
    while ( !m_parameters.empty() )
    {
        m_parameters.pop_back();
    }
}

// =============================================================================
// Add an argument to the enumeration
//
// Parameter: pCommandParameter_ : Argument to add
// -----------------------------------------------------------------------------
void CComCommandParameterEnumImpl::CommandParameterAdd( const CComPtr< IIMCommandParameter >& pCommandParameter_ )
{
    m_parameters.push_back( pCommandParameter_ );
}
