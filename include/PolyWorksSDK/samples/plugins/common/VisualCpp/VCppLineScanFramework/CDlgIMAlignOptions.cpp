// =================================================================================================
//   Plug-in dialog base class implementation.
//
// Copyright © InnovMetric Softwares Inc. 2014 All Rights Reserved
// -------------------------------------------------------------------------------------------------

// =================================================================================================
// ======================================== INCLUDED FILES =========================================

#include "stdafx.h"

#include "CDlgIMAlignOptions.h"

#include "CCompanyNameScannerSettings.h"
#include "CIMPropertyGridCheckBoxProperty.h"
#include "CIMPropertyGridCtrl.h"
#include "CIMPropertyGridProperty.h"

// =================================================================================================
// ========================================= NAMESPACES ============================================

// =================================================================================================
// =========================================== MACROS ==============================================

// =================================================================================================
// ====================================== CONSTANTS, ENUMS =========================================

enum EPropertyPage
{
    E_PROPERTY_PAGE_GENERAL = 0,
    E_PROPERTY_PAGE_SURFACE_SCAN,
    E_PROPERTY_PAGE_FILTERING,

    E_PROPERTY_PAGE_NB
};

enum EPropertyValue
{
    // General
    E_PROPERTY_VALUE_USE_AUDIO_FEEDBACK,
    E_PROPERTY_VALUE_USE_AUTOMATIC_VIEWPOINT,
    E_PROPERTY_VALUE_DEVICE_VERTICAL_AXIS,
    E_PROPERTY_VALUE_STANDARD_ZOOM,
    E_PROPERTY_VALUE_USE_PARALLEL_PROCESSING,
    // Surface Scan
    // Filtering >> Filter scan lines
    E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES,
    E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_STANDARD_DEVIATION,
    E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_MAX_POINT_TO_POINT_DISTANCE,

    E_PROPERTY_VALUE_NB
};

// =================================================================================================
// ================================ TYPES, CLASSES, STRUCTURES =====================================

// =================================================================================================
// ================================== STATIC MEMBER VARIABLES ======================================

// =================================================================================================
// ===================================== GLOBAL VARIABLES ==========================================

// =================================================================================================
// ===================================== FUNCTION PROTOTYPES =======================================

// =================================================================================================
// ===================================== FUNCTION DEFINITIONS ======================================

IMPLEMENT_DYNAMIC( CDlgIMAlignOptions, CIMDlgOptionsBase )

// =================================================================================================
// Message map.
// -------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP( CDlgIMAlignOptions, CIMDlgOptionsBase )
END_MESSAGE_MAP()

// =================================================================================================
//   Ctor.
// -------------------------------------------------------------------------------------------------
CDlgIMAlignOptions::CDlgIMAlignOptions( CWnd* pParent_ /*=nullptr*/ )
: CIMDlgOptionsBase( IDD, pParent_ )
{
}

// =================================================================================================
//   Dtor.
// -------------------------------------------------------------------------------------------------
CDlgIMAlignOptions::~CDlgIMAlignOptions()
{
}

// =================================================================================================
//   Initialize the properties
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::PropertiesInit()
{
    // General
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL, IDS_PROPERTY_VALUE_AUDIO_FEEDBACK,      L"DIGITIZE LINE_SCAN AUDIO_FEEDBACK" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL, IDS_PROPERTY_VALUE_AUTOMATIC_VIEWPOINT, g_cmdAutoViewpointSet );
    std::vector< CPropertyComboValues > verticalAxisValues;
    verticalAxisValues.emplace_back( IDS_PROPERTY_VALUE_VERTICAL_AXIS_PLUS_X,  L"+X" );
    verticalAxisValues.emplace_back( IDS_PROPERTY_VALUE_VERTICAL_AXIS_MINUS_X, L"-X" );
    verticalAxisValues.emplace_back( IDS_PROPERTY_VALUE_VERTICAL_AXIS_PLUS_Y,  L"+Y" );
    verticalAxisValues.emplace_back( IDS_PROPERTY_VALUE_VERTICAL_AXIS_MINUS_Y, L"-Y" );
    verticalAxisValues.emplace_back( IDS_PROPERTY_VALUE_VERTICAL_AXIS_PLUS_Z,  L"+Z" );
    verticalAxisValues.emplace_back( IDS_PROPERTY_VALUE_VERTICAL_AXIS_MINUS_Z, L"-Z" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_STRING, IDS_PROPERTY_VALUE_AUTO_VIEW_POINT_DEVICE_VERTICAL_AXIS,   g_cmdAutoViewpointVerticalAxisSet, verticalAxisValues );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_LONG,   IDS_PROPERTY_VALUE_AUTO_VIEW_POINT_SCAN_LINE_CLOSEUP_ZOOM, g_cmdAutoViewpointCloseUpZoomSet );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_PARALLEL_PROCESSING,                    L"DIGITIZE LINE_SCAN PARALLEL_PROCESSING" );

    // Surface Scan
    // Filtering >> Filter scan lines
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_FILTER_SCAN_LINES,                  L"DIGITIZE LINE_SCAN SCAN_LINE_FILTER" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_FILTER_STANDARD_DEVIATION,          L"DIGITIZE LINE_SCAN SCAN_LINE_FILTER STANDARD_DEVIATION" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_FILTER_MAX_POINT_TO_POINT_DISTANCE, L"DIGITIZE LINE_SCAN SCAN_LINE_FILTER MAX_POINT_TO_POINT_DIST" );
}

// =================================================================================================
//   Initialize the treeview
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::TreeViewInit()
{
    HTREEITEM hGeneral     = PropertyPageAdd( E_PROPERTY_PAGE_GENERAL,      IDS_PROPERTY_VALUE_PAGE_GENERAL );
    HTREEITEM hSurfaceScan = PropertyPageAdd( E_PROPERTY_PAGE_SURFACE_SCAN, IDS_PROPERTY_VALUE_PAGE_SURFACE_SCAN );
    PropertyPageAdd( E_PROPERTY_PAGE_FILTERING, IDS_PROPERTY_VALUE_PAGE_FILTERING, hSurfaceScan );

    m_pPropertyTree->Expand( hSurfaceScan, TVE_EXPAND );

    // Select the first item
    m_pPropertyTree->SelectItem( hGeneral );
}

// =================================================================================================
//   Initialize the property grid
//
// Parameter : selectedItem_ : Selected item of the treeview
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::PropertyGridInit( HTREEITEM selectedItem_ )
{
    m_pPropertyGridCtrl->RemoveAll();

    // Set the witdh of the first column
    HDITEM hdItem;
    hdItem.mask = HDI_WIDTH;
    hdItem.cxy  = 300;
    m_pPropertyGridCtrl->GetHeaderCtrl().SetItem( 0, &hdItem );

    auto propertyPageItr = m_propertyPageMap.find( selectedItem_ );
    if ( propertyPageItr != m_propertyPageMap.end() )
    {
        switch ( propertyPageItr->second )
        {
            case E_PROPERTY_PAGE_GENERAL:
                PropertyGridGeneralInit();
                break;
            case E_PROPERTY_PAGE_SURFACE_SCAN:
                PropertyGridSurfaceScanInit();
                break;
            case E_PROPERTY_PAGE_FILTERING:
                PropertyGridFilteringInit();
                break;
            default: // Unsupported
                ASSERT( FALSE );
                m_pPropertyGridCtrl->Invalidate();
                break;
        }
    }
}

// =================================================================================================
//   Initialize the General property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::PropertyGridGeneralInit()
{
    // Utilities
    // ---------
    CIMPropertyGridProperty* pUtilitiesGroup = MakePropertyGroup( L"Utilities" );
    m_pPropertyGridCtrl->AddProperty( pUtilitiesGroup );
    pUtilitiesGroup->AddSubItem( MakePropertyValue< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_USE_AUDIO_FEEDBACK ) );

    // Automatic viewpoint
    // -------------------
    auto* pUseAutomaticViewpointGroup =
        MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_USE_AUTOMATIC_VIEWPOINT );
    m_pPropertyGridCtrl->AddProperty( pUseAutomaticViewpointGroup );
    pUseAutomaticViewpointGroup->AddSubItem( MakePropertyComboValue( E_PROPERTY_VALUE_DEVICE_VERTICAL_AXIS, FALSE ) );
    pUseAutomaticViewpointGroup->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_STANDARD_ZOOM ) );

    // Data processing
    // ---------------
    CIMPropertyGridProperty* pDataProcessingGroup = MakePropertyGroup( L"Data processing" );
    m_pPropertyGridCtrl->AddProperty( pDataProcessingGroup );

    pDataProcessingGroup->AddSubItem( MakePropertyValue< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_USE_PARALLEL_PROCESSING ) );

    m_pPropertyGridCtrl->ExpandAll();

    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_USE_AUTOMATIC_VIEWPOINT );
}

// =================================================================================================
//   Initialize the Surface Scan property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::PropertyGridSurfaceScanInit()
{
    m_pPropertyGridCtrl->AddProperty( new CIMPropertyGridProperty( L"Select a subcategory" ) );
}

// =================================================================================================
//   Initialize the Filtering property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::PropertyGridFilteringInit()
{
    // Filter scan lines
    // -----------------
    auto* pFilterScanLines = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES );
    m_pPropertyGridCtrl->AddProperty( pFilterScanLines );

    pFilterScanLines->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_STANDARD_DEVIATION ) );

    CIMPropertyGridProperty* pFilterCloudPoints = MakePropertyGroup( L"Points cloud" );
    pFilterScanLines->AddSubItem( pFilterCloudPoints );

    pFilterCloudPoints->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_MAX_POINT_TO_POINT_DISTANCE ) );

    m_pPropertyGridCtrl->ExpandAll();
}

// =================================================================================================
//   Update the enable state of a property.
//
// Parameter : propertyData_ : Property data ID
// Parameter : enable_       : TRUE to enable, FALSE otherwise
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::PropertyEnableUpdate( DWORD propertyData_, BOOL enable_ )
{
    __super::PropertyEnableUpdate( propertyData_, enable_ );

    switch ( propertyData_ )
    {
        case E_PROPERTY_VALUE_USE_AUTOMATIC_VIEWPOINT:
            PropertyEnable( E_PROPERTY_VALUE_DEVICE_VERTICAL_AXIS, enable_ );
            PropertyEnable( E_PROPERTY_VALUE_STANDARD_ZOOM,        enable_ );
            break;
        case E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES:
            PropertyEnable( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_STANDARD_DEVIATION,          enable_ );
            PropertyEnable( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_MAX_POINT_TO_POINT_DISTANCE, enable_ );
            break;
        default: // Unsupported
            ASSERT( FALSE );
            break;
    }
}

// =================================================================================================
//   Obtain the X position of the window.
//
// Return : Position
// -------------------------------------------------------------------------------------------------
long CDlgIMAlignOptions::WindowPositionXGet()
{
    return theCompanyNameScannerSettings().IMAOptionsWindowPositionXGet();
}


// =================================================================================================
//   Set the X position of the window.
//
// Parameter : position_ : Position
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::WindowPositionXSet( long position_ )
{
    theCompanyNameScannerSettings().IMAOptionsWindowPositionXSet( position_ );
}


// =================================================================================================
//   Obtain the Y position of the window.
//
// Return : Position
// -------------------------------------------------------------------------------------------------
long CDlgIMAlignOptions::WindowPositionYGet()
{
    return theCompanyNameScannerSettings().IMAOptionsWindowPositionYGet();
}


// =================================================================================================
//   Sets the Y position of the window.
//
// Parameter : position_ : Position
// -------------------------------------------------------------------------------------------------
void CDlgIMAlignOptions::WindowPositionYSet( long position_ )
{
    theCompanyNameScannerSettings().IMAOptionsWindowPositionYSet( position_ );
}
