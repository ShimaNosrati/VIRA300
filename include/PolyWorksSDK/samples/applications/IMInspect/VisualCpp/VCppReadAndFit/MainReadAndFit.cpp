﻿/* *****************************************************************************
 * File: MainReadAndFit.cpp
 *
 * Description :
 *
 *      Defines the entry point for the console application.
 *      Reads an ASCII file of a point cloud containing points with coordinates and normals.
 *      The points are sent to PolyWorks|Inspector, and a sphere is then fitted to them.
 *      Then, the application verifies if the fit was successful after running a script MSCL.
 * -----------------------------------------------------------------------------
 * InnovMetric Inc. Copyright ( C ) 2002
 *                            All rights reserved
 * ************************************************************************** */

// ===========================================================================
// INCLUDED FILES
// ===========================================================================

#include <atlbase.h>
#include <atlcomcli.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <vector>

#include <PolyWorksSDK/COM/IIMInspect.h>
#include <PolyWorksSDK/COM/IIMInspect_i.c>
#include <PolyWorksSDK/COM/IIMPointCloud.h>
#include <PolyWorksSDK/COM/IIMPointCloud_i.c>
#include <PolyWorksSDK/COM/IIMSceneCamera.h>
#include <PolyWorksSDK/COM/IIMSceneCamera_i.c>
#include <PolyWorksSDK/COM/IMInspect_i.c>

#include "CComInitRAII.h"
#include "CComMessageFilter.h"

#pragma warning(disable : 4996)

// ===========================================================================
// CONSTANTS
// ===========================================================================
#define COEF        1
#define BUFFLEN     COEF* 1020

// ===========================================================================
// GLOBAL VARIABLES
// ===========================================================================
int nbImages = 0;

// color table
const int    GRP_RGBA_NB                     = 25;
const double _rgba_table[ GRP_RGBA_NB ][ 3 ] =
{
    { 1.0, 0.7, 0.7 },
    { 0.7, 1.0, 0.7 },
    { 0.7, 0.7, 1.0 },
    { 1.0, 1.0, 0.6 },
    { 1.0, 0.6, 1.0 },
    { 0.6, 1.0, 1.0 },
    { 0.6, 0.8, 1.0 },
    { 1.0, 0.6, 0.8 },
    { 0.8, 1.0, 0.6 },
    { 1.0, 0.8, 0.6 },
    { 0.6, 1.0, 0.8 },
    { 0.8, 0.6, 1.0 },
    { 0.6, 0.6, 0.6 },
    { 1.0, 0.4, 0.4 },
    { 0.4, 1.0, 0.4 },
    { 0.4, 0.4, 1.0 },
    { 1.0, 1.0, 0.2 },
    { 1.0, 0.2, 1.0 },
    { 0.2, 1.0, 1.0 },
    { 0.2, 0.6, 1.0 },
    { 1.0, 0.2, 0.6 },
    { 0.6, 1.0, 0.2 },
    { 1.0, 0.6, 0.2 },
    { 0.2, 1.0, 0.6 },
    { 0.6, 0.2, 1.0 }
};

// ===========================================================================
// FONCTION PROTOTYPES
// ===========================================================================
wchar_t* CharToWChar( const char* pSrc_, wchar_t* pDest_, size_t size_ );

int FillArraysFromFile(
    char*           filename_,
    int             nbPoints_,
    float**         aCoords_,
    float**         aNormals_,
    unsigned char** aColors_ );

int FillSafeArray(
    int             nbBlock_,
    int             sizeBlock_,
    float**         aCoords_,
    float*          ppArrayCoord_,
    float**         aNormals_,
    float*          ppArrayNormal_,
    unsigned char** aColors_,
    unsigned char*  ppArrayColor_ );

int FillSafeArrayLast(
    int             startIdx_,
    int             nbRemainPt_,
    int             nbTPoints_,
    float**         aCoords_,
    float*          ppArrayCoord_,
    float**         aNormals_,
    float*          ppArrayNormal_,
    unsigned char** aColors_,
    unsigned char*  ppArrayColor_ );

void NameSpheresFeedback( std::vector< std::wstring >& sphereNames_ );

int NbPointsFromFileGet( char* filename_ );

int Prompt( char* buffer );

bool ValueStrGetFromApp(
    const CComPtr< IIMCommandCenter >& commandCenter_,
    const std::wstring&                cmdName_,
    std::wstring&                      value_,
    bool                               withEcho_,
    const std::wstring&                cmdArg_ = L"" );

bool ValueStrArrayGetFromApp(
    const CComPtr< IIMCommandCenter >&          commandCenter_,
    const std::wstring&                         cmdName_,
    std::vector< std::vector< std::wstring > >& values_,
    bool                                        withEcho_,
    const std::wstring&                         cmdArg_ );

bool RunScriptAndReadValueArrays(
    const CComPtr< IIMCommandCenter >&          pCommandCenter_,
    const std::wstring&                         script_,
    const std::vector< std::wstring >&          varNames_,
    std::vector< std::vector< std::wstring > >& values_,
    bool                                        withEcho_ );

// ===========================================================================
// FONCTION DEFINITIONS
// ===========================================================================

/* *****************************************************************************
 *   Main routine
 *
 * Parameter: argc   : nb of arguments
 * Parameter: argv[] : array of arguments
 * -------------------------------------------------------------------------- */
int main( int argc, char* argv[] )
{
    // Initialize the COM library
    CComInitRAII          comInitRAII;
    CRAIIComMessageFilter comMsgFilter;

    //----------------------------
    //Global access to a PolyWorks|Inspector
    HRESULT hr =  0;

    CComPtr< IIMInspect > pIMInspect;

    CLSID progID = CLSID_IMInspect;
    // With the line above, your program will attempt to connect exclusively with the version of PolyWorks|Inspector
    // you're currently working with. If the user upgrades to a more recent version of PolyWorks|Inspector, your program
    // will not attempt to connect to it.
    // Instead, to let your program attempt to work with the latest version of PolyWorks|Inspector installed on the
    // user's computer, uncomment the following line and make sure hr is not an error code before continuing.
    //hr = CLSIDFromProgID( L"InnovMetric.PolyWorks.IMInspect", &progID );

    hr = CoCreateInstance(
        progID,
        nullptr,
        CLSCTX_SERVER,
        IID_IIMInspect,
        ( void** ) &pIMInspect );

    if ( !SUCCEEDED( hr ) )
    {
        return 1;
    }

    //-----------------------------------
    // Obtain PolyWorks|Inspector's current project
    CComPtr< IIMInspectProject > pCurrentProject;
    hr = pIMInspect->ProjectGetCurrent( &pCurrentProject );

    if ( !SUCCEEDED( hr ) || ( pCurrentProject == nullptr ) )
    {
        return 1;
    }

    //--------------
    // CommandCenter
    CComPtr< IIMCommandCenter > pCommandCenter;
    hr = pCurrentProject->CommandCenterCreate( &pCommandCenter );

    if ( !SUCCEEDED( hr ) || ( pCommandCenter == nullptr ) )
    {
        return 1;
    }


    //------------------
    // Introduction text
    std::cout << "ASCII point cloud reader, console version." << std::endl;

    int nbCmdErrors = 0;

    char filename[ 1024 ];
    char filenameClean[ 1024 ];

    int      nameStringSize  = 0;
    int      extensionSize   = 0;
    wchar_t* nameString      = nullptr;
    wchar_t* extensionString = nullptr;

    long res = 0;

    while ( Prompt( filename ) )
    {
        //---------------------
        // Reads the ASCII file
        ( filename[ 0 ] == '\"' ) ? strcpy( filenameClean, &filename[ 1 ] ) : strcpy( filenameClean, &filename[ 0 ] );

        if ( filenameClean[ strlen( filenameClean ) - 1 ] == '\"' )
        {
            filenameClean[ strlen( filenameClean ) - 1 ] = '\0';
        }

        int nbPoints = NbPointsFromFileGet( filenameClean );
        std::cout << "Loading " << nbPoints << " points..." << std::endl;

        float*         aCoords  = nullptr;
        float*         aNormals = nullptr;
        unsigned char* aColors  = nullptr;

        if ( !FillArraysFromFile( filenameClean, nbPoints, &aCoords, &aNormals, &aColors ) )
        {
            continue;
        }

        //-----------------
        // Sends the points
        std::cout << "Sending points..." << std::endl;

        //--------------------------------------------------
        // Obtains only the file name from its complete path
        char objectName[ _MAX_FNAME ];
        char extension[ _MAX_EXT ];

        _splitpath( filenameClean, nullptr, nullptr, objectName, extension );

        //---------------------------------
        // Conversion from char to wchar_t.
        extensionSize  = ( int ) ( strlen( extension )  + 1 );
        nameStringSize = ( int ) ( strlen( objectName ) + 1 );

        nameString = new wchar_t[ nameStringSize + extensionSize ];

        CharToWChar( objectName, nameString, nameStringSize );

        // Add the extension
        extensionString = new wchar_t[ extensionSize ];

        CharToWChar( extension, extensionString, extensionSize );

        wcscat( nameString, extensionString );

        SAFEARRAY* ppBufferCoord  = nullptr;
        SAFEARRAY* ppBufferNormal = nullptr;
        SAFEARRAY* ppBufferColor  = nullptr;

        // scopes pIMPointCould so it is properly released
        {
            //------------------------------------------------------
            // Creates a point cloud in the current PolyWorks|Inspector project
            CComPtr< IIMPointCloud > pIMPointCloud;

            hr = pCurrentProject->PointCloudCreateData( &pIMPointCloud, nameString );

            if ( SUCCEEDED( hr ) && ( pIMPointCloud != nullptr ) )
            {
                // scopes pIMSceneCamera so it is properly released
                {
                    CComQIPtr< IIMSceneCamera > pIMSceneCamera( pIMPointCloud );
                    pIMSceneCamera->RefreshTriggerSetTimeDelay( 1000 );
                }

                int sizeMax = BUFFLEN;

                float* ppArrayCoord = nullptr;

                ppBufferCoord = SafeArrayCreateVector( VT_R4, 0, sizeMax );
                SafeArrayAccessData( ppBufferCoord, ( void** )&ppArrayCoord );

                int isNormal = 0;

                if ( aNormals != 0 )
                {
                    isNormal = 1;
                }

                float* ppArrayNormal = nullptr;

                if ( isNormal )
                {
                    ppBufferNormal = SafeArrayCreateVector( VT_R4, 0, sizeMax );
                    SafeArrayAccessData( ppBufferNormal, ( void** )&ppArrayNormal );
                }

                unsigned char* ppArrayColor = nullptr;

                ppBufferColor = SafeArrayCreateVector( VT_UI1, 0, sizeMax );
                SafeArrayAccessData( ppBufferColor, ( void** )&ppArrayColor );

                //------------------------------------
                // Sends the points to the point cloud
                int nbBlock    = 3 * ( nbPoints ) / ( sizeMax );
                int nbRemainPt = 3 * ( nbPoints ) % ( sizeMax );

                int i = 0;
                for ( ; i < nbBlock; i++ )
                {
                    if ( FillSafeArray(
                             i,
                             sizeMax,
                             &aCoords,
                             ppArrayCoord,
                             &aNormals,
                             ppArrayNormal,
                             &aColors,
                             ppArrayColor ) )
                    {
                        pIMPointCloud->PointsAdd( &ppBufferCoord, &ppBufferNormal, &ppBufferColor );
                    }
                }

                SafeArrayUnaccessData( ppBufferColor );
                SafeArrayUnaccessData( ppBufferCoord );

                if ( isNormal )
                {
                    SafeArrayUnaccessData( ppBufferNormal );
                }

                if ( nbRemainPt != 0 )
                {
                    ppBufferCoord = SafeArrayCreateVector( VT_R4, 0, nbRemainPt );
                    ppArrayCoord  = nullptr;
                    SafeArrayAccessData( ppBufferCoord, ( void** )&ppArrayCoord );

                    if ( isNormal )
                    {
                        ppBufferNormal = SafeArrayCreateVector( VT_R4, 0, nbRemainPt );
                        ppArrayNormal  = nullptr;
                        SafeArrayAccessData( ppBufferNormal, ( void** )&ppArrayNormal );
                    }

                    ppBufferColor = SafeArrayCreateVector( VT_UI1, 0, nbRemainPt );
                    ppArrayColor  = nullptr;
                    SafeArrayAccessData( ppBufferColor, ( void** )&ppArrayColor );

                    //-----------------------------------------
                    // Sends the last points to the point cloud
                    if ( FillSafeArrayLast(
                             i * sizeMax,
                             nbRemainPt,
                             nbPoints,
                             &aCoords,
                             ppArrayCoord,
                             &aNormals,
                             ppArrayNormal,
                             &aColors,
                             ppArrayColor ) )
                    {
                        pIMPointCloud->PointsAdd( &ppBufferCoord, &ppBufferNormal, &ppBufferColor );
                    }

                    SafeArrayUnaccessData( ppBufferCoord );
                    SafeArrayUnaccessData( ppBufferColor );

                    if ( isNormal )
                    {
                        SafeArrayUnaccessData( ppBufferNormal );
                    }
                }
            }
        }
        // release point cloud here
        if ( SUCCEEDED( hr ) )
        {
            //----------------
            // Fitting process
            wchar_t argCmd[ 1024 ];
            long    isSuccess = 0;

            pCommandCenter->CommandExecute( L"VIEW POSE CENTER",            &res );
            pCommandCenter->CommandExecute( L"TREEVIEW OBJECT SELECT NONE", &res );

            // Perform the fit
            std::wstring strCmd = L"TREEVIEW OBJECT_ELEMENTS SELECT ALL ( \"" + std::wstring( nameString ) + L"\" )";
            pCommandCenter->CommandExecute( strCmd.c_str(),                                         &res );
            pCommandCenter->CommandExecute( L"FEATURE PRIMITIVE SPHERE FIT_FROM_SELECTED_ELEMENTS", &res );
            pCommandCenter->ReturnValueIsSuccess( res, &isSuccess );
            if ( isSuccess == 0 )
            {
                std::cout << "The fitting was unsuccessful\n";
            }

            // Gets the name of the last fitted sphere. After the fitting, it is the only object selected.
            std::wstring lastSphereName = L"";
            if ( !ValueStrGetFromApp( pCommandCenter, L"TREEVIEW OBJECT PROPERTIES NAME GET", lastSphereName, false, L"" ) )
            {
                std::cout << "Unable to obtain the name of the fitted sphere";
            }
            else
            {
                // Feedback of the name of the last fitted sphere
                std::wcout << L"Sphere \"" << lastSphereName.c_str() << L"\" was successfully fitted";
            }

            // Gets the name of all spheres
            pCommandCenter->CommandExecute( L"TREEVIEW OBJECT SELECT NONE",          &res );
            pCommandCenter->CommandExecute( L"TREEVIEW PRIMITIVE SPHERE SELECT ALL", &res );

            std::vector< std::vector< std::wstring > > sphereNames;
            if ( !ValueStrArrayGetFromApp( pCommandCenter, L"TREEVIEW OBJECT NAME SELECTED GET", sphereNames, false, L"" ) )
            {
                std::cout << "Unable to obtain the name of the selected objects";
            }

            // Feedback of the name of all spheres
            NameSpheresFeedback( sphereNames[ 0 ] );

            delete[] nameString;
            nameString = nullptr;

            if ( ppBufferCoord != nullptr )
            {
                SafeArrayDestroy( ppBufferCoord );
            }
            if ( ppBufferNormal != nullptr )
            {
                SafeArrayDestroy( ppBufferNormal );
            }
            if ( ppBufferColor != nullptr )
            {
                SafeArrayDestroy( ppBufferColor );
            }
        }
    }

    return 0;
}







/* *****************************************************************************
 *   Converts a char string into a wchar_t string
 *
 * Parameter: pSrc_  : string to convert
 * Parameter: pDest_ : result buffer
 * Parameter: size_  : buffer size
 *
 * Returns: wchar_t* : pointer to result buffer; nullptr if one of the
 *                     pointer arguments is nullptr
 * -------------------------------------------------------------------------- */
wchar_t* CharToWChar( const char* pSrc_, wchar_t* pDest_, size_t size_ )
{
    size_t charNo;
    size_t stringSize;

    if ( pSrc_ == nullptr )
    {
        return nullptr;
    }

    if ( pDest_ == nullptr )
    {
        return nullptr;
    }

    stringSize = strlen( pSrc_ );

    if ( stringSize > size_ - 1 )
    {
        std::cout << "Buffer is too small " << size_ << "for converting:\n" << pSrc_ << std::endl;
        pDest_[ 0 ] = L'\0';
        return pDest_;
    }

    for ( charNo = 0; charNo < stringSize; charNo++ )
    {
        pDest_[ charNo ] = ( unsigned char )pSrc_[ charNo ];
    }

    pDest_[ stringSize ] = L'\0';

    return pDest_;
}


/* *****************************************************************************
 *   Reads and fills the different arrays from the file
 *
 * Parameter: filename_ : file name
 * Parameter: nbPoints_ : nb points to read
 * Parameter: aCoords_  : array of coordinates
 * Parameter: aNormals_ : array of normals
 * Parameter: aColors_  : array of colors
 *
 * Return: int : false, if the reading is impossible
 *               true,  otherwise
 * -------------------------------------------------------------------------- */
int FillArraysFromFile(
    char*           filename_,
    int             nbPoints_,
    float**         aCoords_,
    float**         aNormals_,
    unsigned char** aColors_ )
{
    if ( ( filename_ == nullptr ) || ( strlen( filename_ ) == 0 ) || ( nbPoints_ == 0 ) )
    {
        return false;
    }

    std::ifstream file;

    file.open( filename_, std::ios::in );

    if ( !file.is_open() )
    {
        //------------------
        // File name request
        std::cout << "Cannot open \"" << filename_ << "\" file." << std::endl;
        return false;
    }

    //---------------------------------
    // Determines the color point cloud
    int r, g, b = 0;

    r = ( int ) ( _rgba_table[ nbImages % GRP_RGBA_NB ][ 0 ] * 255 );
    g = ( int ) ( _rgba_table[ nbImages % GRP_RGBA_NB ][ 1 ] * 255 );
    b = ( int ) ( _rgba_table[ nbImages % GRP_RGBA_NB ][ 2 ] * 255 );

    nbImages++;

    *aCoords_ = new         float[ 3 * nbPoints_ ];
    *aColors_ = new unsigned char[ 3 * nbPoints_ ];

    char  lineBuffer[ 1024 ] = { '\0' };
    char* delim              = " ,\t\n";

    int nbPoints          = 0;
    int isNormalAllocated = false;
    int fin               = file.eof();

    while ( !fin )
    {
        file.getline( lineBuffer, 1024, '\n' );

        char* item = strtok( lineBuffer, delim );
        if ( item )
        {
            *( *aCoords_ + nbPoints ) = ( float ) atof( item );
            item                      = strtok( nullptr, delim );
        }
        if ( item )
        {
            *( *aCoords_ + ( nbPoints + 1 ) ) = ( float ) atof( item );
            item                              = strtok( nullptr, delim );
        }
        if ( item )
        {
            *( *aCoords_ + ( nbPoints + 2 ) ) = ( float ) atof( item );
            item                              = strtok( nullptr, delim );
        }

        if ( item != 0 && isNormalAllocated == false )
        {
            *aNormals_        = new float[ 3 * nbPoints_ ];
            isNormalAllocated = true;
        }
        if ( item )
        {
            *( *aNormals_ + nbPoints ) = ( float ) atof( item );
            item                       = strtok( nullptr, delim );
        }
        if ( item )
        {
            *( *aNormals_ + ( nbPoints + 1 ) ) = ( float ) atof( item );
            item                               = strtok( nullptr, delim );
        }
        if ( item )
        {
            *( *aNormals_ + ( nbPoints + 2 ) ) = ( float ) atof( item );
            item                               = strtok( nullptr, delim );
        }

        *( *aColors_ + nbPoints     )     = ( unsigned char ) r;
        *( *aColors_ + ( nbPoints + 1 ) ) = ( unsigned char ) g;
        *( *aColors_ + ( nbPoints + 2 ) ) = ( unsigned char ) b;

        nbPoints += 3;

        fin = file.eof();
    }

    file.close();
    return true;
}


/* *****************************************************************************
 *   Fills the different safearrays from their respective arrays.
 *
 * Parameter: nbBlock_       : nb of paquet
 * Parameter: sizeBlock_     : size of the block
 * Parameter: aCoords_       : array of coordinates
 * Parameter: ppArrayCoord_  : safearray of coordinates
 * Parameter: aNormals_      : array of normals
 * Parameter: ppArrayNormal_ : safearray of normals
 * Parameter: aColors_       : array of colors
 * Parameter: ppArrayColor_  : safearray of colors
 *
 * Return: int : false, if impossible
 *               true,  otherwise
 * -------------------------------------------------------------------------- */
int FillSafeArray(
    int             nbBlock_,
    int             sizeBlock_,
    float**         aCoords_,
    float*          ppArrayCoord_,
    float**         aNormals_,
    float*          ppArrayNormal_,
    unsigned char** aColors_,
    unsigned char*  ppArrayColor_ )
{
    if ( ( *aCoords_ == 0 ) || ( sizeBlock_ == 0 ) || ( ppArrayCoord_  == nullptr ) )
    {
        return false;
    }

    int i   = nbBlock_;
    int pos = sizeBlock_ * i;

    float unAFloat;
    int   unAInt;
    int   idx;

    for ( int j = 0; j < sizeBlock_; j++ )
    {
        idx = j + pos;

        unAFloat           = *( *aCoords_ + idx );
        ppArrayCoord_[ j ] = unAFloat;

        if ( *aNormals_ != 0 )
        {
            unAFloat            = *( *aNormals_ + idx );
            ppArrayNormal_[ j ] = unAFloat;
        }

        if ( *aColors_ != 0 )
        {
            unAInt             = *( *aColors_ + idx );
            ppArrayColor_[ j ] = unAInt;
        }
    }

    return true;
}


/* *****************************************************************************
 *   Fills the last different safearrays from their respective arrays.
 *
 * Parameter: startIdx_      : the lastest point read
 * Parameter: nbRemainPt_    : nb of points to be read
 * Parameter: nbTPoints_     : total nb points
 * Parameter: aCoords_       : array of coordinates
 * Parameter: ppArrayCoord_  : safearray of coordinates
 * Parameter: aNormals_      : array of normals
 * Parameter: ppArrayNormal_ : safearray of normals
 * Parameter: aColors_       : array of colors
 * Parameter: ppArrayColor_  : safearray of colors
 *
 * Return: int : false, if impossible
 *               true,  otherwise
 * -------------------------------------------------------------------------- */
int FillSafeArrayLast(
    int             startIdx_,
    int             nbRemainPt_,
    int             nbTPoints_,
    float**         aCoords_,
    float*          ppArrayCoord_,
    float**         aNormals_,
    float*          ppArrayNormal_,
    unsigned char** aColors_,
    unsigned char*  ppArrayColor_ )
{
    if ( ( *aCoords_ == 0 ) || ( nbRemainPt_ == 0 ) || ( ppArrayCoord_ == nullptr ) )
    {
        return false;
    }

    int nbCoords = 3 * nbTPoints_;

    for ( int i = startIdx_; i < nbCoords; i++ )
    {
        float unAFloat;
        int   unAInt;

        for ( int j = 0; j < nbRemainPt_; j++ )
        {
            unAFloat           = *( *aCoords_ + i );
            ppArrayCoord_[ j ] = unAFloat;

            if ( *aNormals_ != 0 )
            {
                unAFloat            = *( *aNormals_ + i );
                ppArrayNormal_[ j ] = unAFloat;
            }

            if ( *aColors_ != 0 )
            {
                unAInt             = *( *aColors_ + i );
                ppArrayColor_[ j ] = unAInt;
            }

            i++;
        }
    }

    return true;
}


/* *****************************************************************************
 *   Reads the file to determine the number of points
 *
 * Parameter: filename_ : file name
 *
 * Return: int : nb of points in the file
 * -------------------------------------------------------------------------- */
int NbPointsFromFileGet( char* filename_ )
{
    if ( ( filename_ == nullptr ) || ( strlen( filename_ ) == 0 ) )
    {
        return false;
    }

    std::ifstream file;

    file.open( filename_, std::ios::in );

    if ( !file.is_open() )
    {
        //------------------
        // File name request
        std::cout << "Cannot open \"" << filename_ << "\" file." << std::endl;
        return false;
    }

    char  lineBuffer[ 1024 ] = { '\0' };
    char* delim              = " ,\t\n";

    int nbPoints = 0;
    int fin      = file.eof();

    while ( !fin )
    {
        file.getline( lineBuffer, 1024, '\n' );

        char* item = strtok( lineBuffer, delim );

        if ( item )
        {
            nbPoints++;
        }

        fin = file.eof();
    }

    file.close();

    return nbPoints;
}

//=================================================================================================
// Indicates if the specified list of strings is empty.
//
// Parameter : sphereNames_ : sphere names
//
// Return : true if empty, false otherwise
//=================================================================================================
bool IsSphereNamesEmpty( const std::vector< std::wstring >& sphereNames_ )
{
    if ( sphereNames_.empty() )
    {
        return true;
    }

    // Note that in MSCL, an empty array has a size of 1 and that the corresponding element is always 0 whatever its type (int, float, string...).
    if ( sphereNames_.size() == 1 )
    {
        if ( sphereNames_[ 0 ] == L"0" )
        {
            return true;
        }
    }

    return false;
}

//=================================================================================================
// Feedback of the name of all spheres
//
// Parameter : sphereNames_ : sphere names
//=================================================================================================
void NameSpheresFeedback( std::vector< std::wstring >& sphereNames_ )
{
    std::string suffix    = "sphere";
    int         nbSpheres = 0;

    if ( !IsSphereNamesEmpty( sphereNames_ ) )
    {
        nbSpheres = sphereNames_.size();
        if ( nbSpheres > 1 )
        {
            suffix = "spheres";
        }
    }

    std::cout << std::endl << "Name of all spheres: ( " << nbSpheres << " " << suffix.c_str() << " )";

    std::wstring resultAllSelectedSphere;
    for ( int i = 0; i < nbSpheres; i++ )
    {
        if ( i > 0 )
        {
            resultAllSelectedSphere += L", ";
        }

        resultAllSelectedSphere += sphereNames_[ i ];
    }

    std::wcout << std::endl << resultAllSelectedSphere.c_str();
}


/* *****************************************************************************
 *   Prompts the user for a line of text and saves the input in a buffer
 *
 * Parameter: buffer : text buffer
 *
 * Return: false, if leaving,
 *         true,  otherwise
 * -------------------------------------------------------------------------- */
int Prompt( char* buffer )
{
    if ( buffer == nullptr )
    {
        return 0;
    }

    std::cout << std::endl << "Enter an ASCII point cloud file path, or type EXIT to quit." << std::endl;
    std::cout << "File path: " << std::endl;

    std::cin.getline( buffer, 1024, '\n' );

    if ( !std::cin || !_strnicmp( buffer, "EXIT\0", 5 ) )
    {
        return 0;
    }

    return 1;
}

//=================================================================================================
//   Retrieves a string value from the application, using a command.
//
// Parameter : commandCenter_ : command center
// Parameter : cmdName_       : command name
// Parameter : value_         : (out) retrieved value
// Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
// Parameter : cmdArg_        : command arguments
//
// Return : true if successful, false otherwise
// -------------------------------------------------------------------------------------------------
bool ValueStrGetFromApp(
    const CComPtr< IIMCommandCenter >& commandCenter_,
    const std::wstring&                cmdName_,
    std::wstring&                      value_,
    bool                               withEcho_,
    const std::wstring&                cmdArg_ /*= L""*/ )
{
    value_ = L"";
    std::vector< std::vector< std::wstring > > values;

    if ( !ValueStrArrayGetFromApp( commandCenter_, cmdName_, values, withEcho_, cmdArg_ ) )
    {
        return false;
    }

    if ( values.empty() || values[ 0 ].empty() )
    {
        return false;
    }

    value_ = values[ 0 ][ 0 ];
    return true;
}

// =================================================================================================
//    Retrieves an array of string values from the application, using a command.
//
//  Parameter : commandCenter_ : command center
//  Parameter : cmdName_       : command name
//  Parameter : values_        : (out) retrieved values
//  Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
//  Parameter : cmdArg_        : command arguments
//
//  Return : true if successful, false otherwise
//  -------------------------------------------------------------------------------------------------
bool ValueStrArrayGetFromApp(
    const CComPtr< IIMCommandCenter >&          commandCenter_,
    const std::wstring&                         cmdName_,
    std::vector< std::vector< std::wstring > >& values_,
    bool                                        withEcho_,
    const std::wstring&                         cmdArg_ )
{

    std::wstring valueVar = L"value";
    std::wstring script   = L"version \"5.0\"\n";
    script += L"DECLARE " + valueVar + L"\n";
    script += cmdName_ + L" ( ";
    if ( !cmdArg_.empty() )
    {
        script += L"\"" + cmdArg_ + L"\", ";
    }
    script += valueVar + L" )";

    std::vector< std::wstring > values;
    std::vector< std::wstring > valueVarArray;
    valueVarArray.push_back( valueVar );
    if ( !RunScriptAndReadValueArrays( commandCenter_, script, valueVarArray, values_, withEcho_ ) )
    {
        return false;
    }

    return true;
}

//=================================================================================================
//   Retrieves the values of each variable when running a given script
//
// Parameter : commandCenter_ : command center
// Parameter : script_        : script to execute
// Parameter : varNames_      : name of the variables to retrieve
// Parameter : values_        : retrieved values of each variable
// Parameter : withEcho_      : indicates whether the command should be visible in the application's Command History
//
// Return : true if successful, false otherwise
// -------------------------------------------------------------------------------------------------
bool RunScriptAndReadValueArrays(
    const CComPtr< IIMCommandCenter >&          pCommandCenter_,
    const std::wstring&                         script_,
    const std::vector< std::wstring >&          varNames_,
    std::vector< std::vector< std::wstring > >& values_,
    bool                                        withEcho_ )
{
    long res       = 0;
    long isSuccess = 0;

    if ( withEcho_ )
    {
        pCommandCenter_->CommandExecute( L"EchoOn",       &res );
        pCommandCenter_->CommandExecute( L"RecordableOn", &res );
    }
    else
    {
        pCommandCenter_->CommandExecute( L"EchoOff",       &res );
        pCommandCenter_->CommandExecute( L"RecordableOff", &res );

    }

    // Run the script
    if ( pCommandCenter_->ScriptExecuteFromBuffer( script_.c_str(), L"", &res ) == S_OK )
    {
        if ( pCommandCenter_->ReturnValueIsSuccess( res, &isSuccess ) == S_OK &&
             ( isSuccess == 0 ) )
        {
            return false;

        }
    }

    // Retrieves the values of each variable
    for ( int i = 0; i < varNames_.size(); i++ )
    {
        std::vector< std::wstring > values;
        long nbValues = 0;

        pCommandCenter_->ScriptVariableGetNbValues( varNames_[ i ].c_str(), &nbValues );

        for ( int j = 0; j < nbValues; j++ )
        {
            res       = 0;
            isSuccess = 0;
            BSTR value = nullptr;
            if ( ( pCommandCenter_->ScriptVariableGetValueAsString( varNames_[ i ].c_str(), j + 1, &value, &res ) == S_OK ) &&
                 ( pCommandCenter_->ReturnValueIsSuccess( res, &isSuccess ) == S_OK ) &&
                 ( isSuccess == 1 ) &&
                 ( value != nullptr ) )
            {
                values.push_back( value );
                ::SysFreeString( value );
            }
        }
        values_.push_back( values );
    }
    return true;
}