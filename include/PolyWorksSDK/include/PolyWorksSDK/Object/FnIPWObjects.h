﻿#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
///
///    \file     FnIPWObjects.h
///    \brief    Functions to be used with or to get access to IPWObjects interface.
///
///    \copyright InnovMetric Logiciels Inc. Copyright ( C ) 2007 All Rights Reserved All rights reserved
///
////////////////////////////////////////////////////////////////////////////////////////////////////

// =================================================================================================
// ======================================= INCLUDED FILES ==========================================

#include <PolyWorksSDK/Base/PolyWorksSDKApi.h>

// =================================================================================================
// ========================================= NAMESPACES ============================================

namespace IM
{

// =================================================================================================
// ==================================== FORWARD DECLARATIONS =======================================

class IPWObjects;

// =================================================================================================
// ====================================== CONSTANTS, ENUMS =========================================

// =================================================================================================
// ================================= TYPES, CLASSES, STRUCTURES ====================================

// =================================================================================================
// ===================================== FUNCTION PROTOTYPES =======================================

////////////////////////////////////////////////////////////////////////////////////////////////////
///
///    \ingroup  IM_FUNCTIONS
///
///    \brief    Gives a direct access to the module's IPWObjects interface.
///
///    \return    Pointer to the module's IPWObjects interface. NULL if there is an error or if the
///               PolyWorks SDK is not initialized.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
POLYWORKS_SDK_API IPWObjects* PWObjectsGet();

} // namespace IM
