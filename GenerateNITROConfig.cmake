# Generate the NITROConfig.cmake file in the build tree.  Also configure
# one for installation.  The file tells external projects how to use
# NITRO.

#-----------------------------------------------------------------------------
# Settings specific to the build tree.

# Generate CMake lines that will define the NITRO_SOURCE_DIR in the NITROConfig.cmake.
# We want this to happen only in the NITROConfig.cmake of the build dir, not in the
# installed or relocatable one.
SET(NITRO_CONFIG_CODE "
# The NITRO source tree.
# For backward compatibility issues we still need to define this variable, although
# it is highly probable that it will cause more harm than being useful. 
# Use NITRO_INCLUDE_DIRS instead, since NITRO_SOURCE_DIR may point to non-existent directory
IF(NOT NITRO_LEGACY_REMOVE)
  SET(NITRO_SOURCE_DIR \"${NITRO_SOURCE_DIR}\")
ENDIF(NOT NITRO_LEGACY_REMOVE)"
)

# The "use" file.
SET(NITRO_USE_FILE ${NITRO_BINARY_DIR}/UseNITRO.cmake)

# The build settings file.
SET(NITRO_BUILD_SETTINGS_FILE ${NITRO_BINARY_DIR}/NITROBuildSettings.cmake)

# Library directory.
SET(NITRO_LIBRARY_DIRS_CONFIG ${NITRO_LIBRARY_PATH})

# Determine the include directories needed.
SET(NITRO_INCLUDE_DIRS_CONFIG
  ${NITRO_INCLUDE_DIRS_BUILD_TREE}
  ${NITRO_INCLUDE_DIRS_SYSTEM}
)

#-----------------------------------------------------------------------------
# Configure NITROConfig.cmake for the build tree.
CONFIGURE_FILE(${NITRO_SOURCE_DIR}/NITROConfig.cmake.in
               ${NITRO_BINARY_DIR}/NITROConfig.cmake @ONLY IMMEDIATE)

#-----------------------------------------------------------------------------
# Settings specific to the install tree.

# The library dependencies file.
SET(NITRO_LIBRARY_DEPENDS_FILE "\${NITRO_INSTALL_PREFIX}/${NITRO_INSTALL_PACKAGE_DIR}/NITROLibraryDepends.cmake")

# The "use" file.
SET(NITRO_USE_FILE \${NITRO_INSTALL_PREFIX}/${NITRO_INSTALL_PACKAGE_DIR}/UseNITRO.cmake)

# The build settings file.
SET(NITRO_BUILD_SETTINGS_FILE \${NITRO_INSTALL_PREFIX}/${NITRO_INSTALL_PACKAGE_DIR}/NITROBuildSettings.cmake)

# Include directories.
SET(NITRO_INCLUDE_DIRS_CONFIG \${NITRO_INSTALL_PREFIX}/${NITRO_INSTALL_INCLUDE_DIR})
FOREACH(DIR ${NITRO_INCLUDE_RELATIVE_DIRS})
  LIST(APPEND NITRO_INCLUDE_DIRS_CONFIG \${NITRO_INSTALL_PREFIX}/${NITRO_INSTALL_INCLUDE_DIR}/${DIR})
ENDFOREACH(DIR)
IF(NITRO_INCLUDE_DIRS_SYSTEM)
  LIST(APPEND NITRO_INCLUDE_DIRS_CONFIG ${NITRO_INCLUDE_DIRS_SYSTEM})
ENDIF(NITRO_INCLUDE_DIRS_SYSTEM)

# Link directories.
SET(NITRO_LIBRARY_DIRS_CONFIG "\${NITRO_INSTALL_PREFIX}/${NITRO_INSTALL_LIB_DIR}")

#-----------------------------------------------------------------------------
# Configure NITROConfig.cmake for the install tree.

# Construct the proper number of GET_FILENAME_COMPONENT(... PATH)
# calls to compute the installation prefix.
STRING(REGEX REPLACE "/" ";" NITRO_INSTALL_PACKAGE_DIR_COUNT
  "${NITRO_INSTALL_PACKAGE_DIR}")
SET(NITRO_CONFIG_CODE "
# Compute the installation prefix from this NITROConfig.cmake file location.
GET_FILENAME_COMPONENT(NITRO_INSTALL_PREFIX \"\${CMAKE_CURRENT_LIST_FILE}\" PATH)")
FOREACH(p ${NITRO_INSTALL_PACKAGE_DIR_COUNT})
  SET(NITRO_CONFIG_CODE
    "${NITRO_CONFIG_CODE}\nGET_FILENAME_COMPONENT(NITRO_INSTALL_PREFIX \"\${NITRO_INSTALL_PREFIX}\" PATH)"
    )
ENDFOREACH(p)


CONFIGURE_FILE(${NITRO_SOURCE_DIR}/NITROConfig.cmake.in
               ${NITRO_BINARY_DIR}/Utilities/NITROConfig.cmake @ONLY IMMEDIATE)

