﻿// =================================================================================================
// CCompanyNameComPlugin class.
//
// Copyright © InnovMetric Logiciels Inc. 2009 All Rights Reserved
// -------------------------------------------------------------------------------------------------

// =================================================================================================
// ======================================= INCLUDED FILES ==========================================

#include "stdafx.h"

#include "CCompanyNameCppPlugin.h"

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

// =================================================================================================
// Default constructor.
// -------------------------------------------------------------------------------------------------
CCompanyNameCppPlugin::CCompanyNameCppPlugin()
{
}

// =================================================================================================
// Destructor.
// -------------------------------------------------------------------------------------------------
CCompanyNameCppPlugin::~CCompanyNameCppPlugin()
{
}

// =================================================================================================
// Called when the plug-in is loaded by the host application.
// You may do whatever initialisation you want here.
//
// Return: Always true.
//         You could decide to return false to refuse the connection to the host application.
// -------------------------------------------------------------------------------------------------
bool CCompanyNameCppPlugin::Load()
{
    return true;
}

// =================================================================================================
// Called when the plug-in is unloaded by the host application.
// You may do whatever uninitialisation you want here.
//
// Return: Always true.
// -------------------------------------------------------------------------------------------------
bool CCompanyNameCppPlugin::Unload()
{
    return true;
}
