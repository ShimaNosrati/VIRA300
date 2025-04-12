// =================================================================================================
//   Plug-in dialog base class implementation.
//
// Copyright © InnovMetric Softwares Inc. 2014 All Rights Reserved
// -------------------------------------------------------------------------------------------------

// =================================================================================================
// ======================================== INCLUDED FILES =========================================

#include "stdafx.h"

#include "CDlgIMInspectOptions.h"

#include "CCompanyNameScannerSettings.h"
#include "CIMPropertyGridCheckBoxProperty.h"
#include "CIMPropertyGridColorProperty.h"
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
    E_PROPERTY_PAGE_REAL_TIME_QUALITY_MESHING,
    E_PROPERTY_PAGE_POLYGONAL_MODELS,
    E_PROPERTY_PAGE_QUALITY_METRICS,
    E_PROPERTY_PAGE_FILTERING,
    E_PROPERTY_PAGE_HOLE_BOUNDARY_SCAN,
    E_PROPERTY_PAGE_SHARP_EDGE_SCAN,

    E_PROPERTY_PAGE_NB
};

enum EPropertyValue
{
    // General
    E_PROPERTY_VALUE_USE_AUDIO_FEEDBACK,
    E_PROPERTY_VALUE_USE_AUTOMATIC_VIEWPOINT,
    E_PROPERTY_VALUE_DEVICE_VERTICAL_AXIS,
    E_PROPERTY_VALUE_STANDARD_ZOOM,
    E_PROPERTY_VALUE_FEATURE_SCANNING_GUIDANCE_ZOOM,
    E_PROPERTY_VALUE_USE_PARALLEL_PROCESSING,
    E_PROPERTY_VALUE_USE_PRIORITIZE_ACQUISITION_SPEED,
    E_PROPERTY_VALUE_MESHING_SPEED,
    E_PROPERTY_VALUE_USE_FEATURE_SCANNING_GUIDANCE,
    E_PROPERTY_VALUE_SURFACE_HIGHLIGHT_COLOR,
    E_PROPERTY_VALUE_BOUNDARY_HIGHLIGHT_COLOR,

    // Surface Scan
    E_PROPERTY_VALUE_SPLIT_ZIGZAG_SCAN_PASSES,
    E_PROPERTY_VALUE_USE_EXTRACT_NORMAL_VECTORS,
    E_PROPERTY_VALUE_MIN_SEARCH_DISTANCE,
    E_PROPERTY_VALUE_MAX_SEARCH_DISTANCE,

    // Surface Scan >> Real-Time Quality Meshing
    E_PROPERTY_VALUE_SAMPLING_STEP,
    E_PROPERTY_VALUE_MAX_EDGE_LENGTH,
    E_PROPERTY_VALUE_MAX_ANGLE,
    E_PROPERTY_VALUE_RTM_MAX_DISTANCE,
    E_PROPERTY_VALUE_RTM_NUMBER_OF_BLENDING_STEPS,

    // Surface Scan >> Real-Time Quality Meshing >> Polygonal Models
    E_PROPERTY_VALUE_RTM_SMOOTH,
    E_PROPERTY_VALUE_RTM_SMOOTH_LEVEL,
    E_PROPERTY_VALUE_RTM_SMOOTH_CUSTOM_LEVEL_RADIUS,
    E_PROPERTY_VALUE_RTM_SMOOTH_CONSTRAIN_DISPLACEMENT,
    E_PROPERTY_VALUE_RTM_SMOOTH_MAX_DISPLACEMENT,
    E_PROPERTY_VALUE_RTM_SMOOTH_PRESERVE_FEATURES,
    E_PROPERTY_VALUE_RTM_REDUCE,
    E_PROPERTY_VALUE_RTM_REDUCE_LEVEL,
    E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_METHOD,
    E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_TOLERANCE,
    E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_REMAINING_PERCENT,
    E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_REMAINING_TRIANGLES,
    E_PROPERTY_VALUE_RTM_REDUCE_CONSTRAIN_EDGE_LENGTH,
    E_PROPERTY_VALUE_RTM_REDUCE_CONSTRAIN_MAX_EDGE_LENGTH,
    E_PROPERTY_VALUE_RTM_REDUCE_PREREDUCTION_TOLERANCE,

    // Surface Scan >> Real-Time Quality Meshing >> Quality Metrics
    E_PROPERTY_VALUE_RTM_DETECT_MISALIGNED_SCAN_PASSES,
    E_PROPERTY_VALUE_RTM_MAX_AVERAGE_DEVIATION,
    E_PROPERTY_VALUE_RTM_BEHAVIOR_WHEN_MISALIGNED,
    E_PROPERTY_VALUE_RTM_HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE,
    E_PROPERTY_VALUE_RTM_HIGHLIGHT_MAX_ANGLE,
    E_PROPERTY_VALUE_RTM_HIGHLIGHT_MAX_ANGLE_COLOR,
    E_PROPERTY_VALUE_RTM_LOW_SCAN_DENSITY_FOR_CURVATURE,
    E_PROPERTY_VALUE_RTM_MAX_DEVIATION_SURFACE,
    E_PROPERTY_VALUE_RTM_MAX_DEVIATION_SURFACE_COLOR,
    E_PROPERTY_VALUE_RTM_HIGH_NOISE_LEVEL,
    E_PROPERTY_VALUE_RTM_STANDARD_DEVIATION_THRESHOLD,
    E_PROPERTY_VALUE_RTM_STANDARD_DEVIATION_THRESHOLD_COLOR,

    // Filtering >> Filter scan lines
    E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES,
    E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_STANDARD_DEVIATION,
    E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_MAX_POINT_TO_POINT_DISTANCE,

    // Filtering >> Clipping plane
    E_PROPERTY_VALUE_FILTERING_CLIPPING_PLANE_REJECTION_DIST,

    // Surface and Boundary Scan
    E_PROPERTY_VALUE_MIN_HOLE_WIDTH,
    E_PROPERTY_VALUE_EXTERNAL_BOUNDARY_DETECTION,

    // Sharp Edge Scan
    E_PROPERTY_VALUE_EDGE_MAX_POINT_TO_POINT_DISTANCE,
    E_PROPERTY_VALUE_EDGE_MIN_ANGLE,

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

IMPLEMENT_DYNAMIC( CDlgIMInspectOptions, CIMDlgOptionsBase )

// =================================================================================================
// Message map.
// -------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP( CDlgIMInspectOptions, CIMDlgOptionsBase )
END_MESSAGE_MAP()

// =================================================================================================
//   Ctor.
// -------------------------------------------------------------------------------------------------
CDlgIMInspectOptions::CDlgIMInspectOptions( CWnd* pParent_ /*=nullptr*/ )
: CIMDlgOptionsBase( IDD, pParent_ )
{
}

// =================================================================================================
//   Dtor.
// -------------------------------------------------------------------------------------------------
CDlgIMInspectOptions::~CDlgIMInspectOptions()
{
}

// =================================================================================================
//   Initialize the properties
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertiesInit()
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
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_STRING, IDS_PROPERTY_VALUE_AUTO_VIEW_POINT_DEVICE_VERTICAL_AXIS,            g_cmdAutoViewpointVerticalAxisSet, verticalAxisValues );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_LONG,   IDS_PROPERTY_VALUE_AUTO_VIEW_POINT_STANDARD_ZOOM_PERCENTAGE,        g_cmdAutoViewpointCloseUpZoomSet );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_LONG,   IDS_PROPERTY_VALUE_AUTO_VIEW_POINT_FEATURE_SCANNING_GUIDANCE,       L"DIGITIZE DISPLAY AUTOMATIC_VIEWPOINT CLOSE_UP SCAN_LINE_ZOOM FEATURE_SCANNING_GUIDANCE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_PARALLEL_PROCESSING,                             L"DIGITIZE LINE_SCAN PARALLEL_PROCESSING" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_PRIORITIZE_ACQUISITION_SPEED_OVER_MESHING_SPEED, L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING PRIORITIZE_ACQUISITION_SPEED" );
    std::vector< CPropertyComboValues > meshingSpeedValues;
    meshingSpeedValues.emplace_back( IDS_PROPERTY_VALUE_MESHING_SPEED_LOW,    L"Low" );
    meshingSpeedValues.emplace_back( IDS_PROPERTY_VALUE_MESHING_SPEED_MEDIUM, L"Medium" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_STRING, IDS_PROPERTY_VALUE_MESHING_SPEED,             L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING PRIORITIZE_ACQUISITION_SPEED MESHING_SPEED", meshingSpeedValues );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_FEATURE_SCANNING_GUIDANCE, L"DIGITIZE LINE_SCAN FEATURE_SCANNING_GUIDANCE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_COLOR,  IDS_PROPERTY_VALUE_SURFACE_HIGHLIGHT_COLOR,   L"DIGITIZE LINE_SCAN FEATURE_SCANNING_GUIDANCE HIGHLIGHT_COLOR SURFACE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_COLOR,  IDS_PROPERTY_VALUE_BOUNDARY_HIGHLIGHT_COLOR,  L"DIGITIZE LINE_SCAN FEATURE_SCANNING_GUIDANCE HIGHLIGHT_COLOR BOUNDARY" );

    // Surface Scan
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_SURFACE_SPLIT_ZIGZAG_SCAN_PASSES, L"DIGITIZE DEVICE SCAN SURFACE SPLIT_ZIGZAG_SCAN_PASSES" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_SURFACE_EXTRACT_NORMAL_VECTORS,   L"DIGITIZE DEVICE SCAN SURFACE EXTRACT_NORMAL_VECTORS" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_SURFACE_MIN_SEARCH_DISTANCE,      L"DIGITIZE DEVICE SCAN SURFACE EXTRACT_NORMAL_VECTORS MIN_SEARCH_DISTANCE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_SURFACE_MAX_SEARCH_DISTANCE,      L"DIGITIZE DEVICE SCAN SURFACE EXTRACT_NORMAL_VECTORS MAX_SEARCH_DISTANCE" );

    // Surface Scan >> Real-Time Quality Meshing
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_MESHING_SAMPLING_STEP,    L"DATA SURFACE OPTIONS SCAN MESHING SAMPLING_STEP" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_MESHING_MAX_EDGE_LENGTH,  L"DATA SURFACE OPTIONS SCAN MESHING MAX_EDGE_LENGTH" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_MESHING_MAX_ANGLE,        L"DATA OPTIONS SCAN MESHING MAX_ANGLE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_MESHING_MAX_DISTANCE,     L"DATA OPTIONS SCAN MESHING SCAN_PASS_MERGING MAX_DISTANCE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_LONG,   IDS_PROPERTY_VALUE_NUMBER_OF_BLENDING_STEPS, L"DATA OPTIONS SCAN MESHING SCAN_PASS_MERGING NB_BLENDING_STEPS" );

    // Surface Scan >> Real-Time Quality Meshing >> Polygonal Models
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL, IDS_PROPERTY_VALUE_MESHING_SMOOTH, L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING SMOOTH" );
    std::vector< CPropertyComboValues > smoothLevelValues;
    smoothLevelValues.emplace_back( IDS_PROPERTY_VALUE_MESHING_SMOOTH_LEVEL_MINIMUM, L"Minimum" );
    smoothLevelValues.emplace_back( IDS_PROPERTY_VALUE_MESHING_SMOOTH_LEVEL_LOW,     L"Low" );
    smoothLevelValues.emplace_back( IDS_PROPERTY_VALUE_MESHING_SMOOTH_LEVEL_MEDIUM,  L"Medium" );
    smoothLevelValues.emplace_back( IDS_PROPERTY_VALUE_MESHING_SMOOTH_LEVEL_HIGH,    L"High" );
    smoothLevelValues.emplace_back( IDS_PROPERTY_VALUE_MESHING_SMOOTH_LEVEL_CUSTOM,  L"Custom" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_STRING, IDS_PROPERTY_VALUE_MESHING_SMOOTH_LEVEL,                  L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING SMOOTH LEVEL", smoothLevelValues );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_MESHING_SMOOTH_CUSTOM_LEVEL_RADIUS,    L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING SMOOTH LEVEL CUSTOM RADIUS" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_MESHING_SMOOTH_CONSTRAIN_DISPLACEMENT, L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING SMOOTH USE_MAX_DISPLACEMENT" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_MESHING_SMOOTH_MAX_DISPLACEMENT,       L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING SMOOTH MAX_DISPLACEMENT" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_MESHING_SMOOTH_PRESERVE_FEATURES,      L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING SMOOTH PRESERVE_FEATURES" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_MESHING_REDUCE,                        L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE" );
    std::vector< CPropertyComboValues > reduceLevelValues;
    reduceLevelValues.emplace_back( IDS_PROPERTY_VALUE_REDUCE_SMOOTH_LEVEL_LOW,    L"Low" );
    reduceLevelValues.emplace_back( IDS_PROPERTY_VALUE_REDUCE_SMOOTH_LEVEL_MEDIUM, L"Medium" );
    reduceLevelValues.emplace_back( IDS_PROPERTY_VALUE_REDUCE_SMOOTH_LEVEL_HIGH,   L"High" );
    reduceLevelValues.emplace_back( IDS_PROPERTY_VALUE_REDUCE_SMOOTH_LEVEL_CUSTOM, L"Custom" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_STRING, IDS_PROPERTY_VALUE_REDUCE_SMOOTH_LEVEL, L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE LEVEL", reduceLevelValues );
    std::vector< CPropertyComboValues > reduceMethods;
    reduceMethods.emplace_back( IDS_PROPERTY_VALUE_REDUCE_METHOD_TOLERANCE,               L"Tolerance" );
    reduceMethods.emplace_back( IDS_PROPERTY_VALUE_REDUCE_METHOD_PERCENTAGE_OF_TRIANGLES, L"Percentage of Triangles" );
    reduceMethods.emplace_back( IDS_PROPERTY_VALUE_REDUCE_METHOD_NUMBER_OF_TRIANGLES,     L"Number of Triangles" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_STRING, IDS_PROPERTY_VALUE_REDUCE_LEVEL_CUSTOM_METHOD,               L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE LEVEL CUSTOM METHOD", reduceMethods );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_REDUCE_LEVEL_CUSTOM_TOLERANCE,            L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE LEVEL CUSTOM TOLERANCE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_REDUCE_LEVEL_CUSTOM_REMAINING_PERCENTAGE, L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE LEVEL CUSTOM REMAINING_PERCENTAGE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_LONG,   IDS_PROPERTY_VALUE_REDUCE_LEVEL_CUSTOM_REMAINING_TRIANGLES,  L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE LEVEL CUSTOM REMAINING_TRIANGLES" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_REDUCE_LEVEL_CONSTRAIN_EDGE_LENGTH,       L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE USE_MAX_EDGE_LENGTH" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_REDUCE_LEVEL__MAX_EDGE_LENGTH,            L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE MAX_EDGE_LENGTH" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_REDUCE_LEVEL_PREREDUCTION_TOLERANCE,      L"DATA POLYGONAL_MODEL OPTIONS SCAN MESHING REDUCE PREREDUCTION TOLERANCE" );

    // Surface Scan >> Real-Time Quality Meshing >> Quality Metrics
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_QUALITY_METRICS_DETECT_MISALIGNED_SCAN_PASSES, L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS DETECT_MISALIGNED_SCAN_PASSES" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_QUALITY_METRICS_DETECT_MAX_AVERAGE_DEVIATION,  L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS DETECT_MISALIGNED_SCAN_PASSES MAX_AVERAGE_DEVIATION" );
    std::vector< CPropertyComboValues > misalignedBehaviorValues;
    misalignedBehaviorValues.emplace_back( IDS_PROPERTY_VALUE_RTM_BEHAVIOR_WHEN_MISALIGNED_CONFIRM_PASS_DELETION, L"Confirm Pass Deletion" );
    misalignedBehaviorValues.emplace_back( IDS_PROPERTY_VALUE_RTM_BEHAVIOR_WHEN_MISALIGNED_DELETE_PASS,           L"Delete Pass" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_STRING, IDS_PROPERTY_VALUE_QUALITY_METRICS_BEHAVIOR_WHEN_MISALIGNED,                           L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS DETECT_MISALIGNED_SCAN_PASSES BEHAVIOR", misalignedBehaviorValues );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_QUALITY_METRICS_HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE,               L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_QUALITY_METRICS_MAX_ANGLE,                                          L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE MAX_ANGLE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_COLOR,  IDS_PROPERTY_VALUE_QUALITY_METRICS_NORMAL_ANGLE_COLOR,                                 L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE COLOR" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_QUALITY_METRICS_LOW_SCAN_DENSITY_FOR_MESH_CURVATURE,                L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES LOW_SCAN_DENSITY_FOR_MESH_CURVATURE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_QUALITY_METRICS_LOW_SCAN_DENSITY_MAX_DEVIATION_TO_SURFACE,          L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES LOW_SCAN_DENSITY_FOR_MESH_CURVATURE MAX_DEVIATION_TO_SURFACE" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_COLOR,  IDS_PROPERTY_VALUE_QUALITY_METRICS_LOW_SCAN_DENSITY_COLOR,                             L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES LOW_SCAN_DENSITY_FOR_MESH_CURVATURE COLOR" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_QUALITY_METRICS_LOW_QUALITY_TRIANGLES_HIGH_NOISE_LEVEL,             L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES HIGH_NOISE_LEVEL" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_QUALITY_METRICS_LOW_QUALITY_TRIANGLES_STANDARD_DEVIATION_THRESHOLD, L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES HIGH_NOISE_LEVEL THRESHOLD" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_COLOR,  IDS_PROPERTY_VALUE_QUALITY_METRICS_LOW_QUALITY_TRIANGLES_COLOR,                        L"DIGITIZE LINE_SCAN SURFACE REAL_TIME_QUALITY_MESHING QUALITY_METRICS HIGHLIGHT_LOW_QUALITY_TRIANGLES HIGH_NOISE_LEVEL COLOR" );

    // Filtering >> Filter scan lines
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_FILTER_SCAN_LINES,                  L"DIGITIZE LINE_SCAN SCAN_LINE_FILTER" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_FILTER_STANDARD_DEVIATION,          L"DIGITIZE LINE_SCAN SCAN_LINE_FILTER STANDARD_DEVIATION" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_FILTER_MAX_POINT_TO_POINT_DISTANCE, L"DIGITIZE LINE_SCAN SCAN_LINE_FILTER MAX_POINT_TO_POINT_DIST" );

    // Filtering >> Clipping plane
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_CLIPPING_PLACE_POINT_REJECTION_DISTANCE_ABOVE_PLANE, L"DIGITIZE LINE_SCAN SURFACE CLIPPING_PLANE POINT_REJECTION_DISTANCE" );

    // Surface and Boundary Scan
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_SURFACE_AND_BOUNDARY_MIN_HOLE_WIDTH,              L"DIGITIZE DEVICE SCAN SURFACE_AND_BOUNDARY INTERNAL_BOUNDARIES MIN_HOLE_WIDTH" );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_BOOL,   IDS_PROPERTY_VALUE_SURFACE_AND_BOUNDARY_EXTERNAL_BOUNDARY_DETECTION, L"DIGITIZE DEVICE SCAN SURFACE_AND_BOUNDARY EXTERNAL_BOUNDARIES" );

    // Sharp Edge Scan
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_SHARP_EDGE_MAX_POINT_TO_POINT_DISTANCE, g_cmdSharpEdgeMaxPointToPointDistSet );
    m_propertyValues.emplace_back( E_PROPERTY_TYPE_DOUBLE, IDS_PROPERTY_VALUE_SHARP_EDGE_MIN_ANGLE,                   g_cmdSharpEdgeMinAngleSet );
}

// =================================================================================================
//   Initialize the treeview
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::TreeViewInit()
{
    HTREEITEM hGeneral     = PropertyPageAdd( E_PROPERTY_PAGE_GENERAL,                   IDS_PROPERTY_VALUE_PAGE_GENERAL );
    HTREEITEM hSurfaceScan = PropertyPageAdd( E_PROPERTY_PAGE_SURFACE_SCAN, IDS_PROPERTY_VALUE_PAGE_SURFACE_SCAN );
    HTREEITEM hRTM         = PropertyPageAdd( E_PROPERTY_PAGE_REAL_TIME_QUALITY_MESHING, IDS_PROPERTY_VALUE_PAGE_REALTIME_QUALITY_MESHING, hSurfaceScan );
    PropertyPageAdd( E_PROPERTY_PAGE_POLYGONAL_MODELS,   IDS_PROPERTY_VALUE_PAGE_POLYGONAL_MODELS, hRTM );
    PropertyPageAdd( E_PROPERTY_PAGE_QUALITY_METRICS,    IDS_PROPERTY_VALUE_PAGE_QUALITY_METRICS,  hRTM );
    PropertyPageAdd( E_PROPERTY_PAGE_FILTERING,          IDS_PROPERTY_VALUE_PAGE_FILTERING,        hSurfaceScan );
    PropertyPageAdd( E_PROPERTY_PAGE_HOLE_BOUNDARY_SCAN, IDS_PROPERTY_VALUE_PAGE_HOLE_BOUNDARY_SCAN );
    PropertyPageAdd( E_PROPERTY_PAGE_SHARP_EDGE_SCAN,    IDS_PROPERTY_VALUE_PAGE_SHARP_EDGE_SCAN );

    m_pPropertyTree->Expand( hSurfaceScan, TVE_EXPAND );
    m_pPropertyTree->Expand( hRTM,         TVE_EXPAND );

    // Select the first item
    m_pPropertyTree->SelectItem( hGeneral );
}

// =================================================================================================
//   Initialize the property grid
//
// Parameter : selectedItem_ : Selected item of the treeview
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridInit( HTREEITEM selectedItem_ )
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
            case E_PROPERTY_PAGE_REAL_TIME_QUALITY_MESHING:
                PropertyGridRealTimeQualityMeshingInit();
                break;
            case E_PROPERTY_PAGE_POLYGONAL_MODELS:
                PropertyGridRTMPolygonalModelsInit();
                break;
            case E_PROPERTY_PAGE_QUALITY_METRICS:
                PropertyGridRTMQualityMetricsInit();
                break;
            case E_PROPERTY_PAGE_FILTERING:
                PropertyGridFilteringInit();
                break;
            case E_PROPERTY_PAGE_HOLE_BOUNDARY_SCAN:
                PropertyGridHoleBoundaryScanInit();
                break;
            case E_PROPERTY_PAGE_SHARP_EDGE_SCAN:
                PropertyGridSharpEdgeScanInit();
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
void CDlgIMInspectOptions::PropertyGridGeneralInit()
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

    // Scan line close-up
    // ------------------
    CIMPropertyGridProperty* pScanLineCloseUp = MakePropertyGroup( L"Scan line close-up" );
    pUseAutomaticViewpointGroup->AddSubItem( pScanLineCloseUp );
    pScanLineCloseUp->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_STANDARD_ZOOM ) );
    pScanLineCloseUp->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_FEATURE_SCANNING_GUIDANCE_ZOOM ) );

    // Data processing
    // ---------------
    CIMPropertyGridProperty* pDataProcessingGroup = MakePropertyGroup( L"Data processing" );
    m_pPropertyGridCtrl->AddProperty( pDataProcessingGroup );

    pDataProcessingGroup->AddSubItem( MakePropertyValue< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_USE_PARALLEL_PROCESSING ) );
    auto* pPrioritizeAcquisitionSpeedGroup = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_USE_PRIORITIZE_ACQUISITION_SPEED );
    pDataProcessingGroup->AddSubItem( pPrioritizeAcquisitionSpeedGroup );
    pPrioritizeAcquisitionSpeedGroup->AddSubItem( MakePropertyComboValue( E_PROPERTY_VALUE_MESHING_SPEED, FALSE ) );

    // Feature scanning guidance
    // -------------------------
    auto* pFeatureScanGuidanceGroup =
        MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_USE_FEATURE_SCANNING_GUIDANCE );
    m_pPropertyGridCtrl->AddProperty( pFeatureScanGuidanceGroup );

    pFeatureScanGuidanceGroup->AddSubItem( MakePropertyColorValue( E_PROPERTY_VALUE_SURFACE_HIGHLIGHT_COLOR ) );
    pFeatureScanGuidanceGroup->AddSubItem( MakePropertyColorValue( E_PROPERTY_VALUE_BOUNDARY_HIGHLIGHT_COLOR ) );

    m_pPropertyGridCtrl->ExpandAll();

    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_USE_AUTOMATIC_VIEWPOINT );
    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_USE_FEATURE_SCANNING_GUIDANCE );
    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_USE_PRIORITIZE_ACQUISITION_SPEED );
}

// =================================================================================================
//   Initialize the Surface Scan property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridSurfaceScanInit()
{
    m_pPropertyGridCtrl->AddProperty( MakePropertyValue< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_SPLIT_ZIGZAG_SCAN_PASSES ) );

    // Point clouds
    // ------------
    CIMPropertyGridProperty* pPointCloudGroup = MakePropertyGroup( L"Point clouds" );
    m_pPropertyGridCtrl->AddProperty( pPointCloudGroup );

    // Extract normal vectors
    // ----------------------
    auto* pExtractNormalVectors =
        MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_USE_EXTRACT_NORMAL_VECTORS );
    pPointCloudGroup->AddSubItem( pExtractNormalVectors );

    pExtractNormalVectors->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_MIN_SEARCH_DISTANCE ) );
    pExtractNormalVectors->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_MAX_SEARCH_DISTANCE ) );

    m_pPropertyGridCtrl->ExpandAll();

    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_USE_EXTRACT_NORMAL_VECTORS );
}

// =================================================================================================
//   Initialize the Real-Time Quality Meshing property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridRealTimeQualityMeshingInit()
{
    // Default mesh creation parameters
    // --------------------------------
    CIMPropertyGridProperty* pDefaultMeshCreationParametersGroup = MakePropertyGroup( L"Default mesh creation parameters" );
    m_pPropertyGridCtrl->AddProperty( pDefaultMeshCreationParametersGroup );

    pDefaultMeshCreationParametersGroup->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_SAMPLING_STEP ) );
    pDefaultMeshCreationParametersGroup->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_MAX_EDGE_LENGTH ) );
    pDefaultMeshCreationParametersGroup->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_MAX_ANGLE ) );

    // Scan pass merging
    // -----------------
    CIMPropertyGridProperty* pScanPassMerging = MakePropertyGroup( L"Scan pass merging" );
    pDefaultMeshCreationParametersGroup->AddSubItem( pScanPassMerging );

    pScanPassMerging->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_MAX_DISTANCE ) );
    pScanPassMerging->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_NUMBER_OF_BLENDING_STEPS ) );

    m_pPropertyGridCtrl->ExpandAll();
}

// =================================================================================================
//   Initialize the Real-Time Quality Meshing Polygonal Models property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridRTMPolygonalModelsInit()
{
    // Default mesh optimization parameters
    // ------------------------------------
    CIMPropertyGridProperty* pDefaultMeshOptimizationParametersGroup = MakePropertyGroup( L"Default mesh optimization parameters" );
    m_pPropertyGridCtrl->AddProperty( pDefaultMeshOptimizationParametersGroup );

    // Smooth
    // ------
    auto* pRTMSmooth = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_SMOOTH );
    pDefaultMeshOptimizationParametersGroup->AddSubItem( pRTMSmooth );

    pRTMSmooth->AddSubItem( MakePropertyComboValue( E_PROPERTY_VALUE_RTM_SMOOTH_LEVEL, FALSE ) );
    pRTMSmooth->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_SMOOTH_CUSTOM_LEVEL_RADIUS ) );

    CIMPropertyGridProperty* pSmoothConstrainDisplacement = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_SMOOTH_CONSTRAIN_DISPLACEMENT );
    pRTMSmooth->AddSubItem( pSmoothConstrainDisplacement );

    pSmoothConstrainDisplacement->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_SMOOTH_MAX_DISPLACEMENT ) );
    pRTMSmooth->AddSubItem( MakePropertyValue< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_SMOOTH_PRESERVE_FEATURES ) );

    // Reduce
    // ------
    auto* pRTMReduce = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_REDUCE );
    pDefaultMeshOptimizationParametersGroup->AddSubItem( pRTMReduce );
    pRTMReduce->AddSubItem( MakePropertyComboValue( E_PROPERTY_VALUE_RTM_REDUCE_LEVEL, FALSE ) );

    CIMPropertyGridProperty* pRTMReduceCustomLevel = MakePropertyGroup( L"Custom level" );
    pRTMReduce->AddSubItem( pRTMReduceCustomLevel );
    pRTMReduceCustomLevel->AddSubItem( MakePropertyComboValue( E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_METHOD, FALSE ) );
    pRTMReduceCustomLevel->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_TOLERANCE ) );
    pRTMReduceCustomLevel->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_REMAINING_PERCENT ) );
    pRTMReduceCustomLevel->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_REDUCE_CUSTOM_REMAINING_TRIANGLES ) );

    auto* pConstrain = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_REDUCE_CONSTRAIN_EDGE_LENGTH );
    pRTMReduce->AddSubItem( pConstrain );

    pConstrain->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_REDUCE_CONSTRAIN_MAX_EDGE_LENGTH ) );

    pRTMReduce->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_REDUCE_PREREDUCTION_TOLERANCE ) );

    m_pPropertyGridCtrl->ExpandAll();

    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_RTM_REDUCE_CONSTRAIN_EDGE_LENGTH );
}

// =================================================================================================
//   Initialize the Real-Time Quality Meshing Quality Metrics property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridRTMQualityMetricsInit()
{
    // Detect misaligned scan passes
    // -----------------------------
    auto* pDetectMisalignedScanPasses = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_DETECT_MISALIGNED_SCAN_PASSES );
    m_pPropertyGridCtrl->AddProperty( pDetectMisalignedScanPasses );
    pDetectMisalignedScanPasses->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_MAX_AVERAGE_DEVIATION ) );
    pDetectMisalignedScanPasses->AddSubItem( MakePropertyComboValue( E_PROPERTY_VALUE_RTM_BEHAVIOR_WHEN_MISALIGNED, FALSE ) );

    // Highlight low-quality triangles
    // -------------------------------
    CIMPropertyGridProperty* pHighlightLowQuality = MakePropertyGroup( L"Highlight low-quality triangles" );
    m_pPropertyGridCtrl->AddProperty( pHighlightLowQuality );

    // High scanner-to-surface-normal angle
    // ------------------------------------
    auto* pHighScannerToSurfaceNormal = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE );
    pHighlightLowQuality->AddSubItem( pHighScannerToSurfaceNormal );

    pHighScannerToSurfaceNormal->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_HIGHLIGHT_MAX_ANGLE ) );
    pHighScannerToSurfaceNormal->AddSubItem( MakePropertyColorValue( E_PROPERTY_VALUE_RTM_HIGHLIGHT_MAX_ANGLE_COLOR ) );

    // Low scan density for mesh curvature
    // -----------------------------------
    auto* pLowScanDensityForCurvature = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_LOW_SCAN_DENSITY_FOR_CURVATURE );
    pHighlightLowQuality->AddSubItem( pLowScanDensityForCurvature );

    pLowScanDensityForCurvature->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_MAX_DEVIATION_SURFACE ) );
    pLowScanDensityForCurvature->AddSubItem( MakePropertyColorValue( E_PROPERTY_VALUE_RTM_MAX_DEVIATION_SURFACE_COLOR ) );

    // High noise level
    // ----------------
    auto* pHighNoiseLevel = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_RTM_HIGH_NOISE_LEVEL );
    pHighlightLowQuality->AddSubItem( pHighNoiseLevel );

    pHighNoiseLevel->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_RTM_STANDARD_DEVIATION_THRESHOLD ) );
    pHighNoiseLevel->AddSubItem( MakePropertyColorValue( E_PROPERTY_VALUE_RTM_STANDARD_DEVIATION_THRESHOLD_COLOR ) );

    m_pPropertyGridCtrl->ExpandAll();

    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_RTM_DETECT_MISALIGNED_SCAN_PASSES );
    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_RTM_HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE );
    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_RTM_LOW_SCAN_DENSITY_FOR_CURVATURE );
    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_RTM_HIGH_NOISE_LEVEL );
}

// =================================================================================================
//   Initialize the Filtering property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridFilteringInit()
{
    // Filter scan lines
    // -----------------
    auto* pFilterScanLines = MakePropertyValueGroup< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES );
    m_pPropertyGridCtrl->AddProperty( pFilterScanLines );

    pFilterScanLines->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_STANDARD_DEVIATION ) );

    CIMPropertyGridProperty* pFilterCloudPoints = MakePropertyGroup( L"Points cloud" );
    pFilterScanLines->AddSubItem( pFilterCloudPoints );

    pFilterCloudPoints->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_MAX_POINT_TO_POINT_DISTANCE ) );

    // Clipping plane
    // --------------
    CIMPropertyGridProperty* pClippingPlane = MakePropertyGroup( L"Clipping plane" );
    m_pPropertyGridCtrl->AddProperty( pClippingPlane );

    pClippingPlane->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_FILTERING_CLIPPING_PLANE_REJECTION_DIST ) );

    m_pPropertyGridCtrl->ExpandAll();

    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES );
    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_STANDARD_DEVIATION );
    PropertyEnableUpdateAuto( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_MAX_POINT_TO_POINT_DISTANCE );
}

// =================================================================================================
//   Initialize the Hole Boundary Scan property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridHoleBoundaryScanInit()
{
    // Internal boundary detection (holes)
    // -----------------------------------
    CIMPropertyGridProperty* pHoleDetectionGroup = MakePropertyGroup( L"Internal boundary detection (holes)" );
    m_pPropertyGridCtrl->AddProperty( pHoleDetectionGroup );

    pHoleDetectionGroup->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_MIN_HOLE_WIDTH ) );

    // Real-time quality meshing
    // -------------------------
    CIMPropertyGridProperty* pRTMGroup = MakePropertyGroup( L"Real-time quality meshing" );
    m_pPropertyGridCtrl->AddProperty( pRTMGroup );

    pRTMGroup->AddSubItem( MakePropertyValue< CIMPropertyGridCheckBoxProperty >( E_PROPERTY_VALUE_EXTERNAL_BOUNDARY_DETECTION ) );

    m_pPropertyGridCtrl->ExpandAll();
}

// =================================================================================================
//   Initialize the Sharp Edge Scan property grid
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyGridSharpEdgeScanInit()
{
    // Scan line
    // ---------
    CIMPropertyGridProperty* pScanLineGroup = MakePropertyGroup( L"Scan line" );
    m_pPropertyGridCtrl->AddProperty( pScanLineGroup );

    pScanLineGroup->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_EDGE_MAX_POINT_TO_POINT_DISTANCE ) );
    pScanLineGroup->AddSubItem( MakePropertyValue< CIMPropertyGridProperty >( E_PROPERTY_VALUE_EDGE_MIN_ANGLE ) );

    m_pPropertyGridCtrl->ExpandAll();
}

// =================================================================================================
//   Update the enable state of a property.
//
// Parameter : propertyData_ : Property data ID
// Parameter : enable_       : TRUE to enable, FALSE otherwise
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::PropertyEnableUpdate( DWORD propertyData_, BOOL enable_ )
{
    __super::PropertyEnableUpdate( propertyData_, enable_ );

    switch ( propertyData_ )
    {
        case E_PROPERTY_VALUE_USE_AUTOMATIC_VIEWPOINT:
            PropertyEnable( E_PROPERTY_VALUE_DEVICE_VERTICAL_AXIS,           enable_ );
            PropertyEnable( E_PROPERTY_VALUE_STANDARD_ZOOM,                  enable_ );
            PropertyEnable( E_PROPERTY_VALUE_FEATURE_SCANNING_GUIDANCE_ZOOM, enable_ );
            break;
        case E_PROPERTY_VALUE_USE_EXTRACT_NORMAL_VECTORS:
            PropertyEnable( E_PROPERTY_VALUE_MIN_SEARCH_DISTANCE, enable_ );
            PropertyEnable( E_PROPERTY_VALUE_MAX_SEARCH_DISTANCE, enable_ );
            break;
        case E_PROPERTY_VALUE_RTM_DETECT_MISALIGNED_SCAN_PASSES:
            PropertyEnable( E_PROPERTY_VALUE_RTM_MAX_AVERAGE_DEVIATION,    enable_ );
            PropertyEnable( E_PROPERTY_VALUE_RTM_BEHAVIOR_WHEN_MISALIGNED, enable_ );
            break;
        case E_PROPERTY_VALUE_USE_PRIORITIZE_ACQUISITION_SPEED:
            PropertyEnable( E_PROPERTY_VALUE_MESHING_SPEED, enable_ );
            break;
        case E_PROPERTY_VALUE_USE_FEATURE_SCANNING_GUIDANCE:
            PropertyEnable( E_PROPERTY_VALUE_SURFACE_HIGHLIGHT_COLOR,  enable_ );
            PropertyEnable( E_PROPERTY_VALUE_BOUNDARY_HIGHLIGHT_COLOR, enable_ );
            break;
        case E_PROPERTY_VALUE_RTM_HIGH_SCANNER_TO_SURFACE_NORMAL_ANGLE:
            PropertyEnable( E_PROPERTY_VALUE_RTM_HIGHLIGHT_MAX_ANGLE,       enable_ );
            PropertyEnable( E_PROPERTY_VALUE_RTM_HIGHLIGHT_MAX_ANGLE_COLOR, enable_ );
            break;
        case E_PROPERTY_VALUE_RTM_LOW_SCAN_DENSITY_FOR_CURVATURE:
            PropertyEnable( E_PROPERTY_VALUE_RTM_MAX_DEVIATION_SURFACE,       enable_ );
            PropertyEnable( E_PROPERTY_VALUE_RTM_MAX_DEVIATION_SURFACE_COLOR, enable_ );
            break;
        case E_PROPERTY_VALUE_RTM_HIGH_NOISE_LEVEL:
            PropertyEnable( E_PROPERTY_VALUE_RTM_STANDARD_DEVIATION_THRESHOLD,       enable_ );
            PropertyEnable( E_PROPERTY_VALUE_RTM_STANDARD_DEVIATION_THRESHOLD_COLOR, enable_ );
            break;
        case E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES:
            PropertyEnable( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_STANDARD_DEVIATION,          enable_ );
            PropertyEnable( E_PROPERTY_VALUE_FILTERING_FILTER_SCAN_LINES_MAX_POINT_TO_POINT_DISTANCE, enable_ );
            break;
        case E_PROPERTY_VALUE_RTM_REDUCE_CONSTRAIN_EDGE_LENGTH:
            PropertyEnable( E_PROPERTY_VALUE_RTM_REDUCE_CONSTRAIN_MAX_EDGE_LENGTH, enable_ );
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
long CDlgIMInspectOptions::WindowPositionXGet()
{
    return theCompanyNameScannerSettings().IMIOptionsWindowPositionXGet();
}


// =================================================================================================
//   Set the X position of the window.
//
// Parameter : position_ : Position
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::WindowPositionXSet( long position_ )
{
    theCompanyNameScannerSettings().IMIOptionsWindowPositionXSet( position_ );
}


// =================================================================================================
//   Obtain the Y position of the window.
//
// Return : Position
// -------------------------------------------------------------------------------------------------
long CDlgIMInspectOptions::WindowPositionYGet()
{
    return theCompanyNameScannerSettings().IMIOptionsWindowPositionYGet();
}


// =================================================================================================
//   Sets the Y position of the window.
//
// Parameter : position_ : Position
// -------------------------------------------------------------------------------------------------
void CDlgIMInspectOptions::WindowPositionYSet( long position_ )
{
    theCompanyNameScannerSettings().IMIOptionsWindowPositionYSet( position_ );
}
