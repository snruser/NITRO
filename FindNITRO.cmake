# - Find an NITRO installation or build tree.

# When NITRO is found, the NITROConfig.cmake file is sourced to setup the
# location and configuration of NITRO.  Please read this file, or
# NITROConfig.cmake.in from the NITRO source tree for the full list of
# definitions.  Of particular interest is NITRO_USE_FILE, a CMake source file
# that can be included to set the include directories, library directories,
# and preprocessor macros.  In addition to the variables read from
# NITROConfig.cmake, this find module also defines
#  NITRO_DIR  - The directory containing NITROConfig.cmake.  
#             This is either the root of the build tree, 
#             or the lib/NITRO directory.  
#             This is the only cache entry.
#   
#  NITRO_FOUND - Whether NITRO was found.  If this is true, 
#              NITRO_DIR is okay.
#
#  USE_NITRO_FILE - The full path to the UseNITRO.cmake file.  
#                 This is provided for backward 
#                 compatability.  Use NITRO_USE_FILE
#                 instead.


SET(NITRO_DIR_STRING "directory containing NITROConfig.cmake.  This is either the root of the build tree, or PREFIX/lib/nitro for an installation.")

# Search only if the location is not already known.
IF(NOT NITRO_DIR)
  # Get the system search path as a list.
  IF(UNIX)
    STRING(REGEX MATCHALL "[^:]+" NITRO_DIR_SEARCH1 "$ENV{PATH}")
  ELSE(UNIX)
    STRING(REGEX REPLACE "\\\\" "/" NITRO_DIR_SEARCH1 "$ENV{PATH}")
  ENDIF(UNIX)
  STRING(REGEX REPLACE "/;" ";" NITRO_DIR_SEARCH2 ${NITRO_DIR_SEARCH1})

  # Construct a set of paths relative to the system search path.
  SET(NITRO_DIR_SEARCH "")
  FOREACH(dir ${NITRO_DIR_SEARCH2})
    SET(NITRO_DIR_SEARCH ${NITRO_DIR_SEARCH} "${dir}/../lib/nitro")
  ENDFOREACH(dir)

  #
  # Look for an installation or build tree.
  #
  FIND_PATH(NITRO_DIR NITROConfig.cmake
    # Look for an environment variable NITRO_DIR.
    $ENV{NITRO_DIR}

    # Look in places relative to the system executable search path.
    ${NITRO_DIR_SEARCH}

    # Look in standard UNIX install locations.
    /usr/local/lib/nitro
    /usr/lib/nitro

    # Read from the CMakeSetup registry entries.  It is likely that
    # NITRO will have been recently built.
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild1]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild2]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild3]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild4]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild5]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild6]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild7]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild8]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild9]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild10]

    # Help the user find it if we cannot.
    DOC "The ${NITRO_DIR_STRING}"
  )
ENDIF(NOT NITRO_DIR)

# If NITRO was found, load the configuration file to get the rest of the
# settings.
IF(NITRO_DIR)
  SET(NITRO_FOUND 1)
  INCLUDE(${NITRO_DIR}/NITROConfig.cmake)

  # Set USE_NITRO_FILE for backward-compatability.
  SET(USE_NITRO_FILE ${NITRO_USE_FILE})
ELSE(NITRO_DIR)
  SET(NITRO_FOUND 0)
  IF(NITRO_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Please set NITRO_DIR to the ${NITRO_DIR_STRING}")
  ENDIF(NITRO_FIND_REQUIRED)
ENDIF(NITRO_DIR)


