﻿#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
///
///    \file     IUserInterface.h
///    \brief    IUserInterface class.
///
///    \copyright InnovMetric Logiciels Inc. Copyright ( C ) 2007 All Rights Reserved All rights reserved
///
/// ************************************************************************** */

// =================================================================================================
// ======================================= INCLUDED FILES ==========================================

#include "FnIUserInterface.h"

// =================================================================================================
// ========================================= NAMESPACES ============================================

namespace IM
{

// =================================================================================================
// ==================================== FORWARD DECLARATIONS =======================================

class IDialogZone;
class IScene;

// =================================================================================================
// ====================================== CONSTANTS, ENUMS =========================================

// =================================================================================================
// ================================= TYPES, CLASSES, STRUCTURES ====================================

////////////////////////////////////////////////////////////////////////////////////////////////////
///
///    \ingroup  IM_INTERFACES
///
///    \brief    Class giving the user an entry point on every object needed to manage the user interface.
///              You can retrieve a pointer to this class by calling UserInterfaceGet from IKernel.
///
/// ************************************************************************** */
class IUserInterface
{
public:
    // ---------------- Public Types  --------------------------------------------------------------

    // ---------------- Public Methods  ------------------------------------------------------------

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Default constructor.
    ///
    /// ************************************************************************** */
    IUserInterface() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Destructor.
    ///
    /// ************************************************************************** */
    virtual ~IUserInterface() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Returns the pointer to the Dialog Zone.
    ///
    ///    \return    Pointer to the Dialog Zone.
    ///
    /// ************************************************************************** */
    virtual IDialogZone* DialogZoneGet() const = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    ///    \brief    Returns the pointer to the currently used scene (3D Scene).
    ///
    ///    \return    Pointer to the currently used scene
    ///
    /// ************************************************************************** */
    virtual IScene* SceneGet() const = 0;

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
