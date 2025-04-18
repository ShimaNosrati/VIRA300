﻿#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
///
///    \file     ILineScanPass.h
///    \brief    ILineScanPass class.
///
///    \copyright InnovMetric Logiciels Inc. Copyright ( C ) 2007 All Rights Reserved All rights reserved
///
////////////////////////////////////////////////////////////////////////////////////////////////////

// =================================================================================================
// ======================================= INCLUDED FILES ==========================================

#include <PolyWorksSDK/Object/CLineScanLineConstIterator.h>
#include <PolyWorksSDK/Object/CLineScanLineIterator.h>

// =================================================================================================
// ========================================= NAMESPACES ============================================

namespace IM
{

// =================================================================================================
// ==================================== FORWARD DECLARATIONS =======================================

// =================================================================================================
// ====================================== CONSTANTS, ENUMS =========================================

// =================================================================================================
// ================================= TYPES, CLASSES, STRUCTURES ====================================

////////////////////////////////////////////////////////////////////////////////////////////////////
///
///    \ingroup  IM_INTERFACES
///
///    \brief    Interface giving access to a line scan pass information. You can get access to ILineScanPass
///              objects by calling the iterators from ILineScan.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class ILineScanPass
{
public:
    // ---------------- Public Types  --------------------------------------------------------------

    // ---------------- Public Methods  ------------------------------------------------------------

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Creates a new ILineScanPass object.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ILineScanPass() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Destructor.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~ILineScanPass() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Returns an iterator to the first line of the current line scan pass object.
    ///
    ///    \return    Iterator to the first line of the current line scan pass object.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CLineScanLineIterator      LineScanLineBegin()       = 0;
    virtual CLineScanLineConstIterator LineScanLineBegin() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Returns an iterator to the end of the lines collection.
    ///
    ///    \return    Iterator to the end of the lines collection.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CLineScanLineIterator      LineScanLineEnd()       = 0;
    virtual CLineScanLineConstIterator LineScanLineEnd() const = 0;

protected:
    // ---------------- Protected Methods ----------------------------------------------------------

    // ---------------- Protected Member Variables -------------------------------------------------

private:
    // ---------------- Private Methods ------------------------------------------------------------

    // ---------------- Private Member Variables ---------------------------------------------------

};

// =================================================================================================
// ===================================== FUNCTION PROTOTYPES =======================================

} // namespace IM
