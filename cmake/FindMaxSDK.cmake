# * Find 3ds Max SDK
# Find the 3ds Max SDK includes and libraries
#
# MaxSDK_DIR         - 3DSMAX SDK root directory 
# MaxSDK_INCLUDE_DIR - where to find baseinterface.h
# MaxSDK_LIBRARIES   - List of libraries when using 3DSMAX.
# MaxSDK_FOUND       - True if MAX SDK found.

if(MaxSDK_INCLUDE_DIR)
  # Already in cache, be silent
  set(MaxSDK_FIND_QUIETLY TRUE)
endif()

set(_pf_x86 "PROGRAMFILES(x86)")

find_path(
  MaxSDK_DIR "include/maxversion.h"
  HINTS "$ENV{MaxSDK_DIR}"
  PATHS "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2023 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2022 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2021 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2020 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2019 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2018 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2017 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2016 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2015 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2014 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2013 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2012 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2011 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2010 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2009 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 2008 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3ds Max 9 SDK/maxsdk"
        "$ENV{PROGRAMFILES}/Autodesk/3dsMax8/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2023 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2022 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2021 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2020 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2019 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2018 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2017 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2016 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2015 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2014 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2013 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2012 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2011 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2010 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2009 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 2008 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3ds Max 9 SDK/maxsdk"
        "$ENV{${_pf_x86}}/Autodesk/3dsMax8/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2023}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2022}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2021}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2020}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2019}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2018}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2017}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2016}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2015}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2014}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2013}/maxsdk"
        "$ENV{ADSK_3DSMAX_SDK_2012}/maxsdk"
        "$ENV{3DSMAX_2011_SDK_PATH}/maxsdk")

find_path(MaxSDK_INCLUDE_DIR max.h HINTS ${MaxSDK_DIR}/include)

find_path(MaxSDK_CS_INCLUDE_DIR bipexp.h HINTS ${MaxSDK_DIR}/include/CS)

find_path(MaxSDK_ASSETMANAGEMENT_INCLUDE_DIR iassetmanager.h
          HINTS ${MaxSDK_DIR}/include/AssetManagement)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(MaxSDK_LIBRARY_DIRS ${MaxSDK_DIR}/x64/lib ${MaxSDK_DIR}/lib/x64/Release)
else()
  set(MaxSDK_LIBRARY_DIRS ${MaxSDK_DIR}/lib)
endif()

macro(find_3ds_library MYLIBRARY MYLIBRARYNAME)
  find_library(
    ${MYLIBRARY}
    NAMES ${MYLIBRARYNAME}
    HINTS ${MaxSDK_LIBRARY_DIRS})
endmacro()

find_3ds_library(MaxSDK_CORE_LIBRARY core)
find_3ds_library(MaxSDK_GEOM_LIBRARY geom)
find_3ds_library(MaxSDK_GFX_LIBRARY gfx)
find_3ds_library(MaxSDK_MESH_LIBRARY mesh)
find_3ds_library(MaxSDK_MAXUTIL_LIBRARY maxutil)
find_3ds_library(MaxSDK_MAXSCRIPT_LIBRARY maxscrpt)
find_3ds_library(MaxSDK_PARAMBLK2_LIBRARY paramblk2)
find_3ds_library(MaxSDK_BMM_LIBRARY bmm)
find_3ds_library(MaxSDK_ASSETMANAGEMENT_LIBRARY assetmanagement)

# Handle the QUIETLY and REQUIRED arguments and set MaxSDK_FOUND to TRUE if all
# listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MaxSDK DEFAULT_MSG MaxSDK_INCLUDE_DIR
                                  MaxSDK_CORE_LIBRARY)

if(MaxSDK_FOUND)
  set(MaxSDK_LIBRARIES
      ${MaxSDK_CORE_LIBRARY}
      ${MaxSDK_GEOM_LIBRARY}
      ${MaxSDK_GFX_LIBRARY}
      ${MaxSDK_MESH_LIBRARY}
      ${MaxSDK_MAXUTIL_LIBRARY}
      ${MaxSDK_MAXSCRIPT_LIBRARY}
      ${MaxSDK_PARAMBLK2_LIBRARY}
      ${MaxSDK_BMM_LIBRARY}
      ${MaxSDK_ASSETMANAGEMENT_LIBRARY})

  # parse maxversion.h to determine SDK version
  if(EXISTS "${MaxSDK_DIR}/include/maxversion.h")
    file(STRINGS "${MaxSDK_DIR}/include/maxversion.h" LINES
         REGEX "#define MAX_PRODUCT_YEAR_NUMBER ([0-9]+)")

    string(REGEX REPLACE ".+MAX_PRODUCT_YEAR_NUMBER ([0-9]+)" "\\1"
                         MaxSDK_VERSION "${LINES}")
    unset(LINES)
  else()
    set(MaxSDK_VERSION "Unknown")
  endif()

  message(STATUS "Found 3dsmax version ${MaxSDK_VERSION} in ${MaxSDK_DIR}")

  # 3ds Max 2013 and later are always Unicode
  if(MaxSDK_VERSION VERSION_GREATER 2012)
    set(MaxSDK_DEFINITIONS -DUNICODE -D_UNICODE)
  else()
    set(MaxSDK_DEFINITIONS)
  endif()
else()
  set(MaxSDK_LIBRARIES)
endif()

mark_as_advanced(MaxSDK_INCLUDE_DIR MaxSDK_LIBRARY)
